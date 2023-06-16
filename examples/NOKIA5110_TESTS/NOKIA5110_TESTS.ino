/*!
	@file NOKIA5110_TESTS.ino
	@brief Test file for NOKIA5110_TEXT showing various functions, software SPI
	@details URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
	@test
		-# TEST 10 Print function, test  print function to print data types.
		-# TEST 11 Writing text to blocks
		-# TEST 12 Clearing by blocks
		-# TEST 13 Sleep mode
		-# TEST 14 Draw some pixel
		-# TEST 15 Draw a horizontal line with SetPixel across screen at row 10
		-# TEST 16 Draw a vertical line in block 2 of one byte at column 3
		-# TEST 17 Fill Screen with a pattern
		-# TEST 18 Fill block with a pattern
		-# TEST 19 Custom Characters display
*/

// Include the library
#include <NOKIA5110_TEXT.h>

// *************** Defines ***************
#define inverse  false
#define contrast 0xB1 // default is 0xBF set in LCDinit, Try 0xB1 <-> 0xBF, if your display is too dark/dim
#define bias 0x12 // LCD bias mode 1:48: Try 0x12 or 0x13 or 0x14 usually

// LCD Nokia 5110 pinout left to right
// RST / CE / DC / DIN / CLK / VCC/ LIGHT / GND
// GPIO setup software SPI
#define RST 2 // Reset pin
#define CE 3 // Chip enable
#define DC 4 // data or command
#define DIN 5 // Serial Data input
#define CLK 6 // Serial clock

// The constructor object, create an instance of the object
NOKIA5110_TEXT mylcd(RST, CE, DC, DIN, CLK);

// TEST delays setup
#define mydelay1  1000
#define mydelay2  2000
#define mydelay5  5000

void setup() {
  delay(50);
  mylcd.LCDInit(inverse, contrast, bias); // init the lCD
  mylcd.LCDClear(0x00); // clear whole screen
  mylcd.LCDFont(LCDFont_Default); // Set the font
}

void loop() {
  Test10();
  Test11();
  Test12();
  Test13();
  Test14();
  Test15();
  Test16();
  Test17();
  Test18();
  Test19();
}

//  TEST 10 Print function
void Test10(void)
{
  int8_t numNeg = -117;
  uint8_t numPos = 47;
  double  myPI = 3.1415926;
  double myEuler = -2.7182818; 
  bool myChoice = true;

  mylcd.LCDgotoXY(0, 0); 
  mylcd.print(numPos);
  mylcd.LCDgotoXY(0, 1);
  mylcd.print(numNeg); 
  mylcd.LCDgotoXY(0, 2);
  mylcd.print(myPI, 4);  // 3.1416
  mylcd.LCDgotoXY(0, 3);
  mylcd.print(myEuler, 2); // -2.72
  mylcd.LCDgotoXY(0, 4);
  mylcd.print(F("Hello World")); // You can pass flash-memory based strings to print() by wrapping them with F() macro
  mylcd.LCDgotoXY(0, 5);
  mylcd.print(myChoice); // 1 for true
  mylcd.LCDgotoXY(10, 5);
  mylcd.print(!myChoice); // 0 for false
  
  delay(mydelay5);
  mylcd.LCDClear(0x00);

  mylcd.LCDgotoXY(0, 0);
  mylcd.print(numPos , DEC); // 47
  mylcd.LCDgotoXY(0, 1);
  mylcd.print(numPos , BIN); // 10111
  mylcd.LCDgotoXY(0, 2);
  mylcd.print(numPos , OCT); // 57
  mylcd.LCDgotoXY(0, 3);
  mylcd.print(numPos , HEX); // 2F
  mylcd.LCDgotoXY(0, 4);
  mylcd.print('Z');
  mylcd.LCDgotoXY(0, 5);
  mylcd.print(myPI, 0); // 3
   
  delay(mydelay5);
  mylcd.LCDClear(0x00);
}


// TEST 11 Writing text to blocks
void Test11(void)
{
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Block 0"); // print to block 0 (0-5 blocks or row bytes)
  delay(mydelay1);
  mylcd.LCDgotoXY(2, 1);
  mylcd.LCDString("Block 1"); // print to block 1 indented by two
  delay(mydelay1);
  mylcd.LCDgotoXY(4, 2);
  mylcd.LCDString("Block 2"); // print to block 2   indented by four
  delay(mydelay1);
  mylcd.LCDgotoXY(6, 3);
  mylcd.LCDString("Block 3"); // print to block 3  indented by six
  delay(mydelay1);
  mylcd.LCDgotoXY(8, 4);
  mylcd.LCDString("Block 4"); // print to block 4 indented by 8 col
  delay(mydelay1);
  mylcd.LCDgotoXY(10, 5);
  mylcd.LCDString("Block 5"); // print to block 5 indented by 10 col
  delay(mydelay1);
}


