#ifndef _RTC_H
#define _RTC_H

#include "types.h"

void RTC_Init(void);

void RTCGetTime(u32 *,u32 *,u32 *);
void DisplayRTCTime(u32,u32,u32);

void RTCGetDate(u32 *,u32 *,u32 *);
void DisplayRTCDate(u32,u32,u32);

void RTCGetDay(u32 *);
void DisplayRTCDay(u32);

void RTCSetTime(u32,u32,u32);
void RTCSetDate(u32,u32,u32);
void RTCSetDay(u32);

u8 RTCGetSeconds(void);
typedef struct {
    u8 sec;
    u8 min;
    u8 hour;
    u8 day;
    u8 date;
    u8 month;
    u16 year;
} RTC_TIME;

void RTCGetATime(RTC_TIME* t);

#endif
