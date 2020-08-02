// Test file for NOKIA5110_TEXT showing all 8 fonts. 1-8
//
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT 
// 
//NOTE:  ********************************************** NOTE:
// There are eight fonts , font one is default,
// For a non-default font to work , One line in the library header file
// called "NOKIA5110_TEXT.h"  Must be modified by USER
// the Define statement at start of file for Font X must be commented IN.
// #define NOKIA5110_FONT_X where X is number of font
// NOTE:  ********************************************** NOTE:

#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right
// RST 2/ CD 3/ DC 4/ DIN 5/ CLK 6
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);

#define inverse  false
#define contrast 0xB2 // default is 0xBF set in LCDinit, Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
#define bias 0x14 // LCD bias mode 1:48: Try 0x13 or 0x14
uint8_t fontnumber = 1;  // use Font one

//TEST setup
#define mydelay 1000
#define mydelay5 5000

void setup() {
  mylcd.LCDInit(inverse, contrast, bias); //init the lCD 
  mylcd.LCDClear(); //clear whole screen

}

/* 
TEST 1 font 1-6 X by 8 fonts
TEST 2 font 7 16 y 12 font
TEST 3 font 8 24 by 16 font
*/

void loop() {

  // ******** TEST 1 writing the  first six  fonts( X by 8) 1-6 ********
  delay(mydelay);
  mylcd.LCDFont(fontnumber); //font 1
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("1234567890AB"); //print to block 0 
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); // font 2 thick
  mylcd.LCDgotoXY(0, 1); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("12345ABCD"); //print to block 1
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); //font 3
  mylcd.LCDgotoXY(0, 2); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("123ABCDEFGHI"); //print to block 2
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); //font 4 seven segment
  mylcd.LCDgotoXY(0, 3); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("1234567890ABCD"); //print to block 3
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); //font 5 wide
  mylcd.LCDgotoXY(0, 4); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("ABCD1234"); //print to block 4
  delay(mydelay);
  fontnumber ++;
  mylcd.LCDFont(fontnumber); //font 6 tiny
  mylcd.LCDgotoXY(0, 5); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("1234567890ABCDEF"); //print to block 5
  delay(mydelay5);
  
  // ***** TEST 2 font 7 *********
  fontnumber  ++;
  mylcd.LCDClear(); //clear whole screen
  mylcd.LCDFont(fontnumber); //font 7
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDFillBlock(0x2F, 0);
  mylcd.LCDgotoXY(20, 1);
  mylcd.LCDString("TIME"); //NB uppercase ONLY for font 7
  mylcd.LCDgotoXY(15, 3); // this font takes two blocks
  mylcd.LCDString("23:04");
  mylcd.LCDFillBlock(0xF2, 5);
  delay(mydelay5);
 

  // ***** TEST 3 font 8 *********
   fontnumber  ++;
   mylcd.LCDClear();
   mylcd.LCDFont(fontnumber); //font 8 this font takes 3 blocks
   mylcd.LCDgotoXY(0, 0);
   mylcd.LCDString("12:34");
   mylcd.LCDgotoXY(0, 3);
   mylcd.LCDString("4.889");
   delay(mydelay5);
   
   mylcd.LCDClear();
   fontnumber = 1;
  
}
