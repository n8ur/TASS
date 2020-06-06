/* TASS - Defines
 *  
 * Author: Matthew J. Wolf  <matthew.wolf.hpsdr@speciosus.net>
 * Date: 18-NOV-2018
 * 
 * - Version 0.7-n4mtt
 *   = Added: 
 *     -= NUM_TASS_BOARDS_DISPLAY
 *     -= BLUE
 *     -= ORANGE
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

// The Number of TASS boards to inculde on the ethernet, touchscreen, and USB displays.
#define NUM_TASS_BOARDS_DISPLAY 1

// The display also uses hardware SPI, plus #9 & #10
//
// Ethernet and touch screen shield both use digital pin 10 for
// a SPI slave select (SS). I moved the capacitive touchscreen SS 
// from pin 10 to digital pin 2. - N4MTT
//#define TFT_CS 2
#define TFT_CS 10
#define TFT_DC 9

// size of serial command string; includes "<" and ">" delimiters
#define DATABUFFERSIZE 5

// I/O number of first relay on each board; this and the next 8 I/Os will be used for the board
#define A_1 61 // this is analog pin A7
#define B_1 23
#define C_1 32
#define D_1 41

// Size of the selection boxes
#define BOXSIZE 48
#define BOARD_BOXLEFTEDGE 0
#define LEFTBOXEDGE 48
#define RIGHTEDGE 320
#define CMD_BOXLEFTEDGE 272
#define RELAY_ROW_LEFT 64
#define RELAY_ROW_1_TOP 32
#define RELAY_ROW_2_TOP 108
#define CMD_STRING_LEFT 120
#define CMD_STRING_TOP 204

#define FILL 1
#define NOFILL 0

#define WHITE ILI9341_WHITE
#define BLACK ILI9341_BLACK
#define GREEN ILI9341_GREEN
#define RED ILI9341_RED
#define BLUE ILI9341_BLUE
#define ORANGE ILI9341_ORANGE
