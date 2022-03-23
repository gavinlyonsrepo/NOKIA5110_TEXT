// NOKIA5110_HW_SPI.ino
// HARDWARE SPI
// Test file for NOKIA5110_TEXT showing use most basic use case "HELLO WORLD" at 0,0 with font number one using Hardware SPI on an arduino UNO.
// ***************NB NB NOTE **********************
// Software SPI is the orginal and default setup. For  hardware SPI to work the library must be modified:
// In file NOKIA5110_TEXT.h , SPI HARDWARE SECTION , comment in #define SPIHW_ON, it is commented out by default
//****************************************************
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT

// Include the library
#include <NOKIA5110_TEXT.h>

// LCD Nokia 5110 pinout left to right
// RST / CE / DC / DIN / CLK / VCC /LIGHT / GND
#define RST 2
#define CE 3
#define DC 4
//DIN hardware SPI (UNO 11)  MOSI
//CLK hardware SPI (UNO 13)   SCK

// Create an LCD object
NOKIA5110_TEXT mylcd(RST, CE, DC);

#define inverse  false // set to true to invert display pixel color
#define contrast 0xB2 // default is 0xBF set in LCDinit, Try 0xB1 <-> 0xBF if your display is too dark
#define bias 0x13 // LCD bias mode 1:48: Try 0x12 or 0x13 or 0x14

void setup() {
  delay(100);
  mylcd.LCDInit(inverse, contrast, bias); // init  the lCD
  mylcd.LCDClear(0x00); // Clear whole screen
}

void loop() {
  mylcd.LCDFont(LCDFont_Default); // Set the font
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks) top left corner
  mylcd.LCDString("HELLO WORLD"); // print
  mylcd.LCDgotoXY(0, 2); 
  mylcd.LCDString("HW SPI TEST"); // print
  delay(1000);
}
