/* TASS - Ethernet
 *
 * WIZnet W5100 and W5500 Functions
 * 
 * Author: Matthew J. Wolf  <matthew.wolf.hpsdr@speciosus.net>
 * Date: 18-NOV-2018
 * 
 * - Version 0.7-n4mtt
 *   = Renamed TASS_w5100.ino to TASS_ethernet.ino
 *   =Added functions:
 *   -= ethernet_display_info()
 *   -= info_ethernet_board()
 *   -= info_ethernet_relay()
 *   
 * - Original author is John Ackermann, N8UR
 *
 * Copyright (c) 2016 John Ackermann
 * Copyright (c) 2018 Matthew J. Wolf
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files  
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the 
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef USE_ETHERNET

void ethernet_setup() {
 //disable SD
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);

  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}

boolean get_ethernet_data() {

  if (getTelnetString()) {
  board = toupper(dataBuffer[1]);
  relay = atoi(&dataBuffer[2]);
  relay_char =(dataBuffer[2]);
  cmd = toupper(dataBuffer[3]);
  execute = 1;

  // first param is board, A - D
  if (!(board >= 'A' && board <= 'D')) {execute = 0;} // board check

  // second is relay, 0 through 8
  if (!(relay >= 0 && relay <= 8)) {execute = 0;} // relay check

  // third is command -- H, S, or U
  if (!((cmd == 'H') || (cmd == 'S') || (cmd == 'U') || (cmd == 'I') )) {execute = 0;} // cmd check
  } //call getTelnetString

  if (execute) {
    if (telnet_verbose >0) {
      server.write("<");
      server.write(board);
      server.write(relay_char);
      server.write(cmd);
      server.write(">");
      if (telnet_verbose == 1) {server.write("\n");} else {server.write(" ");}
    }
    if (telnet_verbose == 2) {
      server.write("Board: ");
      server.write(board);
      server.write(" relay: ");
      server.write(relay_char);
      server.write(" command: ");
      server.write(cmd);
      if ((cmd == 'U') && (relay == 0)) { server.write(" -- Clear All"); }
      server.write("\n");
    }
  }
  return execute;
}

boolean getTelnetString(){
    static byte dataBufferIndex = 0;
    boolean storeString;
    EthernetClient client = server.available();

    if (client && newclient) {
      server.write("\nTAPR TASS Control Software\n");
      server.write(version);
      server.write("\nCopyright 2015 John Ackermann   N8UR\n");
      server.write("Copyright 2018 Matthew J Wolf  N4MTT\n");
      server.write("Licensed under MIT license\n");
      #ifdef SHOW_INFO_ETHERNET
        ethernet_display_info(NUM_TASS_BOARDS_DISPLAY);
      #else
        server.write("\n");
      #endif
      newclient = 0;
    }
    while (client){
       char incomingbyte = client.read();
       if(incomingbyte==startChar){
            dataBufferIndex = 0;  //Initialize our dataBufferIndex variable
            storeString = true;
        }
        if(storeString){
            // Abort if index outside buffer size
            if(dataBufferIndex==DATABUFFERSIZE){
                dataBufferIndex = 0;
                break;
            }
            if(incomingbyte==endChar){
                dataBuffer[dataBufferIndex] = 0; //null terminate the C string
                //Data string is complete.
                storeString = false;
                return true;
            }
    else{
                dataBuffer[dataBufferIndex++] = incomingbyte;
                dataBuffer[dataBufferIndex] = 0; //null terminate the C string
            }
        }
        else{
        }
    }

    //All data read; no valid string
    return false;
}

// Display status of relays
void ethernet_display_info(int board_num) {
  int i = -1;

  server.write("\n--- Relay State ---\n");
  server.write(" * :Hold enabled\n");

  if (board_num > 0) {
      #ifdef A_DOUBLE_POLE
      server.write("Board A:");
      #ifdef SPLIT
      server.write(" (K9 SPLIT)");
      #endif
      server.write(" (Double Pole)\n");

      // Top relay of double pole
      for ( i=0; i < 4; i++ ) {
        server.write(i+49);
        server.write(":");
        if ( digitalRead(A_1 + i) == 1 ) {
          server.write("ON");
          if ( get_bit_mask_state(i, H_mask_A) == 1) {
            server.write("*");
          }
          else {
            server.write(" ");
          }
        }
        else{
          server.write("OFF ");
        }
        server.write(" ");
      }
      server.write("\n");

      // Bottom relay of double pole
      for ( i=0; i < 4; i++ ) {
        server.write((i+4)+49);
        server.write(":");
        if ( digitalRead(A_1 + (i+4)) == 1 ) {
          server.write("ON");
          if ( get_bit_mask_state((i+4), H_mask_A) == 1) {
            server.write("*");
          }
          else {
            server.write(" ");
          }
        }
        else{
          server.write("OFF ");
        }
        server.write(" ");
      }
      server.write("\n");

      #else
      server.write("Board A:");
      #ifdef SPLIT
      server.write(" (K9 SPLIT)");
      #endif
      server.write("\n");   
      for ( i=0; i < 8; i++ ) {
        server.write(i+49);
        server.write(":");
        if ( digitalRead(A_1 + i) == 1 ) {
          server.write("ON");
          if ( get_bit_mask_state(i, H_mask_A) == 1) {
            server.write("*");
          }
          else {
            server.write(" ");
          }
        }
        else{
          server.write("OFF ");
        }
        server.write(" ");
      }
      #endif
      server.write("Board A:");
      #ifdef SPLIT
      server.write(" (K9 SPLIT)");
      #endif
      #ifdef A_B_COMBINE
      server.write(" (A and B Combined)");
      #endif
      server.write("\n");
      for ( i=0; i < 8; i++ ) {
        server.write(i+49);
        server.write(":");
        if ( digitalRead(A_1 + i) == 1 ) {
          server.write("ON");
          if ( get_bit_mask_state(i, H_mask_A) == 1) {
            server.write("*");
          }
          else {
            server.write(" ");
          }
        }
        else{
          server.write("OFF ");
        }
        server.write(" ");
      }
      server.write("\n");
  }


  if (board_num > 1) {
      server.write("Board B:");
      #ifdef SPLIT
      server.write(" (K9 SPLIT)");
      #endif
      #ifdef A_B_COMBINE
      server.write(" (A and B Combined)");
      #endif
      server.write("\n");
      for ( i=0; i < 8; i++ ) {
        server.write(i+49);
        server.write(":");
        if ( digitalRead(B_1 + i) == 1 ) {
          server.write("ON");
          if ( get_bit_mask_state(i, H_mask_B) == 1) {
            server.write("*");
          }
          else {
            server.write(" ");
          }
        }
        else{
          server.write("OFF ");
        }
        server.write(" ");
      }
      server.write("\n");
  }

  if (board_num > 2) {
      server.write("Board C:");
      #ifdef SPLIT
      server.write(" (K9 SPLIT)");
      #endif
      server.write("\n");      
      for ( i=0; i < 8; i++ ) {
        server.write(i+49);
        server.write(":");
        if ( digitalRead(C_1 + i) == 1 ) {
          server.write("ON");
          if ( get_bit_mask_state(i, H_mask_C) == 1) {
            server.write("*");
          }
          else {
            server.write(" ");
          }
        }
        else{
          server.write("OFF ");
        }
        server.write(" ");
      }
      server.write("\n");
  }

   if (board_num > 3) {
      server.write("Board D:");
      #ifdef SPLIT
      server.write(" (K9 SPLIT)");
      #endif
      server.write("\n");   
      for ( i=0; i < 8; i++ ) {
        server.write(i+49);
        server.write(":");
        if ( digitalRead(D_1 + i) == 1 ) {
          server.write("ON");
          if ( get_bit_mask_state(i, H_mask_D) == 1) {
            server.write("*");
          }
          else {
            server.write(" ");
          }
        }
        else{
          server.write("OFF ");
        }
        server.write(" ");
      }
  }

  server.write("\n");
}

void info_ethernet_board(int board,int first_dpin,int h_mask){
  int x = -1;
 
  server.print("i,");
  server.write(board);
  server.print(","); 

  for ( x=0; x < 8; x++ ) {
    if ( digitalRead(first_dpin + x) ) {
          
      if ( get_bit_mask_state(x, h_mask) == 1) {
        server.print("h");
      }
      else {
        server.print("s");
      }
    } 
    else {
      server.print("0");
    }
    if ( x < 7) {
      server.print(",");
    }
  }
  Serial.print("\n");
}

void info_ethernet_relay(int board, int relay,int first_dpin,int h_mask){
 
  server.print("i,");
  server.write(board);
  server.print(","); 
  server.print(relay);
  server.print(",");
  
  if ( digitalRead(first_dpin + (relay-1)) ) { 
    if ( get_bit_mask_state((relay-1), h_mask) == 1) {
      server.print("h");
    }
    else {
      server.print("s");
    }
  }  
  else { 
    server.print("0");
  }
  server.print("\n");   
}

#endif
