[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)

![ pcb ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA.jpg)


# NOKIA5110_TEXT

Table of contents
---------------------------

  * [Overview](#overview)
  * [Tested](#tested)
  * [Output](#output)
  * [Installation](#installation)
  * [Hardware](#hardware)
  * [Software](#software)
  
Overview
--------------------
* Name : NOKIA5110_TEXT
* Title : Library for Nokia 5110 LCD (PCD8544 controller) for the Arduino eco-system
* Description : 

1. Arduino eco system library, C++.      
2. Inverse, bias and contrast control. 
3. ASCII strings and character text display.
4. Nine different ASCII text fonts. 
5. Sleep mode.
6. Designed to be light weight, low memory footprint. see memory section.
7. Custom characters and bitmap supported
8. No graphics buffer to reduce memory footprint but 
basic graphics patterns can be created using custom characters, pixels, block patterns , lines.
9. Hardware or software SPI interface.
10. Print method for numerical data.

* Author: Gavin Lyons


Tested 
-----------------------------
* Tested on following MCUs (The file testedMCU_pinouts.txt in extras folder, shows pins used in testing)
 
1. Arduino  UNO & NANO v3
2. ESP8266  
3. ESP32 
4. STM32 STM32F103C8T6  "blue pill" 
5. ATtiny85
6. Arduino UNO R4 minima

Output
---------------------------------

Output Screenshots, From left to right top to bottom.

1. Custom characters + fill patterns 
2. Font 7 "Large"
3. Half screen bitmap
4. Font 9 "Mega"  
5. First 6  fonts (byte high), num 1-6, one font in each row block
6. Font 8 "Huge" 

![ font pic 1 ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT1.jpg)

![ font pic 2 ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT2.jpg)

![ font pic 3 ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_FONT_ALL.jpg)

Installation
------------------------------

The library is included in the official Arduino library manger and the optimum way to install it 
is using the library manager.

Hardware
-------------------------
The Nokia 5110 is a basic LCD screen for lots of applications. 
It was originally intended to be used as a mobile phone screen. 
It uses the PCD8544 controller, which is the same used in the Nokia 3310 LCD. 
The PCD8544 is a low power CMOS LCD controller/driver.

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
The example files use Pin D2-RST <.....> D6-CLK for UNO. 

| MCU   | Nokia 5110 LCD |
| ------ | ------ |
| Digital GPIO | LCD_CLK Pin 5 clock in |
| Digital GPIO | LCD_DIN Pin 4 data in |
| Digital GPIO | LCD_DC Pin 3 data/command|
| Digital GPIO | LCD_CE Pin 2 chip enable |
| Digital GPIO | LCD_RST Pin 1 reset|

**SPI interface bus**

The PCD8544 interfaces to microcontrollers through a serial bus interface(SPI).
The library originally and by default  used software SPI. 
As of Version 2.2 it can support hardware SPI as well.
Hardware SPI is much faster but two of the pins are fixed, is more difficult to port to new MCU's and includes the arduino SPI library. 
The file testedMCU_pinouts.txt show in extra folder shows pins used in testing of various MCU's.

To switch from the default software SPI to Hardware SPI, two steps are required:

1. In file NOKIA5110_TEXT.h , in SPI HARDWARE SECTION, comment in: define SPIHW_ON.
2. Use the constructor with 3 Parameters not 5. There is hardware SPI example file called NOKIA5110_HIW_HWSPI for UNO which shows this.

Pinout of a Nokia 5110 LCD.

![ pinout ](https://github.com/gavinlyonsrepo/NOKIA5110_TEXT/blob/master/extras/image/NOKIA_PINOUT.jpg)

The LCD Vcc runs at 3.3V so you'll need to use level shifting/dropping  to use with safely with  5V microcontroller.

Software
---------------------------

**Fonts**

There are 9 fonts.
By default only Font 1 is commented in and ready to go.
So to use a non-default Font (2-9), two steps.

1. Comment in the respective define at top of library header file NOKIA5110_TEXT_FONT_DATA.h in the FONT DEFINE SECTION.
2. Call LCDFont function and pass it enum label of respective font.

Only include what fonts you want in order to keep program size as small as possible.
Some fonts do not have lowercase letters and others are numbers only.
For fonts 1-6 each character is a byte of pixels in height(Y). One pixel of empty space on each side is added by code (padding). So a 5x8 (XxY) pixel character is in reality 7x8. 
Each of the six rowblock is one byte height. 

Total characters = (Screen Width/Character width  + padding) X (Screen height/Character height).

Font table:

| num | name | Character size  | Total characters | Note | size in bytes |
| ------ | ------ | ------ | ------ |  ------ | ----- |
| 1 | Default | 5x8 |  72 |   ------ | 465 |
| 2 | Thick   | 7x8 | 54 |  no lowercase letters  | 406 |
| 3 | Homespun | 7x8 | 54 | ------ | 658 |
| 4 | Seven segment | 4x8 | 84 | ------ | 364 |
| 5 | Wide | 8x8 |  48 | no lowercase letters | 464 | 
| 6 | Tiny | 3x8 | 96  | ------ | 285 |
| 7 | Large | 12x16 |  21 |  no lowercase letters | 1392 |
| 8 | Huge | 16x24 |  10  | Numbers + : . only, use / for space | 832 |
| 9 | Mega | 16x32 |  5  | Numbers + : . only, use / for space | 832 |

**Bitmaps** 

Libray can display bitmaps, Data in bitmaps must be vertically addressed and can be placed in PROGMEM, see examples files. 

**Print method**

There is a print method which utilises the arduino print.h 
to print data types other than character strings
see example file NOKIA5110_TESTS. 
The user can pass flash-memory based strings to print() by wrapping them with F() macro. 

