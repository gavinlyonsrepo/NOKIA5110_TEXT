/*
* Project Name: Nokia 5110
* File: NOKIA5110_TEXT.h
* Description: Nokia library header file
* Author: Gavin Lyons.
* IC: ATmega328P 
* IDE:  Arduino 1.8.5 
* Created March 2019
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
*/


#ifndef NOKIA5110_TEXT_H
#define NOKIA5110_TEXT_H


#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

//LCD Commands PCD8544_
#define LCD_COMMAND_MODE 0x21  //FUNCTIONSET + extended instruction
#define LCD_CONTRAST     0xBF  //Set LCD VOP Contrast Try 0xB1 or 0xBF if is too dark range = ((0x00-0x7F) |0x80)
#define LCD_TEMP_COEF    0x04  //Set Temp coefficient
#define LCD_BIAS         0x14  // //LCD bias mode 1:48: Try 0x13 or 0x14
#define LCD_FUNCTIONSET  0x20//We must send 0x20 before modifying the display control mode
#define LCD_DISPLAYCONTROL 0x0C //Set display control, normal mode. 0x0D for inverse
#define LCD_POWERDOWN    0x24 //LCD power off


//The DC pin tells the LCD if sending a command or data
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


class NOKIA5110_TEXT {

  public:
	// Constructor 
	NOKIA5110_TEXT(uint8_t LCD_RST, uint8_t LCD_CE, uint8_t LCD_DC, uint8_t LCD_DIN, uint8_t LCD_CLK);
    // Methods
    void LCDInit(void);
	void LCDgotoXY(uint8_t , uint8_t);
	void LCDClear(void);
	void LCDClearBlock(uint8_t);
	void LCDString(const char *characters);
    void LCDsetContrast(uint8_t );
    void LCDenableSleep(void);
    void LCDdisableSleep(void);
    void LCDCharacter(char);
    void LCDWrite(unsigned char , unsigned char);

  private:
  	
	uint8_t _LCD_RST;
	uint8_t _LCD_CE;
	uint8_t _LCD_DC;
	uint8_t _LCD_DIN;
	uint8_t  _LCD_CLK;

    uint8_t  _contrast = LCD_CONTRAST ; //Set LCD VOP Contrast, range = ((0x00-0x7F) |0x80)

	boolean	_sleep;
};


#endif