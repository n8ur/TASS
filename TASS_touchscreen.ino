/* TASS - Touchscreen
 *  
 * Functions for using Adafruit ILI9341 Captouch Shield (Product ID 1947)  
 * 
 * Author: Matthew J. Wolf  <matthew.wolf.hpsdr@speciosus.net>
 * Date: 18-NOV-2018
 * 
 * - Version 0.7-n4mtt
 *   = Many changes
 *   = Remove board 5
 *   = Commented out command 4
 *   = Added to use of font FreeSans 9pt
 *   = Added two colors: Blue, Orange 
 *   = Replaced individual draw_relay#() functions with 
 *     one draw_relay() function.
 *   = Added functions 
 *   -= draw_relay()
 *   -= draw_relays_status()
 *   -= draw_board_status()
 *   -= draw_relay_labels() 
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

#ifdef USE_TS

/*  TASS_touchscreen -- functions for touchscreen (duh)

 BASED ON:
  
  This is our touchscreen painting example for the Adafruit ILI9341
  captouch shield
  ----> http://www.adafruit.com/products/1947

  Check out the links above for our tutorials and wiring diagrams

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution.
*/

boolean get_ts_data() {
  int i = -1;
  int board_number = -1;

    if (board == 'A') {
      board_number = 1;
    } else if (board == 'B') {
      board_number = 2;
    } else if (board == 'C') {
      board_number = 3;
    } else if (board == 'D') {
      board_number = 4;
    }

  // Wait for a touch
  execute = 0;
  if (! ctp.touched()) {
      return execute;
  }
  
  // Retrieve a point  
  TS_Point p = ctp.getPoint();
 
  // flip it around to match the screen.
 p.y = map(p.y, 0, 320, 320, 0);
 
 // we're using board 90 degrees from default, I guess
 int x_pos = p.y;
 int y_pos = p.x;

  // set board -- all choices are in left-most box space
  if (x_pos <= BOXSIZE) {  
    draw_boards();
    if ( (y_pos < BOXSIZE) 
          && (NUM_TASS_BOARDS_DISPLAY > 0) ) {
      draw_board1(FILL, BLUE, WHITE); 
      board = 'A';
      draw_board_status(1);
      draw_relays_status(1);
      
    } else if ( (y_pos >= BOXSIZE && y_pos < BOXSIZE*2) 
                && (NUM_TASS_BOARDS_DISPLAY > 1) ) { 
      draw_board2(FILL, BLUE, WHITE);
      board = 'B';
      draw_board_status(2);
      draw_relays_status(2);      
           
    } else if ( (y_pos >= BOXSIZE*2 && y_pos < BOXSIZE*3) 
                && (NUM_TASS_BOARDS_DISPLAY > 2) ) {
      draw_board3(FILL, BLUE, WHITE);
      board = 'C';
      draw_board_status(3);
      draw_relays_status(3);      
            
    } else if ( (y_pos >= BOXSIZE*3 && y_pos < BOXSIZE*4)
                && (NUM_TASS_BOARDS_DISPLAY > 3) ) { 
      draw_board4(FILL, BLUE, WHITE); 
      board = 'D';
      draw_board_status(4);
      draw_relays_status(4);      
    }
    
  } // set board
  
  // set relays -- choices are in the middle
  if (x_pos >= RELAY_ROW_LEFT && x_pos <= RELAY_ROW_LEFT + BOXSIZE*4
        && y_pos >= RELAY_ROW_1_TOP && y_pos <= RELAY_ROW_2_TOP + BOXSIZE) {

    draw_relays();
      
    // set relay row 1
    if (y_pos >=RELAY_ROW_1_TOP && y_pos <= RELAY_ROW_1_TOP + BOXSIZE) {
  
      if (x_pos <= RELAY_ROW_LEFT + BOXSIZE) {
      draw_board_relay(1, board_number, FILL, BLUE);  
      relay = 1;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*2) { 
      draw_board_relay(2, board_number, FILL, BLUE);
      relay = 2;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*3) {
      draw_board_relay(3, board_number, FILL, BLUE);
      relay = 3;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*4) { 
      draw_board_relay(4, board_number, FILL, BLUE);
      relay = 4;
    } 
  } 
  
  // set relay row 2
  if (x_pos >= RELAY_ROW_LEFT && x_pos <= RELAY_ROW_LEFT + BOXSIZE*4
        && y_pos >= RELAY_ROW_2_TOP && y_pos <= RELAY_ROW_2_TOP + BOXSIZE) {
    if (x_pos <= RELAY_ROW_LEFT + BOXSIZE) {
      draw_board_relay(5, board_number, FILL, BLUE);
      relay = 5;
     } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*2) {
      draw_board_relay(6, board_number, FILL, BLUE); 
      relay = 6;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*3) {
      draw_board_relay(7, board_number, FILL, BLUE);
      relay = 7;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*4) { 
      draw_board_relay(8, board_number, FILL, BLUE);
      relay = 8;
    } 
  }
 } // set relays 
  
  // set command -- all choices are in right-most box space
  if (x_pos >=CMD_BOXLEFTEDGE) {  
    draw_cmds();
    if (y_pos < BOXSIZE) {
      draw_cmd1(FILL, BLUE, WHITE); 
      cmd = 'S';
    } else if (y_pos >= BOXSIZE && y_pos < BOXSIZE*2) { 
      draw_cmd2(FILL, BLUE, WHITE);
      cmd = 'H';
    } else if (y_pos >= BOXSIZE*2 && y_pos < BOXSIZE*3) {
      draw_cmd3(FILL, BLUE, WHITE);
      cmd = 'U';
    } 
//    else if (y_pos >= BOXSIZE*3 && y_pos < BOXSIZE*4) { 
//      draw_cmd4(FILL, BLUE, WHITE); 
//      cmd = ' ';
//      Serial.println("Command: (not implemented)");
//    }
  }  // set command
 
  if (x_pos >= CMD_BOXLEFTEDGE && y_pos >= BOXSIZE*4) { 
    draw_boards();
    
      draw_relays();

    
    draw_cmds();  
    draw_cmd5(FILL, GREEN, WHITE);
    draw_board_status(0);
      execute = 1;
  } else {
      draw_cmd5(FILL, BLACK, BLACK);
      draw_cmd5(NOFILL, GREEN, GREEN);
      execute = 0;
  }

  draw_status();
  
  if (execute) {
    dataBuffer[0] = '<';
    dataBuffer[1] = board;
    dataBuffer[2] = relay+48; // convert int to ASCII number
    dataBuffer[3] = cmd;
    dataBuffer[4] = '>';
    dataBuffer[5] = 0; //null terminate the C string
  }
  return execute;
    
}  // of get_ts_data

