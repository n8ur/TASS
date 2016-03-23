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
// Wait for a touch
  execute = 0;
  if (! ctp.touched()) {
      return execute;
  }

  // Retrieve a point  
  TS_Point p = ctp.getPoint();
 
  // flip it around to match the screen.
 // p.x = map(p.x, 0, 240, 240, 0);
 p.y = map(p.y, 0, 320, 320, 0);
 
 // we're using board 90 degrees from default, I guess
 int x_pos = p.y;
 int y_pos = p.x;

   // set board -- all choices are in left-most box space
  if (x_pos <= BOXSIZE) {  
    draw_boards();
    if (y_pos < BOXSIZE) {
      draw_board1(FILL, RED, WHITE); 
      board = 'A';
    } else if (y_pos >= BOXSIZE && y_pos < BOXSIZE*2) { 
      draw_board2(FILL, RED, WHITE);
      board = 'B';
    } else if (y_pos >= BOXSIZE*2 && y_pos < BOXSIZE*3) {
      draw_board3(FILL, RED, WHITE);
      board = 'C';
    } else if (y_pos >= BOXSIZE*3 && y_pos < BOXSIZE*4) { 
      draw_board4(FILL, RED, WHITE); 
      board = 'D';
    } else if (y_pos >= BOXSIZE*4) { 
      draw_board5(FILL, RED, WHITE);
      board = 'E';
    }
  } // set board
  
  // set relays -- choices are in the middle
  if (x_pos >= RELAY_ROW_LEFT && x_pos <= RELAY_ROW_LEFT + BOXSIZE*4
        && y_pos >= RELAY_ROW_1_TOP && y_pos <= RELAY_ROW_2_TOP + BOXSIZE) {

    draw_relays();
      
    // set relay row 1
    if (y_pos >=RELAY_ROW_1_TOP && y_pos <= RELAY_ROW_1_TOP + BOXSIZE) {
  
      if (x_pos <= RELAY_ROW_LEFT + BOXSIZE) {
      draw_relay1(FILL, RED, WHITE); 
      relay = 1;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*2) { 
      draw_relay2(FILL, RED, WHITE);
      relay = 2;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*3) {
      draw_relay3(FILL, RED, WHITE);
      relay = 3;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*4) { 
      draw_relay4(FILL, RED, WHITE); 
      relay = 4;
    } 
  } 
  
  // set relay row 2
  if (x_pos >= RELAY_ROW_LEFT && x_pos <= RELAY_ROW_LEFT + BOXSIZE*4
        && y_pos >= RELAY_ROW_2_TOP && y_pos <= RELAY_ROW_2_TOP + BOXSIZE) {
    if (x_pos <= RELAY_ROW_LEFT + BOXSIZE) {
      draw_relay5(FILL, RED, WHITE); 
      relay = 5;
     } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*2) { 
      draw_relay6(FILL, RED, WHITE);
      relay = 6;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*3) {
      draw_relay7(FILL, RED, WHITE);
      relay = 7;
    } else if (x_pos <= RELAY_ROW_LEFT + BOXSIZE*4) { 
      draw_relay8(FILL, RED, WHITE); 
      relay = 8;
    } 
  }
 } // set relays 
  
  // set command -- all choices are in right-most box space
  if (x_pos >=CMD_BOXLEFTEDGE) {  
    draw_cmds();
    if (y_pos < BOXSIZE) {
      draw_cmd1(FILL, RED, WHITE); 
      cmd = 'S';
    } else if (y_pos >= BOXSIZE && y_pos < BOXSIZE*2) { 
      draw_cmd2(FILL, RED, WHITE);
      cmd = 'H';
    } else if (y_pos >= BOXSIZE*2 && y_pos < BOXSIZE*3) {
      draw_cmd3(FILL, RED, WHITE);
      cmd = 'U';
    } else if (y_pos >= BOXSIZE*3 && y_pos < BOXSIZE*4) { 
      draw_cmd4(FILL, RED, WHITE); 
      cmd = ' ';
      Serial.println("Command: (not implemented)");
    }
  }  // set command
 
    
  if (x_pos >= CMD_BOXLEFTEDGE && y_pos >= BOXSIZE*4) { 
    draw_boards();
    draw_relays();
    draw_cmds();  
    draw_cmd5(FILL, GREEN, WHITE);
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
  if (fill) {
    tft.fillRect(BOARD_BOXLEFTEDGE, 0, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 12, char('A'), text_color, box_color, 4);
  } else {
    tft.drawRect(BOARD_BOXLEFTEDGE, 0, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 12, char('A'), text_color, box_color, 4);
  }
}

