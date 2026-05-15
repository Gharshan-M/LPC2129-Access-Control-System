#include "eeprom.h"
#include "i2c.h"
#include "delay.h"

#define EEPROM_W 0xA0
#define EEPROM_R 0xA1

void EEPROM_Write(u8 addr, u8 data)
{
    if(!I2C_Start())
    {
        I2C_Stop();
        return;
    }

    if(!I2C_Write(EEPROM_W))
    {
        I2C_Stop();
        return;
    }

    if(!I2C_Write(addr))
    {
        I2C_Stop();
        return;
    }

    if(!I2C_Write(data))
    {
        I2C_Stop();
        return;
    }

    I2C_Stop();

    delay_ms(10);
}

u8 EEPROM_Read(u8 addr)
{
    u8 data;

    data = 0xFF;

    if(!I2C_Start())
    {
        I2C_Stop();
        return data;
    }

    if(!I2C_Write(EEPROM_W))
    {
        I2C_Stop();
        return data;
    }

    if(!I2C_Write(addr))
    {
        I2C_Stop();
        return data;
    }

    if(!I2C_ReStart())
    {
        I2C_Stop();
        return data;
    }

    if(!I2C_Write(EEPROM_R))
    {
        I2C_Stop();
        return data;
    }

    if(!I2C_Read_NACK(&data))
    {
        I2C_Stop();
        return 0xFF;
    }

    I2C_Stop();

    return data;
}