void draw_board1 (boolean fill, int box_color, int text_color) {
  tft.setFont();
  if (fill) {
    tft.fillRect(BOARD_BOXLEFTEDGE, 0, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 12, char('A'), text_color, box_color, 4);
  } else {
    tft.drawRect(BOARD_BOXLEFTEDGE, 0, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 12, char('A'), text_color, box_color, 4);
  }
}

void draw_board2 (boolean fill, int box_color, int text_color) {
  tft.setFont();
  if (fill) {
    tft.fillRect(BOARD_BOXLEFTEDGE, BOXSIZE, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 60, char('B'), text_color, box_color, 4);
  } else {
    tft.drawRect(BOARD_BOXLEFTEDGE, BOXSIZE, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 60, char('B'), text_color, box_color, 4);
  }
}
 
void draw_board3 (boolean fill, int box_color, int text_color) {
  tft.setFont();
  if (fill) {
    tft.fillRect(BOARD_BOXLEFTEDGE, BOXSIZE*2, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 108, char('C'), text_color, box_color, 4);
  } else {
    tft.drawRect(BOARD_BOXLEFTEDGE, BOXSIZE*2, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 108, char('C'), text_color, box_color, 4);
  }
}
 
 void draw_board4 (boolean fill, int box_color, int text_color) {
  tft.setFont();
  if (fill) {
    tft.fillRect(BOARD_BOXLEFTEDGE, BOXSIZE*3, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 156, char('D'), text_color, box_color, 4);
  } else {
    tft.drawRect(BOARD_BOXLEFTEDGE, BOXSIZE*3, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 156, char('D'), text_color, box_color, 4);
  }
}

