// Longan Nano with Arduino

// LCD, GPIO test

// font data is from:
// https://ftp.gnu.org/old-gnu/intlfonts/intlfonts-1.1-split/

// User (boot0) button  PA8 H:Push L:10k external pulldown
//
//  -----------+
//   (BOOT0) o |
//             | USB
//   (RESET) o |
//  -----------+

#include <Arduino.h>
extern "C" {
#include "lcd/lcd.h"
}
#include <stdio.h>
#include <inttypes.h>

void setup()
{
    Lcd_Init();
    LCD_Clear(BLACK);
    BACK_COLOR = BLACK;

  LCD_ShowString(0,0,(u8 const *)"BDF font demo",WHITE);
  LCD_ShowString(0,16,(u8 const *)" 012345678901234567",CYAN);
  LCD_ShowString(0,32,(u8 const *)" ABCDEFGHIJKLMNOPQR",YELLOW);
  LCD_ShowString(0,48,(u8 const *)" abcdefghijklmnopqr",GREEN);
  //LCD_ShowString(0,64,(u8 const *)" !#$%&'()=-^~@*+<>",MAGENTA);

}

int c=0;

void loop()
{
  String s;
  char str[50];
  //s="   Count "+String(c,DEC);
  s="   Count "+String(c,BIN);
  s.toCharArray(str,50);
  LCD_ShowString(0,64,(u8 const *)str,MAGENTA);
  delay(1000);
  c++;
}
