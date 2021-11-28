
#include <Arduino.h>       
extern "C" {
#include "lcd/lcd.h"
}

#define CYCLES         4  // 2 yields a heartbeat effect
#define SHORT_DELAY  100  // 1/10 second
#define LONG_DELAY  1000  // 1 second

// the setup function runs once when you press reset or power the board
void setup() {
   char buf[64];

   // initialize digital pin LED_BUILTIN as an output.
   pinMode(LED_BUILTIN, OUTPUT);
   
   // initialize LCD and clear the display to black 
   Lcd_Init();
   LCD_Clear(BLACK);

   // write "Hello World!" at the top of the LCD, blue on white
   BACK_COLOR = WHITE;
   sprintf(buf, "Hello World!");
   LCD_ShowString(0, 0, (u8 const *) buf, BLUE);
   BACK_COLOR = BLACK;

   sprintf(buf, "Count:");
   LCD_ShowString(0, 16, (u8 const *) buf, GBLUE);
}

int count = 0;

// the loop function runs over and over again forever
void loop() {
   char buf[64];
   
   sprintf(buf, "%d", count);
   LCD_ShowString(7*8, 16, (u8 const *) buf, YELLOW);
   count++;

   sprintf(buf, "                   ");
   LCD_ShowString(0, 32, (u8 const *) buf, BLACK);
   delay(SHORT_DELAY);

   sprintf(buf, "ON");
   int x = 0;
   for (int i=0; i<CYCLES; i++) {
     digitalWrite(LED_BUILTIN, LOW);    // turn the red LED on (it is active when the pin is LOW)
     LCD_ShowString(x, 32, (u8 const *) buf, GREEN);  //print "ON" on the LCD
     x = x + 3*8;                       // move cursor 3 chars to the right 
     delay(SHORT_DELAY);                // wait for a short on period
     digitalWrite(LED_BUILTIN, HIGH);   // turn the red LED off (by setting the active LOW pin HIGH)
     delay(SHORT_DELAY);                // wait for a short off period
   }    
   digitalWrite(LED_BUILTIN, HIGH);     // turn the LED off
   sprintf(buf, "OFF");
   LCD_ShowString(x, 32, (u8 const *) buf, RED);  //print "OFF" on the LCD
   delay(LONG_DELAY);                   // wait for a long off period
}
