#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right 
// RST 1/ CD 2/ DC 3/ DIN 4/ CLK 5 
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);

#define mydelay 1000

void setup() {
  // put your setup code here, to run once:
  
   mylcd.LCDInit(); 
   mylcd.LCDClear();
   //mylcd.LCDsetContrast(0xB1);
}

void loop() {
  // put your main code here, to run repeatedly:
   delay(mydelay);
   mylcd.LCDgotoXY(0,0);
   mylcd.LCDString("Line1");
   delay(mydelay);
   /*
   mylcd.LCDenableSleep();
   delay(mydelay);
   delay(mydelay);
   delay(mydelay);
   mylcd.LCDdisableSleep();
   */
}