// TEST 12 Clearing by blocks
void Test12(void)
{
  mylcd.LCDClearBlock(0);  // clear line/block 0
  delay(mydelay1);
  mylcd.LCDClearBlock(5); // clear line/block 5
  delay(mydelay2);
}

// TEST 13 sleep mode
void Test13(void)
{
  mylcd.LCDClear(0x00);

  mylcd.LCDgotoXY(0, 2); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Sleep Mode  ");
  mylcd.LCDgotoXY(0, 3);
  mylcd.LCDString("TEST 5s");
  delay(mydelay2);
  mylcd.LCDenableSleep(); // goto sleep
  delay(mydelay5);
  mylcd.LCDdisableSleep(); // wake up
  mylcd.LCDgotoXY(0, 3); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Sleep Mode  TEST over");
  delay(mydelay2);
}

// TEST 14 Draw some pixel
void Test14(void)
{
  mylcd.LCDClear(0x00);

  mylcd.LCDgotoXY(0, 5); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Draw Pixels"); // print to block 0 (0-5 blocks or row bytes)
  delay(mydelay1);
  mylcd.LCDSetPixel(82, 1);
  for (uint8_t Pixels = 11  ; Pixels < 255 ; Pixels++)
  {
    mylcd.LCDSetPixel(Pixels / 5, Pixels / 10);
    delay(10);
  }
}
// TEST 15 Draw a horizontal line with SetPixel across screen
void Test15(void)
{
  mylcd.LCDClear(0x00);
  mylcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks)
  mylcd.LCDString("Draw Lines"); // print to block 0 (0-5 blocks or row bytes)
  delay(mydelay1);
  for (uint8_t col = 3 ; col < 71 ; col++)
  {
    mylcd.LCDSetPixel(col, 23);
    mylcd.LCDSetPixel(col, 31);
  }
  delay(mydelay2);
}

// TEST 16 Draw two vertical lines of one byte high
void Test16(void)
{
  mylcd.LCDgotoXY(3, 3);
  mylcd.LCDSPIWrite(LCD_DATA, 0xFF);
  mylcd.LCDgotoXY(70, 3);
  mylcd.LCDSPIWrite(LCD_DATA, 0xFF);
  delay(mydelay2);
}

// TEST 17 Fill whole with Screen with pattern
void Test17(void)
{
  mylcd.LCDClear(0x00);
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("Fill Screen");
  delay(mydelay1);

  mylcd.LCDClear(0xBA); // pattern 0b10111010
  delay(mydelay5);
}

// Test 18 Fill block
void Test18(void)
{
  mylcd.LCDClear(0X00);
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("Fill block");
  delay(mydelay1);

  mylcd.LCDFillBlock(0xAB, 4); // 0b10101011
  delay(mydelay5);
}

// Test 19 Custom characters
void Test19(void)
{
  // Custom Characters for  TEST 9 Custom Character. data vertical addressed 
  const unsigned char power[13] = {0xff, 0xe7, 0xc3, 0x99, 0xa5, 0xad, 0xad, 0xa5, 0x99, 0xc3, 0xe7, 0xff}; //power icon
  const unsigned char myspeed[13] = {0xff, 0xff, 0xf7, 0xb3, 0xd1, 0xc0, 0xe0, 0xf4, 0xf6, 0xfe, 0xff, 0xff}; //lighting symbol
  
  mylcd.LCDClear(0X00);
  delay(mydelay1);
  mylcd.LCDgotoXY(0, 0);
  mylcd.LCDString("Custom char");
  mylcd.LCDgotoXY(40, 2);
  mylcd.LCDCustomChar(power, sizeof(power) / sizeof(unsigned char), LCDPadding_Both, false);
  mylcd.LCDgotoXY(20, 4);
  mylcd.LCDCustomChar(myspeed, sizeof(myspeed) / sizeof(unsigned char), LCDPadding_Both, false);
  delay(mydelay5);
  mylcd.LCDClear(0x00);
  delay(mydelay1);
}
