/*!
	@file NOKIA5110_TEXT.cpp
	@brief Nokia library Source file
	@author Gavin Lyons
	@details Project Name NOKIA5110_TEXT URL:https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
*/

#include "NOKIA5110_TEXT.h"
#include  "NOKIA5110_TEXT_FONT_DATA.h"

/*!
	@brief Software SPI default
	@details Constructor of the class object from left to right pin 1-5(LCD)
	@param LCD_RST GPIO reset line 
	@param LCD_CE GPIO chip enable line 
	@param LCD_DC GPIO data or command line 
	@param LCD_DIN GPIO data in , MOSI line 
	@param LCD_CLK GPIO clock  line 
*/
NOKIA5110_TEXT::NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC, int8_t LCD_DIN, int8_t LCD_CLK) {
	
	_LCD_RST = LCD_RST;
	_LCD_CE = LCD_CE;
	_LCD_DC  = LCD_DC;
	_LCD_DIN  = LCD_DIN;
	_LCD_CLK  = LCD_CLK;
	
}

/*!
	@brief Hardware SPI 
	@details Constructor of the class object from left to right pin 1-3(LCD)
	@param LCD_RST GPIO reset line 
	@param LCD_CE GPIO chip enable line 
	@param LCD_DC GPIO data or command line 
*/
NOKIA5110_TEXT::NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC) {
	
	_LCD_RST = LCD_RST;
	_LCD_CE = LCD_CE;
	_LCD_DC  = LCD_DC;
	_LCD_DIN  = -1;  // -1 for din  specify using hardware SPI
	_LCD_CLK  = -1; // -1 for  sclk specify using hardware SPI
	
}

/*!
	@brief LCDinit This sends the commands to the PCD8544 to init LCD. 
	@param Inverse inverts the display. 
	@param Contrast This value allows us to change LCD's contrast Try B0 to BF.
	@param  Bias Value is for system biasing, try 0x12<->0X14
*/
void NOKIA5110_TEXT::LCDInit(bool Inverse, uint8_t Contrast,uint8_t Bias) {
	
	_inverse = Inverse;
	_bias = Bias;
	_contrast = Contrast;

   if (isHardwareSPI()) 
  {
#ifdef SPIHW_ON 
   SPI.begin();
   //There is a pre-defined macro SPI_HAS_TRANSACTION in SPI library for checking whether the firmware //of the Arduino board supports SPI.beginTransaction().
#ifdef SPI_HAS_TRANSACTION
	{
	//SPI.setClockDivider(SPI_CLOCK_DIV8);
	SPI.beginTransaction(SPISettings(SPI_FREQ, MSBFIRST, SPI_MODE0));
   }
#else
	{
		//STM32 blue pill uses this 
		SPI.setClockDivider(SPI_CLOCK_DIV8); // 72/8 = 9Mhz
	  }
#endif
#endif
  }else
  {
	 // Set software SPI specific pin outputs.
	pinMode(_LCD_DIN, OUTPUT);
	pinMode(_LCD_CLK, OUTPUT);
	_LCD_DIN_SetLow;
	_LCD_CLK_SetLow;

  }
	pinMode(_LCD_RST,OUTPUT);
	pinMode(_LCD_CE,OUTPUT);
	pinMode(_LCD_DC,OUTPUT);
	_LCD_DC_SetLow;
	//Reset the LCD to a known state
	_LCD_RST_SetLow;
	delay(LCD_RESET_DELAY);
	_LCD_RST_SetHigh;
	LCDSPIWrite(LCD_COMMAND, LCD_COMMAND_MODE); //Tell LCD that extended commands follow
	LCDSPIWrite(LCD_COMMAND, _contrast); //Set LCD Vop (Contrast): Try 0xB1 or 0xBF if your display is too dark
	LCDSPIWrite(LCD_COMMAND, LCD_TEMP_COEF); //Set Temp coefficent
	LCDSPIWrite(LCD_COMMAND, _bias); //LCD bias mode 1:48: Try 0x13 or 0x14
	LCDSPIWrite(LCD_COMMAND, LCD_FUNCTIONSET ); //We must send 0x20 before modifying the display control mode
	if (_inverse  == false)
		LCDSPIWrite(LCD_COMMAND, LCD_DISPLAYCONTROL); //Set display control, normal mode. 
	else
		LCDSPIWrite(LCD_COMMAND, LCD_DISPLAYCONTROL_INVERSE); //Set display control, normal mode. 0x0D for inverse
}


