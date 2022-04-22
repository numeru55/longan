// Longan Nano with Arduino

// I2C test

#include <Arduino.h>
extern "C" {
#include "lcd/lcd.h"
}
#include <stdio.h>
#include <inttypes.h>

#include <Wire.h>

void setup()
{
    Lcd_Init();
    LCD_Clear(BLACK);
    BACK_COLOR = BLACK;

    LCD_ShowString( 0, 0, (u8 *)"I2C Scan test", WHITE );
}


void loop()
{
  byte error, address;
  int nDevices;
 
  LCD_ShowString( 0, 16, (u8 *)"Scanning...    ",CYAN);
 
  nDevices = 0;
  for(address = 64; address < 65; address++ ) 
  {
    Wire.begin(address);
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      LCD_ShowString( 0, 16, (u8 *)"Found!         ",CYAN);
      nDevices++;
    }
    else if (error==4) 
    {
      LCD_ShowString( 0, 16, (u8 *)"Error            ",CYAN);
    }    
  }
  if (nDevices == 0)
    LCD_ShowString( 0,16,(u8 *)"No I2C devices found  ",YELLOW);
  else
    LCD_ShowString( 0,16,(u8 *)"Done.                 ",GREEN);
 
  delay(5000);           // wait 5 seconds for next scan
}
