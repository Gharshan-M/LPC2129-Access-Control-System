#include <LPC21xx.h>
#include "pins.h"
#include "delay.h"

u8 keymap[4][4] =
{
    {'7','8','9','/'},
    {'4','5','6','X'},
    {'1','2','3','-'},
    {'C','0','=','+'}
};

u8 Keypad_GetKey(void)
{
    u8 row, col;

    IODIR1 |= R0|R1|R2|R3;

    while(1)
    {
        IOCLR1 = R0|R1|R2|R3;
        IOSET1 = C0|C1|C2|C3;

        while(C0 && C1 && C2 && C3);

        for(row=0; row<4; row++)
        {
            IOSET1 = R0|R1|R2|R3;

            IOCLR1 = (1<<(16+row));

            if(!(C0 && C1 && C2 && C3))
                break;
        }

        if(!C0)
            col=0;
        else if(!C1)
            col=1;
        else if(!C2)
            col=2;
        else
            col=3;

        delay_ms(150);

        while(!(C0 && C1 && C2 && C3));

        return keymap[row][col];
    }
}
