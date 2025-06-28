//gsm.c
void uart_gsm(char *number, char *msg)
{
    #define GSM_RESP_TIMEOUT_MS 5000

    char respBuffer[100];
    int i, c;
    unsigned int startTime;

    UART0_Init();
    delay_ms(2);

    CmdLCD(CLEAR_LCD);
    delay_ms(2);

    // Helper function: read GSM response with timeout
    // returns 1 if expected substring found, else 0
    int wait_for_response(const char* expected, unsigned int timeout_ms)
    {
        unsigned int len = 0;
        unsigned int start = 0;        
        start = 0;
        unsigned int ticks_start = 0; // you may implement a millis timer if available
        unsigned int ticks_now = 0;

        start = 0;
        for (len = 0; len < sizeof(respBuffer) - 1; len++)
            respBuffer[len] = 0;

        startTime = 0; // some timer here - you must implement or adapt this to your delay mechanism

        unsigned int timer = 0; // pseudo timer variable
        // For this example, we simulate delay with a for loop - you must replace with your timer function

        len = 0;
        startTime = 0;
        unsigned int timeoutTicks = timeout_ms * (CCLK / 1000 / 12); // rough ticks for timeout

        // read chars until timeout or expected found
        while (timer < timeoutTicks)
        {
            if ((U0LSR & (1 << RDR_BIT)) != 0)
            {
                c = U0RBR; // read char

                if (len < sizeof(respBuffer) - 1)
                {
                    respBuffer[len++] = (char)c;
                    respBuffer[len] = '\0';

                    if (strstr(respBuffer, expected) != NULL)
                        return 1; // found expected response
                    if (strstr(respBuffer, "ERROR") != NULL)
                        return 0; // error received
                }
            }
            // simple delay - you should replace with accurate timer tick or ms delay function
            delay_us(100);
            timer++;
        }

        return 0; // timeout - expected response not found
    }

    // 1. Test module with "AT"
    UART0_TxString("AT\r\n");
    if (!wait_for_response("OK", GSM_RESP_TIMEOUT_MS))
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ERROR");
        return;
    }

    // 2. Set SMS text mode
    UART0_TxString("AT+CMGF=1\r\n");
    if (!wait_for_response("OK", GSM_RESP_TIMEOUT_MS))
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ERROR");
        return;
    }

    // 3. Send SMS command with number
    UART0_TxString("AT+CMGS=\"");
    UART0_TxString(number);
    UART0_TxString("\"\r\n");

    if (!wait_for_response(">", GSM_RESP_TIMEOUT_MS))
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ERROR");
        return;
    }

    // 4. Send the OTP message plus agency info, then Ctrl+Z
    UART0_TxString(msg);
    UART0_TxString("\r\nMessage from Vector Security Agency\r\n");
    UART0_TxChar(26); // Ctrl+Z to send SMS

    // Wait for message send confirmation
    if (!wait_for_response("OK", 10000)) // message send can take longer
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ERROR");
        return;
    }

    // 5. Display success message
    CmdLCD(CLEAR_LCD);
    delay_ms(2);
    StrLCD("MSG SENT!");
    delay_s(2);
}
