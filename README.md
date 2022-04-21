# longan

```platformio.ini
[env:sipeed-longan-nano]
platform = gd32v
board = sipeed-longan-nano
framework = arduino
platform_packages = framework-arduino-gd32v @ https://github.com/mpmarks/framework-arduino-gd32v.git

upload_protocol = dfu
```

```main.cpp
// blink
#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(100);
}
```

https://github.com/sipeed/Longan_GD32VF_examples

