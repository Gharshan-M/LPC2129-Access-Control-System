#include <LPC21xx.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "delay.h"
#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include "i2c.h"
#include "eeprom.h"
#include "motor.h"
#include "pins.h"

#define DEFAULT_PWD "1234"
#define OTP_SW      (1<<24)

char stored_pwd[5];
char input_pwd[5];
char input_otp[5];

u32 otp;

void Generate_OTP(void)
{
    otp = (rand() % 9000) + 1000;
}

void Load_Password(void)
{
    int i;

    for(i = 0; i < 4; i++)
    {
        stored_pwd[i] = EEPROM_Read(i);
    }

    stored_pwd[4] = '\0';

    if((u8)stored_pwd[0] == 0xFFu)
    {
        for(i = 0; i < 4; i++)
        {
            EEPROM_Write(i, DEFAULT_PWD[i]);

            stored_pwd[i] = DEFAULT_PWD[i];
        }
    }
}

void Write_Default_Password(void)
{
    int i;

    for(i = 0; i < 4; i++)
    {
        EEPROM_Write(i, DEFAULT_PWD[i]);
    }
}

void OTP_Switch_Init(void)
{
    IODIR0 &= ~OTP_SW;
}

u8 OTP_Switch_Pressed(void)
{
    if(!(IOPIN0 & OTP_SW))
    {
        delay_ms(20);

        if(!(IOPIN0 & OTP_SW))
        {
            while(!(IOPIN0 & OTP_SW));

            return 1;
        }
    }

    return 0;
}

int Get_Input(char *buf)
{
    int i;

    for(i = 0; i < 4; i++)
    {
        buf[i] = Keypad_GetKey();

        if(buf[i] == 'C')
        {
            return 1;
        }

        LCD_Data(buf[i]);
    }

    buf[4] = '\0';

    return 0;
}

int main(void)
{
    UART0_Init();

    I2C_Init();

    LCD_Init();

    LCD_Scroll_Title();

    Motor_Init();

    OTP_Switch_Init();

    Load_Password();

    srand(T0TC);

    while(1)
    {
        LCD_Cmd(0x01);

        LCD_String("Enter Password");

        LCD_Cmd(0xC0);

        UART0_TxString("\r\nENTER PASSWORD\r\n");

        if(Get_Input(input_pwd))
        {
            Write_Default_Password();

            LCD_Cmd(0x01);

            LCD_String("EEPROM WR OK");

            delay_ms(800);
        }
        else
        {
            if(strcmp(input_pwd, stored_pwd) == 0)
            {
                char buffer[20];

                LCD_Cmd(0x01);

                LCD_String("Press SW for OTP");

                UART0_TxString("\r\nPRESS SWITCH FOR OTP\r\n");

                while(!OTP_Switch_Pressed());

                Generate_OTP();

                sprintf(buffer, "OTP:%lu\r\n", otp);

                UART0_TxString(buffer);

                LCD_Cmd(0x01);

                LCD_String("Enter OTP:");

                LCD_Cmd(0xC0);

                Get_Input(input_otp);

                if(atoi(input_otp) == otp)
                {
                    LCD_Cmd(0x01);

                    LCD_String("Access Granted");

                    Motor_Run_With_LED_Blink(1000);
                }
                else
                {
                    LCD_Cmd(0x01);

                    LCD_String("Wrong OTP");

                    delay_ms(500);

                    LCD_Cmd(0x01);

                    LCD_String("Access Denied");

                    Rotate_motor_2();

                    delay_ms(500);

                    Stop_motor_2();
                }
            }
            else
            {
                LCD_Cmd(0x01);

                LCD_String("Wrong Password");

                delay_ms(2000);
            }
        }
    }
}
