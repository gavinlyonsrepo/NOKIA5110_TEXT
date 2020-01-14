// Test file for NOKIA5110_TEXT showing use of font two.
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT 

#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right
// RST 1/ CD 2/ DC 3/ DIN 4/ CLK 5
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);

#define inverse  false
#define UseDefaultFont  false
#define contrast 0xBF // default is 0xBF set in LCDinit, Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
#define bias 0x14 // LCD bias mode 1:48: Try 0x13 or 0x14

//TEST setup
#define mydelay 1000

void setup() {
  mylcd.LCDInit(inverse, contrast, bias); //init the lCD passed inverse true or false
  mylcd.LCDClear(); //clear whole screen
  mylcd.LCDFont(UseDefaultFont ); //use Font two
}

void loop() {

  //TEST 1 writing text to blocks
  delay(mydelay);
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("VOLTAGE:"); //print to block 0 (0-5 blocks or row bytes)
  delay(mydelay);
  mylcd.LCDgotoXY(0, 1); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("5.84 "); //print to block 1 indented by two
  delay(mydelay);

}
