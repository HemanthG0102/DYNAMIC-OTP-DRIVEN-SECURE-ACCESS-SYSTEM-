#include <LPC214x.h>
#include <time.h>
#include <stdlib.h>	
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "keypad.h"
#include "lcd.h"
#include "rtc.h"
#include "lcd_defines.h"
#include "Secure.h"
#include "sys_config.h"
#include "pin_cfg.h"
#include "defines.h"
#include "motor.h"
#include "uart_gsm.h"


unsigned char otp_str[6];

int uart_gsm(char* number, char* msg);
char number[15] = "+917306664415"; 

u32 keyc,otp,changePasswordFlag;
u8 pass[6];
s8 i;


void eint0_isr(void) __irq
{
	  delay_ms(50);
	  SETBIT(IOSET0,EINT0_LED);
      changePasswordFlag = 1;
      EXTINT = 1<<0;
      VICVectAddr = 0;	
}	

void Enable_EINT0(void)
{
	//configure P0.1/P0.16 as EINT0 input pin
	CfgPortPin(PORT0,EINT0_PIN,PIN_FUNC2);
	EXTMODE |= 1 << 0;         // Edge triggered
    EXTPOLAR &= ~(1 << 0);    // Falling edge
	//configure VIC (Vector Interrupt controller)
	//def External interrupts (EINT0/EINT1/EINT2/EINT3) is IRQ types (by using VICIntSelect SFR)
	VICIntEnable |= 1<<EINT0_VIC_CHNO;
	//enable vectored irq slot 0 for EINT0 (0-15 based on requirement ? by using VICVectCntl0 SFR)
	VICVectCntl0 = (1<<5) | (EINT0_VIC_CHNO);
	//load isr address into slot 0 (0-15 based on requirement ? by using VICVectAddr0 SFR)
	VICVectAddr0 = (u32)eint0_isr;
	//configure External Interrupts Peripheral
	//configure EINT0/EINT1/EINT2/EINT3 as edge triggered (use EXTMODE SFR)
	//EXTMODE = 1<<0;
	//def EINT0/EINT1/EINT2/EINT3 is Falling Edge Triggerd (use EXTPOLAR SFR)
}

int main()
{ 
   SETBIT(IODIR0,EINT0_LED);
   SETBIT(IODIR0,MOTOR_IN1);  
   SETBIT(IODIR0,MOTOR_IN2);
   InitLCD();
   init_i2c();
   UART0_Init();   
   Enable_EINT0();
   RTC_Init();
   CmdLCD(MODE_8BIT_2LINE);
   CmdLCD(0x0C);//DSP_ON_CUR_OFF
   Keypad_Init();
   RTCSetTime(03,45,00);
   RTCSetDate(26,05,2025);
   RTCSetDay(1);
   def_Password();
   CmdLCD(GOTO_LINE1_POS0);
   StrLCD("OTP-DRIVEN");
   CmdLCD(GOTO_LINE2_POS0);
   StrLCD("SECURE SYSTEM");
   delay_s(2);

while(1)
{  
	 if(changePasswordFlag)
    {
		  CmdLCD(CLEAR_LCD);
	      delay_ms(2);
	      StrLCD("Enter RPassword:");
	      CmdLCD(GOTO_LINE2_POS0);
	  																							 
	      for(i=0;i<6;i++)
	     {
					pass[i]=keyscan();
					CharLCD(pass[i]);
					delay_ms(300);
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD('*');
		 }
		   if(passwordVerify(pass))
	     {
						passwordChange();
						CmdLCD(CLEAR_LCD);
						StrLCD("Returning...");
						delay_s(1);
						changePasswordFlag = 0;				
			 }
			 else
				 {
				    CmdLCD(CLEAR_LCD);
				    StrLCD("WRONG...");
				    delay_ms(500);				 
			   }
				CLRBIT(IOSET0,EINT0_LED);
    }	 
  
	  CmdLCD(CLEAR_LCD);
	  delay_ms(2);
	  StrLCD("Enter Password:");
	  CmdLCD(GOTO_LINE2_POS0);
	  																							 
	  for(i=0;i<6;i++)
	  {
			pass[i]=keyscan();
			CharLCD(pass[i]);
			delay_ms(300);
			CmdLCD(SHIFT_CUR_LEFT);
			CharLCD('*');
	  }
	
	  if(passwordVerify(pass))
	  {
			CmdLCD(CLEAR_LCD);
			delay_ms(2);
			StrLCD("Password");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("Matched !");
				
			delay_s(2);
			
			//GSM	
			CmdLCD(CLEAR_LCD);
			delay_ms(2);
			StrLCD("Sending OTP...");	
			//srand(time(NULL));
			srand(RTCGetSeconds());
		    otp = (rand() % 9000) + 1000;  // Generates OTP between 1000 and 9999
			CmdLCD(GOTO_LINE2_POS0);
			U32LCD(otp);
			delay_s(1);
            sprintf((char *)otp_str, "%04d", otp);  // cast to char*
            if(uart_gsm(number, (char *)otp_str))
            { 
			   delay_s(1);
			   CmdLCD(CLEAR_LCD);
			   delay_ms(2);
			   StrLCD("OTP Sent !");
			   delay_s(1);
				//OTP_ENTRY	
				if (otp_entry())
				{
					CmdLCD(CLEAR_LCD);
					delay_ms(2);
					StrLCD("Access Granted");
					delay_ms(3);
					
					CmdLCD(CLEAR_LCD);
					StrLCD("DOOR OPENING !!");
					Motor_Forward();  // Turn on motor
					delay_s(3);       // Run for 3 seconds
					Motor_Stop();     // Stop motor
					delay_s(3);

					CmdLCD(CLEAR_LCD);
					StrLCD("CLOSING DOOR !");
					delay_s(1);
					Motor_Reverse();
				}

				else
				{
					CmdLCD(CLEAR_LCD);
					delay_ms(2);
					StrLCD("OTP wrong!");
					delay_s(2);
				}
			}
			else
			{	
			    CmdLCD(CLEAR_LCD);
			    delay_ms(2);
			    StrLCD("UART FAILED!");			  
			}
			    	
		}
		else
		{
				CmdLCD(CLEAR_LCD);
				delay_ms(2);
				StrLCD("****WRONG!****");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("***PASSWORD***");
				delay_s(2);
		}				
  }
	
}
