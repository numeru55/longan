
// original
// https://github.com/takamame0205/LonganNanoLCD

// font: paw16a.fnt paw16k.fnt   size:8*16
// put them to sdcard

// 160x80 IPS display

// 

#include "lcd/lcd.h"
#include "gd32vf103.h"
#include <stdio.h>
#include <string.h>

// メインプログラム
int main( void ) {
    uint8_t str[15];

    LCD_Init();				// lcdを初期化する
    LCD_Clear( BLACK );		// lcdをクリアする

    // 文字列表示
    LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 0, "日本語テスト", CYAN );

    uint32_t c=0;

    while( 1 ) {
        delay_1ms(1000);
        sprintf(str,"  Up:  %6d",c);
        LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 3 / 2, str, WHITE );
        delay_1ms(1000);
        sprintf(str," Down: %6d",100000-c);
        LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 3, str, GREEN );

        c++;
    }
}
