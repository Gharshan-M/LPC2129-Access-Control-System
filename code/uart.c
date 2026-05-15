#include <LPC21xx.h>
#include "types.h"

void UART0_Init(void)
{
    PINSEL0 |= 0x00000005;

    U0LCR = 0x83;

    U0DLL = 97;

    U0LCR = 0x03;
}

void UART0_TxChar(u8 ch)
{
    while(!(U0LSR & (1<<5)));

    U0THR = ch;
}

void UART0_TxString(char *str)
{
    while(*str)
    {
        UART0_TxChar(*str++);
    }
}

u8 UART0_RxCharAvailable(void)
{
    if(U0LSR & (1<<0))
        return 1;

    return 0;
}

u8 UART0_RxChar(void)
{
    while(!UART0_RxCharAvailable());

    return (u8)U0RBR;
}
