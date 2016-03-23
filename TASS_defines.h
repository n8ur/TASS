/* defines for TASS
*/


// The display also uses hardware SPI, plus #9 & #10
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
