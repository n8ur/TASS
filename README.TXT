TASS Software v0.80 (6 June 2020)
-- Merged in N4MTT's changes from 18 November 2018
   with a few tweaks (version number, etc.)

TASS Software v0.70-n4mtt (18 November 2018)
-- Tested support for using both an Ethernet shield and the touch screen
   shield. A version 2 (WIZnet w5500) Ethernet shield is required. The
   the earlier Ethernet shield is missing four pins that are needed for
   the touch screen shield.
   = The Ethernet shield and the touch screen shield both use digital pin 
     10 as a slave select (SS). I cut the psychical pin for digital pin
     10 on the touch screen shield. Then I ran a wire from the PCB pad
     for pin 10 to the pad for digital pin 2. Then in changed the        
     define TFT_CS from 10 to 2.
-- Added support for WIZnet w5500 Ethernet shields to use the Ethernet2
   library.
   = Enabled with the "USE_W5500" define.
-- Added displaying the current status of the relays to the telnet
   server and USB output.
   = Enable the "SHOW_INFO_ETHERNET" define for display with the telnet
     server.
   = Enable the "SHOW_INFO_USB" define for the display with the USB
     output.
-- Updated the touch screen display to show the current status of the
   relays. When the board field is touched the relay fields display the
   status of the relays. The color of the relay number shows the status
   the relay.
   = Red:    The relay is set.
   = Orange: The relay is "hold".
-- Added support to not display all four boards on the touch screen and 
   in the "SHOW_INFO_ETHERNET" and "SHOW_INFO_USB" displays.
   -= Set the "NUM_TASS_BOARDS_DISPLAY" to the number of boards to 
      display.
   --= On the touch screen the fields for the non-displayed boards
       are not active.
-- Added saving and restoring the state of the relays after a reset 
   or power on. The S and H masks are saved to the EEPROM. When the
   sketch starts to run the S and H masks are read from EEPROM. The
   masks are then used to restore the state of the relays. 
   = Enabled with the "USE_EEPROM" define.
-- Added the "I" command. The I command displays a comma-separated 
   values (CSV) format of the status of the relays.
   = Command format:  <'board''relay'I>
   -= Relay "0" display the status of all the relays on a board.
   = Output format:
   -= Relay status:
   --= Off:  0
   --= Set:  s
   --= Hold: h
   -= Board: (relay 0)
    i,'board',0,'relay 1 state','relay 2 state', ... 'relay 7 state'
   --= Example:
    i,A,0,s,0,0,h,0,0,0 
   -= Relay:
    i,'board','relay','state'
   --= Examples:
    i,A,1,0
    i,A,2,s
    1,A,5,h
-- No changes where made to the LED 8x8 display.
-- BUG - Touch Screen: Sometimes the relay status is wrong. Selecting a
       board will update the relay status. The root cause may be floating
       emulation. 

TASS Software v0.60 (24 January 2016)
-- Added #ifdef for "COMBINE_A_B" which causes boards A and B to act
   as a single board for purposes of the "S" command.  This allows for
   a 16 input switch.
-- Added #ifdef for "D_DOUBLE_POLE" which gangs together ports 1-5, 2-6,
   3-7, and 4-8 to create a four-throw double-pole switch.  e.g., enter
   <D1S> and both relays 1 and 5 will energize, or enter <D7S> and both
   relays 3 and 7 will energize.
-- Additional logic fixes and code cleanup

TASS Software v0.51 (10 January 2016)
-- Lots of code cleanup, moving routines into their own file to simplify
   the main loop.
-- If you tried versino 0.45, it probably didn't work as the routine to
   write to the board was not called properly, and if it had been, it would
   not have properly cleared unset relays.  Both should be fixed now.

TASS Software v0.45 (16 December 2015)
-- MAJOR FIX.  Restructured variables and logic for multi-board support
-- Added support for 8x8 LED matrix status display (USE_LED8X8)
-- Other cleanup

TASS Software v0.42 (4 October 2015)

-- Fixed bug in mask clearing that made the "U" command fail
-- Added function to allow display of relay and hold masks
-- Prettied up the TFT display a little

TASS Software v0.40
This version introduces support for Wiznet W5100 ethernet shields.  When
enabled via the USE_W5100 define, it operates a telnet server on port 23
that accepts the same command syntax as the USB serial connection.

You'll need to enter network information in the main TASS.ino file.
There's an option "telnet_verbose" that determines what commands are
returned from the server.  Setting to 0 means no echo of successful commands.
Setting to 1 will echo the raw command setting, e.g. "<A1S>".  Setting to
2 will echo the raw setting plus additional description.

Note that the server is very primitive.  I am not sure how it will work if
more than one client connects to the board.  You Have Been Warned.

TASS Software v0.32
This version is the first release that is minimally usable.  It supports
commands via USB and also will work with an Adafruit 2.8 inch capacitive
TFT touchscreen (product ID 1947).  To enable the touchscreen, use the
IS_TFT define.  If the touchscreen is enabled, it must be present for the
code to run.  You Have Been Warned.

