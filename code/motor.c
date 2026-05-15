#include <LPC21xx.h>
#include "pins.h"
#include "types.h"
#include "delay.h"

void Motor_Init(void)
{
    IODIR1 |= IN1|IN2|IN3|IN4;
}

void Rotate_motor_1(void)
{
    IOSET1 = IN1;
    IOCLR1 = IN2;
}

void Stop_motor_1(void)
{
    IOCLR1 = IN1;
    IOCLR1 = IN2;
}

void Rotate_motor_2(void)
{
    IOSET1 = IN3;
    IOCLR1 = IN4;
}

void Stop_motor_2(void)
{
    IOCLR1 = IN3;
    IOCLR1 = IN4;
}

void Motor_Run_With_LED_Blink(u32 run_ms)
{
    u32 elapsed = 0;

    IODIR0 |= LED_PIN;

    Rotate_motor_1();

    while(elapsed < run_ms)
    {
        IOSET0 = LED_PIN;

        delay_ms(100);

        IOCLR0 = LED_PIN;

        delay_ms(100);

        elapsed += 200;
    }

    Stop_motor_1();

    IOCLR0 = LED_PIN;
}
