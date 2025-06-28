//Secure.c
#include "Secure.h"
#include "lcd.h"
#include "keypad.h"
#include "lcd_defines.h"
#include "rtc.h"
#include <string.h>
#include <stdio.h>

#define I2C_EEPROM_SA 0x50 // 7-bit slave addr

u32 alh, almin, alsec;
u8 passn[6];

#define OTP_TIMEOUT_SECONDS 60

int passwordVerify(u8 *p)
{
    s32 i;
    u8 buff[6];
    init_i2c();

    i2c_eeprom_seq_read(I2C_EEPROM_SA, 0x0000, buff, 6);

    for(i = 0; i < 6; i++)
    {
        if(p[i] != buff[i])
        {
            return 0; // Mismatch
        }
    }
    return 1; // Verified
}

void passwordChange()
{
    s32 i;
    u8 passn[6];  // declare here if not global

    CmdLCD(CLEAR_LCD);
    delay_ms(2);
    StrLCD("Enter NPassword:");
    CmdLCD(GOTO_LINE2_POS0);

    for(i = 0; i < 6; i++)
    {
        passn[i] = keyscan();
        CharLCD(passn[i]);
        delay_ms(300);
        CmdLCD(SHIFT_CUR_LEFT);
        CharLCD('*');
    }

    CmdLCD(CLEAR_LCD);
    StrLCD("Saving...");
    delay_ms(1);

    i2c_eeprom_page_write(I2C_EEPROM_SA, 0x0000, passn, 6);
    delay_ms(10);

    CmdLCD(CLEAR_LCD);
    StrLCD("Password");
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("Changed!");
    delay_s(2);

    CmdLCD(CLEAR_LCD);  // prepare LCD for return to main
}



int otp_entry()

{

    u8 otp[5]; // 4 digits + null

    u8 i = 0;

    u8 key;

    int elapsed_sec;

    RTC_TIME startTime, currTime;


    // Get start time

    RTCGetATime(&startTime);


    CmdLCD(CLEAR_LCD);

    delay_ms(2);

    StrLCD("Enter OTP:");


    CmdLCD(GOTO_LINE2_POS0);

    StrLCD("OTP: ");


    while (i < 4)

    {

        key = keyscan();


        if (key >= '0' && key <= '9')

        {

            otp[i++] = key;


            CharLCD('*'); // Show '*'

            delay_ms(250);

        }


        RTCGetATime(&currTime);


        // Calculate elapsed time in seconds

        elapsed_sec = (currTime.min - startTime.min) * 60 + (currTime.sec - startTime.sec);

        if (elapsed_sec < 0) elapsed_sec += 60; // Handle minute wrap


        if (elapsed_sec >= OTP_TIMEOUT_SECONDS)

        {

            CmdLCD(CLEAR_LCD);

            StrLCD("TIMEOUT");

            delay_s(2);

            return 0;

        }

    }


    otp[4] = '\0'; // Null-terminate


    // Compare entered OTP with actual

    if (strcmp((const char *)otp, (const char *)otp_str) == 0)

        return 1;


    CmdLCD(CLEAR_LCD);

    StrLCD("Wrong OTP!");

    delay_s(2);

    return 0;

}


void def_Password()
{
    u8 default_pass[6] = {'0','0','0','0','0','0'};
    i2c_eeprom_page_write(I2C_EEPROM_SA, 0x0000, default_pass, 6);
    delay_ms(10);
}
