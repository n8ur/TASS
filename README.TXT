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

