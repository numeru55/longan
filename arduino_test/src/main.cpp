
#include <Arduino.h>

//#include <stdio.h>
//#include <inttypes.h>

//#include <USBSerial.h>

#include <CDC.h>

void setup()
{
  CDC_Init();
}

void loop()
{
  CDC_write((uint8_t *)"aaa ",4);
  delay(1000);
}