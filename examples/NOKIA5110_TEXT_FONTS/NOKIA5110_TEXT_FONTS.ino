// Test file for NOKIA5110_TEXT showing all 9 fonts. 1-9
//
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
//
//NOTE NB NB **************************************** NOTE:
//
// There are Nine fonts , font one is default,
// For a non-default font to work , One line in the library header file
// called "NOKIA5110_TEXT.h"  Must be modified by USER
// the Define statement at start of file for Font X must be commented IN.
// #define NOKIA5110_FONT_X where X is number of font in  FONT DEFINE SECTION.
// Tests will  not work fully if non-default fonts are not commented in, nothing will appear.
//  For all this example file to work fully all fonts must be commented in
// NOTE NB NB **************************************** NOTE:

// Include the library.
#include <NOKIA5110_TEXT.h>

// Create an instance of the class
//LCD Nokia 5110 pinout left to right
// RST 1/ CD 2/ DC 3/ DIN 4/ CLK 5
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);

#define inverse  false
#define contrast 0xB2 // default is 0xBF set in LCDinit, Try 0xB1- 0xBF if your display is too dark
#define bias 0x12 // LCD bias mode 1:48: Try )x12 or  0x13 or 0x14 usually. 

// TEST delays
#define mydelay 1000
#define mydelay5 5000

// *********** SETUP **********
void setup() {
  mylcd.LCDInit(inverse, contrast, bias); //init the lCD
  mylcd.LCDClear(); //clear whole screen
  delay(mydelay);
  mylcd.LCDFont(1); // Font 1 default
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("Fonts tests");
  mylcd.LCDgotoXY(0, 1);
  mylcd.LCDString("READ Notes ");
  mylcd.LCDgotoXY(0, 2);
  mylcd.LCDString("in ex file");
  delay(mydelay5);
}

// *********** MAIN LOOP **********
void loop() {
  /*
    TEST 1 font 1-6, X by 8 fonts
    TEST 2 font 7, 16 by 12 font
    TEST 3 font 8, 24 by 16 font
    TEST 4 font 9, 16 by 32 font
  */

  Test1();
  Test2();
  Test3();
  Test4();
}

// ******** TEST 1 writing the  first six  fonts( X by 8) 1-6 ********
void Test1(void)
{
  mylcd.LCDClear(0X00); //clear whole screen

  mylcd.LCDFont(1); // Font 1 default
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Default Font"); //print to block 0
  delay(mydelay);

  mylcd.LCDFont(2); // Font 2 thick: NO LOWER CASE LETTERS
  mylcd.LCDgotoXY(0, 1);
  mylcd.LCDString("THICKFONT"); //print to block 1
  delay(mydelay);

  mylcd.LCDFont(3); // font 3 Aurebesh
  mylcd.LCDgotoXY(0, 2);
  mylcd.LCDString("5FYABCDEFGI"); //print to block 2
  delay(mydelay);

  mylcd.LCDFont(4); // font 4 seven segment
  mylcd.LCDgotoXY(0, 3);
  mylcd.LCDString("7 Segment font"); //print to block 3
  delay(mydelay);

  mylcd.LCDFont(5); // font 5 wide :NO LOWER CASE LETTERS
  mylcd.LCDgotoXY(0, 4);
  mylcd.LCDString("WIDEFONT"); // print to block 4
  delay(mydelay);

  mylcd.LCDFont(6); // font 6 tiny
  mylcd.LCDgotoXY(0, 5);
  mylcd.LCDString("Tiny font 16wide"); // print to block 5

  delay(mydelay5);
}

// ***** TEST 2 font 7 large 12 * 16 *********
// :NO LOWER CASE LETTERS for  font 7
void Test2(void)
{
  mylcd.LCDClear(0X00); //clear whole screen
  mylcd.LCDFont(7); //font 7
  mylcd.LCDgotoXY(20, 1);
  mylcd.LCDString("TIME");
  mylcd.LCDgotoXY(15, 3); // this font takes two blocks
  mylcd.LCDString("23:04");
  delay(mydelay5);
}

// ***** TEST 3 font 8 huge 16 * 24 *********
// NUMBERS  only + : . /
void Test3(void)
{
  mylcd.LCDClear(0x00);
  mylcd.LCDFont(8);  // font 8 this font takes 3 blocks
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("10:39");
  mylcd.LCDgotoXY(0, 3);
  mylcd.LCDString("4.288");
  delay(mydelay5);
}
// ********** TEST 4 font 9 MEGA font 16 * 32 *********
//  NUMBERS  only + : . /
void Test4(void)
{
  mylcd.LCDClear(0x00);
  mylcd.LCDFont(9);  // font 8 this font takes 4 blocks
  mylcd.LCDgotoXY(0, 1);
  mylcd.LCDString("14.23");
  delay(mydelay5);
}
