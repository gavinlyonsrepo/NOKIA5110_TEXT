// Example file name : NOKIA5110_TEXT_TEST.ino
// Description:
// Test file for NOKIA5110_TEXT showing use of font one, sleep mode and clear line/screen, pixel tests,
// Fill , Fill block, custom character, Fonts and Bitmap.
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT

//INclude the library
#include <NOKIA5110_TEXT.h>

// *************** Defines ****************
#define inverse  false
#define contrast 0xB4 // default is 0xBF set in LCDinit, Try 0xB1 - 0xBF, if your display is too dark
#define bias 0x12 // LCD bias mode 1:48: Try 0x12 or 0x13 or 0x14 usually
#define FontNumber 1 //1-9, 1 is default ,  Change define in NOKIA5110_TEXT.h if using non default

#define RST 2 // Reset pin
#define CE 3  //Chip enable
#define DC 4 // data or command
#define DIN 5 // Serial Data input
#define CLK 6 // Serial clock

// The constructor object, create an instance of the object
//LCD Nokia 5110 pinout left to right
NOKIA5110_TEXT mylcd(RST, CE, DC, DIN, CLK);


// TEST setup
#define mydelay 2000
#define mydelay5 5000

//Custom Characters for  TEST 9 Custom Character
const unsigned char power[12] = {0xff, 0xe7, 0xc3, 0x99, 0xa5, 0xad, 0xad, 0xa5, 0x99, 0xc3, 0xe7, 0xff}; //power icon
const unsigned char myspeed[12] = {0xff, 0xff, 0xf7, 0xb3, 0xd1, 0xc0, 0xe0, 0xf4, 0xf6, 0xfe, 0xff, 0xff}; //lighting symbol

void setup() {
  mylcd.LCDInit(inverse, contrast, bias); // init the lCD
  mylcd.LCDClear(0x00); //clear whole screen
  mylcd.LCDFont(FontNumber); // Set the font
}

void loop() {

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
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();
  Test8();
  Test9();
  mylcd.LCDClear(0x00);
  delay(mydelay);
}

//TEST 1 writing text to blocks
void Test1(void)
{
  delay(mydelay);
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Block 0"); //print to block 0 (0-5 blocks or row bytes)
  delay(mydelay);
  mylcd.LCDgotoXY(2, 1);
  mylcd.LCDString("Block 1"); //print to block 1 indented by two
  delay(mydelay);
  mylcd.LCDgotoXY(4, 2);
  mylcd.LCDString("Block 2"); //print to block 2   indented by four
  delay(mydelay);
  mylcd.LCDgotoXY(6, 3);
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
void Test2(void)
{
  mylcd.LCDClearBlock(0);  //clear line/block 0
  delay(mydelay);
  mylcd.LCDClearBlock(5); //clear line/block 5
  delay(mydelay);
}

//TEST 3 sleep mode
void Test3(void)
{
  mylcd.LCDClear(0x00);

  mylcd.LCDgotoXY(0, 2); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Sleep Mode  ");
  mylcd.LCDgotoXY(0, 3);
  mylcd.LCDString("TEST 10s");
  delay(mydelay);
  mylcd.LCDenableSleep(); //goto sleep
  delay(mydelay5);
  delay(mydelay5);
  mylcd.LCDdisableSleep(); //wake up
  mylcd.LCDgotoXY(0, 3); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Sleep Mode  TEST over");
  delay(mydelay);

}

// TEST 4 Draw some pixel
void Test4(void)
{
  mylcd.LCDClear(0x00);

  mylcd.LCDgotoXY(0, 5); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Draw Pixels"); //print to block 0 (0-5 blocks or row bytes)
  delay(mydelay);

  for (uint8_t Pixels = 11  ; Pixels < 255 ; Pixels++)
  {
    mylcd.LCDSetPixel(Pixels / 5, Pixels / 10);
    delay(25);
  }
}
// TEST 5 Draw a horizontal line with SetPixel across screen
void Test5(void)
{
  mylcd.LCDClear(0x00);
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Draw Lines"); //print to block 0 (0-5 blocks or row bytes)
  delay(mydelay);

  for (uint8_t col = 3 ; col < 71 ; col++)
  {
    mylcd.LCDSetPixel(col, 23);
    mylcd.LCDSetPixel(col, 31);
  }
  delay(mydelay);
}

// TEST 6 Draw a vertical line in block 2 of one byte at column 3
void Test6(void)
{
  mylcd.LCDgotoXY(3, 3);
  mylcd.LCDWrite(LCD_DATA, 0xFF);
  mylcd.LCDgotoXY(70, 3);
  mylcd.LCDWrite(LCD_DATA, 0xFF);
  delay(mydelay);
}

// TEST 7 Fill whole with Screen with pattern
void Test7(void)
{
  mylcd.LCDClear(0x00);
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("Fill Screen");
  delay(mydelay);

  mylcd.LCDClear(0xBA); //  pattern 0b10111010
  delay(mydelay5);

}

// Test 8 fill block
void Test8(void)
{
  mylcd.LCDClear(0X00);
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("Fill block");
  delay(mydelay);

  mylcd.LCDFillBlock(0xAB, 4); //  0b10101011
  delay(mydelay5);
}

//Test 9 Custom characters
void Test9(void)
{
  mylcd.LCDClear(0X00);
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("Custom char");
  mylcd.LCDgotoXY(40, 2);
  mylcd.LCDCustomChar(power, sizeof(power) / sizeof(unsigned char), 0x03, false);
  mylcd.LCDgotoXY(40, 4);
  mylcd.LCDCustomChar(myspeed, sizeof(myspeed) / sizeof(unsigned char), 0x03, false);
  delay(mydelay5);

}
