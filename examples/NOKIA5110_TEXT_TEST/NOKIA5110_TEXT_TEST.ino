// Test file for NOKIA5110_TEXT showing use of font one, sleep mode and clear line/screen.
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT 
#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right
// RST 1/ CD 2/ DC 3/ DIN 4/ CLK 5
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);
#define inverse  false
#define contrast 0xBE // default is 0xBF set in LCDinit, Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
#define bias 0x14 // LCD bias mode 1:48: Try 0x13 or 0x14
#define FontNumber 1

//TEST setup
#define mydelay 1000
boolean sleepmodetest = false;
boolean clearline = true; //will delete block 0 and 5 before full screen

void setup() {
  mylcd.LCDInit(inverse, contrast, bias); //init the lCD passed inverse true or false
  mylcd.LCDClear(); //clear whole screen
  mylcd.LCDFont(FontNumber); //use Font One default
}

void loop() {
  
  //TEST 1 writing text to blocks 
  delay(mydelay);
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Block 0"); //print to block 0 (0-5 blocks or row bytes)
  delay(mydelay);
  mylcd.LCDgotoXY(2, 1); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Block 1"); //print to block 1 indented by two  
  delay(mydelay);
  mylcd.LCDgotoXY(4, 2); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Block 2"); //print to block 2   indented by four 
  delay(mydelay);
  mylcd.LCDgotoXY(6, 3); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Block 3"); //print to block 3  indented by six 
  delay(mydelay);
  mylcd.LCDgotoXY(8, 4);
  mylcd.LCDString("Block 4"); //print to block 4 indented by 8 col
  delay(mydelay);
  mylcd.LCDgotoXY(10, 5);
  mylcd.LCDString("Block 5"); //print to block 5 indented by 10 col
  delay(mydelay);
  

  
  // TEST 2 clearing by  blocks 
  if (clearline == true)
  {
    mylcd.LCDClearBlock(0);  //clear line/block 1
    delay(mydelay);
    mylcd.LCDClearBlock(5); //clear line 5
    delay(mydelay);
  }

  //TEST 3 sleep mode
  if (sleepmodetest  ==  true)
  {
    mylcd.LCDenableSleep(); //goto sleep
    delay(mydelay);
    delay(mydelay);
    mylcd.LCDdisableSleep(); //wake up
    delay(mydelay);
  }
   //TEST 4 whole screen clear
  delay(mydelay);
  mylcd.LCDClear();
}

