# Changelog

* version 1.0.0 March 2019
	* first release

* Version 1.0.1 May 2019
	* Keywords.txt modified for tabs instead of spaces as per "per1234" 
	* pull request on github

* Version 1.1.0 Dec 2019
	* Added two new examples.
	* Added inverse and bias control.
	* Added optional Aurebesh font.
	
* version 1.2.0 Jan 2020
	* Added "Font two"
	
* Version 1.3.0 Feb 2020
	* Use define statements to let User pick required fonts
	for their use case 
	* Method LCDFont() input parameter is changed from bool to int to enable font selection
	* Added 3 new fonts( Wide, Tiny and Segment) 
	* created A set pixel method for basic graphics
	* removed pinmode statements from constructor
	
* Version 2.0.0 July 2020
	* LCDFillBlock() method added
	* Modify LCDclear() to take parameter to fill screen with pattern.
	* LCDCustomChar() method added to display custom characters and bitmap
	* Added two new Large Fonts,  Font 7 Large(16*12) and Font 8 Huge (24*16)
	* Added new example file. 
	
* Version 2.1.0 August 2020
	* "Bias" member created.
	* Issue 1 on github closed , public access to "sleep" member granted via new function LCDisSleeping()
	* Added font 9 "Mega" 16*32, takes 4 row blocks, 5 characters max. 
	* Changed function header of "LCDCustomChar()" so it complies for ESP32
	* Tested on new boards : ESP32, ESP8266 and STM32 "blue pill" , It Works!!
	
