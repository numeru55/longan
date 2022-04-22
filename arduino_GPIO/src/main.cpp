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

  // initialize LED digital pin as an output.
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  digitalWrite(LED_RED, HIGH); // off
  digitalWrite(LED_GREEN, HIGH); // off
  digitalWrite(LED_BLUE, HIGH); // off

  LCD_ShowString(0,0,(u8 const *)"",WHITE);
  LCD_ShowString(0,16,(u8 const *)"GPIO test",CYAN);
  LCD_ShowString(0,32,(u8 const *)"",YELLOW);
  LCD_ShowString(0,48,(u8 const *)"   PUSH BOOT0",GREEN);
  LCD_ShowString(0,64,(u8 const *)"",MAGENTA);

  pinMode(PA8, INPUT);
}


void loop()
{
  if (digitalRead(PA8)) {
    digitalWrite(LED_GREEN, LOW);
    delay(50);
    digitalWrite(LED_GREEN, HIGH);
    delay(200);
    digitalWrite(LED_BLUE, LOW);
    delay(50);
    digitalWrite(LED_BLUE, HIGH);
    delay(200);
  } else {
      digitalWrite(LED_RED, LOW); // on
      delay(1000);
      digitalWrite(LED_RED, HIGH); // off
      delay(1000);
  }
}
