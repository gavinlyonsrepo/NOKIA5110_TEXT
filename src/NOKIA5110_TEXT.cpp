/*
* Project Name: Nokia 5110
* File: NOKIA5110_TEXT.cpp
* Description: Nokia library cpp file
* Author: Gavin Lyons.
* IC: ATmega328P 
* IDE:  Arduino 1.8.5
* Created March 2019
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
*/

#include "NOKIA5110_TEXT.h"

NOKIA5110_TEXT::NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC, uint8_t LCD_DIN, uint8_t LCD_CLK) {
	
	_LCD_RST = LCD_RST;
	_LCD_CE = LCD_CE;
	_LCD_DC  = LCD_DC;
	_LCD_DIN  = LCD_DIN;
	_LCD_CLK  = LCD_CLK;
	
}

/*Function : LCDinit
This sends the  commands to the PCD8544 to  init LCD
*/
void NOKIA5110_TEXT::LCDInit(bool Inverse = false, uint8_t Contrast = LCD_CONTRAST,uint8_t Bias = LCD_BIAS) {
	
	pinMode(_LCD_RST,OUTPUT);
	pinMode(_LCD_CE,OUTPUT);
	pinMode(_LCD_DC,OUTPUT);
	pinMode(_LCD_DIN,OUTPUT);
	pinMode(_LCD_CLK,OUTPUT);
	_inverse = Inverse;
	_contrast = Contrast;
	//Configure control pins
	_LCD_DIN_SetLow;
	_LCD_CLK_SetLow;
	_LCD_DC_SetLow;
	//Reset the LCD to a known state
	_LCD_RST_SetLow;
	_LCD_RST_SetHigh;
	LCDWrite(LCD_COMMAND, LCD_COMMAND_MODE); //Tell LCD that extended commands follow
	LCDWrite(LCD_COMMAND, _contrast); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
	LCDWrite(LCD_COMMAND, LCD_TEMP_COEF); //Set Temp coefficent
	LCDWrite(LCD_COMMAND, Bias); //LCD bias mode 1:48: Try 0x13 or 0x14
	LCDWrite(LCD_COMMAND, LCD_FUNCTIONSET ); //We must send 0x20 before modifying the display control mode
	if (_inverse  == false)
		LCDWrite(LCD_COMMAND, LCD_DISPLAYCONTROL); //Set display control, normal mode. 0x0D for inverse
	else
		LCDWrite(LCD_COMMAND, LCD_DISPLAYCONTROL_INVERSE); //Set display control, normal mode. 0x0D for inverse
}

/* Function: LCDFont
Passed a int to set between fonts , 1-6
default font is 1, Font_two is 2. Font_three is 3 etc
 */
void NOKIA5110_TEXT::LCDFont(uint8_t  FontNumber)
{
	_FontNumber = FontNumber;
}


/* Function: LCDClear 
Clears the LCD by writing zeros to the entire screen
 */
