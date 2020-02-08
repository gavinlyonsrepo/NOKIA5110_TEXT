// Test file for NOKIA5110_TEXT showing use of all five fonts 
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT 
// NOTE:  ********************************************** NOTE:
// There are six fonts , font one is default,
// For a non-default font to work , One line in the library header file
// called "NOKIA5110_TEXT.h"  Must be modified 
// the Define statement at start of file for Font X must be commented IN.
// #define NOKIA5110_FONT_X where X is number of font
// NOTE:  ********************************************** NOTE:

#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right
// RST 1/ CD 2/ DC 3/ DIN 4/ CLK 5
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);

#define inverse  false
#define contrast 0xBF // default is 0xBF set in LCDinit, Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
#define bias 0x14 // LCD bias mode 1:48: Try 0x13 or 0x14
uint8_t fontnumber = 1;  // use Font one

//TEST setup
#define mydelay 1000

void setup() {
  mylcd.LCDInit(inverse, contrast, bias); //init the lCD 
  mylcd.LCDClear(); //clear whole screen

}

void loop() {

  //TEST 1 writing
  delay(mydelay);
  mylcd.LCDFont(fontnumber); //font 1
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("1234567890AB"); //print to block 0 
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); // font 2 
  mylcd.LCDgotoXY(0, 1); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("VOLTAGE 2"); //print to block 1
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); //font 3
  mylcd.LCDgotoXY(0, 2); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("ABCDEFGHIJK"); //print to block 2
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); //font 4
  mylcd.LCDgotoXY(0, 3); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("VOLTAGE 5.843"); //print to block 3
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); //font 5
  mylcd.LCDgotoXY(0, 4); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("VOLTAGE"); //print to block 4
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); //font 6
  mylcd.LCDgotoXY(0, 5); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("1234567890123456"); //print to block 5
  delay(mydelay);
  fontnumber = 1;
}