void draw_cmd1 (boolean fill, int box_color, int text_color) {
  tft.setFont();
  if (fill) {
    tft.fillRect(CMD_BOXLEFTEDGE, 0, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 12, char('S'), text_color, box_color, 4);
  } else {
    tft.drawRect(CMD_BOXLEFTEDGE, 0, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 12, char('S'), text_color, box_color, 4);
  }
}

 void draw_cmd2 (boolean fill, int box_color, int text_color) {
  tft.setFont();
  if (fill) {
    tft.fillRect(CMD_BOXLEFTEDGE, BOXSIZE, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 60, char('H'), text_color, box_color, 4);
  } else {
    tft.drawRect(CMD_BOXLEFTEDGE, BOXSIZE, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 60, char('H'), text_color, box_color, 4);
  }
}
 
 void draw_cmd3 (boolean fill, int box_color, int text_color) {
  tft.setFont();
  if (fill) {
    tft.fillRect(CMD_BOXLEFTEDGE, BOXSIZE*2, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 108, char('U'), text_color, box_color, 4);
  } else {
    tft.drawRect(CMD_BOXLEFTEDGE, BOXSIZE*2, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 108, char('U'), text_color, box_color, 4);
  }
}
  
//// cmd_4 not implemented yet
//void draw_cmd4 (boolean fill, int box_color, int text_color) {
//  tft.setFont();
//  if (fill) {
//    tft.fillRect(CMD_BOXLEFTEDGE, BOXSIZE*3, BOXSIZE, BOXSIZE, box_color);
//    tft.drawChar(CMD_BOXLEFTEDGE+12, 156, char(' '), text_color, box_color, 4);
//  } else {
//    tft.drawRect(CMD_BOXLEFTEDGE, BOXSIZE*3, BOXSIZE, BOXSIZE, box_color);
//    tft.drawChar(CMD_BOXLEFTEDGE+12, 156, char(' '), text_color, box_color, 4);
//  }
//}
 
void draw_cmd5 (boolean fill, int box_color, int text_color) {
  tft.setFont();
  if (fill) {
    tft.fillRect(CMD_BOXLEFTEDGE, BOXSIZE*4, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 204, char('G'), text_color, box_color, 4);
  } else {
    tft.drawRect(CMD_BOXLEFTEDGE, BOXSIZE*4, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 204, char('G'), text_color, box_color, 4);
  }
}

void draw_relay (int relay, boolean fill, int box_color, int text_color, int text_bg) {
  uint16_t x = 0;
  uint16_t y = 0;
  int box = 0;

  switch(relay) {
    case 1:
       x = 12;
       y = RELAY_ROW_1_TOP;
       box = 0;
       break;
    case 2:
       x = 60;
       y = RELAY_ROW_1_TOP;
       box = 1;
       break;
    case 3:
       x = 108;
       y = RELAY_ROW_1_TOP;
       box = 2;
       break;       
    case 4:
       x = 156;
       y= RELAY_ROW_1_TOP;
       box = 3;
       break;
    case 5:
       x = 12;
       y = RELAY_ROW_2_TOP;
       box = 0;
       break;
    case 6:
       x = 60;
       y = RELAY_ROW_2_TOP;
       box = 1;
       break;
    case 7:
       x = 108;
       y = RELAY_ROW_2_TOP;
       box = 2;
       break;       
    case 8:
       x = 156;
       y= RELAY_ROW_2_TOP;
       box = 3;
       break;       
  }

  tft.setFont();

  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT + (BOXSIZE * box), y, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT + x, y + 12, char(relay+48), text_color, text_bg, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT + (BOXSIZE * box), y, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT + x, y + 12, char(relay+48), text_color, text_bg, 4);
  }
               
}

