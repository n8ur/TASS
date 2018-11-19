/* TASS - Board
 *  
 *  Hardware write functions
 *  
 * Author: Matthew J. Wolf  <matthew.wolf.hpsdr@speciosus.net>
 * Date: 18-NOV-2018
 *  
 * - Version 0.7-n4mtt
 *   = Added logic to restore the relays after a reset or power on.
 *   = Added function
 *     -= restore_relays()
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

void setup_board() {
// set configuration pins to input pullup
  pinMode(14,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);
  pinMode(16,INPUT_PULLUP);
  pinMode(17,INPUT_PULLUP);
  pinMode(18,INPUT_PULLUP);
  pinMode(19,INPUT_PULLUP);
  pinMode(22,INPUT_PULLUP);

// set up digital pins for each board
  for (int relay_num=A_1;relay_num<=A_1+8;relay_num++){
    pinMode(relay_num, OUTPUT);}
  for (int relay_num=B_1;relay_num<=B_1+8;relay_num++){
    pinMode(relay_num, OUTPUT);}
  for (int relay_num=C_1;relay_num<=C_1+8;relay_num++){
    pinMode(relay_num, OUTPUT);}
  for (int relay_num=D_1;relay_num<=D_1+8;relay_num++){
    pinMode(relay_num, OUTPUT);}

// Restore the relays from masks stored in EEPROM
#ifdef USE_EEPROM

  // Board A
  restore_relays(1,0,4);
  
  // Board B
  restore_relays(2,1,5);

  // Board C
  restore_relays(3,2,6);
  
  // Board D
  restore_relays(4,3,7);

#endif 
    
} // setup_board()


void write_board(int first_io, byte cmd_mask,bool K9) {
    int counter = first_io; // first relay
    for (byte mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
      if (cmd_mask & mask) { // if bitwise AND resolves to true     
        digitalWrite(counter,HIGH);
      } else {
        digitalWrite(counter,LOW);  
      } // of if
      counter++;
    } // of for
  
#ifndef SPLIT
  // set K9
  if (K9) {
    digitalWrite(first_io+8,HIGH);
  } else {
    digitalWrite(first_io+8,LOW);
  }  // if
#endif

}  // of write_board

#ifdef USE_EEPROM
void restore_relays(int board, int s_mask_loc, int h_mask_loc) {

  /* Test EEPROM values for the correct range.
   *  
   * The EEPROM is empty (NAN) when the sketch is run
   * on a microprocessor that had it's EEPROM
   * erased. When a microprocessor is recycled there
   * is no way of knowing what values are stored in 
   * the EEPROM. The tests are need because I am not 
   * aware of any way Arduino can directly initialize  
   * EEPROM values.
   */

  int s_mask = -1;
  int h_mask = -1;
  int cmd_mask = -1;
  int i = -1;

  s_mask = EEPROM.read(s_mask_loc);
  h_mask = EEPROM.read(h_mask_loc);

  // Only if bits in the masks are nether all low or all high. 
  if ( ((s_mask != 0) || (s_mask != 255))
       || ((h_mask != 0) || (h_mask != 255)) ) {
    
    cmd_mask = h_mask | s_mask;

    switch (board) {
      case 1: 
             H_mask_A = h_mask;
             S_mask_A = s_mask;
             write_board(A_1,cmd_mask,K9);
             break;
      case 2: 
             H_mask_B = h_mask;
             S_mask_B = s_mask;
             write_board(B_1,cmd_mask,K9);
             break;
      case 3: 
             H_mask_C = h_mask;
             S_mask_C = s_mask;
             write_board(C_1,cmd_mask,K9);
             break;
      case 4: 
             H_mask_D = h_mask;
             S_mask_D = s_mask;
             write_board(D_1,cmd_mask,K9);
             break;
    } 
    
  }

}
#endif
