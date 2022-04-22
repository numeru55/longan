// from:
// GD32VF103_Firmware_Library_V1.0.1/Examples/TIMER/TIMER1_timebase

// PA1  LED_G L:ON H:OFF
// PA2  LED_B L:ON H:OFF
// PA8  GD_BOOT0  H:Push L:10k external pulldown
// PC13 LED_R L:ON H:OFF

// PA13 JTMS
// PA14 JTCK
// PA15 JTDI
// PB3  JTDO

// PA10 GD_UART0_RX
// PA9  GD_UART0_TX

// PB12 SPI1_CS_TF
// PB14 SPI1_MISO
// PB13 SPI1_SCLK
// PB15 SPI1_MOSI

// PA7  TFT_SDA
// PA5  TFT_SCL
// PB0  TFT_RS
// PB1  TFT_RST
// PB2  TFT_CS

// USER PIN

// PA0 TIMER0

#include "lcd/lcd.h"
#include "gd32vf103.h"
#include <stdio.h>
#include <string.h>

void gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);

    /*Configure PA0(TIMER1 CH0) as alternate function*/
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);

}

void timer_config(void)
{
    /* ----------------------------------------------------------------------------            
    TIMER1 Configuration:                                                                      
    TIMER1CLK = SystemCoreClock/5400 = 20KHz.                                                  
    TIMER1 configuration is timing mode, and the timing is 0.2s(4000/20000 = 0.2s).            
    CH0 update rate = TIMER1 counter clock/CH0CV = 20000/4000 = 5Hz.                           

    -- update 0.2s -> 1s
    period 4000 -> 20000

    ---------------------------------------------------------------------------- */
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER1);

    timer_deinit(TIMER1);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER1 configuration */
    timer_initpara.prescaler         = 5399;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 20000;
    // timer_initpara.period            = 4000;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_init(TIMER1, &timer_initpara);

    /* initialize TIMER channel output parameter struct */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    /* CH0,CH1 and CH2 configuration in OC timing mode */
    timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER1, TIMER_CH_0, &timer_ocinitpara);

    /* CH0 configuration in OC timing mode */
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, 2000);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_0, TIMER_OC_MODE_TIMING);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

    timer_interrupt_enable(TIMER1, TIMER_INT_CH0);
    timer_enable(TIMER1);
}

uint32_t c=0;

void TIMER1_IRQHandler(void)
{
    if(SET == timer_interrupt_flag_get(TIMER1, TIMER_INT_CH0)){
        /* clear channel 0 interrupt bit */
        timer_interrupt_flag_clear(TIMER1, TIMER_INT_CH0);

        // toggle LED_B
		// gpio_bit_write(GPIO_PORT_LED_B, GPIO_PIN_LED_B,
        //     ! gpio_input_bit_get( GPIO_PORT_LED_B, GPIO_PIN_LED_B ));

        uint8_t str[15];
        sprintf(str,"Count %d",c);        
        LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 3 / 2, str, YELLOW );

        c++;
    }
}


int main( void ) {
    uint8_t str[15];

    LCD_Init();
    LCD_Clear( BLACK );

    LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 0, "TIMER DEMO", WHITE );

    led_init();

    gpio_config();
    eclic_global_interrupt_enable();
    eclic_set_nlbits(ECLIC_GROUP_LEVEL3_PRIO1);
    eclic_irq_enable(TIMER1_IRQn,1,0);
    timer_config();
    
    while( 1 ) {
    }
}
