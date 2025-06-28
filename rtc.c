#include <LPC214x.h> 
#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"
#include "rtc.h"

static const char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

// Initialize the RTC with prescalers and enable it
void RTC_Init(void) 
{
    CCR = RTC_CTC_RESET;         // Reset RTC
    PREINT = PREINT_VAL;         // Set prescaler integer
    PREFRAC = PREFRAC_VAL;       // Set prescaler fractional
    CCR = RTC_CCR_EN | RTC_CLKSRC; // Enable RTC with external clock
}

void RTCGetTime(u32 *hr, u32 *mi, u32 *se)
{
    *hr = HOUR;
    *mi = MIN;
    *se = SEC;
}

void RTCGetATime(RTC_TIME* t)
{
    t->hour = HOUR;
    t->min = MIN;
    t->sec = SEC;
}

void DisplayRTCTime(u32 hr, u32 mi, u32 se)
{
    SetCursor(1,0);
    CharLCD((hr / 10) + '0');
    CharLCD((hr % 10) + '0');
    CharLCD(':');
    CharLCD((mi / 10) + '0');
    CharLCD((mi % 10) + '0');
    CharLCD(':');
    CharLCD((se / 10) + '0');
    CharLCD((se % 10) + '0');
}

void RTCGetDate(u32 *dt, u32 *mo, u32 *yr)
{
    *dt = DOM;
    *mo = MONTH;
    *yr = YEAR;
}

void DisplayRTCDate(u32 dt, u32 mo, u32 yr)
{
    SetCursor(2,0);
    CharLCD((dt / 10) + '0');
    CharLCD((dt % 10) + '0');
    CharLCD('/');
    CharLCD((mo / 10) + '0');
    CharLCD((mo % 10) + '0');
    CharLCD('/');
    U32LCD(yr);
}

void RTCGetDay(u32 *day)
{
    *day = DOW;
}

void DisplayRTCDay(u32 day)
{
    SetCursor(1,10);
    StrLCD((u8 *)week[day]);
}

void RTCSetTime(u32 hr, u32 mi, u32 se)
{
    HOUR = hr;
    MIN = mi;
    SEC = se;
}

void RTCSetDate(u32 dt, u32 mo, u32 yr)
{
    DOM = dt;
    MONTH = mo;
    YEAR = yr;
}

void RTCSetDay(u32 day)
{
    DOW = day;
}

u8 RTCGetSeconds(void)
{
    return (u8)SEC;  // Directly return the current seconds from RTC
}