void draw_board_relay(int relay, int board, boolean fill, int box_color){
  uint16_t x = 0;
  uint16_t y = 0;
  int box = 0;
  int text_color = 0;
  int text_bg = box_color;
  int first_dpin = 0;
  int hold_mask = 0;

  switch(relay) {
    case 1:
       x = 12;
       y = RELAY_ROW_1_TOP;
       box = 0;
       break;
    case 2:
       x = 60;
       y = RELAY_ROW_1_TOP;
       box = 1;
       break;
    case 3:
       x = 108;
       y = RELAY_ROW_1_TOP;
       box = 2;
       break;       
    case 4:
       x = 156;
       y= RELAY_ROW_1_TOP;
       box = 3;
       break;
    case 5:
       x = 12;
       y = RELAY_ROW_2_TOP;
       box = 0;
       break;
    case 6:
       x = 60;
       y = RELAY_ROW_2_TOP;
       box = 1;
       break;
    case 7:
       x = 108;
       y = RELAY_ROW_2_TOP;
       box = 2;
       break;       
    case 8:
       x = 156;
       y= RELAY_ROW_2_TOP;
       box = 3;
       break;       
  }
  
  switch(board){
    case 1:
           first_dpin = A_1;
           hold_mask =  H_mask_A;
           break;
    case 2:
           first_dpin = B_1;
           hold_mask =  H_mask_B;
           break;
    case 3:
           first_dpin = C_1;
           hold_mask =  H_mask_C;
           break;
    case 4:
           first_dpin = D_1;
           hold_mask =  H_mask_D;
           break;
  }


  draw_relays_status(board);

  if ( digitalRead(first_dpin + ( relay - 1)) ) {
    if (get_bit_mask_state(relay -1, hold_mask) == 1) {
       text_color = ORANGE;
    }
    else {
      text_color = RED;         
    }
    
  }
  else {
    text_color = WHITE;
  }

  tft.setFont();

  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT + (BOXSIZE * box), y, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT + x, y + 12, char(relay+48), text_color, text_bg, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT + (BOXSIZE * box), y, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT + x, y + 12, char(relay+48), text_color, text_bg, 4);
  }
  
}

void draw_boards() {
// to clear previous fill, we do twice, -- once with fill with black, then nofill with colors

  if (NUM_TASS_BOARDS_DISPLAY > 0) {
    draw_board1(FILL, BLACK, BLACK);
    draw_board1(NOFILL, WHITE, WHITE);
  }
  
  if (NUM_TASS_BOARDS_DISPLAY > 1) {
    draw_board2(FILL, BLACK, BLACK);
    draw_board2(NOFILL, WHITE, WHITE);
  }

  if (NUM_TASS_BOARDS_DISPLAY > 2) {
    draw_board3(FILL, BLACK, BLACK);
    draw_board3(NOFILL, WHITE, WHITE);
  }

  if (NUM_TASS_BOARDS_DISPLAY > 3) {
    draw_board4(FILL, BLACK, BLACK);
    draw_board4(NOFILL, WHITE, WHITE);
  }
  
}

void draw_cmds() {
  draw_cmd1(FILL, BLACK, BLACK);
  draw_cmd2(FILL, BLACK, BLACK);
  draw_cmd3(FILL, BLACK, BLACK);
  //draw_cmd4(FILL, BLACK, BLACK);
  draw_cmd5(FILL, BLACK, BLACK);
  
  draw_cmd1(NOFILL, WHITE, WHITE);
  draw_cmd2(NOFILL, WHITE, WHITE); 
  draw_cmd3(NOFILL, WHITE, WHITE);
  //draw_cmd4(NOFILL, WHITE, WHITE);
  draw_cmd5(NOFILL, GREEN, GREEN); // cmd5 is execute, so we give him a different color
}

void draw_relays() {

  draw_relay(1, FILL, BLACK, BLACK, BLACK);
  draw_relay(2, FILL, BLACK, BLACK, BLACK);
  draw_relay(3, FILL, BLACK, BLACK, BLACK);
  draw_relay(4, FILL, BLACK, BLACK, BLACK);
  draw_relay(5, FILL, BLACK, BLACK, BLACK);
  draw_relay(6, FILL, BLACK, BLACK, BLACK);
  draw_relay(7, FILL, BLACK, BLACK, BLACK);
  draw_relay(8, FILL, BLACK, BLACK, BLACK);

  draw_relay(1, NOFILL, WHITE, WHITE, WHITE);
  draw_relay(2, NOFILL, WHITE, WHITE, WHITE);
  draw_relay(3, NOFILL, WHITE, WHITE, WHITE);
  draw_relay(4, NOFILL, WHITE, WHITE, WHITE);
  draw_relay(5, NOFILL, WHITE, WHITE, WHITE);
  draw_relay(6, NOFILL, WHITE, WHITE, WHITE);
  draw_relay(7, NOFILL, WHITE, WHITE, WHITE);
  draw_relay(8, NOFILL, WHITE, WHITE, WHITE);
 }

 
