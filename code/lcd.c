#include <LPC21xx.h>
#include "pins.h"
#include "delay.h"

void LCD_Cmd(u8 cmd)
{
    IOCLR0 = LCD_DATA_MASK | LCD_RS;
    IOSET0 = (cmd << 8);
    IOSET0 = LCD_EN;
    delay_ms(2);
    IOCLR0 = LCD_EN;

    if(cmd == 0x01 || cmd == 0x02)
        delay_ms(2);
}

void LCD_Data(u8 data)
{
    IOCLR0 = LCD_DATA_MASK;
    IOSET0 = LCD_RS;
    IOSET0 = (data << 8);
    IOSET0 = LCD_EN;
    delay_ms(2);
    IOCLR0 = LCD_EN;
}

void LCD_Init(void)
{
    IODIR0 |= LCD_DATA_MASK | LCD_RS | LCD_EN;

    delay_ms(40);

    LCD_Cmd(0x38);
    delay_ms(2);

    LCD_Cmd(0x0C);
    delay_ms(2);

    LCD_Cmd(0x01);
}

void LCD_String(char *s)
{
    unsigned char pos = 0;

    while(*s)
    {
        LCD_Data(*s++);

        pos++;

        if(pos == 16)
        {
            LCD_Cmd(0xC0);
        }
        else if(pos == 32)
        {
            break;
        }
    }
}

void LCD_Scroll_Title(void)
{
    char title[] = "   MULTILEVEL SECURITY ACCESS CONTROL SYSTEM   ";

    int i, j;

    for(i = 0; title[i+15] != '\0'; i++)
    {
        LCD_Cmd(0x01);
        LCD_Cmd(0x80);

        for(j = 0; j < 16; j++)
        {
            LCD_Data(title[i + j]);
        }

        delay_ms(300);
    }
}
