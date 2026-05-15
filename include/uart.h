#ifndef UART_H
#define UART_H

#include "types.h"

void UART0_Init(void);

void UART0_TxChar(u8 ch);

void UART0_TxString(char *str);

u8 UART0_RxCharAvailable(void);

u8 UART0_RxChar(void);

#endif
