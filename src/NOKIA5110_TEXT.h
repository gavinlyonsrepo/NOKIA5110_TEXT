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
   #include "Print.h" 
#else
  #include "WProgram.h"
#endif

// **********************************************
// ******* SPI HARDWARE SECTION ************
//Comment this define(SPIHW_ON) in for hardware SPI , software SPI is default
//#define SPIHW_ON 

#ifdef SPIHW_ON 
	#include <SPI.h>
	#define SPI_FREQ 8000000 // Mhz
	//#define SPI_FREQ 1000000 // Mhz, 
#endif

#define LCD_HIGH_FREQ_DELAY 1 // uS delay used in sw SPI, increase for high MC Freq 
// ****** END OF SPI HARDWARE SECTION ****  
// **********************************************


// LCD Commands PCD8544_
#define LCD_COMMAND_MODE 0x21  // FUNCTIONSET + extended instruction
#define LCD_CONTRAST     0xBF  // Set LCD VOP Contrast Try 0xB1 or 0xBF if is too dark range = ((0x00-0x7F) |0x80)
#define LCD_TEMP_COEF    0x04  // Set Temp coefficient
#define LCD_BIAS         0x14  // LCD bias mode 1:48: Try 0x12 , 0x13 or 0x14
#define LCD_FUNCTIONSET  0x20  // We must send 0x20 before modifying the display control mode
#define LCD_DISPLAYCONTROL 0x0C // Set display control, normal mode. 0x0D for inverse
#define LCD_DISPLAYCONTROL_INVERSE 0x0D // Set display control, inverse mode. 0x0D for inverse
#define LCD_POWERDOWN    0x24 // LCD power off
#define LCD_RESET_DELAY 50 // mS

// The DC pin tells the LCD if sending a command or data
#define LCD_COMMAND 0
#define LCD_DATA 1

// 84 by 48 pixels screen
#define LCD_X 84
#define LCD_Y 48

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

// Section :: enums

typedef enum {
	LCDFont_Default = 1, // Default 5X8
	LCDFont_Thick = 2, // Thick 7X8  (NO LOWERCASE LETTERS)
	LCDFont_HomeSpun = 3, // homespun 7X8 
	LCDFont_Seven_Seg = 4, // seven segment 4X8
	LCDFont_Wide = 5, // Wide  8X8 (NO LOWERCASE LETTERS)
	LCDFont_Tiny = 6, // tiny 3x8
	LCDFont_Large = 7, // Large 12 X 16 (no lowercase letters)
	LCDFont_Huge = 8, // Huge 16 X24 (numbers + . : only) 
	LCDFont_Mega = 9 // Mega 16 X 32 (numbers + . : / only)
} LCDFontType_e; // type of font


typedef enum {
	LCDPadding_None = 0, // no padding 
	LCDPadding_LHS = 1, // Left hand side padding only
	LCDPadding_RHS = 2, // Right hand side padding only 
	LCDPadding_Both = 3 // LHS + RHS padding
} LCDPaddingType_e; // Padding value


class NOKIA5110_TEXT  : public Print{

  public:
   
	// Constructors
	 NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC, int8_t LCD_DIN, int8_t LCD_CLK);
	 NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC);
	 ~NOKIA5110_TEXT(){};
	 
	// Methods
	
	void LCDInit(bool Inverse = false, uint8_t Contrast = LCD_CONTRAST,uint8_t Bias = LCD_BIAS);
	void LCDsetContrast(uint8_t contrast);
	void LCDenableSleep(void);
	void LCDdisableSleep(void);
	void LCDSPIWrite(unsigned char DataOrCommand, unsigned char data);
	bool LCDIsSleeping(void);
		
	void LCDgotoXY(uint8_t x, uint8_t y);
	void LCDClear(uint8_t FillData = 0x00);
	void LCDClearBlock(uint8_t RowBlockNum = 0);
	void LCDFillBlock(uint8_t FillData = 0xFF , uint8_t RowBlockNum = 0);
	
	void LCDFont(LCDFontType_e FontNumber);
	void LCDCharacter(char character);
	void LCDString(const char *characters);
	void LCDSetPixel(uint8_t col = 0, uint8_t row = 0);
	void LCDCustomChar(const unsigned char character[], uint16_t numChars, LCDPaddingType_e, bool ProgMemLocale );

#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void   write(uint8_t);
#endif

  private:
	
	void LCDdraw_fonts_1TO6(char character); // 8 bit tall fonts
	void LCDdraw_fonts_7(char character); // 16 bit tall fonts
	void LCDdraw_fonts_8TO9(char character); // 24 and 32 bit tall fonts
	bool isHardwareSPI(void);
	
	uint8_t _LCD_RST;
	uint8_t _LCD_CE;
	uint8_t _LCD_DC;
	int8_t _LCD_DIN; // Software SPI only
	int8_t  _LCD_CLK; // Software SPI only

	uint8_t  _contrast = LCD_CONTRAST ; 
	uint8_t  _bias = LCD_BIAS ; 
	bool	 _inverse = false;
	bool _sleep = false; // False awake , true sleep;
	uint8_t _Block = 0; 
	uint8_t _Col = 0;
	
	uint8_t	_CurrentFontNumber = LCDFont_Default;
	uint8_t _CurrentFontWidth =  5;
	uint8_t _CurrentFontOffset = 0x20 ;
	
};


#endif
