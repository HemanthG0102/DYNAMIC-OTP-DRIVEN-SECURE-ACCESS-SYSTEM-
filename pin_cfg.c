//pin_cfg.c

#include <LPC214x.H>
#include "types.h"

void CfgPortPin(u32 portno,u32 pinno,u32 func)
{
	if(pinno<16)

		PINSEL0 = (PINSEL0&~(3<<(pinno*2))) | (func<<(pinno*2));
	else
		PINSEL1 = (PINSEL1&~(3<<((pinno-16)*2))) | (func<<((pinno-16)*2));
   	
}
