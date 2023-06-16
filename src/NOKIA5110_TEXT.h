/*!
	@file NOKIA5110_TEXT.h
	@brief Nokia library header file
	@author Gavin Lyons
	@details Project Name NOKIA5110_TEXT URL:https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
*/

#ifndef NOKIA5110_TEXT_H
#define NOKIA5110_TEXT_H

#if (ARDUINO >=100)
  #include "Arduino.h"
   #include "Print.h" 
#else
  #include "WProgram.h"
#endif


/*! 
 @brief SPI HARDWARE SECTION  Comment this define(SPIHW_ON) in for hardware SPI , software SPI is default
*/
//#define SPIHW_ON 

#ifdef SPIHW_ON 
	#include <SPI.h>
	#define SPI_FREQ 8000000 // Mhz
	//#define SPI_FREQ 1000000 // Mhz, 
#endif

#define LCD_HIGH_FREQ_DELAY 1 // uS delay used in sw SPI, increase for high MC Freq 
// ****** END OF SPI HARDWARE SECTION ****  



// LCD Commands PCD8544
#define LCD_COMMAND_MODE 0x21  /**< FUNCTIONSET + extended instruction */
#define LCD_CONTRAST     0xBF  /**<  Set LCD VOP Contrast Try 0xB1 or 0xBF if is too dark range = ((0x00-0x7F) |0x80) */
#define LCD_TEMP_COEF    0x04 /**<  Set Temp coefficient */
#define LCD_BIAS         0x14  /**< LCD bias mode 1:48: Try 0x12 , 0x13 or 0x14 */
#define LCD_FUNCTIONSET  0x20  /**< We must send 0x20 before modifying the display control mode */
#define LCD_DISPLAYCONTROL 0x0C /**<  Set display control, normal mode. 0x0D for inverse */
#define LCD_DISPLAYCONTROL_INVERSE 0x0D /**<  Set display control, inverse mode. 0x0D for inverse */
#define LCD_POWERDOWN    0x24 /**< LCD power off */
#define LCD_RESET_DELAY 50 //**<  Reset delay in mS */

// The DC pin tells the LCD if sending a command or data
#define LCD_COMMAND 0 /**< Send an LCD command */
#define LCD_DATA 1 /**< Send data to  LCD*/

// 84 by 48 pixels screen
#define LCD_X 84 /**< LCD Width in pixels  */
#define LCD_Y 48 /**< LCD Height in pixels  */

// GPIO abstraction on/off
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

/*! Enum to define current font type selected  */
enum LCDFontType_e : uint8_t 
{
	LCDFont_Default = 1, /**<  Default 5X8 */
	LCDFont_Thick = 2, /**<  Thick 7X8  (NO LOWERCASE LETTERS */
	LCDFont_HomeSpun = 3, /**<  homespun 7X8  */
	LCDFont_Seven_Seg = 4, /**<  seven segment 4X8 */
	LCDFont_Wide = 5, /**<  Wide  8X8 (NO LOWERCASE LETTERS) */
	LCDFont_Tiny = 6, /**<  tiny 3x8 */
	LCDFont_Large = 7, /**<  Large 12 X 16 (no lowercase letters) */
	LCDFont_Huge = 8, /**<  Huge 16 X24 (numbers + . : only)  */
	LCDFont_Mega = 9 /**<  Mega 16 X 32 (numbers + . : / only) */
};

/*! Padding type to add to selected  font and custom character , padding consist of a single byte of data , vertical column */
enum  LCDPaddingType_e : uint8_t{
	LCDPadding_None = 0, /**<  no padding */
	LCDPadding_LHS = 1,  /**<  Left hand side padding only  */
	LCDPadding_RHS = 2,  /**<  Right hand side padding only  */
	LCDPadding_Both = 3  /**<  Both LHS + RHS padding */
};

class NOKIA5110_TEXT  : public Print{

  public:
   
	 NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC, int8_t LCD_DIN, int8_t LCD_CLK);
	 NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC);
	 ~NOKIA5110_TEXT(){};
	
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

	void LCDdraw_fonts_1TO6(char character); 
	void LCDdraw_fonts_7(char character); 
	void LCDdraw_fonts_8TO9(char character); 
	bool isHardwareSPI(void);

	uint8_t _LCD_RST;   /**< GPIO for reset line */
	uint8_t _LCD_CE;    /**< GPIO for Chip enable  line */
	uint8_t _LCD_DC;    /**< GPIO for Data or command line */
	int8_t _LCD_DIN;    /**< GPIO for Data line (MOSI) , Software SPI only*/ 
	int8_t  _LCD_CLK;   /**< GPIO for SPI clock line, Software SPI only*/ 

	uint8_t  _contrast = LCD_CONTRAST ;  /**<  LCD Contrast */
	uint8_t  _bias = LCD_BIAS ; /**<  LCD Bias */
	bool	 _inverse = false;   /**<  LCD Inversion mode , Pixels black or white*/
	bool _sleep = false;  /**<  LCD Sleep mode false awake , true LCD sleep */
	uint8_t _Block = 0;  /**< LCD block 0-5, screen is heigh of 48 pixels is divided into 6 block's each a byte high */
	uint8_t _Col = 0;   /**< LCD Column 0-83 */
	
	uint8_t	_CurrentFontNumber = LCDFont_Default; /**<  Stores Current font 1-9*/
	uint8_t _CurrentFontWidth =  5;                      /**<  Stores Current font width*/
	uint8_t _CurrentFontOffset = 0x20 ;   /**<  Stores Current font offset in the ASCII table*/
	
};


#endif
