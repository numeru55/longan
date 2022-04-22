// Longan Nano with Arduino

// RTC test

#include <Arduino.h>
extern "C"
{
#include "lcd/lcd.h"
}
#include <stdio.h>
#include <inttypes.h>

void rtc_configuration(void)
{
  /* enable PMU and BKPI clocks */
  rcu_periph_clock_enable(RCU_BKPI);
  rcu_periph_clock_enable(RCU_PMU);
  /* allow access to BKP domain */
  pmu_backup_write_enable();

  /* reset backup domain */
  bkp_deinit();

  /* enable LXTAL */
  rcu_osci_on(RCU_LXTAL);
  /* wait till LXTAL is ready */
  rcu_osci_stab_wait(RCU_LXTAL);

  /* select RCU_LXTAL as RTC clock source */
  rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);

  /* enable RTC Clock */
  rcu_periph_clock_enable(RCU_RTC);

  /* wait for RTC registers synchronization */
  rtc_register_sync_wait();

  /* wait until last write operation on RTC registers has finished */
  rtc_lwoff_wait();

  /* enable the RTC second interrupt*/
  rtc_interrupt_enable(RTC_INT_SECOND);

  /* wait until last write operation on RTC registers has finished */
  rtc_lwoff_wait();

  /* set RTC prescaler: set RTC period to 1s */
  rtc_prescaler_set(32767);

  /* wait until last write operation on RTC registers has finished */
  rtc_lwoff_wait();
}

void time_adjust(uint32_t t)
{
  /* wait until last write operation on RTC registers has finished */
  rtc_lwoff_wait();
  /* change the current time */
  rtc_counter_set(t);
  /* wait until last write operation on RTC registers has finished */
  rtc_lwoff_wait();
}

void setup()
{
  Lcd_Init();
  LCD_Clear(BLACK);
  BACK_COLOR = BLACK;

  LCD_ShowString(0, 0, (u8 const *)"RTC demo", WHITE);

  rtc_configuration();
  time_adjust(0);
}

void loop()
{
  uint32_t t;

  t = rtc_counter_get();

  uint32_t thh = 0, tmm = 0, tss = 0;

  /* compute  hours */
  thh = t / 3600;
  /* compute minutes */
  tmm = (t % 3600) / 60;
  /* compute seconds */
  tss = (t % 3600) % 60;

  char str[50];
  sprintf(str, " Time: %0.2d:%0.2d:%0.2d", thh, tmm, tss);
  LCD_ShowString(0, 32, (u8 const *)str, YELLOW);
}
