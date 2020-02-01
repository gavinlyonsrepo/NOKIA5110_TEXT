// Test file for NOKIA5110_TEXT lib showing use of font number 3
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT 
//
// NOTE:  ********************************************** NOTE:
// For this non-default font to work, One line in the library header file
// called "NOKIA5110_TEXT.h"  Must be modified ,
// the Define statement at start of file for Font3 must be commented IN.
// #define NOKIA5110_FONT_3
// NOTE:  ********************************************** NOTE:

#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right
// RST 1/ CD 2/ DC 3/ DIN 4/ CLK 5
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);
#define inverse  false
#define contrast 0xBE // default is 0xBF set in LCDinit, Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
#define bias 0x13 // LCD bias mode 1:48: Try 0x13 or 0x14
#define FontNumber 3

//TEST setup
#define mydelay 1000

void setup() {
  mylcd.LCDInit(inverse, contrast, bias); //init the lCD passed inverse true or false
  mylcd.LCDClear(); //clear whole screen
  mylcd.LCDsetContrast(contrast); 
  mylcd.LCDFont(FontNumber); //use Font three default.
}

void loop() {
  
  //TEST 1 writing Aurebesh text to blocks 
  delay(mydelay);
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("ANAKIN TURN"); //print to block 0 (0-5 blocks or row bytes)
  mylcd.LCDgotoXY(0, 1); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("THE SHIP"); //print to block 0 (0-5 blocks or row bytes)
  mylcd.LCDgotoXY(0, 2); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("AROUND AND"); //print to block 0 (0-5 blocks or row bytes)
  mylcd.LCDgotoXY(0, 3); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("GO BACK HOME"); //print to block 0 (0-5 blocks or row bytes)
  mylcd.LCDgotoXY(0, 4); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("RIGHT AWAY"); //print to block 0 (0-5 blocks or row bytes)
  delay(mydelay);
}