/*!
	@brief  LCDgotoXY gotoXY routine to position cursor (x,y)
	@param x range: 0 to 83 (0 to 0x53)
	@param y range: 0 to 5 (6 blocks one byte each 6*8 = 48)
*/
void NOKIA5110_TEXT::LCDgotoXY(uint8_t  x, uint8_t  y) {
	LCDSPIWrite(LCD_COMMAND, 0x80 | x); // Column. (result 0x80 to 0xD3)
	LCDSPIWrite(LCD_COMMAND, 0x40 | y); // Row.
	_Block= y;
	_Col = x;
}

/*! 
	@brief  LCDClear Clears the LCD by writing zeros to the entire screen
	@param FillData Default is zero but can be passed 
		a fill pattern eg 0xFF  = all pixels on.
*/
void NOKIA5110_TEXT::LCDClear(uint8_t  FillData) {
	for (uint16_t index = 0 ; index < (LCD_X * (LCD_Y / 8)) ; index++)
	{
		LCDSPIWrite(LCD_DATA, FillData);
	}
	LCDgotoXY(0, 0); //After we clear the display, return to the home position
	}

/*! 
	@brief  LCDClearBlock Clears one of the 6 row blocks(one byte height) on LCD 
	by writing zeros to the line. More efficient than clearing whole screen.
	@param RowBlockNum Send the row block number 0-5
*/
void NOKIA5110_TEXT::LCDClearBlock(uint8_t RowBlockNum) {
	LCDgotoXY(0, RowBlockNum);
	for (uint8_t index = 0 ; index < (LCD_X) ; index++)
		{
			LCDSPIWrite(LCD_DATA, 0x00);
		}
	}

/*!
	@brief  LCDFont
	@param FontNumber  a enum  LCDFontType_e  to set between fonts , 1-9
*/
void NOKIA5110_TEXT::LCDFont(LCDFontType_e FontNumber)
{

/*! Enum to store current font width , Size width of fonts in pixels,*/
enum LCDFontWidth_e : uint8_t{
	LCDFont_W_3 = 3,  /**<  tiny font */
	LCDFont_W_4 = 4,  /**<  seven segment font */
	LCDFont_W_5 = 5,  /**<  Default */
	LCDFont_W_7 = 7,  /**<  thick + homeSpun */
	LCDFont_W_8 = 8,  /**<  wide */
	LCDFont_W_12 = 12,  /**<  large , no lowercase letters */
	LCDFont_W_16 = 16  /**<  mega and huge , numbers only */
};

/*! font offset in the ASCII table */
enum LCDFontOffset_e :uint8_t{
	LCDFont_O_Full = 0x00,          /**<   full ASCII */
	LCDFont_O_Space = 0x20,     /**<  Starts at Space */
	LCDFont_O_Number = 0x2E, /**< ASCII code for . is 0X2E (. / 0 1 etc) */
}; 
	
	_CurrentFontNumber = FontNumber;
	
		switch (_CurrentFontNumber) {
		case LCDFont_Default:  // default
			_CurrentFontWidth = LCDFont_W_5;
			_CurrentFontOffset =  LCDFont_O_Space ;
		break; 
		case LCDFont_Thick: // Thick 
		case LCDFont_HomeSpun:  // homespun
			_CurrentFontWidth = LCDFont_W_7;
			_CurrentFontOffset =  LCDFont_O_Space;
		break; 
		case LCDFont_Seven_Seg:  //seven seg
			_CurrentFontWidth = LCDFont_W_4;
			_CurrentFontOffset =  LCDFont_O_Space;
		break;
		case LCDFont_Wide :  //wide
			_CurrentFontWidth = LCDFont_W_8;
			_CurrentFontOffset =   LCDFont_O_Space;
		break; 
		case LCDFont_Tiny : // tiny
			_CurrentFontWidth = LCDFont_W_3;
			_CurrentFontOffset =   LCDFont_O_Space;
		break; 
		case LCDFont_Large : // large
			_CurrentFontWidth = LCDFont_W_12;
			_CurrentFontOffset =  LCDFont_O_Space;
		break; 
		case LCDFont_Huge: // huge
			_CurrentFontWidth = LCDFont_W_16;
			_CurrentFontOffset =  LCDFont_O_Number ;
		break; 
		case LCDFont_Mega: // mega
			_CurrentFontWidth = LCDFont_W_16;
			_CurrentFontOffset =  LCDFont_O_Number ;
		break; 
	}
}

