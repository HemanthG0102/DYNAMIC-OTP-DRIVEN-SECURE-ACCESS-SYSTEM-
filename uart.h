#ifndef UART_H
#define UART_H

#include <lpc214x.h>
// UART0 Register Definitions
/*
#define U0RBR   (*((volatile unsigned char *) 0xE000C000)) // Receiver Buffer Register
#define U0THR   (*((volatile unsigned char *) 0xE000C000)) // Transmit Holding Register
#define U0DLL   (*((volatile unsigned char *) 0xE000C000)) // Divisor Latch LSB
#define U0DLM   (*((volatile unsigned char *) 0xE000C004)) // Divisor Latch MSB
#define U0LCR   (*((volatile unsigned char *) 0xE000C00C)) // Line Control Register
#define U0LSR   (*((volatile unsigned char *) 0xE000C014)) // Line Status Register 
*/
#include "delay.h"
#include "types.h"
#include "defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "pin_cfg.h"

#define BAUDRATE    9600
#define DIVISOR     (PCLK / (16 * BAUDRATE))

// UART0 Line Control Register bits
#define BIT_5       0x00
#define BIT_6       0x01
#define BIT_7       0x02
#define BIT_8       0x03
#define WORD_LENGTH_SELECT BIT_8 
#define DLAB_BIT    7    

// UART0 Line Status Register bits
#define RDR_BIT     0      // Receiver Data Ready
#define THRE_BIT    5      // Transmitter Holding Register Empty
#define TEMT_BIT    6      // Transmitter Empty

#define TXD0 0
#define RXD0 1

void UART0_Init(void);
void UART0_TxChar(char ch);
void UART0_TxString(char *str);

#endif
