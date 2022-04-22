// Longan Nano with Arduino
// INA219 test

// thanks to:
// https://garchiving.com/current-voltage-measurement-with-arduino/

#include <Arduino.h>
extern "C"
{
#include "lcd/lcd.h"
}
#include <stdio.h>
#include <inttypes.h>

#include <Wire.h>

const uint16_t INA219_address = 64; // (1000 000x) >> 1

void write_INA219(
    uint8_t p, //  pointer address
    uint16_t d // data
)
{

    Wire.beginTransmission(INA219_address);
    Wire.write(p);
    Wire.write((d >> 8) & 0xff);
    Wire.write(d & 0xff);
    Wire.endTransmission();
}

uint16_t read_INA219(
    uint8_t p //  pointer address
)
{

    Wire.beginTransmission(INA219_address);
    Wire.write(p);
    Wire.endTransmission();

    uint8_t d0, d1;
    Wire.requestFrom(INA219_address, 16);
    while (Wire.available() < 16)
        ;
    d0 = Wire.read();
    d1 = Wire.read();
    Wire.endTransmission();

    return (d0 << 8) | d1;
}

char str[64];

void setup()
{
    Lcd_Init();
    LCD_Clear(BLACK);
    BACK_COLOR = BLACK;

    Wire.begin(INA219_address);

    write_INA219(0, 0x39FF); // set pointer address=0 to default
    write_INA219(5, 410);    // set pointer address=5 to 410  near 40.96/0.1

    // sprintf(str,"Config reg. %4x",read_INA219(0));
    // LCD_ShowString( 0, 0, (u8 *)str, CYAN );
}

uint32_t c = 0;
int32_t sum = 0;

void loop()
{
    uint16_t v0, v1;
    v0 = ((read_INA219(2)) >> 3) * 4; // address=2: Bus Voltage [mV]
    v1 = v0 / 1000;
    v0 = v0 - v1 * 1000;

    sprintf(str, "  %d.%03d [V]   ", v1, v0);
    LCD_ShowString(0, 0, (u8 *)str, WHITE);

    int32_t a;
    a = (int32_t)((int16_t)read_INA219(4)); // a=4: current
    sprintf(str, "  %+d [mA]     ", a);
    LCD_ShowString(0, 16 * 1.2, (u8 *)str, GREEN);

    sum += a;

    sprintf(str, "  %+d [mA] ave     ", sum / (int)(c + 1));
    LCD_ShowString(0, 16 * 2.4, (u8 *)str, YELLOW);

    sprintf(str, "%15d  ", c + 1);
    LCD_ShowString(0, 16 * 3.6, (u8 *)str, CYAN);
    c++;
}
