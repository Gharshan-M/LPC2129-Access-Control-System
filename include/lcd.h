#ifndef LCD_H
#define LCD_H

#include "types.h"

void LCD_Init(void);
void LCD_Cmd(u8 cmd);
void LCD_Data(u8 data);
void LCD_String(char *str);
void LCD_Scroll_Title(void);

#endif
