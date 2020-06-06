/* TASS - Mask
 *  
 * Bytemask Manipulation Functions 
 * 
 * Author: Matthew J. Wolf  <matthew.wolf.hpsdr@speciosus.net>
 * Date: 12-NOV-2018
 * 
 * - Version 0.7-n4mtt
 *   = Added function get_bit_mask_state() 
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

byte set_mask(int x, byte mask) {
  switch (x) {
    case 1: mask |= 0x01; break;
    case 2: mask |= 0x02; break;
    case 3: mask |= 0x04; break;
    case 4: mask |= 0x08; break;
    case 5: mask |= 0x10; break;
    case 6: mask |= 0x20; break;
    case 7: mask |= 0x40; break;
    case 8: mask |= 0x80; break;
  }
  return mask;
} // of set_mask

byte clear_mask_top(byte mask) {
  mask = mask & 0xF0;
     return mask;   
}

byte clear_mask_bottom(byte mask) {
  mask = mask & 0x0F;
  return mask;  
}

byte clear_mask(byte mask) { 
  mask = mask & 0x00;
  return mask;  
}

byte clear_S_mask(int relay,byte mask) {
 #ifdef SPLIT
  if (relay >=1 && relay <=4) { 
    mask = clear_mask_top(mask);
    } else {
    mask = clear_mask_bottom(mask);
  } // if   
  #else
  mask = clear_mask(mask);
  #endif
  return mask;  
}

int get_bit_mask_state(int relay, byte mask) {
   int temp = -1;

     switch(relay){
      case 0:
          temp = mask & 0x01;
          if (temp == 0x01) {
            return (1);
          }
          else {
            return(0);
          }
          break;
      case 1:
          temp = mask & 0x02;
          if (temp == 0x02) {
            return (1);
          }
          else {
            return(0);
          }
          break;
      case 2:
          temp = mask & 0x04; 
          if (temp == 0x04) {
            return (1);
          }
          else {
            return(0);
          }      
          break;
      case 3:
          temp = mask & 0x08;
          if (temp == 0x08) {
            return (1);
          }
          else {
            return(0);
          }   
          break;
      case 4:
          temp = mask & 0x10;
          if (temp == 0x10) {
            return (1);
          }
          else {
            return(0);
          }   
          break;
      case 5:
          temp = mask & 0x20;
          if (temp == 0x20) {
            return (1);
          }
          else {
            return(0);
          }   
          break;
      case 6:
          temp = mask & 0x40;
          if (temp == 0x40) {
            return (1);
          }
          else {
            return(0);
          }   
          break;
      case 7:
          temp = mask & 0x80;
          if (temp == 0x80) {
            return (1);
          }
          else {
            return(0);
          }   
          break;
      default:
          return (0);
          break;                          
   }
}
