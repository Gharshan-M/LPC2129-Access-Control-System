#include <LPC21xx.h>
#include "i2c.h"

#define I2C_I2EN      (1u<<6)
#define I2C_STA       (1u<<5)
#define I2C_STO       (1u<<4)
#define I2C_SI        (1u<<3)
#define I2C_AA        (1u<<2)

#define I2C_TIMEOUT   100000UL

#define I2C_STAT_START_TX       0x08u
#define I2C_STAT_RESTART_TX     0x10u
#define I2C_STAT_SLAW_ACK       0x18u
#define I2C_STAT_DATA_TX_ACK    0x28u
#define I2C_STAT_SLAR_ACK       0x40u
#define I2C_STAT_DATA_RX_NACK   0x58u

static u8 I2C_WaitSI(void)
{
    u32 timeout;

    timeout = I2C_TIMEOUT;

    while(!(I2CONSET & I2C_SI))
    {
        if(timeout == 0)
            return 0;

        timeout--;
    }

    return 1;
}

void I2C_Init(void)
{
    PINSEL0 = (PINSEL0 & ~0x000000F0) | 0x00000050;

    I2SCLL = 75;
    I2SCLH = 75;

    I2CONCLR = I2C_AA | I2C_SI | I2C_STA | I2C_I2EN;

    I2CONSET = I2C_I2EN;
}

u8 I2C_Start(void)
{
    u8 status;

    I2CONSET = I2C_STA;
    I2CONCLR = I2C_SI;

    if(!I2C_WaitSI())
        return 0;

    status = I2STAT;

    if((status != I2C_STAT_START_TX) &&
       (status != I2C_STAT_RESTART_TX))
        return 0;

    I2CONCLR = I2C_STA;

    return 1;
}

u8 I2C_ReStart(void)
{
    I2CONSET = I2C_STA;
    I2CONCLR = I2C_SI;

    if(!I2C_WaitSI())
        return 0;

    if(I2STAT != I2C_STAT_RESTART_TX)
        return 0;

    I2CONCLR = I2C_STA;

    return 1;
}

u8 I2C_Write(u8 data)
{
    u8 status;

    I2DAT = data;

    I2CONCLR = I2C_SI;

    if(!I2C_WaitSI())
        return 0;

    status = I2STAT;

    if((status == I2C_STAT_SLAW_ACK) ||
       (status == I2C_STAT_DATA_TX_ACK) ||
       (status == I2C_STAT_SLAR_ACK))
        return 1;

    return 0;
}

void I2C_Stop(void)
{
    I2CONSET = I2C_STO;

    I2CONCLR = I2C_SI | I2C_STA | I2C_AA;
}

u8 I2C_Read_NACK(u8 *data)
{
    if(data == 0)
        return 0;

    I2CONCLR = I2C_AA;
    I2CONCLR = I2C_SI;

    if(!I2C_WaitSI())
        return 0;

    if(I2STAT != I2C_STAT_DATA_RX_NACK)
        return 0;

    *data = I2DAT;

    return 1;
}
