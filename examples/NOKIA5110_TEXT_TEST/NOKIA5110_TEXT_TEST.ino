// NOKIA5110_TEXT_TEST.ino
// Test file for NOKIA5110_TEXT showing use of font one, sleep mode and clear line/screen, pixel tests, Fill , Fill block, and custom character
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right
// RST 2/ CD 3/ DC 4/ DIN 5/ CLK 6
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);
#define inverse  false
#define contrast 0xB2 // default is 0xBF set in LCDinit, Try 0xB1(good @ 3.3V) <-> 0xBF if your display is too dark
#define bias 0x14 // LCD bias mode 1:48: Try 0x13 or 0x14
#define FontNumber 1 //1-6, 1 is default ,  Change define in NOKIA5110_TEXT.h if using non default

// TEST setup
#define mydelay 2000
boolean drawtext = true; //enable  TEST 1
boolean clearline = true; //enable  TEST 2
boolean sleepmodetest = true;// enable TEST 3
boolean pixeltest = true; // enable TEST 4 5 6


//Custom Characters for  test 9 
  unsigned char power[12] = {0xff, 0xe7, 0xc3, 0x99, 0xa5, 0xad, 0xad, 0xa5, 0x99, 0xc3, 0xe7, 0xff}; //power icon
  unsigned char myspeed[12] = {0xff, 0xff, 0xf7, 0xb3, 0xd1, 0xc0, 0xe0, 0xf4, 0xf6, 0xfe, 0xff, 0xff}; //lighting symbol
  
void setup() {
  mylcd.LCDInit(inverse, contrast, bias); //init the lCD
  mylcd.LCDClear(); //clear whole screen
  mylcd.LCDFont(FontNumber); //
}


/* TESTS
1. TEST 1 writing text to blocks
2. TEST 2 clearing by  blocks
3. TEST 3 sleep mode
4. TEST 4 Draw some pixel
5. TEST 5 Draw a horizontal line with SetPixel across screen at row 10 
6. TEST 6 Draw a vertical line in block 2 of one byte at column 3  
7. TEST 7 Fill Screen
8. TEST 8 Fill block
9. TEST 9 Custom Character
*/

void loop() {

  //TEST 1 writing text to blocks
  if (drawtext == true)
  {
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
  }


  // TEST 2 clearing by  blocks
  if (clearline == true)
  {
    mylcd.LCDClearBlock(0);  //clear line/block 0
    delay(mydelay);
    mylcd.LCDClearBlock(5); //clear line/block 5
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

  //whole screen clear
  delay(mydelay);
  mylcd.LCDClear();
  delay(mydelay);


  if (pixeltest  ==  true)
  {
    // TEST 4 Draw some pixel
    mylcd.LCDSetPixel(5, 10);
    delay(mydelay);
    mylcd.LCDSetPixel(40, 22);
    delay(mydelay);
    mylcd.LCDSetPixel(75, 30);
    delay(mydelay);
    delay(mydelay);

    // TEST 5 Draw a horizontal line with SetPixel across screen 
    for (uint8_t col = 0 ; col < 83 ; col++)
    {
      mylcd.LCDSetPixel(col, 8);
    }
    delay(mydelay);
    
    // TEST 6 Draw a vertical line in block 2 of one byte at column 3  
    mylcd.LCDgotoXY(3, 2);
    mylcd.LCDWrite(LCD_DATA, 0xFF);
    delay(mydelay);
  }

  // TEST 7 Fill whole with Screen with pattern 
  mylcd.LCDClear(0xF2);
  delay(mydelay);
  mylcd.LCDClear();
  
  // Test 8 fill block
  mylcd.LCDgotoXY(0, 1);
  mylcd.LCDFillBlock(0x0F);
  delay(mydelay);

  //Test 9 
   mylcd.LCDgotoXY(0, 3);
   mylcd.LCDCustomChar(power, sizeof(power) / sizeof(unsigned char), 0x03, false);
   mylcd.LCDCustomChar(myspeed, sizeof(myspeed) / sizeof(unsigned char), 0x03, false);
   delay(mydelay);
   
  //whole screen clear again
  mylcd.LCDClear();
  delay(mydelay);
}
