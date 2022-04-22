// from
// http://kyoro205.blog.fc2.com/blog-entry-667.html?sp

#include "lcd/lcd.h"

int main( void ) {
	// LCD制御サンプルプログラム

	Lcd_Init();				// lcdを初期化する
	LCD_Clear( BLACK );		// lcdをクリアする
	BACK_COLOR = BLACK;		// 文字の背景色を指定
	LCD_ShowString( 10, 4, "Longan Nano", CYAN );
	LCD_ShowString( 10,24, "LCD Test", WHITE );

	while( 1 );
}