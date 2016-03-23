/***************************************************
TASS Control Software by John Ackermann N8UR.  Based on Adafruit examples below

Hardware write functions

****************************************************/

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

