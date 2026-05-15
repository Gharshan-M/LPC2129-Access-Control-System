#include <LPC21xx.h>
#include "types.h"

void delay_ms(u32 ms)
{
    T0PR = 15000 - 1;
    T0TCR = 0x01;

    while(T0TC < ms);

    T0TCR = 0x03;
    T0TCR = 0x00;
}
