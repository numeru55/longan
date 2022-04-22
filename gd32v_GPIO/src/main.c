// GPIO demo

#include "lcd/lcd.h" // edited to turn OFF LED blink
#include "gd32vf103.h"
#include <stdio.h>
#include <string.h>

// メインプログラム
int main( void ) {
    uint8_t str[15];

    LCD_Init();
    LCD_Clear( BLACK );

    LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 0, "Push BOOT0 ->", WHITE );

    led_init();

    // Boot0 button: PA8  H:Push L:10k external pulldown

    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    while( 1 ) {

        delay_1ms(1000);
        LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 3 / 2, "   RED    ", RED );
        led_on(LED_R);
        led_off(LED_G);
        led_off(LED_B);

        delay_1ms(1000);
        LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 3 / 2, "   GREEN  ", GREEN );
        led_off(LED_R);
        led_on(LED_G);
        led_off(LED_B);

        delay_1ms(1000);
        LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 3 / 2, "   BLUE   ", BLUE );
        led_off(LED_R);
        led_off(LED_G);
        led_on(LED_B);

        // read BOOT0 button

        if (gpio_input_bit_get(GPIOA, GPIO_PIN_8)) {
            LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 3, "      Pressed.", YELLOW );
            delay_1ms(1000);
            LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 3, "              ", YELLOW );
        }


    }
}
