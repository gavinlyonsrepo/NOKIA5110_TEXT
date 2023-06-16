/*!
	@file NOKIA5110_TEXT_FONT_DATA.h
	@brief Font data file , 9 fonts
	@author Gavin Lyons
	@details Project Name NOKIA5110_TEXT URL:https://github.com/gavinlyonsrepo/NOKIA5110_TEXT
	@note Comment in the fonts YOU want, NOKIA5110_FONT_One is default. 
	-#  NOKIA5110_FONT_Default  
	-#  NOKIA5110_FONT_Thick (NO LOWERCASE)
	-#  NOKIA5110_FONT_HomeSpun 
	-#  NOKIA5110_FONT_SevenSeg 
	-#  NOKIA5110_FONT_Wide (NO LOWERCASE)
	-#  NOKIA5110_FONT_Tiny
	-#  NOKIA5110_FONT_Large (NO LOWERCASE)
	-#  NOKIA5110_FONT_Huge Numbers + : . only, use / for space
	-#  NOKIA5110_FONT_Mega Numbers + : . only, use / for space
*/

#ifndef _HEADER_NOKIAFONT_H
#define _HEADER_NOKIAFONT_H

#if (ARDUINO >=100)
  #include "Arduino.h"
   #include "Print.h" 
#else
  #include "WProgram.h"
#endif


//   FONT DEFINE SECTION 
#define NOKIA5110_FONT_Default  /**< (1) default */ 
//#define NOKIA5110_FONT_Thick    /**< (2) thick (NO LOWERCASE) */
//#define NOKIA5110_FONT_HomeSpun /**< (3) HomeSpun */
//#define NOKIA5110_FONT_SevenSeg  /**<  (4) seven segment  */
//#define NOKIA5110_FONT_Wide /**<  (5) wide (NO LOWERCASE) */
//#define NOKIA5110_FONT_Tiny  /**< (6) tiny */
//#define NOKIA5110_FONT_Large /**< (7) Large 12x16 */
//#define NOKIA5110_FONT_Huge  /**< (8) Huge 16x24 */
//#define NOKIA5110_FONT_Mega  /**< (9) Mega 16x32 */


#ifdef  NOKIA5110_FONT_Default
extern const unsigned char (* pFontDefaultPtr)[5];
#endif
#ifdef NOKIA5110_FONT_Thick 
extern const unsigned char (* pFontThickPtr)[7];
#endif
#ifdef NOKIA5110_FONT_HomeSpun
extern const unsigned char (* pFontHomeSpunPtr)[7];
#endif
#ifdef NOKIA5110_FONT_SevenSeg
extern const unsigned char (* pFontSevenSegPtr)[4];
#endif
#ifdef NOKIA5110_FONT_Wide
extern const unsigned char (* pFontWidePtr)[8];
#endif
#ifdef NOKIA5110_FONT_Tiny
extern const  unsigned char (* pFontTinyPtr)[3];
#endif
#ifdef NOKIA5110_FONT_Large
extern const  uint16_t (* pFontLargePtr)[12];
#endif
#ifdef NOKIA5110_FONT_Huge
extern const  uint32_t  (* pFontHugePtr)[16];
#endif
#ifdef NOKIA5110_FONT_Mega
extern const  uint32_t  (* pFontMegaPtr)[16];
#endif



#endif	// endif header guard

// ** EOF **
