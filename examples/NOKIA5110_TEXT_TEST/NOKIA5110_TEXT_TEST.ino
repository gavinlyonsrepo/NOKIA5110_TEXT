#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right 
// RST 1/ CD 2/ DC 3/ DIN 4/ CLK 5 
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);

#define mydelay 1000

void setup() {
   mylcd.LCDInit();  //init the lCD
   mylcd.LCDClear(); //clear whole screen
   //mylcd.LCDsetContrast(0xB1); // default is 0xBF set in init
}

void loop() {
   delay(mydelay);
   mylcd.LCDgotoXY(0,0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
   mylcd.LCDString("Block 0"); //print to block 0 (0-5 blocks or row bytes)
   delay(mydelay);
   mylcd.LCDgotoXY(4,5);
   mylcd.LCDString("Block 5"); //print to block 5 indented by 4 col
   delay(mydelay);
   mylcd.LCDClearBlock(0);  //clear line/block 1
   delay(mydelay);
   mylcd.LCDClearBlock(5); //clear line 5
   delay(mydelay);
   
   mylcd.LCDenableSleep(); //goto sleep
   delay(mydelay);
   delay(mydelay);
   mylcd.LCDdisableSleep(); //wake up
   delay(mydelay);
}
