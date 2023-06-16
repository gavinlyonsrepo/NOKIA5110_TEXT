/*!
	@file NOKIA5110_HELLOWORLD.ino
	@brief Test file for NOKIA5110_TEXT showing use most basic use case "HELLO WORLD" at 0,0 with font number one, software SPI.(defaults) for arduino UNO
	@details URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
	@test
		-# Test 0 Display Hello world  
*/

// Include the library
#include <NOKIA5110_TEXT.h>

// LCD Nokia 5110 pinout left to right
// RST / CE / DC / DIN / CLK / VCC /LIGHT / GND
#define RST 2
#define CE 3
#define DC 4
#define DIN 5
#define CLK 6

// Create an LCD object
NOKIA5110_TEXT mylcd(RST, CE, DC, DIN, CLK);

#define inverse  false // set to true to invert display pixel color
#define contrast 0xB2 // default is 0xBF set in LCDinit, Try 0xB1 <-> 0xBF if your display is too dark/dim
#define bias 0x13 // LCD bias mode 1:48: Try 0x12 or 0x13 or 0x14


void setup() {
  delay(50);
  mylcd.LCDInit(inverse, contrast, bias); // init  the lCD
  mylcd.LCDClear(0x00); // Clear whole screen
}

void loop() {
  mylcd.LCDFont(LCDFont_Default); // Set the font
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks) top left corner
  mylcd.LCDString("HELLO WORLD"); // print
  delay(5000);
}
