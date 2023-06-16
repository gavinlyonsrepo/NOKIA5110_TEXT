/*!
	@file NOKIA5110_FONTS.ino
	@brief Test file for NOKIA5110_TEXT showing all 9 fonts. 1-9, software SPI
	@note
		 -# There are Nine fonts , font one is default,
		 -# For a non-default font to work , One line in the library header file
		 -# called "NOKIA5110_TEXT_FONT_DATA.h"  Must be modified by USER
		 -# the Define statement at start of file for Font X must be commented IN.
		 -# define NOKIA5110_FONT_X where X is name of font in  FONT DEFINE SECTION.
		 -# Tests will  not work fully if non-default fonts are not commented in, nothing will appear.
		 -# For all this example file to work fully all fonts must be commented in
	@details URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
	@test
		-# TEST 1 font 1-6, X by 8 fonts 
		-# TEST 2 font 7, 12 by 16 font
		-# TEST 3 font 8, 16 by 24  font
		-# TEST 4 font 9, 16 by 32 font
*/

// Include the library.
#include <NOKIA5110_TEXT.h>

// LCD Nokia 5110 pinout left to right , software SPI
// RST / CE / DC / DIN / CLK / VCC / LIGHT / GND

#define RST 2 // Reset pin
#define CE 3 // Chip enable
#define DC 4 // data or command
#define DIN 5 // Serial Data input
#define CLK 6 // Serial clock

// Create an LCD object
NOKIA5110_TEXT mylcd(RST, CE, DC, DIN, CLK);

#define inverse  false
#define contrast 0xBF // default is 0xBF set in LCDinit, Try 0xB1 - 0xBF if your display is too dark/dim
#define bias 0x12 // LCD bias mode 1:48: Try 0x12, 0x13 or 0x14

// TEST delays
#define mydelay 1000
#define mydelay5 5000

// ********** SETUP **********
void setup() {
  delay(50);
  mylcd.LCDInit(inverse, contrast, bias); // init the lCD
  mylcd.LCDClear(); // clear whole screen
  mylcd.LCDFont(LCDFont_Default); // Font 1 default
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("Fonts tests");
  mylcd.LCDgotoXY(0, 1);
  mylcd.LCDString("READ Note in");
  mylcd.LCDgotoXY(0, 2);
  mylcd.LCDString("example file");
  delay(mydelay5);
}

// *********** MAIN LOOP ***********
void loop() {
  Test1();
  Test2();
  Test3();
  Test4();
}

// ******** TEST 1 writing the first six fonts( X by 8) 1-6 ********
void Test1(void)
{
  mylcd.LCDClear(0X00); // clear whole screen

  mylcd.LCDFont(LCDFont_Default); // font 1 default
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Default Font"); // print to block 0
  delay(mydelay);

  mylcd.LCDFont(LCDFont_Thick); // font 2 thick: NO LOWER CASE LETTERS
  mylcd.LCDgotoXY(0, 1);
  mylcd.LCDString("THICKFONT"); // print to block 1
  delay(mydelay);

  mylcd.LCDFont(LCDFont_HomeSpun); // font 3 Homespun
  mylcd.LCDgotoXY(0, 2);
  mylcd.LCDString("HOMESPUN2"); // print to block 2
  delay(mydelay);

  mylcd.LCDFont(LCDFont_Seven_Seg); // font 4 seven segment
  mylcd.LCDgotoXY(0, 3);
  mylcd.LCDString("7 Segment font"); // print to block 3
  delay(mydelay);

  mylcd.LCDFont(LCDFont_Wide); // font 5 wide :NO LOWER CASE LETTERS
  mylcd.LCDgotoXY(0, 4);
  mylcd.LCDString("WIDEFONT"); // print to block 4
  delay(mydelay);

  mylcd.LCDFont(LCDFont_Tiny); // font 6 tiny
  mylcd.LCDgotoXY(0, 5);
  mylcd.LCDString("Tiny font 16wide"); // print to block 5

  delay(mydelay5);
}

// ******** TEST 2 font 7 large 12 * 16 ********
// NO LOWER CASE LETTERS for font 7
void Test2(void)
{
  mylcd.LCDClear(0X00); // clear whole screen
  mylcd.LCDFont(LCDFont_Large); // font 7
  mylcd.LCDgotoXY(20, 1);
  mylcd.LCDString("TIME");
  mylcd.LCDgotoXY(15, 3); // this font takes two blocks
  mylcd.LCDString("23:04");
  delay(mydelay5);
}

// ******** TEST 3 font 8 huge 16 * 24 ********
// NUMBERS only + : . /
void Test3(void)
{
  mylcd.LCDClear(0x00);
  mylcd.LCDFont(LCDFont_Huge);  // font 8 this font takes 3 blocks
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("10:39");
  mylcd.LCDgotoXY(0, 3);
  mylcd.LCDString("4.288");
  delay(mydelay5);
}
// ******** TEST 4 font 9 MEGA font 16 * 32 ********
// NUMBERS only + : . /
void Test4(void)
{
  mylcd.LCDClear(0x00);
  mylcd.LCDFont(LCDFont_Mega);  // font 9, this font takes 4 blocks
  mylcd.LCDgotoXY(0, 1);
  mylcd.LCDString("14.23");
  delay(mydelay5);
}