/*! 
	@brief  LCDSPIWrite write to display
	@param data the data byte to write
	@param DataOrCommand one = data, zero = command
	@note There are two banks in the LCD, data and commands. This
	function sets the DC pin high or low depending, and then sends
	the data byte. The first byte is one(data) or zero(cmd), second byte data.
	Prints the byte down from current position, it is used internally 
	to draw cols of characters it can be used to create vertical lines or patterns.
*/
void NOKIA5110_TEXT::LCDSPIWrite(unsigned char DataOrCommand, unsigned char data) {
	unsigned char i;
	
	if(DataOrCommand==0)_LCD_DC_SetLow;
	else _LCD_DC_SetHigh;
	//DataOrCommand; 
	//Tell the LCD that we are writing either to data or a command
	//Send the data
	_LCD_CE_SetLow;
	  if (isHardwareSPI()) 
	{
#ifdef SPIHW_ON
		(void)SPI.transfer(data); // Hardware SPI
#endif
	}else
	{
		for (i = 0; i < 8; i++) {
			_LCD_DIN_SetLow;
			if (data & 0x80)_LCD_DIN_SetHigh; // b1000000 Mask with 0 & all zeros out.
			_LCD_CLK_SetHigh;
			data <<= 1;
			delayMicroseconds(LCD_HIGH_FREQ_DELAY); 
			_LCD_CLK_SetLow;
		}
	}
	_LCD_CE_SetHigh;
}

/*!
	@brief  LCDCharacter  print character Calls relevant method for the font set 
	@param character the character to print 
 */
void NOKIA5110_TEXT::LCDCharacter(char character) 
{
	switch (_CurrentFontNumber) {
		case LCDFont_Default:   
		case LCDFont_Thick: 
		case LCDFont_HomeSpun: 
		case LCDFont_Seven_Seg:  
		case LCDFont_Wide:   
		case LCDFont_Tiny: LCDdraw_fonts_1TO6(character);
			break;
		case LCDFont_Large: LCDdraw_fonts_7(character);
			break;
		case LCDFont_Huge: LCDdraw_fonts_8TO9(character);
			break;
		case LCDFont_Mega: LCDdraw_fonts_8TO9(character);
			break;
	}
}

/*! 
	@brief  LCDString given a string of characters, one by one is passed to the LCD.
	@param characters pointer to string array
*/
void NOKIA5110_TEXT::LCDString(const char * characters) {
	while (*characters)
	LCDCharacter(*characters++);
}

/*! 
	@brief  LCDSetPixel Method to set a individual pixel
	@param col column position X = 0-83
	@param row row position Y = 0-47
	@details Can be used to create simple graphics.
*/
void NOKIA5110_TEXT::LCDSetPixel(uint8_t col,  uint8_t row ) 
{
		uint8_t rowblock = row/8; //0 -5
		LCDgotoXY(col, rowblock);
		LCDSPIWrite(LCD_DATA, 1 << (row-(rowblock*8)));
}

/*! 
	@brief  LCDSetContrast to set LCD contrast 
	@param contrast Set LCD VOP Contrast, range = ((0x00-0x7F) |0x80) 0xB5 = (0x35|0x80) try B1 - BF normally. 
*/
void NOKIA5110_TEXT::LCDsetContrast(uint8_t contrast)
{
	_contrast = contrast;
	LCDSPIWrite(LCD_COMMAND, LCD_COMMAND_MODE); //Tell LCD that extended commands follow
	LCDSPIWrite(LCD_COMMAND, _contrast); //Set LCD Vop (Contrast): 
	LCDSPIWrite(LCD_COMMAND, LCD_FUNCTIONSET ); //We must send 0x20 before modifying the display control mode
}

