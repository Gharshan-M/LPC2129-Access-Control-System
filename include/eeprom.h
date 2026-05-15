#ifndef EEPROM_H
#define EEPROM_H

#include "types.h"

void EEPROM_Write(u8 addr, u8 data);
u8 EEPROM_Read(u8 addr);

#endif