void draw_board2 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(BOARD_BOXLEFTEDGE, BOXSIZE, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 60, char('B'), text_color, box_color, 4);
  } else {
    tft.drawRect(BOARD_BOXLEFTEDGE, BOXSIZE, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 60, char('B'), text_color, box_color, 4);
  }
}
 
void draw_board3 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(BOARD_BOXLEFTEDGE, BOXSIZE*2, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 108, char('C'), text_color, box_color, 4);
  } else {
    tft.drawRect(BOARD_BOXLEFTEDGE, BOXSIZE*2, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 108, char('C'), text_color, box_color, 4);
  }
}
 
 void draw_board4 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(BOARD_BOXLEFTEDGE, BOXSIZE*3, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 156, char('D'), text_color, box_color, 4);
  } else {
    tft.drawRect(BOARD_BOXLEFTEDGE, BOXSIZE*3, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 156, char('D'), text_color, box_color, 4);
  }
}

 void draw_board5 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(BOARD_BOXLEFTEDGE, BOXSIZE*4, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 204, char(' '), text_color, box_color, 4);
  } else {
    tft.drawRect(BOARD_BOXLEFTEDGE, BOXSIZE*4, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(12, 204, char(' '), text_color, box_color, 4);
  }
}

void draw_cmd1 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(CMD_BOXLEFTEDGE, 0, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 12, char('S'), text_color, box_color, 4);
  } else {
    tft.drawRect(CMD_BOXLEFTEDGE, 0, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 12, char('S'), text_color, box_color, 4);
  }
}

 void draw_cmd2 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(CMD_BOXLEFTEDGE, BOXSIZE, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 60, char('H'), text_color, box_color, 4);
  } else {
    tft.drawRect(CMD_BOXLEFTEDGE, BOXSIZE, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 60, char('H'), text_color, box_color, 4);
  }
}
 
 void draw_cmd3 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(CMD_BOXLEFTEDGE, BOXSIZE*2, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 108, char('U'), text_color, box_color, 4);
  } else {
    tft.drawRect(CMD_BOXLEFTEDGE, BOXSIZE*2, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 108, char('U'), text_color, box_color, 4);
  }
}
  
// cmd_4 not implemented yet
void draw_cmd4 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(CMD_BOXLEFTEDGE, BOXSIZE*3, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 156, char(' '), text_color, box_color, 4);
  } else {
    tft.drawRect(CMD_BOXLEFTEDGE, BOXSIZE*3, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 156, char(' '), text_color, box_color, 4);
  }
}
 
void draw_cmd5 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(CMD_BOXLEFTEDGE, BOXSIZE*4, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 204, char('G'), text_color, box_color, 4);
  } else {
    tft.drawRect(CMD_BOXLEFTEDGE, BOXSIZE*4, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(CMD_BOXLEFTEDGE+12, 204, char('G'), text_color, box_color, 4);
  }
}


void draw_relay1 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT, RELAY_ROW_1_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+12, RELAY_ROW_1_TOP+12, char('1'), text_color, box_color, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT, RELAY_ROW_1_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+12, RELAY_ROW_1_TOP+12, char('1'), text_color, box_color, 4);
  }
}

void draw_relay2 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT+BOXSIZE, RELAY_ROW_1_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+60, RELAY_ROW_1_TOP+12, char('2'), text_color, box_color, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT+BOXSIZE, RELAY_ROW_1_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+60, RELAY_ROW_1_TOP+12, char('2'), text_color, box_color, 4);
  }
}

void draw_relay3 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT+BOXSIZE*2, RELAY_ROW_1_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+108, RELAY_ROW_1_TOP+12, char('3'), text_color, box_color, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT+BOXSIZE*2, RELAY_ROW_1_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+108, RELAY_ROW_1_TOP+12, char('3'), text_color, box_color, 4);
  }
}

void draw_relay4 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT+BOXSIZE*3, RELAY_ROW_1_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+156, RELAY_ROW_1_TOP+12, char('4'), text_color, box_color, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT+BOXSIZE*3, RELAY_ROW_1_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+156, RELAY_ROW_1_TOP+12, char('4'), text_color, box_color, 4);
  }
}

void draw_relay5 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT, RELAY_ROW_2_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+12, RELAY_ROW_2_TOP+12, char('5'), text_color, box_color, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT, RELAY_ROW_2_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+12, RELAY_ROW_2_TOP+12, char('5'), text_color, box_color, 4);
  }
}

void draw_relay6 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT+BOXSIZE, RELAY_ROW_2_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+60, RELAY_ROW_2_TOP+12, char('6'), text_color, box_color, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT+BOXSIZE, RELAY_ROW_2_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+60, RELAY_ROW_2_TOP+12, char('6'), text_color, box_color, 4);
  }
}

