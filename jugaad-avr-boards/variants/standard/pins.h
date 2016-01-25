#ifndef _PINS_H_
#define _PINS_H_

#include <avr/io.h>

#define NUM_DIGITAL_PINS            20
#define NUM_ANALOG_INPUTS           6

/*

    ATMEL ATMEGA8 & 168 / ARDUINO

                     +-\/-+
               PC6  1|    |28  PC5 (AI 5)
         (D 0) PD0  2|    |27  PC4 (AI 4)
         (D 1) PD1  3|    |26  PC3 (AI 3)
         (D 2) PD2  4|    |25  PC2 (AI 2)
    PWM+ (D 3) PD3  5|    |24  PC1 (AI 1)
         (D 4) PD4  6|    |23  PC0 (AI 0)
               VCC  7|    |22  GND
               GND  8|    |21  AREF
               PB6  9|    |20  AVCC
               PB7 10|    |19  PB5 (D 13)
    PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
    PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
         (D 7) PD7 13|    |16  PB2 (D 10) PWM
         (D 8) PB0 14|    |15  PB1 (D 9) PWM
                     +----+

    (PWM+ indicates the additional PWM pins on the ATmega168.)

*/

#define PD0    0
#define PD1    1
#define PD2    2
#define PD3    3
#define PD4    4
#define PD5    5
#define PD6    6
#define PD7    7
#define PB0    8
#define PB1    9
#define PB2    10
#define PB3    11
#define PB4    12
#define PB5    13
#define PC0    14
#define PC1    15
#define PC2    16
#define PC3    17
#define PC4    18
#define PC5    19

#define D0    0
#define D1    1
#define D2    2
#define D3    3
#define D4    4
#define D5    5
#define D6    6
#define D7    7
#define D8    8
#define D9    9
#define D10    10
#define D11    11
#define D12    12
#define D13    13
#define A0    14
#define A1    15
#define A2    16
#define A3    17
#define A4    18
#define A5    19

#define SS    10
#define MOSI    11
#define MISO    12
#define SCK    13

#define SDA 18
#define SCL 19

#define LED_BUILTIN    13

#define pin2out(p) (p<PB0)?&PORTD:((p<PC0)?&PORTB:&PORTC)
#define pin2dir(p) (p<PB0)?&DDRD:((p<PC0)?&DDRB:&DDRC)
#define pin2inp(p) (p<PB0)?&PIND:((p<PC0)?&PINB:&PINC)
#define pin2bit(p) (p<PB0)?_BV(p):((p<PC0)?_BV(p-PB0):_BV(p-PC0))
#define pin2int_chan(p) ((p==PD2) || (p==PD3))?(p-PD2):0xFF
#define pin2anlog_chan(p) (p>PB5 && p<NUM_DIGITAL_PINS)?(p-A0):0xFF

