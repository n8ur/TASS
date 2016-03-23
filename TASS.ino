/***************************************************
TASS Control Software by John Ackermann N8UR.  Based on Adafruit examples below
****************************************************/

char version[] = "v0.60 -- 24 Jan 2016";

// BOF preprocessor bug prevent - insert me on top of your arduino-code
// From: http://www.a-control.de/arduino-fehler/?lang=en
#if 1
__asm volatile ("nop");
#endif

// uncomment to enable Adafruit 2.8 inch TFT and capacitive touchscreen
//#define USE_TS

// uncomment to endable Adafruit 1.2 inch 8x8 LED matrix
#define USE_LED8X8

// uncomment to enable Wiznet W5100 ethernet shield
// #define USE_W5100

// comment this to set board up as single 8 pole using K9
// #define SPLIT

// uncomment this to display bitmasks on the serial console
#define SHOW_MASKS

// uncomment to combine boards A and B into a single 16 port switch
// This causes boards A and B to act as one for "S"et commands.  Setting
// a relay on either A or B will cause both boards to be cleared with the
// new relay then set.  Relay K9 on both boards will follow the relay selection,
// so J16 on either board may be used as the common output.

#define A_B_COMBINE

// uncomment to set board D to double pole mode
// This will cause setting or holding a relay on board D to
// also set its equivalent on the other bank,  thus pairing 
// 1-5, 2-6, 3-7, 4-8 to create a 4-throw double-pole switch
#define D_DOUBLE_POLE

#include "TASS_defines.h"

#ifdef USE_TS
  #include <Wire.h>
  #include <SPI.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_ILI9341.h>
  #include <Adafruit_FT6206.h>
  Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
  Adafruit_FT6206 ctp = Adafruit_FT6206();
#endif // USE_TS

#ifdef USE_LED8X8
  #include <Wire.h>
  #include <SPI.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_LEDBackpack.h>
  Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
  #define HB_BLINK_MS 1000;
 #endif // USE_LED8X8 

#ifdef USE_W5100
  #include <SPI.h>
  #include <EthernetUdp.h>
  #include <Dhcp.h>
  #include <Dns.h>
  #include <util.h>
  #include <Ethernet.h>
  #include <EthernetServer.h>
  #include <EthernetClient.h>

  // variable
  EthernetServer server = EthernetServer(23);
  EthernetClient client = 0;
  
  // ******************************************************
  // If using ethernet, set network stuff here:
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(10,73,3,177);
  IPAddress gateway(10,73,1,1);
  IPAddress subnet(255,255,0,0);
  
  // what to echo to the telnet port, if anything
  // 0 = no echo, 1 = echo raw command, 2 = interpreted output
  int telnet_verbose = 2; 
  //*******************************************************
  
#endif  // USE_W5100

char board = ' ';
int relay = 0;
char cmd = ' ';
byte relay_num = 0;
char relay_char = ' '; 
boolean newclient = 1;
boolean execute = 0;
boolean BadCmd = 0;
boolean K9 = 0;

// these keep the relay settings for each board across commands
byte S_mask_A = 0;
byte S_mask_B = 0;
byte S_mask_C = 0;
byte S_mask_D = 0;

// these keep the hold settings for each board across commands
byte H_mask_A = 0;
byte H_mask_B = 0;
byte H_mask_C = 0;
byte H_mask_D = 0;

// these hold the current status (set + hold) for each board
byte cmd_mask_A = 0;
byte cmd_mask_B = 0;
byte cmd_mask_C = 0;
byte cmd_mask_D = 0;

// setup for serial input
const char startChar = '<';
const char endChar = '>';
char dataBuffer[DATABUFFERSIZE+1]; //Add 1 for NULL terminator

void setup(void) {

  usb_setup();
  setup_board();

  #ifdef USE_TS
    tft_setup();
  #endif

  #ifdef USE_LED8X8
    led8x8_setup();
  #endif

  #ifdef USE_W5100
    w5100_setup();
  #endif

} // setup

