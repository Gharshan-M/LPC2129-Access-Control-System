#ifndef I2C_H
#define I2C_H

#include "types.h"

void I2C_Init(void);
u8 I2C_Start(void);
void I2C_Stop(void);
u8 I2C_Write(u8 data);
u8 I2C_Read_NACK(u8 *data);
u8 I2C_ReStart(void);

#endif
