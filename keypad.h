#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "types.h"

void Keypad_Init(void);
u32 ColScan(void);
u32 RowCheck(void);
u32 ColCheck(void);
u32 keyscan(void);
u32 ReadNum(void);

#endif
