![ pcb ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Output](#output)
  * [Installation](#installation)
  * [Features](#features)
  * [Hardware](#hardware)
  * [Fonts](#fonts)
  * [Functions](#functions)
  * [Memory](#memory)
  * [Tested Boards(#tested-boards)
  
Overview
--------------------
* Name : NOKIA5110_TEXT
* Title : Library for Nokia 5110 LCD (PCD8544 controller) for the Arduino eco-system
* Description : 

1. Arduino library.      ]
2. Inverse, Bias and contrast control. 
3. ASCII strings and character text display.
4. Eight different ASCII text fonts. 
5. Sleep mode.
6. Designed to be light weight, low memory footprint. see memory section.
7. Custom characters and bitmap supported
8. No graphics buffer to reduce memory footprint but 
basic graphics can be created using custom characters, pixels, block patterns , lines.
 
* Author: Gavin Lyons
* Arduino IDE: 1.8.5
* Tested: UNO, NANO v3 and ESP8266 Nodemcu ESP-12e v0.1

Output
---------------------------------

Output Screenshots, From left to right top to bottom.

1. Custom characters, [Website to create them](https://javl.github.io/image2cpp/) .
2. Font 7 "Large"
3. Half bitmap + Font 7 "large"
4. Full Bitmap 
5. Output showing first 6 (8 by X) fonts, #1-6, one font in each row block:
6. Font 8 "Huge" 

![ font pic 1 ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT1.jpg)

![ font pic 2 ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT2.jpg)

![ font pic 3 ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT_ALL.jpg)


Installation
------------------------------

The library is included in the official Arduino library manger and the optimum way to install it 
is using the library manager which can be opened by the *manage libraries* option in Arduino IDE. 
Search "Nokia" in search bar of library manager to find it.

See link below for instruction for this and for the other methods too.

[Installing Additional Arduino Libraries guide](https://www.arduino.cc/en/Guide/Libraries)


Features
-------------------------
The Nokia 5110 is a basic LCD screen for lots of applications. 
It was originally intended to be used as a mobile phone screen. 
It uses the PCD8544 controller, which is the same used in the Nokia 3310 LCD. 
The PCD8544 is a low power CMOS LCD controller/driver, designed to drive a graphic display of 48 rows and 84 columns.
All necessary functions for the display are provided in a single chip, including on-chip generation of LCD supply and bias voltages,
resulting in a minimum of external components and low power consumption. 
The PCD8544 interfaces to microcontrollers through a serial bus interface(SPI).
The library uses bit-banging rather than importing SPI libraries.
The library has 10 src files (NOKIA5110_TEXT.cpp  NOKIA5110_TEXT.h and 8 font header files).
The library has 5 examples files.

The screen is 84 X 48 pixels. The X-Axis has 84 columns.
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

Hardware 
---------------------------

GPIO function on Arduino, 5 Nokia 5110 LCD lines SPI bus.
The example files use Pin D2-RST <.....> D6-CLK.

| Arduino    | Nokia 5110 LCD |
| ------ | ------ |
| Digital GPIO | LCD_CLK Pin 5 clock in |
| Digital GPIO | LCD_DIN Pin 4 data in |
| Digital GPIO | LCD_DC Pin 3 data/command|
| Digital GPIO | LCD_CE Pin 2 chip enable |
| Digital GPIO | LCD_RST Pin 1 reset|

Pinout of a Nokia 5110 LCD.

![ pinout ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_PINOUT.jpg)

The LCD Vcc runs at 3.3V. The signal lines run at 3.3V level so you'll need to use voltage level shifting/dropping to use with safely with  5V microcontroller.

Fonts 
---------------------------

There are 8 fonts.
By default only Font 1 is commented in and ready to go.
So to use a non-default Font (2-8), two steps to complete

1. Comment in the respective define at top of library header file NOKIA5110_TEXT.h in the FONT DEFINE SECTION.
2. Call LCDFont function and pass it number of respective font.

Only include what fonts you want in order to keep program size as small as possible.
Each font is a header file, NOKIA5110_FONT_X.h where X is number of Font(1-8)

**Font table**

| Font num | Font name | Pixel size | total characters | blocks used |
| ------ | ------ | ------ | ------ | ----- |
| 1 | Default | 5x8 | (84/5+2) * (48/8) = 72 | 1 |
| 2 | Thick   | 7x8 | (84/7+2) * (48/8)  = 54 |  1 |
| 3 | Aurebesh | 5x8 | (84/5+2) * (48/8)  = 72 | 1 |
| 4 | Seven segment | 4x8 | (84/4+2) * (48/8) = 84 | 1 |
| 5 | Wide | 8x8 | (84/8+2) * (48/8) = 48 | 1 |
| 6 | Tiny | 3x8 | (84/3+2) * (48/8) = 96  | 1 |
| 7 | Large | 12x16 | (84/12) * (48/16) = 21 | 2 |
| 8 | Huge | 16x24 | (84/16) * (48/24) = 10  | 3| 

| Font num | Font file  | Font define  | Note |
| ------ | ------ | ------ | ------ | 
| 1 | NOKIA5110_FONT.h | NOKIA5110_FONT_1 | --- |
| 2 | NOKIA5110_FONT_TWO.h | NOKIA5110_FONT_2 | no lowercase letters |
| 3 | NOKIA5110_FONT_THREE.h | NOKIA5110_FONT_3 | --- | 
| 4 | NOKIA5110_FONT_FOUR.h | NOKIA5110_FONT_4 | --- |
| 5 | NOKIA5110_FONT_FIVE.h | NOKIA5110_FONT_5 |  no lowercase letters |
| 6 | NOKIA5110_FONT_SIX.h | NOKIA5110_FONT_6 | --- |
| 7 | NOKIA5110_FONT_FIVE.h | NOKIA5110_FONT_7 | no lowercase letters |
| 8 | NOKIA5110_FONT_SIX.h | NOKIA5110_FONT_8 | Numbers + : . only |

Note:
For fonts 1-6 Each character is a byte of pixels in height(Y). One pixel of empty space on each side 
is added by code. So a 5x8 (XxY) pixel character is in reality 7x8. 
Each of the first six rowblock is one byte height. So to get total number of characters,
divide screen width ( 84 ) by number of characters across and multiple by number of rowblocks,
 ( 6, 3 or 2 ) 6 in this case.
For example with "default" is a 5x8 pixel font with the two blank spaces its 7x8 for each character, 
So (84/7) = 12 characters across columns. 
There are (48/8) = 6 row blocks that gives (12 x 06) = 72 characters in total.
Total characters = (Screen Width/Character length  + padding) X (Screen height/Character height).

Functions
----------------------------------------
 
Look in the NOKIA5110_TEXT.h header file at the function headers  for more detailed information.
 
1. NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC, uint8_t LCD_DIN, uint8_t LCD_CLK)

Construct of the class object from left to right pin 1-5(LCD)
RST pin 1, CD pin 2, DC pin 3, DIN pin 4, CLK pin 5 

2. LCDInit(bool Inverse, uint8_t Contrast, uint8_t Bias )

This sends the  commands to the PCD8544 to init LCD. Inverse inverts the
display. Contrast, This value allows us to change LCD's contrast Try B0 to BF.
The Bias Value is for system biasing, try about 0x13-0X14


3. LCDgotoXY(uint8_t , uint8_t)

gotoXY routine to position cursor,  x - range: 0 to 84 (0 to 0x53), 
y - range: 0 to 5 ( 6 blocks one byte each 6 * 8 = 48

4. LCDClear(uint8_t )

Clears the LCD by writing zeros to the entire screen.
Default is zero but can be passed a fill pattern

5. LCDWrite(unsigned char , unsigned char)

There are two  banks in the LCD, data and commands. 
This function sets the DC pin high or low depending, and then sends
the data byte The first byte is one(data) or zero(cmd) , second byte data.
prints the byte down from current position , It is used internally 
to draw cols of characters it can be used to create vertical lines or patterns.

6. LCDString(const char * characters);

Given a string of characters, one by one is passed to the LCD
The library can only take in characters and strings so if the user wants to display numbers (ints, floats)
They must be converted or parsed first, there is an example file "NOKA5110_TEXT_DHT11.ino" 
which shows one way to do this with floats.

7. LCDsetContrast(uint8_t )

Function to set contrast passed a byte , default BF.
Set LCD VOP Contrast, range = ((0x00-0x7F) |0x80) , 0xB5 = (0x35|0x80) try B1 - BF normally.

8. LCDenableSleep()
9. LCDdisableSleep()

10. LCDClearBlock(uint8_t)

Function Clears a block(block of rows, one byte) passed block number 0-5 
More efficient than clearing whole screen

11. LCDFont(uint8_t)

Set the font, 3 choices 1 = font 1 , 2 = font 2,  3 = font 3. 
default is 1. Fonts can be changed on the fly but non-default fonts must be included
by commenting in the relevant Define statement at top of library header .h file.
 
12. LCDCharacter(char character)

Prints a character to screen.

13. LCDSetPixel(uint8_t, uint8_t)

Passed Col and row position of a pixel , can be used to set a individual pixel
Can be used to create simple graphics like lines, boxes.

14. LCDFillBlock(uint8_t  , uint8_t)

Can be used to fill a row with a pattern.

15. LCDCustomChar(unsigned chararray, uint16_t, uint8_t , bool  )

Can be used to create custom characters and Bitmaps.


Memory
---------------------------

Memory usage data from an Arduino UNO.

1. NOKIA5110_HELLOWORLD sketch, Font 1 "default".

Sketch uses 1956 bytes (6%) of program storage space and 32 bytes (1%) of dynamic memory.

2. NOKIA5110_HELLOWORLD sketch, Font 6 "tiny".

Sketch uses 1772 bytes (5%) of program storage space and 32 bytes (1%) of dynamic memory.

3. NOKIA5110_HELLOWORLD  sketch ,Font 6 "large".

Sketch uses 2988 bytes (9%) of program storage space and 32 bytes (1%) of dynamic memory.

All fonts enabled for the NOKIA5110_TEXT_FONTS sketch example.

4. Sketch uses 7340 bytes (22%) of program storage space and 106 bytes (5%) of dynamic memory.

Tested Boards
------------------------------------

1. Arduino UNO 
2. Arduino Nano v3
3. ESP8266 NodeMcu ESP-12e v0.1 at both 80 and 160 MHz

Note  ESP8266:

See issue 1 on github for pinout used.
The only problem here is the example file called,
"NOKIA5110_BITMAP.ino" it will not compile on ESP8266,
invalid conversion from 'const unsigned char*' to 'unsigned char*',
As a workaround until fixed, remove the const keyword from mybitmap and mybitmap2.

 
