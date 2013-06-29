#ifndef RTC_H
#define RTC_H

void rtc_init();
void rtc_isr();
u32_t rtc_time();
void rtc_sleep();

#endif