void NOKIA5110_TEXT::LCDClear(void) {
	for (uint16_t index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
	{
		LCDWrite(LCD_DATA, 0x00);
	}
	LCDgotoXY(0, 0); //After we clear the display, return to the home position
	}

/* Function: LCDClear 
Clears one of the 6 row blocks(one byte height) on LCD 
by writing zeros to the line. Send the row block number 0-5
 */
void NOKIA5110_TEXT::LCDClearBlock(uint8_t RowBlockNum) {
	LCDgotoXY(0, RowBlockNum);
	for (uint8_t index = 0 ; index < (LCD_X) ; index++)
		{
			LCDWrite(LCD_DATA, 0x00);
		}
	}

/* Function: gotoXY gotoXY routine to position cursor 
 x - range: 0 to 84 (0 to 0x53)
 y - range: 0 to 5 ( 6 blocks one byte each 6*8 = 48*/
void NOKIA5110_TEXT::LCDgotoXY(uint8_t  x, uint8_t  y) {
	LCDWrite(LCD_COMMAND, 0x80 | x); // Column. (result 0x80 to 0xD3)
	LCDWrite(LCD_COMMAND, 0x40 | y); // Row.
}

/* Function: LCDWrite 
There are two  banks in the LCD, data and commands. This
function sets the DC pin high or low depending, and then sends
the data byte
 */
void NOKIA5110_TEXT::LCDWrite(unsigned char data_or_command, unsigned char data) {
	unsigned char i,d;
	d=data;
	if(data_or_command==0)_LCD_DC_SetLow;
	else _LCD_DC_SetHigh;
	//data_or_command; 
	//Tell the LCD that we are writing either to data or a command
	//Send the data
	_LCD_CE_SetLow;
	for(i=0;i<8;i++)
	{
		_LCD_DIN_SetLow;
		if(d&0x80)_LCD_DIN_SetHigh; // b1000000 Mask with 0 & all zeros out.
		_LCD_CLK_SetHigh;
		d<<=1;
		_LCD_CLK_SetLow;
	}
   _LCD_CE_SetHigh;
}

/* Function: LCDCharacter.
 This function takes in a character, looks it up in the font table/array
And writes it to the screen
Each character is 8 bits tall and 5 bits wide. We pad one blank column of
pixels on each side of the character for readability.
 */
void NOKIA5110_TEXT::LCDCharacter(char character) 
{
	uint8_t column = 0;
	LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding , LHS
	switch(_FontNumber)
	{
		case 1:
			#ifdef NOKIA5110_FONT_1
				for (column = 0 ; column < 5 ; column++){
					LCDWrite(LCD_DATA, (pgm_read_byte(&ASCII[character - LCD_ASCII_OFFSET][column])));
				}
			#endif
		break;
		case 2:
			#ifdef NOKIA5110_FONT_2
				for (column = 0 ; column < 7 ; column++) {
					LCDWrite(LCD_DATA, (pgm_read_byte(&ASCII_TWO[character - LCD_ASCII_OFFSET][column])));
				}
			#endif
		break;
		case 3:
			#ifdef NOKIA5110_FONT_3
				for (column = 0 ; column < 5 ; column++) {
					LCDWrite(LCD_DATA, (pgm_read_byte(&ASCII_THREE[character - LCD_ASCII_OFFSET][column])));
				}
			#endif
		break;
		case 4:
			#ifdef NOKIA5110_FONT_4
				for (column = 0 ; column < 4 ; column++) {
					LCDWrite(LCD_DATA, (pgm_read_byte(&ASCII_FOUR[character - LCD_ASCII_OFFSET][column])));
				}
			#endif
		break;
		case 5:
			#ifdef NOKIA5110_FONT_5
				for (column = 0 ; column < 8 ; column++){
					LCDWrite(LCD_DATA, (pgm_read_byte(&ASCII_FIVE[character - LCD_ASCII_OFFSET][column])));
				}
			#endif
		break;
		case 6:
			#ifdef NOKIA5110_FONT_6
				for (column = 0 ; column < 3 ; column++){
					LCDWrite(LCD_DATA, (pgm_read_byte(&ASCII_SIX[character - LCD_ASCII_OFFSET][column])));
				}
			#endif
		break;
	}
	LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding RHS
}

/* Function: LCDString.
 Given a string of characters, one by one is passed to the LCD
 */
void NOKIA5110_TEXT::LCDString(const char  *characters) {
	while (*characters)
	LCDCharacter(*characters++);
}

/* Function: LCDSetPixel
 Function to set one pixel on
 Passed two byte X and Y , Column and row position to set the the bit
 X = 0-83 , Y = 0-47.
 */
void NOKIA5110_TEXT::LCDSetPixel(uint8_t col = 0,  uint8_t row = 0) 
{
		uint8_t rowblock = row/8; //0 -5
		LCDgotoXY(col, rowblock);
		LCDWrite(LCD_DATA, 1 << (row-(rowblock*8)));
}

/* Function: LCDSetContrast
 Function to set contrast passed a byte 
 Set LCD VOP Contrast, range = ((0x00-0x7F) |0x80) 0xB5 = (0x35|0x80) try B1 - BF normally. 
 */
void NOKIA5110_TEXT::LCDsetContrast(uint8_t contrast)
{
	_contrast = contrast;
	LCDWrite(LCD_COMMAND, LCD_COMMAND_MODE); //Tell LCD that extended commands follow
	LCDWrite(LCD_COMMAND, _contrast); //Set LCD Vop (Contrast): 
	LCDWrite(LCD_COMMAND, LCD_FUNCTIONSET ); //We must send 0x20 before modifying the display control mode
}

// Put the LCD to Sleep function
void NOKIA5110_TEXT::LCDenableSleep()
{
	_sleep = true;
	for (uint16_t index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
	{
		LCDWrite(LCD_DATA, 0x00);
	}
	LCDgotoXY(0, 0);
	LCDWrite(LCD_COMMAND, LCD_POWERDOWN);
}

// Wake the LCD up from Sleep function
void NOKIA5110_TEXT::LCDdisableSleep()
{
   
	_sleep = false;
	LCDWrite(LCD_COMMAND , LCD_COMMAND_MODE);
	LCDWrite(LCD_COMMAND , _contrast);
	LCDWrite(LCD_COMMAND,  LCD_TEMP_COEF );
	LCDWrite(LCD_COMMAND,  LCD_BIAS );
	LCDWrite(LCD_COMMAND, LCD_FUNCTIONSET );
	if (_inverse  == false)
		LCDWrite(LCD_COMMAND, LCD_DISPLAYCONTROL); //Set display control, normal mode. 0x0D for inverse
	else
		LCDWrite(LCD_COMMAND, LCD_DISPLAYCONTROL_INVERSE); //Set display control, normal mode. 0x0D for inverse
}

/* =========== EOF ===========*/