void draw_relays_status(int board) {
  int first_dpin = -1;
  int hold_mask = -1;
  int i = -1;

  switch(board){
    case 1:
           first_dpin = A_1;
           hold_mask =  H_mask_A;
           break;
    case 2:
           first_dpin = B_1;
           hold_mask =  H_mask_B;
           break;
    case 3:
           first_dpin = C_1;
           hold_mask =  H_mask_C;
           break;
    case 4:
           first_dpin = D_1;
           hold_mask =  H_mask_D;
           break;
  }

  for ( i=0; i < 8; i++ ) {
    if ( digitalRead(first_dpin + i) ) {
       if ( get_bit_mask_state(i, hold_mask) == 1 ) { 
          draw_relay(i+1,NOFILL, WHITE, ORANGE, BLACK);
       }  
       else {  
         draw_relay(i+1,NOFILL, WHITE, RED, BLACK);
       }
    }
    else {
      draw_relay(i+1,NOFILL, WHITE, WHITE, BLACK);
    }
  }  
   
}

  
 void draw_status() {
   int fg = 0;
   int bg = BLACK;

   if (!execute) {
      tft.setTextColor(WHITE, BLACK);
      fg = WHITE;
    } else{
      tft.setTextColor(GREEN, BLACK);
      fg = GREEN;
    }

    tft.setFont(&FreeSans9pt7b); 
    tft.setTextSize(1);
        
    tft.setCursor(102, 185);
    tft.print("Board = ");
    tft.fillRect(207,173,12,14,BLACK);
    tft.drawChar(207,185,char(board),fg,bg,1);
    
    tft.setCursor(102, 205);
    tft.print("Relay = ");
    tft.fillRect(207,193,12,14,BLACK);
    tft.drawChar(207,205,relay+48,fg,bg,1);

    tft.setCursor(102, 225);
    tft.print("Command = ");
    tft.fillRect(207,213,12,14,BLACK);
    tft.drawChar(207,225,char(cmd),fg,bg,1); 
    
 } // draw status

void draw_board_status(int board) {
  board == 0 ;

  // Clear display area with a black rectangle.
  tft.fillRect(57,0,205,25,BLACK);

  #ifdef SPLIT
  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(1);
  tft.setCursor(64, 20);
  tft.print("K9 SPLIT");       
  #endif

  // This need for the else if in the ifdef.
  if (board == 0) {
  }
  
  #ifdef A_B_COMBINE
  else if (board == 1) {
      tft.setFont(&FreeSans9pt7b);
      tft.setTextColor(WHITE, BLACK);
      tft.setTextSize(1);
      tft.setCursor(57, 20);
      tft.print("Board A and B Combined");       
  }
  else if (board == 2) {
      tft.setFont(&FreeSans9pt7b);
      tft.setTextColor(WHITE, BLACK);
      tft.setTextSize(1);
      tft.setCursor(57, 20);
      tft.print("Board A and B Combined");       
  }  
  #endif
  #ifdef A_DOUBLE_POLE
  else if (board == 1) {
      tft.setFont(&FreeSans9pt7b);
      tft.setTextColor(WHITE, BLACK);
      tft.setTextSize(1);
      tft.setCursor(70, 20);
      tft.print("Board A - Double Pole");       
  }  
  #endif
} 

void draw_relay_labels() {
  tft.setFont();
  tft.setTextColor(RED, BLACK);
  tft.setTextSize(1);
  tft.setCursor(95, 85);
  tft.print("RED:    Relay is SET");
  tft.setTextColor(ORANGE, BLACK);
  tft.setCursor(95, 95);
  tft.print("ORANGE: Relay is HELD");
}
 
void tft_setup() {
 // initialize tft 
  tft.begin();

  if (! ctp.begin(40)) {  // pass in 'sensitivity' coefficient
    Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1);
  }

  tft.setFont();
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(80, 40);
  tft.print("N8UR/TAPR");
  tft.setTextColor(BLUE);
  tft.setCursor(115, 80);
//  tft.print("N4MTT");
//  tft.setTextColor(WHITE);
  tft.setCursor(30, 120);
  tft.print("TASS Controller");
  tft.setFont();
  tft.setTextColor(ORANGE);
  tft.setTextSize(2);
  tft.setCursor(0, 220);
  tft.print(version);
  delay(5000);
  tft.fillScreen(BLACK);
  draw_boards();
  draw_relays();
  draw_cmds();
  draw_status();
  draw_relay_labels();
} // tft_setup
#endif