/*! 
	@brief  LCDenableSleep Put the LCD to Sleep function.
*/
void NOKIA5110_TEXT::LCDenableSleep()
{
	_sleep = true;
	for (uint16_t index = 0 ; index < (LCD_X * (LCD_Y / 8)) ; index++)
	{
		LCDSPIWrite(LCD_DATA, 0x00);
	}
	LCDgotoXY(0, 0);
	LCDSPIWrite(LCD_COMMAND, LCD_POWERDOWN);
}

/*! 
	@brief  LCDdisableSleep Wake the LCD up from Sleep.
*/
void NOKIA5110_TEXT::LCDdisableSleep()
{
   
	_sleep = false;
	LCDSPIWrite(LCD_COMMAND , LCD_COMMAND_MODE);
	LCDSPIWrite(LCD_COMMAND , _contrast);
	LCDSPIWrite(LCD_COMMAND,  LCD_TEMP_COEF );
	LCDSPIWrite(LCD_COMMAND,  _bias );
	LCDSPIWrite(LCD_COMMAND, LCD_FUNCTIONSET );
	if (_inverse  == false)
		LCDSPIWrite(LCD_COMMAND, LCD_DISPLAYCONTROL); //Set display control, normal mode. 0x0D for inverse
	else
		LCDSPIWrite(LCD_COMMAND, LCD_DISPLAYCONTROL_INVERSE); //Set display control, normal mode. 0x0D for inverse
}

/*! 
	@brief  LCDFillBlock Clears one of the 6 row blocks(one byte height) on LCD 
	@param FillData data to write 0-0xFF
	@param RowBlockNum row block number 0-5
	@note The pattern of data can be reversed by changing filldata
	i.e 0x0F will half fill a block with ones.
*/
void NOKIA5110_TEXT::LCDFillBlock(uint8_t FillData , uint8_t RowBlockNum) {
	LCDgotoXY(0, RowBlockNum);
	for (uint8_t index = 0 ; index < (LCD_X) ; index++)
		{
			LCDSPIWrite(LCD_DATA, FillData);
		}
	}

/*! 
	@brief  LCDCustomChar Write a custom character or bitmap to screen X by Y. 
	@param  character Example: 5 by 8 = || || = Char array unsigned char power[5] = {0xFF, 0xFF, 0x00, 0xFF, 0xFF}; 
	@param  numChars Size of array, sizeof(power) / sizeof(unsigned char)
	@param  padding Blank vertical line padding  padding 4 values
		-# 0 = no padding 
		-# 1 = Left hand side padding only
		-# 2 = Right hand side padding only 
		-# 3 = LHS + RHS
	@param ProgMemLocale Is the data of character[] in PROGMEM? true for PROGMEM , false for SRAM/data
*/
void NOKIA5110_TEXT::LCDCustomChar(const unsigned char character[], uint16_t numChars ,LCDPaddingType_e padding, bool ProgMemLocale ) 
{

	uint16_t column = 0; // max 504 bytes.
	if (padding == LCDPadding_LHS || padding == LCDPadding_Both)
		{
			LCDSPIWrite(LCD_DATA, 0x00); //Blank vertical line padding , LHS
		}
		
	for (column = 0 ; column < numChars ; column++)
		{
		if (ProgMemLocale  == true)
			LCDSPIWrite(LCD_DATA, pgm_read_byte(&(character[column])));
		else
			LCDSPIWrite(LCD_DATA, character[column]);
		}
		
	if (padding == LCDPadding_RHS || padding == LCDPadding_Both)
		{
			LCDSPIWrite(LCD_DATA, 0x00); //Blank vertical line padding RHS
		}
}

