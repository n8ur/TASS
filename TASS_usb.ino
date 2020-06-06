/* TASS - USB
 *  
 * USB Serial Functions
 * 
 * Author: Matthew J. Wolf  <matthew.wolf.hpsdr@speciosus.net>
 * Date: 18-NOV-2018
 * 
 * - Version 0.7-n4mtt 
 *   = Added functions 
 *   -= usb_display_info()
 *   -= info_usb_board()
 *   -= info_usb_relay()
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

void usb_setup() {
// initialize serial:
  Serial.begin(115200);
// splash
  Serial.println("TAPR TASS Control Software");
  Serial.println(version);
  Serial.println("Copyright 2015 John Ackermann   N8UR");
  Serial.println("Copyright 2018 Matthew J Wolf  N4MTT");
  Serial.println("Licensed under MIT license");
  #ifdef SHOW_INFO_USB 
    usb_display_info(NUM_TASS_BOARDS_DISPLAY);
  #else
     Serial.println("");
  #endif  
} // usb_setup()


boolean get_usb_data() {
  if ( getSerialString() ) {
    board = toupper(dataBuffer[1]);
    relay = atoi(&dataBuffer[2]);
    cmd = toupper(dataBuffer[3]);
    execute = 1;
    // first param is board, A - D
    if (!(board >= 'A' && board <= 'D')) {execute = 0;} // board check

    // second is relay, 0 through 8
    if (!(relay >= 0 && relay <= 8)) {execute = 0;} // relay check

    // third is command -- H, S, or U
    if (!((cmd == 'H') || (cmd == 'S') || (cmd == 'U') || (cmd == 'I'))) {execute = 0;} // cmd check
  
  } //call getSerialString
  return execute;
} //get_usb_data

boolean getSerialString(){
    static byte dataBufferIndex = 0;
    boolean storeString;
    while(Serial.available()>0){
        char incomingbyte = Serial.read();
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

void usb_print_status(){  
  Serial.println("");
  Serial.print ("Board: ");
  Serial.print (board);
  Serial.print (" relay: ");
  Serial.print (relay);
  Serial.print (" command: ");
  Serial.print (cmd);

  if ((cmd == 'U') && (relay == 0)) { Serial.print(" -- Clear All"); }
  Serial.println();

  #ifdef SHOW_INFO_USB 
    usb_display_info(NUM_TASS_BOARDS_DISPLAY);
  #endif  

  #ifdef SHOW_MASKS
    usb_display_masks();
    Serial.println();
  #endif
} // usb_print_status()


// Display status of relays
void usb_display_info(int board_num) {
  int i = -1;

  Serial.println();
  Serial.println("--- Relay State ---");
  Serial.println(" * :Hold enabled");

  if (board_num > 0) {
      Serial.print("Board A:");
      #ifdef SPLIT
      Serial.print(" (K9 SPLIT)");
      #endif      
      #ifdef A_B_COMBINE
      Serial.print(" (A and B Combined)");
      #endif
      Serial.println(); 
      for ( i=0; i < 8; i++ ) {
        Serial.print((i+1),DEC);
        Serial.print(":");
        if ( digitalRead(A_1 + i) ) {
          Serial.print("ON");
          
          if ( get_bit_mask_state(i, H_mask_A) == 1) {
            Serial.print("*");
          }
          else {
            Serial.print(" ");
          }
        } 
        else {
          Serial.print("OFF");
        }
        Serial.print(" ");
      }
      Serial.println();
  }

  if (board_num > 1) {
      Serial.print("Board B:");
      #ifdef SPLIT
      Serial.print(" (K9 SPLIT)");
      #endif       
      #ifdef A_B_COMBINE
      Serial.print(" (A and B Combined)");
      #endif
      Serial.println();     
      for ( i=0; i < 8; i++ ) {
        Serial.print((i+1),DEC);
        Serial.print(":");
        if ( digitalRead(B_1 + i) ) {
          Serial.print("ON");
          
          if ( get_bit_mask_state(i, H_mask_B) == 1) {
            Serial.print("*");
          }
          else {
            Serial.print(" ");
          }
        } 
        else {
          Serial.print("OFF");
        }
        Serial.print(" ");
      }
      Serial.println();
  }     

  if (board_num > 2) {
      Serial.print("Board C:");
      #ifdef SPLIT
      Serial.print(" (K9 SPLIT)");
      #endif 
      Serial.println();   
      for ( i=0; i < 8; i++ ) {
        Serial.print((i+1),DEC);
        Serial.print(":");
        if ( digitalRead(C_1 + i) ) {
          Serial.print("ON");
          
          if ( get_bit_mask_state(i, H_mask_C) == 1) {
            Serial.print("*");
          }
          else {
            Serial.print(" ");
          }
        } 
        else {
          Serial.print("OFF");
        }
        Serial.print(" ");
      }
      Serial.println();
  }  

  if (board_num > 3) {
      #ifdef D_DOUBLE_POLE
      Serial.print("Board D:");
      #ifdef SPLIT
      Serial.print(" (K9 SPLIT)");
      #endif       
      Serial.println(" (Double Pole)");
      // Top relay of double pole
      for ( i=0; i < 4; i++ ) {
        Serial.print((i+1),DEC);
        Serial.print(":");
        if ( digitalRead(D_1 + i) ) {
          Serial.print("ON");
          
          if ( get_bit_mask_state(i, H_mask_D) == 1) {
            Serial.print("*");
          }
          else {
            Serial.print(" ");
          }
        } 
        else {
          Serial.print("OFF");
        }
        Serial.print(" ");
      }
      Serial.println();
      

      // Bottom relay of double pole
      for ( i=0; i < 4; i++ ) {
        Serial.print((i+5),DEC);
        Serial.print(":");
        if ( digitalRead(D_1 + (i+4)) ) {
          Serial.print("ON");
          
          if ( get_bit_mask_state((i+4), H_mask_D) == 1) {
            Serial.print("*");
          }
          else {
            Serial.print(" ");
          }
        } 
        else {
          Serial.print("OFF");
        }
        Serial.print(" ");
      }
      Serial.println();

      #else
      Serial.print("Board D:");
      #ifdef SPLIT
      Serial.print(" (K9 SPLIT)");
      #endif
      Serial.println();    
      for ( i=0; i < 8; i++ ) {
        Serial.print((i+1),DEC);
        Serial.print(":");
        if ( digitalRead(D_1 + i) ) {
          Serial.print("ON");
          
          if ( get_bit_mask_state(i, H_mask_D) == 1) {
            Serial.print("*");
          }
          else {
            Serial.print(" ");
          }
        } 
        else {
          Serial.print("OFF");
        }
        Serial.print(" ");
      }
      Serial.println();
      #endif
  }  
  
  
}

void usb_display_masks() {
   Serial.println();
   Serial.print("S Masks:     ");
   usb_printBits(S_mask_A); 
   Serial.print(" ");
   usb_printBits(S_mask_B); 
   Serial.print(" ");
   usb_printBits(S_mask_C); 
   Serial.print(" ");
   usb_printBits(S_mask_D); 
   Serial.println();
   Serial.print("H Masks:     ");
   usb_printBits(H_mask_A); 
   Serial.print(" ");
   usb_printBits(H_mask_B); 
   Serial.print(" ");
   usb_printBits(H_mask_C); 
   Serial.print(" ");
   usb_printBits(H_mask_D); 
   Serial.println();
   Serial.print("Write Masks: ");
   usb_printBits(cmd_mask_A); 
   Serial.print(" ");
   usb_printBits(cmd_mask_B); 
   Serial.print(" ");
   usb_printBits(cmd_mask_C); 
   Serial.print(" ");
   usb_printBits(cmd_mask_D);
    Serial.println();
} // display_masks()
   
void usb_printBits(byte myByte){
 for (byte mask = 0x80; mask; mask >>= 1){
   if (mask  & myByte)
       Serial.print('1');
   else
       Serial.print('0');
   }
} // usb_printBits()


void info_usb_board(int board,int first_dpin,int h_mask){
  int x = -1;
 
  Serial.print("i,");
  Serial.write(board);
  Serial.print(","); 

  for ( x=0; x < 8; x++ ) {
    if ( digitalRead(first_dpin + x) ) {
          
      if ( get_bit_mask_state(x, h_mask) == 1) {
        Serial.print("h");
      }
      else {
        Serial.print("s");
      }
    } 
    else {
      Serial.print("0");
    }
    if ( x < 7) {
      Serial.print(",");
    }
  }
  Serial.print("\n");
}

void info_usb_relay(int board, int relay,int first_dpin,int h_mask){
 
  Serial.print("i,");
  Serial.write(board);
  Serial.print(","); 
  Serial.print(relay);
  Serial.print(",");
  
  if ( digitalRead(first_dpin + (relay-1)) ) { 
    if ( get_bit_mask_state((relay-1), h_mask) == 1) {
      Serial.print("h");
    }
    else {
      Serial.print("s");
    }
  }  
  else { 
    Serial.print("0");
  }
  Serial.print("\n");   
}
