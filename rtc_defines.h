#ifndef _RTC_DEFINES_H
#define _RTC_DEFINES_H

#include "sys_config.h"

// RTC Prescaler values
#define PREINT_VAL  ((int)(PCLK / 32768) - 1)
#define PREFRAC_VAL (int)(PCLK - ((PREINT_VAL + 1) * 32768))

// RTC Control Register Bits
#define RTC_CCR_EN      (1 << 0)
#define RTC_CTC_RESET   (1 << 1)
#define RTC_CLKSRC      (1 << 4)

#endif