/*!
	@brief Draw font 1-6:  8 bit high fonts
	@param character the character to print
*/
void NOKIA5110_TEXT::LCDdraw_fonts_1TO6(char character)
{
	LCDSPIWrite(LCD_DATA, 0x00); // Blank vertical line padding , LHS
	for (uint8_t  column = 0 ; column < _CurrentFontWidth ; column++)
	{
		switch(_CurrentFontNumber)
		{
		case LCDFont_Default: 
		#ifdef NOKIA5110_FONT_Default
			LCDSPIWrite(LCD_DATA, (pgm_read_byte(&pFontDefaultPtr[character - _CurrentFontOffset][column]))); 
		#endif
		break;
		case LCDFont_Thick: 
		#ifdef NOKIA5110_FONT_Thick
			LCDSPIWrite(LCD_DATA, (pgm_read_byte(&pFontThickPtr[character - _CurrentFontOffset][column]))); 
		#endif
		break;
		case LCDFont_HomeSpun: 
		#ifdef NOKIA5110_FONT_HomeSpun
			LCDSPIWrite(LCD_DATA, (pgm_read_byte(&pFontHomeSpunPtr[character - _CurrentFontOffset][column]))); 
		#endif
		break;
		case LCDFont_Seven_Seg: 
		#ifdef  NOKIA5110_FONT_SevenSeg
			LCDSPIWrite(LCD_DATA, (pgm_read_byte(&pFontSevenSegPtr[character - _CurrentFontOffset][column]))); 
		#endif
		break; 
		case LCDFont_Wide: 
		#ifdef NOKIA5110_FONT_Wide
			LCDSPIWrite(LCD_DATA, (pgm_read_byte(&pFontWidePtr[character - _CurrentFontOffset][column]))); 
		#endif
		break;
		case LCDFont_Tiny: 
		#ifdef NOKIA5110_FONT_Tiny
			LCDSPIWrite(LCD_DATA, (pgm_read_byte(&pFontTinyPtr[character - _CurrentFontOffset][column]))); 
		#endif
		break;
		}
	}
	LCDSPIWrite(LCD_DATA, 0x00); // Blank vertical line padding RHS
}

