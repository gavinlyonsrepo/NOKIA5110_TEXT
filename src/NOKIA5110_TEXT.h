/*
* Project Name: NOKIA5110_TEXT
* File: NOKIA5110_TEXT.h
* Description: Nokia library header file
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
*/
#ifndef NOKIA5110_TEXT_H
#define NOKIA5110_TEXT_H

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// **********************************************
// ******** FONT DEFINE SECTION ****** ****** 
// Comment in the fonts YOU want, X_1 is default., see comments just  below in indef section for font  name.

#define NOKIA5110_FONT_1 
//#define NOKIA5110_FONT_2 
//#define NOKIA5110_FONT_3
//#define NOKIA5110_FONT_4
//#define NOKIA5110_FONT_5
//#define NOKIA5110_FONT_6
//#define NOKIA5110_FONT_7
//#define NOKIA5110_FONT_8
//#define NOKIA5110_FONT_9

// **** END OF FONT DEFINE SECTION ******  
// ********************************************

#ifdef NOKIA5110_FONT_1
	#include "NOKIA5110_TEXT_FONT.h" // Default 5X8
#endif
#ifdef NOKIA5110_FONT_2
	#include "NOKIA5110_TEXT_FONT_TWO.h" // Thick 7X8  (NO LOWERCASE LETTERS)
#endif
#ifdef NOKIA5110_FONT_3
	#include "NOKIA5110_TEXT_FONT_THREE.h" // Aurebesh 5X8
#endif
#ifdef NOKIA5110_FONT_4
	#include "NOKIA5110_TEXT_FONT_FOUR.h" //seven segment 4X8
#endif
#ifdef NOKIA5110_FONT_5
	#include "NOKIA5110_TEXT_FONT_FIVE.h" // Wide  8X8 (NO LOWERCASE LETTERS)
#endif
#ifdef NOKIA5110_FONT_6
	#include "NOKIA5110_TEXT_FONT_SIX.h" // Tiny 3X8
#endif
#ifdef NOKIA5110_FONT_7
	#include "NOKIA5110_TEXT_FONT_SEVEN.h" // Large 12 X 16 (no lowercase letters)
#endif
#ifdef NOKIA5110_FONT_8
	#include "NOKIA5110_TEXT_FONT_EIGHT.h" // Huge 16 X24 (numbers + . : only) 
#endif
#ifdef NOKIA5110_FONT_9
	#include "NOKIA5110_TEXT_FONT_NINE.h" // Mega 16 X 32 (numbers + . : / only)
#endif

//LCD Commands PCD8544_
#define LCD_COMMAND_MODE 0x21  //FUNCTIONSET + extended instruction
#define LCD_CONTRAST     0xBF  //Set LCD VOP Contrast Try 0xB1 or 0xBF if is too dark range = ((0x00-0x7F) |0x80)
#define LCD_TEMP_COEF    0x04  //Set Temp coefficient
#define LCD_BIAS         0x14  // //LCD bias mode 1:48: Try 0x13 or 0x14
#define LCD_FUNCTIONSET  0x20  //We must send 0x20 before modifying the display control mode
#define LCD_DISPLAYCONTROL 0x0C //Set display control, normal mode. 0x0D for inverse
#define LCD_DISPLAYCONTROL_INVERSE 0x0D //Set display control, inverse mode. 0x0D for inverse
#define LCD_POWERDOWN    0x24 //LCD power off

// Misc LCD Data 
#define LCD_FONTNUMBER  0x01 // default Font number 1,  1 to 6 fonts
#define LCD_ASCII_OFFSET 0x20 //0x20, ASCII character for Space, The font table starts with this character
#define LCD_ASCII_OFFSET_ZERO 0x2E // ASCII code for . is 0X2E (. / 0 1 etc)

//The DC pin tells the LCD if sending a command or data
#define LCD_COMMAND 0
#define LCD_DATA 1

// 84 by 48 pixels screen
#define LCD_X 84
#define LCD_Y 48

// Size width of fonts in pixels, add 2 for padding 1-6
#define LCD_FONT_WIDTH_1 5
#define LCD_FONT_WIDTH_2 7
#define LCD_FONT_WIDTH_3 5
#define LCD_FONT_WIDTH_4 4
#define LCD_FONT_WIDTH_5 8
#define LCD_FONT_WIDTH_6 3
#define LCD_FONT_WIDTH_7 12 // No padding  , no lowercase letters
#define LCD_FONT_WIDTH_8 16 // No padding ,  numbers only
#define LCD_FONT_WIDTH_9 16 // No padding ,  numbers only


// GPIO on/off
#define _LCD_CLK_SetHigh            digitalWrite(_LCD_CLK, true)
#define _LCD_CLK_SetLow             digitalWrite(_LCD_CLK, false)
#define _LCD_DIN_SetHigh            digitalWrite(_LCD_DIN, true)
#define _LCD_DIN_SetLow             digitalWrite(_LCD_DIN, false)
#define _LCD_DC_SetHigh             digitalWrite(_LCD_DC, true)
#define _LCD_DC_SetLow              digitalWrite(_LCD_DC, false)
#define _LCD_CE_SetHigh             digitalWrite(_LCD_CE, true)
#define _LCD_CE_SetLow              digitalWrite(_LCD_CE, false)
#define _LCD_RST_SetHigh            digitalWrite(_LCD_RST, true)
#define _LCD_RST_SetLow             digitalWrite(_LCD_RST, false)


class NOKIA5110_TEXT {

