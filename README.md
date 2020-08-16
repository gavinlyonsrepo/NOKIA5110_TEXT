![ pcb ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Output](#output)
  * [Installation](#installation)
  * [Features](#features)
  * [Fonts](#fonts)
  
Overview
--------------------
* Name : NOKIA5110_TEXT
* Title : Library for Nokia 5110 LCD (PCD8544 controller) for the Arduino eco-system
* Description : 

1. Arduino library.      
2. Inverse, Bias and contrast control. 
3. ASCII strings and character text display.
4. Nine different ASCII text fonts. 
5. Sleep mode.
6. Designed to be light weight, low memory footprint. see memory section.
7. Custom characters and bitmap supported
8. No graphics buffer to reduce memory footprint but 
basic graphics patterns can be created using custom characters, pixels, block patterns , lines.
 
* Author: Gavin Lyons
* Arduino IDE: 1.8.10
* Functions: Detailed information on the functions can be found in comments in the library .h header file and a concise list of them in keywords.txt and they are 5 example files. 
* Memory usage data results can be found in the extras folder. MemoryTestResults.md.

* Tested on following MCUs.
1. Arduino  UNO & NANO v3
2. ESP8266 
3. ESP32 
4. STM32 "blue pill"

Output
---------------------------------

Output Screenshots, From left to right top to bottom.

1. Custom characters + fill patterns 
2. Font 7 "Large"
3. Half screen bitmap + Font 7 "large"
4. Font 9 "Mega"  
5. Output showing first 6 (X by 8) fonts, #1-6, one font in each row block:
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
The PCD8544 interfaces to microcontrollers through a serial bus interface(SPI).
The library uses bit-banging software SPI rather than importing SPI libraries.
The library has 11 code files (NOKIA5110_TEXT.cpp  NOKIA5110_TEXT.h and 9 font header files).
In addition the library has 5 examples files. 

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

The LCD Vcc runs at 3.3V so you'll need to use level shifting/dropping  to use with safely with  5V microcontroller.

Fonts 
---------------------------

There are 9 fonts.
By default only Font 1 is commented in and ready to go.
So to use a non-default Font (2-9), two steps.

1. Comment in the respective define at top of library header file NOKIA5110_TEXT.h in the FONT DEFINE SECTION.
2. Call LCDFont function and pass it number of respective font.

Only include what fonts you want in order to keep program size as small as possible.
Each font is a header file, NOKIA5110_FONT_X.h where X is number of Font(1-9)
Some fonts do not have lowercase letters and others are numbers only.
For fonts 1-6 Each character is a byte of pixels in height(Y). One pixel of empty space on each side 
is added by code (padding). So a 5x8 (XxY) pixel character is in reality 7x8. 
Each of the six rowblock is one byte height. 

Total characters = (Screen Width/Character width  + padding) X (Screen height/Character height).

**Font table**

| Font num | Font name | Pixel size | total characters | Note |
| ------ | ------ | ------ | ------ |  ------ |
| 1 | Default | 5x8 | (84/5+2) * (48/8) = 72 |   ------ |
| 2 | Thick   | 7x8 | (84/7+2) * (48/8)  = 54 |  no lowercase letters  |
| 3 | Aurebesh | 5x8 | (84/5+2) * (48/8)  = 72 | ------ |
| 4 | Seven segment | 4x8 | (84/4+2) * (48/8) = 84 | ------ |
| 5 | Wide | 8x8 | (84/8+2) * (48/8) = 48 | no lowercase letters |
| 6 | Tiny | 3x8 | (84/3+2) * (48/8) = 96  | ------ |
| 7 | Large | 12x16 | (84/12) * (48/16) = 21 |  no lowercase letters |
| 8 | Huge | 16x24 | (84/16) * (48/24) = 10  | Numbers + : . only |
| 9 | Mega | 16x32 | (84/16) * (48/32) = 5  | Numbers + : . only |