/*!
	@brief used to draw fonts 7 large
	@param character passed a char
	@note 
		-# data format  of uint16_t fetched from font table
		-# 0xAABB font 7  16 bit high
		-# BB Upper byte top half of character
		-# AA  lower byte bot half of character
*/
void NOKIA5110_TEXT::LCDdraw_fonts_7(char character)
{
	#ifdef NOKIA5110_FONT_Large
		uint16_t totalchar = 0;
		uint8_t  topchar =0;
		uint8_t  botchar =0;
		uint8_t column= 0;
		//print upper byte
		for (column = 0 ; column <_CurrentFontWidth ; column++){
				totalchar = (pgm_read_word(&pFontLargePtr[character  - _CurrentFontOffset][column]));
				topchar = totalchar & 0x00FF;
				LCDSPIWrite(LCD_DATA, topchar);
			}
			//Move to next block
			LCDgotoXY(_Col, _Block+1);
			//print lowerbyte
			for (column = 0 ; column < _CurrentFontWidth ; column++){
				totalchar = (pgm_read_word(&pFontLargePtr[character  - _CurrentFontOffset][column]));
				botchar = (totalchar >> 8) & 0xFF;
				LCDSPIWrite(LCD_DATA, botchar);
			}
			//move back to upper block  
			LCDgotoXY(_Col+_CurrentFontWidth , _Block-1);
	#endif
	character += 2; // Get rid of unused variable warning in event of font not defined
}

	/*!
	@brief used to draw fonts: huge and mega , 8 and 9
	@param character passed a char
	@note 
		-# data format of uint32_t fetched from font file
		-# 0xAABBCCDD font 9  32 bit high
		-# 0x--BBCCDD   font 8  24 bit high
		9  font |     8 font      |  data
		 ---- |  ---- |  ----  
		DD | DD|  Upper byte
		CC | CC | upper middle byte
		BB | BB | lower middle byte
		AA | --   | lower byte , -- = n/a for font 8
*/
void NOKIA5110_TEXT::LCDdraw_fonts_8TO9(char character)
{
		uint32_t totaldata = 0;
		uint8_t  topbyte =0;
		uint8_t  middleupperbyte=0;
		uint8_t  middlelowerbyte =0;
		uint8_t  lowerbyte =0;
		uint8_t column= 0;
		//print upper byte  DD
		for (column = 0 ; column < _CurrentFontWidth; column++)
		{
			if (_CurrentFontNumber == LCDFont_Huge)
				{
				#ifdef NOKIA5110_FONT_Huge
					totaldata =  (pgm_read_dword_near(&pFontHugePtr[character - _CurrentFontOffset][column]));
				#endif
			}
			else{
				#ifdef NOKIA5110_FONT_Mega
					totaldata =  (pgm_read_dword_near(&pFontMegaPtr[character - _CurrentFontOffset][column]));
				#endif
				}
			topbyte = totaldata & 0xFF;
			LCDSPIWrite(LCD_DATA, topbyte);
		}
		totaldata=0;
		LCDgotoXY(_Col, _Block+1); //goto next block
		
		// print middle upper byte CC
		for (column = 0 ; column < _CurrentFontWidth ; column++)
		{
			if (_CurrentFontNumber == LCDFont_Huge)
				{
				#ifdef NOKIA5110_FONT_Huge
					totaldata =  (pgm_read_dword_near(&pFontHugePtr[character - _CurrentFontOffset][column]));
				#endif
				}
			else{
				#ifdef NOKIA5110_FONT_Mega
					totaldata =  (pgm_read_dword_near(&pFontMegaPtr[character - _CurrentFontOffset][column]));
				#endif
				}
			middleupperbyte= (totaldata >> 8) & 0xFF;
			LCDSPIWrite(LCD_DATA, middleupperbyte);
		}
		totaldata=0;
		LCDgotoXY(_Col, _Block+1); //goto next block
		
		// print middle lower byte BB
		for (column = 0 ; column < _CurrentFontWidth ; column++)
		{
			if (_CurrentFontNumber == LCDFont_Huge)
				{
				#ifdef NOKIA5110_FONT_Huge
					totaldata =  (pgm_read_dword_near(&pFontHugePtr[character - _CurrentFontOffset][column]));
				#endif
				}
			else
				{
				#ifdef NOKIA5110_FONT_Mega
					totaldata =  (pgm_read_dword_near(&pFontMegaPtr[character - _CurrentFontOffset][column]));
				#endif
				}
			middlelowerbyte = (totaldata >> 16) & 0xFF;
			LCDSPIWrite(LCD_DATA, middlelowerbyte);
		}
		
		// print lower byte AA, no need if printing font huge
		if (_CurrentFontNumber == LCDFont_Huge)
			LCDgotoXY(_Col + _CurrentFontWidth , _Block-2); 	//move back for next character 
		else
			{
			totaldata=0;
			LCDgotoXY(_Col, _Block+1); //goto next block
				for (column = 0 ; column < _CurrentFontWidth ; column++)
				{
				#ifdef NOKIA5110_FONT_Mega
					totaldata =  (pgm_read_dword_near(&pFontMegaPtr[character - _CurrentFontOffset][column]));
					lowerbyte = (totaldata >> 24) & 0xFF;
					LCDSPIWrite(LCD_DATA, lowerbyte);
				#endif
				}
			LCDgotoXY(_Col +  _CurrentFontWidth, _Block-3); 	//move back for next character 
			}
			character += lowerbyte; // Get rid of unused variable warning 
}
/*!
	@brief LCDisSleeping
	@returns  value of _sleep, if true LCD is in sleep mode.
*/
bool NOKIA5110_TEXT::LCDIsSleeping() { return _sleep;}

/*!
	@brief isHardwareSPI
	@details Checks if software SPI is on
	@returns true 1 if hardware SPi on , false 0 for software spi
*/
bool NOKIA5110_TEXT::isHardwareSPI() 
{
  return (_LCD_DIN == -1 && _LCD_CLK == -1);
}
 
/*!
 @brief write is used by print super class simply wraps
 LCDCharacter when called by print  
 @param c The character to print
*/
 #if ARDUINO >= 100
size_t NOKIA5110_TEXT::write(uint8_t c) {
#else
void NOKIA5110_TEXT::write(uint8_t c) {
#endif

LCDCharacter(c);
 
#if ARDUINO >= 100
	return 1;
#endif
}
 
/* =========== EOF ===========*/
