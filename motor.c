#include <LPC214x.h>
#include "defines.h"  
#include "motor.h"

void Motor_Forward(void)
{
    SETBIT(IOSET0, MOTOR_IN1);   // IN1 = HIGH
    CLRBIT(IOCLR0, MOTOR_IN2);   // IN2 = LOW
}

void Motor_Reverse(void)
{
    CLRBIT(IOCLR0, MOTOR_IN1);   // IN1 = LOW
    SETBIT(IOSET0, MOTOR_IN2);   // IN2 = HIGH
}

void Motor_Stop(void)
{
    CLRBIT(IOCLR0, MOTOR_IN1);   // IN1 = LOW
    CLRBIT(IOCLR0, MOTOR_IN2);   // IN2 = LOW
}

