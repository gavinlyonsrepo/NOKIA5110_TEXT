Overview
--------------------
* Name : NOKIA5110_TEXT
* Title : Library for Nokia 5110 LCD (PCD8544 controller) for the Arduino eco-system
* Description : 

1. Arduino library.      
2. Inverse, Bias and contrast control. 
3. ASCII character text.
4. Font 1 (12 * 6 ) 72 characters in total.
5. Font 2 (9 * 6  ) 54  characters in total.
6. Font 3 (12 * 6 ) 72 characters in total.
7. Three fonts. Text only. 
8. Sleep mode.
9. Light weight, low memory footprint. 
10. Basic Example program font one only (tested on UNO) uses 1874 bytes (5%) of program storage space. Maximum is 32256 bytes.
Global variables use 22 bytes (1%) of dynamic memory, leaving 2026 bytes for local variables. Maximum is 2048 bytes.

* Author: Gavin Lyons
* Arduino IDE: 1.8.5
* Tested: UNO and NANO v3


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

GPIO function on PIC, 5 Nokia 5110 LCD lines SPI bus.

| Arduino    | Nokia 5110 LCD |
| ------ | ------ |
| Digital GPIO | LCD_CLK Pin 5 clock in |
| Digital GPIO | LCD_DIN Pin 4 data in |
| Digital GPIO | LCD_DC Pin 3 data/command|
| Digital GPIO | LCD_CE Pin 2 chip enable |
| Digital GPIO | LCD_RST Pin 1 reset|

The library uses bit-banging rather than importing SPI libraries.

Example program default font only (tested on UNO) uses 1874 bytes (5%) of program storage space. Maximum is 32256 bytes.
Global variables use 22 bytes (1%) of dynamic memory, leaving 2026 bytes for local variables. Maximum is 2048 bytes.
This compares to Adafruit text based library example of 20% and 38% for program storage and global variables respectively. 

There are 3 fonts you include the ones you want by means of "define" statements at top of library header file.
You change the current font using the "LCDFont" function. 
Only include what font you want in order to keep program size as small as possible.
The default font is "font number 1" and included by default.

The library has main 5 files (NOKIA5110_TEXT.cpp  NOKIA5110_TEXT.h and 3 font header files).

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

The ASCII library in a font header file: Each character is 5 pixel wide. Plus one pixel of empty space on each side.
Also each character is a byte of pixels in height.
So each character is in a 7 by 8 pixel block. So you can fit (84/7) 12 characters across columns and with (48/8).
6 row blocks that gives 72 characters in total (12X06).

The library can only take in characters and strings so if the user wants to display numbers (ints, floats)
They must be converted or parsed first, there is an example file "NOKA5110_TEXT_DHT11.ino" 
which shows one way to do this with floats.

**Font2** 
The library also includes a "font 2", this is a thicker/wider font with same height. 
Each character is in a 9 by 8 pixel block so you can fit 84/9 = 12 characters across columns and with
6 row blocks that gives 54 characters in total (9X06). There is an example file for this font.
In order to save program space this font is uppercase letters only.
To Include this font by commenting in #define NOKIA5110_FONT_2 at top of library header file
and to use it pass 2 to "LCDFont" function.

**Font3**
The library also has a optional font 3 Aurebesh<->ASCII font file. 
An example file for this is in examples. This font is same size as font 1.
To Include this font by commenting in #define NOKIA5110_FONT_3 at top of library header file
and to use it pass 3 to "LCDFont" function.

Functions
----------------------------------------
 

1. NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC, uint8_t LCD_DIN, uint8_t LCD_CLK)

Construct of the class object from left to right pin 1-5(LCD)
RST pin 1, CD pin 2, DC pin 3, DIN pin 4, CLK pin 5 

2. LCDInit(bool Inverse, uint8_t Contrast, uint8_t Bias )

This sends the  commands to the PCD8544 to init LCD. Inverse inverts the
display see image 4. Contrast, This value allows us to change LCD's contrast Try B0 to BF.
The Bias Value is for system biasing, try about 0x13-0X14


3. LCDgotoXY(uint8_t , uint8_t)

gotoXY routine to position cursor,  x - range: 0 to 84 (0 to 0x53), 
y - range: 0 to 5 ( 6 blocks one byte each 6 * 8 = 48

4. LCDClear(void)

Clears the LCD by writing zeros to the entire screen

5. LCDWrite(unsigned char , unsigned char)

There are two  banks in the LCD, data and commands. 
This function sets the DC pin high or low depending, and then sends
the data byte The first byte is one(data) or zero(cmd) , second byte data


6. LCDString(const char * characters);

Given a string of characters, one by one is passed to the LCD

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

Pictures
---------------------------

Output showing Blocks numbers from main test file NOKIA_TEXT_TEST.ino.

![ScreenShot pic](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA.jpg)

Pinout of a Nokia 5110 LCD.

![ScreenShot pic2](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA2.jpg)

Output showing inverse function.

![ScreenShot pic4](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA4.jpg)

Output showing Font two. NOKIA5110_TEXT_FONT2.h.

![ScreenShot pic4](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA6.jpg)

Output showing  Font 3 NOKIA5110_TEXT_FONT_AUREBESH.h .

![ScreenShot pic5](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA5.jpg)