void loop() {
  board = ' ';
  relay = 0;
  cmd = ' ';
  BadCmd = 0;
  
  #ifdef USE_LED8X8  
     heartbeat();
  #endif

  if (!execute) {
    #ifdef USE_TS 
      get_ts_data();
    #endif
    #ifdef USE_W5100
      get_w5100_data();
    #endif
    get_usb_data();
 }
 if (execute) {
    board = toupper(dataBuffer[1]);
    relay = atoi(&dataBuffer[2]);
    cmd = toupper(dataBuffer[3]); 
    
     // set relay K9 to either upper or lower bus depending on relay selected
     // K9 = 0 connects to the bus for relays 1-4
     if (relay < 5) {
       K9 = 0;
    } else {
       K9 = 1;
    } // set K9
  
    byte cmd_mask = 0;
      
  // start of command == "S"
    if (cmd == 'S') {    
    
      // first, clear mask
#ifndef A_B_COMBINE  
     switch (board) {
       case 'A': S_mask_A = clear_S_mask(relay,S_mask_A);break;
       case 'B': S_mask_B = clear_S_mask(relay,S_mask_B);break;
       case 'C': S_mask_C = clear_S_mask(relay,S_mask_C);break;
       case 'D': S_mask_D = clear_S_mask(relay,S_mask_D);break;
       } // switch
#else // if A_B_COMBINE, clear both sides of A and B
       if ((board == 'A') || (board == 'B')) {
         S_mask_A = clear_mask(S_mask_A);
         S_mask_B = clear_mask(S_mask_B);
       }
       switch (board) {
         case 'C': S_mask_C = clear_S_mask(relay,S_mask_C);break;
         case 'D': S_mask_D = clear_S_mask(relay,S_mask_D);break;
         } // switch
#endif
        
   // then set the relay mask    
#ifndef A_B_COMBINE
    switch (board) {
       case 'A': S_mask_A = set_mask(relay,S_mask_A); break;
       case 'B': S_mask_B = set_mask(relay,S_mask_B); break;
       case 'C': S_mask_C = set_mask(relay,S_mask_C); break;
       case 'D': S_mask_D = set_mask(relay,S_mask_D); break;
    } // switch
#else // if A_B_COMBINE
     switch (board) {
       case 'A': S_mask_A = set_mask(relay,S_mask_A); set_mask(0,S_mask_B);break;
       case 'B': S_mask_B = set_mask(relay,S_mask_B); set_mask(0,S_mask_A);break;
       case 'C': S_mask_C = set_mask(relay,S_mask_C); break;
       case 'D': S_mask_D = set_mask(relay,S_mask_D); break;
    } // switch      
#endif

  // if using board D as double pole, take the final mask and pair relays
  // to pair 1&5, 2&6, 3&7, 4&8.  Works both ways, so you can select
  // either the high or low relay to get the pair
#ifdef D_DOUBLE_POLE
  if ((board == 'D') && (relay != 0)) {
    if (relay < 5) {
      S_mask_D = set_mask(relay + 4,S_mask_D);
    } else{
      S_mask_D = set_mask(relay - 4,S_mask_D);
    }
  }
 #endif // D_DOUBLE_POLE    
  }
// end of command == "S"

// start of command == "U" 
    if (cmd == 'U') {
      // clear H mask
      switch (board) {
        case 'A': H_mask_A = clear_mask(H_mask_A); break;
        case 'B': H_mask_B = clear_mask(H_mask_B); break;
        case 'C': H_mask_C = clear_mask(H_mask_C); break;
        case 'D': H_mask_D = clear_mask(H_mask_D); break;
      } // switch
      
      // special case - relay 0 means clear both set and hold masks
      // don't use "clear_set_mask" because we want to wipe both halves
      if (relay == 0) { 
      // clear S mask
        switch(board) {
          case 'A': S_mask_A = clear_mask(S_mask_A);break;
          case 'B': S_mask_B = clear_mask(S_mask_B);break;
          case 'C': S_mask_C = clear_mask(S_mask_C);break;
          case 'D': S_mask_D = clear_mask(S_mask_D);break;
        } // switch
      } // if relay == 0
   } // if
  // end of command == "U"

  // start of command == "H"
    if (cmd == 'H') {
      // set appropriate hold mask
      switch (board) {
        case 'A': H_mask_A = set_mask(relay,H_mask_A); break;
        case 'B': H_mask_B = set_mask(relay,H_mask_B); break;
        case 'C': H_mask_C = set_mask(relay,H_mask_C); break;
        case 'D': H_mask_D = set_mask(relay,H_mask_D);break;
        } // switch
         
    // if using board D as double pole, take the final mask and pair relays
    // to pair 1&5, 2&6, 3&7, 4&8.  Works both ways, so you can select
    // either the high or low relay to get the pair
#ifdef D_DOUBLE_POLE
    if ((board == 'D') && (relay != 0)) {
      if (relay < 5) {
        H_mask_D = set_mask(relay + 4,H_mask_D);
      } else{
        H_mask_D = set_mask(relay - 4,H_mask_D);
      }
    }
#endif // D_DOUBLE_POLE    
   } // if
// end of command == "H"
      
  // create the mask that will be written to board by combining hold and set masks
  cmd_mask_A = H_mask_A | S_mask_A;
  cmd_mask_B = H_mask_B | S_mask_B;
  cmd_mask_C = H_mask_C | S_mask_C;
  cmd_mask_D = H_mask_D | S_mask_D;
  
  // write to appropriate board
  // if A_B_COMBINE, write to both boards
#ifndef A_B_COMBINE
     switch (board) {
       case 'A': write_board(A_1,cmd_mask_A,K9);break;
       case 'B': write_board(B_1,cmd_mask_B,K9);break;
       case 'C': write_board(C_1,cmd_mask_C,K9);break;
       case 'D': write_board(D_1,cmd_mask_D,K9);break;
    } // switch
#else
   if ((board == 'A') || (board == 'B')) { 
     write_board(A_1,cmd_mask_A,K9);
     write_board(B_1,cmd_mask_B,K9);
   }
   switch (board) {
      case 'C': write_board(C_1,cmd_mask_C,K9);break;
      case 'D': write_board(D_1,cmd_mask_D,K9);break;
   } // switch
#endif

  // work is done, now update status for USB and other installed IO methods  
  usb_print_status();
  
  #ifdef USE_TS
    draw_status();
  #endif
  
  #ifdef USE_LED8X8
    draw_LED_status();
  #endif
  
  execute = 0;
  } // execute 

} // of loop

