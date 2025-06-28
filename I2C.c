#include <lpc214x.h>
#include "types.h"
#include "delay.h"
#include "i2c_defines.h"

void init_i2c(void)
{
    // Configure pins for SCL and SDA (PINSEL0)
    PINSEL0 |= (SCL_EN | SDA_EN);

    // Configure I2C clock speed
    I2C0SCLL = LOADVAL;
    I2C0SCLH = LOADVAL;

    // Enable I2C peripheral
    I2C0CONSET = (1 << I2EN_BIT);
}

void i2c_start(void)
{
    I2C0CONSET = (1 << STA_BIT);
    while(((I2C0CONSET >> SI_BIT) & 1) == 0);
    I2C0CONCLR = (1 << STA_BIT);
}

void i2c_restart(void)
{
    I2C0CONSET = (1 << STA_BIT);
    I2C0CONCLR = (1 << SI_BIT);
    while(((I2C0CONSET >> SI_BIT) & 1) == 0);
    I2C0CONCLR = (1 << STA_BIT);
}

void i2c_write(u8 dat)
{
    I2C0DAT = dat;
    I2C0CONCLR = (1 << SI_BIT);
    while(((I2C0CONSET >> SI_BIT) & 1) == 0);
}

void i2c_stop(void)
{
    I2C0CONSET = (1 << STO_BIT);
    I2C0CONCLR = (1 << SI_BIT);
    // stop condition cleared automatically
}

u8 i2c_nack(void)
{
    // Clear ACK bit (bit 2) to 0, and clear SI to release bus
    I2C0CONCLR = (1 << ACK_BIT) | (1 << SI_BIT);
    while(((I2C0CONSET >> SI_BIT) & 1) == 0);
    return I2C0DAT;
}

u8 i2c_mack(void)
{
    I2C0CONSET = (1 << ACK_BIT);
    I2C0CONCLR = (1 << SI_BIT);
    while(((I2C0CONSET >> SI_BIT) & 1) == 0);
    I2C0CONCLR = (1 << ACK_BIT);
    return I2C0DAT;
}
