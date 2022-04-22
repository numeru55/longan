# Longan Nano LCD with Arduino

Font data is converted from:

https://ftp.gnu.org/old-gnu/intlfonts/intlfonts-1.1-split/

to include/lcd/lcd.h

# platformio.ini

thanks to mpmarks

```
[env:sipeed-longan-nano]
platform = gd32v
board = sipeed-longan-nano
framework = arduino
platform_packages = framework-arduino-gd32v @ https://github.com/mpmarks/framework-arduino-gd32v.git
upload_protocol = dfu
```