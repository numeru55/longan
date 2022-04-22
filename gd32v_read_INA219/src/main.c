
// original
// https://github.com/takamame0205/LonganNanoLCD

// font: paw16a.fnt paw16k.fnt   size:8*16
// put them to sdcard

// 160x80 IPS display

// I2C
// https://jhalfmoon.com/dbc/2020/07/02/%E9%B3%A5%E3%81%AA%E3%81%8D%E9%87%8C%E3%81%AE%E3%83%9E%E3%82%A4%E3%82%B3%E3%83%B3%E5%B1%8B89-longan-nano%E3%80%81i2c%E3%81%A7aqm1602/

// PB6/PB7 I2C0

#include "lcd/lcd.h"
#include "gd32vf103.h"
#include <stdio.h>
#include <string.h>

const INA219_address = 0b10000000;

void write_INA219(
    int m,     // mode 0: Pointer Address only 1:address + data
    uint8_t p, //  pointer address
    uint16_t d)
{ // data

    while (i2c_flag_get(I2C0, I2C_FLAG_I2CBSY))
        ;
    i2c_start_on_bus(I2C0);
    while (!i2c_flag_get(I2C0, I2C_FLAG_SBSEND))
        ;
    i2c_master_addressing(I2C0, INA219_address, I2C_TRANSMITTER);
    while (!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND))
        ;
    i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
    while (!i2c_flag_get(I2C0, I2C_FLAG_TBE))
        ;

    // send pointer address

    i2c_data_transmit(I2C0, p);
    while (!i2c_flag_get(I2C0, I2C_FLAG_TBE))
        ;

    if (m == 1)
    {
        i2c_data_transmit(I2C0, (uint8_t)(d >> 8));
        while (!i2c_flag_get(I2C0, I2C_FLAG_TBE))
            ;
        i2c_data_transmit(I2C0, (uint8_t)(d & 0xff));
        while (!i2c_flag_get(I2C0, I2C_FLAG_TBE))
            ;
    }

    i2c_stop_on_bus(I2C0);
    while (I2C_CTL0(I2C0) & 0x0200)
        ;
}

uint16_t read_INA219_2byte()
{

    // I2C read 2byte
    // from GD32VF103_Firmware_Library_V1.0.1/Examples/I2C/Master_receiver_two_bytes

    i2c_ackpos_config(I2C0, I2C_ACKPOS_NEXT);
    while (i2c_flag_get(I2C0, I2C_FLAG_I2CBSY))
        ;
    i2c_start_on_bus(I2C0);
    while (!i2c_flag_get(I2C0, I2C_FLAG_SBSEND))
        ;
    i2c_master_addressing(I2C0, INA219_address, I2C_RECEIVER);
    i2c_ack_config(I2C0, I2C_ACK_DISABLE);
    while (!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND))
        ;
    i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
    while (!i2c_flag_get(I2C0, I2C_FLAG_BTC))
        ;
    while (!i2c_flag_get(I2C0, I2C_FLAG_RBNE))
        ;

    uint8_t d0 = i2c_data_receive(I2C0);
    while (!i2c_flag_get(I2C0, I2C_FLAG_RBNE))
        ;
    uint8_t d1 = i2c_data_receive(I2C0);
    i2c_stop_on_bus(I2C0);
    while (I2C_CTL0(I2C0) & 0x0200)
        ;
    i2c_ackpos_config(I2C0, I2C_ACKPOS_CURRENT);
    i2c_ack_config(I2C0, I2C_ACK_ENABLE);

    return (d0 << 8) | d1;
}

int main(void)
{
    uint8_t str[15];

    LCD_Init();
    LCD_Clear(BLACK);

    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_I2C0);
    gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7); // I2C0

    // init I2C
    i2c_clock_config(I2C0, 400000, I2C_DTCY_2);
    i2c_mode_addr_config(I2C0, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0);
    i2c_enable(I2C0);
    i2c_ack_config(I2C0, I2C_ACK_ENABLE);
    // end of init I2C

    write_INA219(1, 0, 0x39FF); // set pointer address=0 to default
    write_INA219(1, 5, 410);    // set pointer address=5 to 410  near 40.96/0.1

#if 0 
    write_INA219(0,0,0); // set pointer address=0
    sprintf(str,"Config reg. %4x",read_INA219_2byte());
    LCD_ShowString( 0, ( FONT_HEIGHT + 1 ) * 0, str, CYAN );
#endif

    uint32_t c = 0;
    int32_t sum = 0;

    while (1)
    {

        write_INA219(0, 2, 0); // set pointer address=2 Bus Voltage
        uint16_t v0, v1;
        v0 = ((read_INA219_2byte()) >> 3) * 4; // v0 = Bus Voltage [mV]
        v1 = v0 / 1000;
        v0 = v0 - v1 * 1000;

        sprintf(str, "  %d.%03d [V]   ", v1, v0);
        LCD_ShowString(0, (FONT_HEIGHT + 1) * 0, str, WHITE);

        write_INA219(0, 4, 0); // set pointer address=4 Current
        int32_t a;
        a = (int32_t)((int16_t)read_INA219_2byte());
        sprintf(str, "  %+d [mA]     ", a);
        LCD_ShowString(0, (FONT_HEIGHT + 1) * 1, str, GREEN);

        sum += a;

        sprintf(str, "  %+d [mA] ave     ", sum / (int)(c + 1));
        LCD_ShowString(0, (FONT_HEIGHT + 1) * 2, str, YELLOW);

        sprintf(str, "%15d  ", c + 1);
        LCD_ShowString(0, (FONT_HEIGHT + 1) * 3, str, CYAN);
        c++;
    }
}
