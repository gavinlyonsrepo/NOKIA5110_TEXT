// NOKIA5110_HELLOWORLD.ino
// Test file for NOKIA5110_TEXT showing use most basic use case "HELLO WORLD" at 0,0
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
//Include the library 
#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right
// RST 1/ CD 2/ DC 3/ DIN 4/ CLK 5
// Create an LCD object 
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);

#define inverse  false
#define contrast 0xBE // default is 0xBF set in LCDinit, Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
#define bias 0x14 // LCD bias mode 1:48: Try 0x13 or 0x14
#define FontNumber 1 //1-6, 1 is default ,  Comment in  defines at top of  NOKIA5110_TEXT.h if using non default


void setup() {
  delay(1000);
  mylcd.LCDInit(inverse, contrast, bias); // init  the lCD
  mylcd.LCDClear(); // Clear whole screen
  mylcd.LCDFont(FontNumber); // Set the font
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks) top left corner
  mylcd.LCDString("HELLO WORLD"); //print
}

void loop() {

}
