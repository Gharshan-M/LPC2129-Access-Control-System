#ifndef MOTOR_H
#define MOTOR_H

#include "types.h"

void Motor_Init(void);

void Rotate_motor_1(void);
void Stop_motor_1(void);

void Rotate_motor_2(void);
void Stop_motor_2(void);

void Motor_Run_With_LED_Blink(u32 run_ms);

#endif
