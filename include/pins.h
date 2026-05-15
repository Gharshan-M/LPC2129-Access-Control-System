#ifndef PINS_H
#define PINS_H

/*  PORT0  */

/* UART0 */
#define UART_TX        (1<<0)
#define UART_RX        (1<<1)

/* I2C */
#define I2C_SCL        (1<<2)
#define I2C_SDA        (1<<3)

/* LCD - PORT0 */
#define LCD_D0 (1<<8)
#define LCD_D1 (1<<9)
#define LCD_D2 (1<<10)
#define LCD_D3 (1<<11)
#define LCD_D4 (1<<12)
#define LCD_D5 (1<<13)
#define LCD_D6 (1<<14)
#define LCD_D7 (1<<15)

#define LCD_DATA_MASK (0xFF << 8)

#define LCD_RS        (1<<16)
#define LCD_EN        (1<<17)

/* LED */
#define LED_PIN       (1<<23)

/*  PORT1  */

/* Keypad Rows */
#define R0 (1<<16)
#define R1 (1<<17)
#define R2 (1<<18)
#define R3 (1<<19)

/* Keypad Columns */
#define C0 (IOPIN1 &(1<<20))
#define C1 (IOPIN1 &(1<<21))
#define C2 (IOPIN1 &(1<<22))
#define C3 (IOPIN1 &(1<<23))

/* Motor */
#define IN1 (1<<24)
#define IN2 (1<<25)
#define IN3 (1<<26)
#define IN4 (1<<27)

#endif
