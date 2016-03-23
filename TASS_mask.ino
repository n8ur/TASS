/***************************************************
TASS Control Software by John Ackermann N8UR.  Based on Adafruit examples below

bytemask manipulation functions

****************************************************/

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
