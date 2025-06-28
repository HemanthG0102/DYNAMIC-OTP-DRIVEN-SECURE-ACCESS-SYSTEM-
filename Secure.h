//Secure.h
#ifndef SECURE_H
#define SECURE_H

#include <LPC214x.h>  
#include "types.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "delay.h"
#include "i2c_defines.h"

// EINT0 defines
#define EINT0_PIN      16       // Port pin for EINT0
#define EINT0_VIC_CHNO 14       // VIC channel number for EINT0
#define EINT0_LED      27        // LED toggle pin for interrupt

int passwordVerify(u8 *p);
void passwordChange(void);
void rtc_enter(int, int, int);
int otp_entry(void);
void def_Password(void);
void UART0_Init(void);

extern u8 otp_str[6]; // OTP storage

#endif