  public:
   
    
    //Constructor of the class object from left to right pin 1-5(LCD)
    //RST pin 1, CD pin 2, DC pin 3, DIN pin 4, CLK pin 5 
	 NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC, uint8_t LCD_DIN, uint8_t LCD_CLK);
	
	// Methods
	
	/*Function : LCDinit
	This sends the  commands to the PCD8544 to init LCD. Inverse inverts the
	display. Contrast, This value allows us to change LCD's contrast Try B0 to BF.
	The Bias Value is for system biasing, try about 0x12-0X14
	*/
	void LCDInit(bool Inverse = false, uint8_t Contrast = LCD_CONTRAST,uint8_t Bias = LCD_BIAS);
	
	/* Function: gotoXY gotoXY routine to position cursor 
		x- range: 0 to 83 (0 to 0x53)
		y - range: 0 to 5 ( 6 blocks one byte each 6*8 = 48
	*/
	void LCDgotoXY(uint8_t x, uint8_t y);
	
	/* Function: LCDClear 
		Clears the LCD by writing zeros to the entire screen
		Default is zero but can be passed a fill pattern eg 0xFF  = all pixels on.
	*/
	void LCDClear(uint8_t FillData = 0x00);
	
	/* Function: LCDClearBlock
		Clears one of the 6 row blocks(one byte height) on LCD 
		by writing zeros to the line. Send the row block number 0-5
		More efficient than clearing whole screen
	*/
	void LCDClearBlock(uint8_t RowBlockNum = 0);
	
	/* Function: LCDFont
	Passed a int to set between fonts , 1-6
	default font is 1, Font_two is 2. Font_three is 3 etc
	*/
	void LCDFont(uint8_t FontNumber);
	
	/* Function: LCDWrite 
	There are two  banks in the LCD, data and commands. This
	function sets the DC pin high or low depending, and then sends
	the data byte  The first byte is one(data) or zero(cmd) , second byte data.
	prints the byte down from current position , It is used internally 
	to draw cols of characters it can be used to create vertical lines or patterns.
	 */
	void LCDWrite(unsigned char data_or_command, unsigned char data);
	
	/* Function: LCDCharacter.
	 This function takes in a character, looks it up in the font table/array
	And writes it to the screen
	Each character (default) is 8 bits tall and 5 bits wide. We pad one blank column of
	pixels on each side of the character for readability.
	 */
	void LCDCharacter(char character);
	
	/* Function: LCDString.
	 Given a string of characters, one by one is passed to the LCD
	The library can only take in characters and strings so if the user wants to display numbers (ints, floats)
	They must be converted or parsed first, there is an example file "NOKA5110_TEXT_DHT11.ino" 
	which shows one way to do this with floats.
	 */
	void LCDString(const char *characters);
	
	/* Function: LCDSetPixel
	Function to set one pixel on
	Passed two byte X and Y , Column and row position to set the the bit
	X = 0-83 , Y = 0-47. Passed can be used to set a individual pixel
	Can be used to create simple graphics like lines, boxes.
	*/
	void LCDSetPixel(uint8_t col = 0, uint8_t row = 0);
	
	/* Function: LCDSetContrast
	 Function to set contrast passed a byte 
	 Set LCD VOP Contrast, range = ((0x00-0x7F) |0x80) 0xB5 = (0x35|0x80) try B1 - BF normally. 
	 */
	void LCDsetContrast(uint8_t contrast);
	
	/* Function: LCDenableSleep
	  Put the LCD to Sleep function
	*/
	void LCDenableSleep(void);
	
	/* Function: LCDdisableSleep
	  wake the LCD up from Sleep
	*/
	void LCDdisableSleep(void);
	
	/* Function: LCDFillBlock
	Clears one of the 6 row blocks(one byte height) on LCD 
	by writing ones to the line. Send the row block number 0-5
	The  pattern of data can be reversed by changing filldata
	i.e 0x0F will half fill a block with ones
	*/
	void LCDFillBlock(uint8_t FillData = 0xFF , uint8_t RowBlockNum = 0);
	
	/* Function: LCDCustomChar
	 Write a custom character to screen X by Y. Y is fixed at 8
	 Parameters 1 Example: 5 by 8 = || || = Char array unsigned char power[5] = {0xFF, 0xFF, 0x00, 0xFF, 0xFF}; 
	 Parameters 2: Size of array,  sizeof(power)/sizeof(unsigned char)
	 Parameter 3: Blank vertical line padding  padding 4 values
	 0 = no padding 
	 1 = Left hand side padding only
	 2 = Right hand side padding only 
	 3 = LHS + RHS
	 
	 Parameter 4: Is the data of character[] in flash memory or SRAM?
	 true for flash, false for SRAM
	 */
	void LCDCustomChar(const unsigned char character[], uint16_t numChars, uint8_t padding, bool ProgMemLocale );
	
	//Function LCDissleeping
	// Returns  value of _sleep, if true LCD is in sleep mode.
	bool LCDIsSleeping(void);
	
  private:
	
	void LCDdraw_fonts_1TO6(char character, uint8_t font_width); //8 bit tall fonts
	void LCDdraw_fonts_7(char character); // 16 bit tall fonts
	void LCDdraw_fonts_8TO9(char character); // 24 and 32 bit tall fonts
	
	uint8_t _LCD_RST;
	uint8_t _LCD_CE;
	uint8_t _LCD_DC;
	uint8_t _LCD_DIN;
	uint8_t  _LCD_CLK;

	uint8_t  _contrast = LCD_CONTRAST ; 
	uint8_t  _bias = LCD_BIAS ; 
	uint8_t	_FontNumber = LCD_FONTNUMBER;
	bool _sleep = false; // False awake , true sleep;
	bool	 _inverse = false;
	uint8_t _Block = 0; 
	uint8_t _Col = 0;
	
};


#endif
