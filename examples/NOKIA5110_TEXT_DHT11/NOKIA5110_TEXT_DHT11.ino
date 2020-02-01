// Test file for NOKIA5110_TEXT showing use of library with a DHT11 sensor data.
// URL: https://github.com/gavinlyonsrepo/NOKIA5110_TEXT 

#include <dht.h> //DHT11
#include <NOKIA5110_TEXT.h>

//LCD Nokia 5110 pinout left to right
// RST 1/ CD 2/ DC 3/ DIN 4/ CLK 5
NOKIA5110_TEXT mylcd(2, 3, 4, 5, 6);
#define inverse  false
#define contrast 0xBE // default is 0xBF set in LCDinit, Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
#define bias 0x13 // LCD bias mode 1:48: Try 0x13 or 0x14
#define FontNumber 1

//dht
#define dht_dpin A0 //no ; here. Set equal to channel sensor is on

void setup() {
  // put your setup code here, to run once:
  Serialinit();
  //setup lcd
  mylcd.LCDInit(inverse, contrast, bias); //init the lCD passed inverse true or false
  mylcd.LCDClear(); //clear whole screen
  mylcd.LCDFont(FontNumber); //use Font One default
}

void loop() {
  // put your main code here, to run repeatedly:
  DisplayDHT();
}

//Function to setup serial called from setup
void Serialinit()
{
  Serial.begin(9600);
  delay(100);
  Serial.println("------------- Comms UP------------");
}

//Function  to Display DHT11 sensor data to LCD
void DisplayDHT()
{ //dht11.
  dht DHT;
  static char outstrHum[8];
  static char outstrTemp[8];

  DHT.read11(dht_dpin);
  Serial.println("Humdity as float:");
  Serial.println(DHT.humidity);
  dtostrf(DHT.humidity, 6, 2, outstrHum);
  Serial.println("Humdity as string :");
  Serial.println(outstrHum);
  mylcd.LCDgotoXY(0,0);
  mylcd.LCDString("Humdity");
  mylcd.LCDgotoXY(0,1);
  mylcd.LCDString(outstrHum);
  delay(2000);
  
  Serial.println("Temperature as float :");
  Serial.println(DHT.temperature);
  dtostrf(DHT.temperature, 6, 2, outstrTemp);
  Serial.println("Temperature as string:");
  Serial.println(outstrTemp);
  mylcd.LCDgotoXY(0,2);
  mylcd.LCDString("Temperature");
  mylcd.LCDgotoXY(0,3);
  mylcd.LCDString(outstrTemp);
  delay(2000);
}
