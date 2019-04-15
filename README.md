Overview
--------------------
* Name : NOKIA5110_TEXT
* Title : Library for Nokia 5110 LCD (PCD8544 controller) for the Arduino eco-system
* Description : Arduino library,  ASCII character text only (12 * 6 ) 72 characters in total, Sleep mode, minimalist. Single font. Example program(tested on UNO) uses 1874 bytes (5%) of program storage space. Maximum is 32256 bytes.
Global variables use 22 bytes (1%) of dynamic memory, leaving 2026 bytes for local variables. Maximum is 2048 bytes.

* Author: Gavin Lyons
* Arduino 1.8.5

Features
-------------------------
The Nokia 5110 is a basic graphic LCD screen for lots of applications. It was originally intended to be used as a cell phone screen. It uses the PCD8544 controller, which is the same used in the Nokia 3310 LCD. The PCD8544 is a low power CMOS LCD controller/driver, designed to drive a graphic display of 48 rows and 84 columns. All necessary functions for the display are provided in a single chip, including on-chip generation of LCD supply and bias voltages, resulting in a minimum of external components and low power consumption. The PCD8544 interfaces to microcontrollers through a serial bus interface(SPI).

GPIO function on PIC, 5 Nokia 5110 LCD lines SPI bus.

| Arduino    | Nokia 5110 LCD |
| ------ | ------ |
| Digital GPIO | LCD_CLK Pin 5 clock in |
| Digital GPIO | LCD_DIN Pin 4 data in |
| Digital GPIO | LCD_DC Pin 3 data/command|
| Digital GPIO | LCD_CE Pin 2 chip enable |
| Digital GPIO | LCD_RST Pin 1 reset|

Arduino library,  ASCII character text only(12 * 6) 72 characters in total, Sleep mode, minimalist. Single font.

The library uses bit-banging rather than importing SPI libraries.

Example program(tested on UNO) uses 1874 bytes (5%) of program storage space. Maximum is 32256 bytes.
Global variables use 22 bytes (1%) of dynamic memory, leaving 2026 bytes for local variables. Maximum is 2048 bytes.

This compares to Adafruit text based library example of 20% and 38% for program storage and global variables respectively. 

The library has main 3 files (NOKIA5110_TEXT.cpp  NOKIA5110_TEXT.h and NOKIA5110_TEXT_FONT.h).

The screen is 84  X 48 pixels. The X-Axis has 84 columns.
The Y_Axis(rows) the 48 pixels are divided into 6 row blocks. 
Each block containing one byte of pixels. 6 * 8 = 48.

| Block number   | Pixel number Y axis|
| ------ | ------ |
| Block 0 | 0-7 |
| Block 1 | 8-15 |
| Block 2 | 16-23|
| Block 3 | 24-31 |
| Block 4 | 32-39 |
| Block 5 | 40-47 |

The ASCII library in font file: Each character is 5 pixel wide. Plus one pixel of empty space on each side.
Also each character is a byte of pixels in height.
So each character is in a 7 by 8 pixel block. So you can fit (84/7) 12 characters across columns and with (48/8) 6 row blocks that gives 72 characters in total (12X06).

Functions
----------------------------------------

Construct of the class object from left to right pin 1-5(LCD)
RST pin 1, CD pin 2, DC pin 3, DIN pin 4, CLK pin 5  

1. NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC, uint8_t LCD_DIN, uint8_t LCD_CLK)


This sends the  commands to the PCD8544 to init LCD

2. LCDInit()

gotoXY routine to position cursor,  x - range: 0 to 84 (0 to 0x53), 
y - range: 0 to 5 ( 6 blocks one byte each 6 * 8 = 48

3. LCDgotoXY(uint8_t , uint8_t);

Clears the LCD by writing zeros to the entire screen

4. LCDClear(void)

There are two  banks in the LCD, data and commands. 
This function sets the DC pin high or low depending, and then sends
the data byte The first byte is one(data) or zero(cmd) , second byte data

5. LCDWrite(unsigned char , unsigned char);

Given a string of characters, one by one is passed to the LCD

6. LCDString(const char * characters);

Function to set contrast passed a byte , default BF.
 Set LCD VOP Contrast, range = ((0x00-0x7F) |0x80) , 0xB5 = (0x35|0x80) try B1 - BF normally. 

7. LCDsetContrast(uint8_t )

8. LCDenableSleep()
9. LCDdisableSleep()


Function Clears a block(block of rows, one byte) passed block number 0-5 
More efficient than clearing whole screen.

10. LCDClearBlock(uint8_t)


Installation
------------------------------

[Installing Additional Arduino Libraries guide](https://www.arduino.cc/en/Guide/Libraries)

Pictures
---------------------------

![ScreenShot pic](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA.jpg)

![ScreenShot pic2](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA2.jpg)


