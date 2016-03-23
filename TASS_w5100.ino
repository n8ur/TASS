#ifdef USE_W5100

void w5100_setup() {
 //disable SD
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);

  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
} // w5100_setup


boolean get_w5100_data() {
  
  if (getTelnetString()) {
  board = toupper(dataBuffer[1]);
  relay = atoi(&dataBuffer[2]);
  relay_char =(dataBuffer[2]);
  cmd = toupper(dataBuffer[3]);
  execute = 1;
  
  // first param is board, A - D
  if (!(board >= 'A' && board <= 'D')) {execute = 0;} // board check

  // second is relay, 0 through 8
  if (!(relay >= 0 && relay <= 8)) {execute = 0;} // relay check

  // third is command -- H, S, or U
  if (!((cmd == 'H') || (cmd == 'S') || (cmd == 'U'))) {execute = 0;} // cmd check
  } //call getTelnetString

if (execute) {
  if (telnet_verbose >0) { 
    server.write("<");
    server.write(board);
    server.write(relay_char);
    server.write(cmd);
    server.write(">");
    if (telnet_verbose == 1) {server.write("\n");} else {server.write(" ");}
  }
  if (telnet_verbose == 2) {
    server.write("Board: ");
    server.write(board);
    server.write(" relay: ");
    server.write(relay_char);
    server.write(" command: ");
    server.write(cmd);
    if ((cmd == 'U') && (relay == 0)) { server.write(" -- Clear All"); }
    server.write("\n");
  } 
} 
return execute;
} //get_w5100_data

boolean getTelnetString(){
    static byte dataBufferIndex = 0;
    boolean storeString;
    EthernetClient client = server.available();
    
    if (client && newclient) {
      server.write("\nTAPR TASS Control Software\n");
      server.write(version);
      server.write("\nCopyright 2015 John Ackermann   N8UR\n");
      server.write("Licensed under MIT license\n");
      server.write("\n");
      newclient = 0;
    }
    while (client){
       char incomingbyte = client.read();    
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

#endif
