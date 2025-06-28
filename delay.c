//DELAY.C
#include "types.h"

// Uncomment this when simulating in Proteus
//#define PROTEUS_SIMULATION

#ifndef PROTEUS_SIMULATION
void delay_us(u32 dlyUS)
{
    for(dlyUS *= 12; dlyUS > 0; dlyUS--);
}
void delay_ms(u32 dlyMS)
{
    for(dlyMS *= 12000; dlyMS > 0; dlyMS--);
}
void delay_s(u32 dlyS)
{
    for(dlyS *= 12000000; dlyS > 0; dlyS--);
}
#else
// Faster simulation-friendly versions
void delay_us(u32 dlyUS) { for(u32 i=0; i<dlyUS; i++); }
void delay_ms(u32 dlyMS) { for(u32 i=0; i<dlyMS*10; i++); }
void delay_s(u32 dlyS)   { for(u32 i=0; i<dlyS*100; i++); }
#endif
