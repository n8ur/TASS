/***************************************************
TASS Control Software by John Ackermann N8UR.  Based on Adafruit examples below

USB serial functions
****************************************************/

void usb_setup() {
// initialize serial:
  Serial.begin(115200);
// splash
  Serial.println("TAPR TASS Control Software");
  Serial.println(version);
  Serial.println("Copyright 2015 John Ackermann   N8UR");
  Serial.println("Licensed under MIT license");
  Serial.println("");
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
    if (!((cmd == 'H') || (cmd == 'S') || (cmd == 'U'))) {execute = 0;} // cmd check
  
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
  
  #ifdef SHOW_MASKS
    usb_display_masks();
    Serial.println();
  #endif
} // usb_print_status()

void usb_display_masks() {
   Serial.print("\n");
   Serial.print(" S Masks:     ");
   usb_printBits(S_mask_A); 
   Serial.print(" ");
   usb_printBits(S_mask_B); 
   Serial.print(" ");
   usb_printBits(S_mask_C); 
   Serial.print(" ");
   usb_printBits(S_mask_D); 
   Serial.print("\n");
   Serial.print(" H Masks:     ");
   usb_printBits(H_mask_A); 
   Serial.print(" ");
   usb_printBits(H_mask_B); 
   Serial.print(" ");
   usb_printBits(H_mask_C); 
   Serial.print(" ");
   usb_printBits(H_mask_D); 
   Serial.print("\n");
   Serial.print(" Write Masks: ");
   usb_printBits(cmd_mask_A); 
   Serial.print(" ");
   usb_printBits(cmd_mask_B); 
   Serial.print(" ");
   usb_printBits(cmd_mask_C); 
   Serial.print(" ");
   usb_printBits(cmd_mask_D); 
   Serial.print("\n");
} // display_masks()
   
void usb_printBits(byte myByte){
 for (byte mask = 0x80; mask; mask >>= 1){
   if (mask  & myByte)
       Serial.print('1');
   else
       Serial.print('0');
   }
} // usb_printBits()

