#ifndef __SYSTEM_CONFIG_H__
#define __SYSTEM_CONFIG_H__

#define FOSC        12000000UL          // 12 MHz crystal
#define CCLK        (5 * FOSC)          // 60 MHz CPU clock
#define PCLK        (CCLK / 4)          // 15 MHz peripheral clock

#endif