/*
#define PD0    _BV(0)
#define D0    _BV(0)
#define PD0_PORT    PORTD
#define D0_PORT    PORTD
#define PD0_DIR    DDRD
#define D0_DIR    DDRD
#define PD0_PWM    0xFF
#define D0_PWM    0xFF
#define PD0_AIN    0xFF
#define D0_AIN    0xFF

#define PD1    _BV(1)
#define D1    _BV(1)
#define PD1_PORT    PORTD
#define D1_PORT    PORTD
#define PD1_DIR    DDRD
#define D1_DIR    DDRD
#define PD1_PWM    0xFF
#define D1_PWM    0xFF
#define PD1_AIN    0xFF
#define D1_AIN    0xFF

#define PD2    _BV(2)
#define D2    _BV(2)
#define PD2_PORT    PORTD
#define D2_PORT    PORTD
#define PD2_DIR    DDRD
#define D2_DIR    DDRD
#define PD2_PWM    0xFF
#define D2_PWM    0xFF
#define PD2_AIN    0xFF
#define D2_AIN    0xFF

#define PD3    _BV(3)
#define D3    _BV(3)
#define PD3_PORT    PORTD
#define D3_PORT    PORTD
#define PD3_DIR    DDRD
#define D3_DIR    DDRD
#define PD3_PWM    0xFF
#define D3_PWM    0xFF
#define PD3_AIN    0xFF
#define D3_AIN    0xFF

#define PD4    _BV(4)
#define D4    _BV(4)
#define PD4_PORT    PORTD
#define D4_PORT    PORTD
#define PD4_DIR    DDRD
#define D4_DIR    DDRD
#define PD4_PWM    0xFF
#define D4_PWM    0xFF
#define PD4_AIN    0xFF
#define D4_AIN    0xFF

#define PD5    _BV(5)
#define D5    _BV(5)
#define PD5_PORT    PORTD
#define D5_PORT    PORTD
#define PD5_DIR    DDRD
#define D5_DIR    DDRD
#define PD5_PWM    0xFF
#define D5_PWM    0xFF
#define PD5_AIN    0xFF
#define D5_AIN    0xFF

#define PD6    _BV(6)
#define D6    _BV(6)
#define PD6_PORT    PORTD
#define D6_PORT    PORTD
#define PD6_DIR    DDRD
#define D6_DIR    DDRD
#define PD6_PWM    0xFF
#define D6_PWM    0xFF
#define PD6_AIN    0xFF
#define D6_AIN    0xFF

#define PD7    _BV(7)
#define D7    _BV(7)
#define PD7_PORT    PORTD
#define D7_PORT    PORTD
#define PD7_DIR    DDRD
#define D7_DIR    DDRD
#define PD7_PWM    0xFF
#define D7_PWM    0xFF
#define PD7_AIN    0xFF
#define D7_AIN    0xFF

#define PB0    _BV(0)
#define D8    _BV(0)
#define PB0_PORT    PORTB
#define D8_PORT    PORTB
#define PB0_DIR    DDRB
#define D8_DIR    DDRB
#define PB0_PWM    0xFF
#define D8_PWM    0xFF
#define PB0_AIN    0xFF
#define D8_AIN    0xFF

#define PB1    _BV(1)
#define D9    _BV(1)
#define PB1_PORT    PORTB
#define D9_PORT    PORTB
#define PB1_DIR    DDRB
#define D9_DIR    DDRB
#define PB1_PWM    0
#define D9_PWM    0
#define PB1_AIN    0xFF
#define D9_AIN    0xFF

#define PB2    _BV(2)
#define D10    _BV(2)
#define PB2_PORT    PORTB
#define D10_PORT    PORTB
#define PB2_DIR    DDRB
#define D10_DIR    DDRB
#define PB2_PWM    1
#define D10_PWM    1
#define PB2_AIN    0xFF
#define D10_AIN    0xFF

#define PB3    _BV(3)
#define D11    _BV(3)
#define PB3_PORT    PORTB
#define D11_PORT    PORTB
#define PB3_DIR    DDRB
#define D11_DIR    DDRB
#define PB3_PWM    0xFF
#define D11_PWM    0xFF
#define PB3_AIN    0xFF
#define D11_AIN    0xFF

#define PB4    _BV(4)
#define D12    _BV(4)
#define PB4_PORT    PORTB
#define D12_PORT    PORTB
#define PB4_DIR    DDRB
#define D12_DIR    DDRB
#define PB4_PWM    0xFF
#define D12_PWM    0xFF
#define PB4_AIN    0xFF
#define D12_AIN    0xFF

#define PB5    _BV(5)
#define D13    _BV(5)
#define PB5_PORT    PORTB
#define D13_PORT    PORTB
#define PB5_DIR    DDRB
#define D13_DIR    DDRB
#define PB5_PWM    0xFF
#define D13_PWM    0xFF
#define PB5_AIN    0xFF
#define D13_AIN    0xFF

#define PC0    _BV(0)
#define A0    _BV(0)
#define PC0_PORT    PORTC
#define A0_PORT    PORTC
#define PC0_DIR    DDRC
#define A0_DIR    DDRC
#define PC0_PWM    0xFF
#define A0_PWM    0xFF
#define PC0_AIN    0
#define A0_AIN    0

#define PC1    _BV(1)
#define A1    _BV(1)
#define PC1_PORT    PORTC
#define A1_PORT    PORTC
#define PC1_DIR    DDRC
#define A1_DIR    DDRC
#define PC1_PWM    0xFF
#define A1_PWM    0xFF
#define PC1_AIN    1
#define A1_AIN    1

#define PC2    _BV(2)
#define A2    _BV(2)
#define PC2_PORT    PORTC
#define A2_PORT    PORTC
#define PC2_DIR    DDRC
#define A2_DIR    DDRC
#define PC2_PWM    0xFF
#define A2_PWM    0xFF
#define PC2_AIN    2
#define A2_AIN    2

#define PC3    _BV(3)
#define A3    _BV(3)
#define PC3_PORT    PORTC
#define A3_PORT    PORTC
#define PC3_DIR    DDRC
#define A3_DIR    DDRC
#define PC3_PWM    0xFF
#define A3_PWM    0xFF
#define PC3_AIN    3
#define A3_AIN    3

#define PC4    _BV(4)
#define A4    _BV(4)
#define PC4_PORT    PORTC
#define A4_PORT    PORTC
#define PC4_DIR    DDRC
#define A4_DIR    DDRC
#define PC4_PWM    0xFF
#define A4_PWM    0xFF
#define PC4_AIN    4
#define A4_AIN    4

#define PC5    _BV(5)
#define A5    _BV(5)
#define PC5_PORT    PORTC
#define A5_PORT    PORTC
#define PC5_DIR    DDRC
#define A5_DIR    DDRC
#define PC5_PWM    0xFF
#define A5_PWM    0xFF
#define PC5_AIN    5
#define A5_AIN    5
*/

/*************************************************************/
/* Board Features */

/* Built In LED */
/*
#define LED_BUILTIN _BV(5)
#define LED_BUILTIN_PORT    PORTB
#define LED_BUILTIN_DIR    DDRB
#define LED_BUILTIN_PWM    0xFF
#define LED_BUILTIN_AIN    0xFF
*/

#endif /* _PINS_H_ */
