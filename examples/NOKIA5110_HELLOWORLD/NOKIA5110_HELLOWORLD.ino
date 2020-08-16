// NOKIA5110_HELLOWORLD.ino
// Test file for NOKIA5110_TEXT showing use most basic use case "HELLO WORLD" at 0,0 with font number one
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT

//Include the library
#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right
// RST 1/ CD 2/ DC 3/ DIN 5/ CLK 5 / VCC 6 /LED 7 /GND 8
// Create an LCD object
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);

#define inverse  false // set to true to invert display pixel color
#define contrast 0xB2 // default is 0xBF set in LCDinit, Try 0xB1<-> 0xBF if your display is too dark
#define bias 0x13 // LCD bias mode 1:48: Try 0x12 or 0x13 or 0x14
#define FontNumber 1 //1-6, 1 is default ,  Comment in  defines at top of  NOKIA5110_TEXT.h if using non default


void setup() {
  delay(1000);
  mylcd.LCDInit(inverse, contrast, bias); // init  the lCD
  mylcd.LCDClear(0x00); // Clear whole screen
}

void loop() {
  mylcd.LCDFont(FontNumber); // Set the font
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks) top left corner
  mylcd.LCDString("HELLO WORLD"); //print
  delay(1000);
}
