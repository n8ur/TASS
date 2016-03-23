/***************************************************
TASS Control Software by John Ackermann N8UR.  Based on Adafruit examples below

LED 8X8 Matrix

****************************************************/

#ifdef USE_LED8X8
void led8x8_setup() {
 matrix.begin(0x70);
  matrix.clear();
  matrix.setBrightness(0);
  matrix.drawPixel(0,0,LED_ON);
  matrix.writeDisplay();
  delay(1000);
  int col;
  int row;
  for( col = 0; col <= 7; col++ ){
    for( row = 0; row <= 7; row++ ){
      matrix.drawPixel(row,col,LED_ON);
      matrix.writeDisplay();
      delay(10);
    }
  }
  delay(250);
  matrix.clear();
  matrix.writeDisplay();
} // led8x8_setup()  

void draw_LED_status(){
  set_LED_row(2,cmd_mask_A);
  set_LED_row(3,cmd_mask_B);
  set_LED_row(4,cmd_mask_C);
  set_LED_row(5,cmd_mask_D);
} // draw_LED_status()

void set_LED_row(int row, byte myByte){
  int col = 7;  // count backwards since bit mask moves LSB -> MSB
  for (byte mask = 0x80; mask; mask >>= 1){
    matrix.drawPixel(col,row,LED_OFF); // clear previous
    if (mask  & myByte) {
      matrix.drawPixel(col,row,LED_ON);
    }
    col--; 
  }
  matrix.writeDisplay();
} // set_LED_row

void heartbeat() {
  // based on LED Heartbeat routine by Allen C. Huffman (www.appleause.com)
  static unsigned int  hbStatus = LOW;  // Last set mode.
  static unsigned long hbBlinkTime = 0; // blink time.

  // LED blinking heartbeat. Yes, we are alive.
  // For explanation, see:
  // http://playground.arduino.cc/Code/TimingRollover
  if ( (long)(millis()-hbBlinkTime) >= 0 )
  {
    // Toggle LED.
    hbStatus = (hbStatus==HIGH ? LOW : HIGH);
    matrix.drawPixel(7,7,hbStatus);
    matrix.writeDisplay();

    // Reset "next time to toggle" time.
    hbBlinkTime = millis()+HB_BLINK_MS;
  }
} // End of ledBlink()
#endif // USE_LED8X8