void draw_relay7 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT+BOXSIZE*2, RELAY_ROW_2_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+108, RELAY_ROW_2_TOP+12, char('7'), text_color, box_color, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT+BOXSIZE*2, RELAY_ROW_2_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+108, RELAY_ROW_2_TOP+12, char('7'), text_color, box_color, 4);
  }
}

void draw_relay8 (boolean fill, int box_color, int text_color) {
  if (fill) {
    tft.fillRect(RELAY_ROW_LEFT+BOXSIZE*3, RELAY_ROW_2_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+156, RELAY_ROW_2_TOP+12, char('8'), text_color, box_color, 4);
  } else {
    tft.drawRect(RELAY_ROW_LEFT+BOXSIZE*3, RELAY_ROW_2_TOP, BOXSIZE, BOXSIZE, box_color);
    tft.drawChar(RELAY_ROW_LEFT+156, RELAY_ROW_2_TOP+12, char('8'), text_color, box_color, 4);
  }
}

void draw_boards() {
// to clear previous fill, we do twice, -- once with fill with black, then nofill with colors
  draw_board1(FILL, BLACK, BLACK);
  draw_board2(FILL, BLACK, BLACK);
  draw_board3(FILL, BLACK, BLACK);
  draw_board4(FILL, BLACK, BLACK);
  draw_board5(FILL, BLACK, BLACK);
  
  draw_board1(NOFILL, WHITE, WHITE);
  draw_board2(NOFILL, WHITE, WHITE); 
  draw_board3(NOFILL, WHITE, WHITE);
  draw_board4(NOFILL, WHITE, WHITE);
  draw_board5(NOFILL, WHITE, WHITE);
}

void draw_cmds() {
  draw_cmd1(FILL, BLACK, BLACK);
  draw_cmd2(FILL, BLACK, BLACK);
  draw_cmd3(FILL, BLACK, BLACK);
  draw_cmd4(FILL, BLACK, BLACK);
  draw_cmd5(FILL, BLACK, BLACK);
  
  draw_cmd1(NOFILL, WHITE, WHITE);
  draw_cmd2(NOFILL, WHITE, WHITE); 
  draw_cmd3(NOFILL, WHITE, WHITE);
  draw_cmd4(NOFILL, WHITE, WHITE);
  draw_cmd5(NOFILL, GREEN, GREEN); // cmd5 is execute, so we give him a different color
}

void draw_relays() {
  draw_relay1(FILL, BLACK, BLACK);
  draw_relay2(FILL, BLACK, BLACK);
  draw_relay3(FILL, BLACK, BLACK);
  draw_relay4(FILL, BLACK, BLACK);
  draw_relay5(FILL, BLACK, BLACK);
  draw_relay6(FILL, BLACK, BLACK);
  draw_relay7(FILL, BLACK, BLACK);
  draw_relay8(FILL, BLACK, BLACK);
  
  draw_relay1(NOFILL, WHITE, WHITE);
  draw_relay2(NOFILL, WHITE, WHITE);
  draw_relay3(NOFILL, WHITE, WHITE);
  draw_relay4(NOFILL, WHITE, WHITE);
  draw_relay5(NOFILL, WHITE, WHITE);
  draw_relay6(NOFILL, WHITE, WHITE);
  draw_relay7(NOFILL, WHITE, WHITE);
  draw_relay8(NOFILL, WHITE, WHITE);
 }
 
 void draw_status() {
   if (!execute) {
      tft.setTextColor(WHITE, BLACK);
    } else{
      tft.setTextColor(GREEN, BLACK);
    }
    tft.setTextSize(2);
    tft.setCursor(100, 170);
    tft.print("Board: ");
    tft.print(board);
    tft.setCursor(100, 190);
    tft.print("Relay: ");
    tft.print(relay);
    tft.setCursor(100, 210);
    tft.print("Command: ");
    tft.print(cmd); 
 } // draw status
 
 void tft_setup() {
 // initialize tft 
  tft.begin();

  if (! ctp.begin(40)) {  // pass in 'sensitivity' coefficient
    Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1);
  }

  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(80, 80);
  tft.print("N8UR/TAPR");
  tft.setCursor(30, 120);
  tft.print("TASS Controller");
  tft.setTextSize(2);
  tft.setCursor(0, 220);
  tft.print(version);
  delay(5000);
  tft.fillScreen(BLACK);
  draw_boards();
  draw_relays();
  draw_cmds();
  draw_status();
} // tft_setup
#endif
