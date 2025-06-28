// uart_gsm.c
#include <lpc214x.h>
#include <string.h>
#include "uart.h"
#include "delay.h"
#include "lcd.h"
#include "defines.h"
#include "uart_gsm.h"

// Wait for expected response string from GSM module within timeout
int wait_for_response(const char* expected, unsigned int timeout_ms)
{
    char respBuffer[100] = {0};
    unsigned int len = 0;
    unsigned int elapsed_ms = 0;

    while (elapsed_ms < timeout_ms)
    {
        if (U0LSR & (1 << RDR_BIT))
        {
            char c = U0RBR;
            if (len < sizeof(respBuffer) - 1)
            {
                respBuffer[len++] = c;
                respBuffer[len] = '\0';

                if (strstr(respBuffer, expected) != NULL)
                    return 1;
                if (strstr(respBuffer, "ERROR") != NULL)
                    return 0;
            }
        }
        delay_ms(1);
        elapsed_ms++;
    }
    return 0;
}

int uart_gsm(char *number, char *msg)
{
    // Clear LCD and display status
    CmdLCD(CLEAR_LCD);
    delay_ms(5);

    // 1. Test GSM module
    UART0_TxString("AT\r\n");
    if (!wait_for_response("OK", GSM_RESP_TIMEOUT_MS))
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ERROR1");
		delay_s(1);
        return 0;
    }

	// E. Set SMS mode to text
    UART0_TxString("AT+CMGF=1\r\n");
    if (!wait_for_response("OK", GSM_RESP_TIMEOUT_MS))
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ERROR2");
		delay_s(1);
        return 0;
    }
    // 2. Set SMS mode to text
    UART0_TxString("ATE0\r\n");
    if (!wait_for_response("OK", GSM_RESP_TIMEOUT_MS))
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ERRORE");
		delay_s(1);
        return 0;
    }

    // 3. Send recipient number
    UART0_TxString("AT+CMGS=\"");
    UART0_TxString(number);  // Full international format number
    UART0_TxString("\"\r\n");

    if (!wait_for_response(">", GSM_RESP_TIMEOUT_MS))
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ERROR3");
		delay_s(1);
        return 0;
    }

    // 4. Send message + Ctrl+Z
    UART0_TxString(msg);
    UART0_TxString("\r\nMessage from Vector Security Agency\r\n");
    UART0_TxChar(26); // Ctrl+Z

    // 5. Wait for confirmation
    if (!wait_for_response("OK", 10000))
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ERROR4");
		delay_s(1);
        return 0;
    }

    CmdLCD(CLEAR_LCD);
    delay_ms(50);
    StrLCD("MSG SENT!");
    delay_s(2);
    return 1;
}

