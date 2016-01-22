#ifndef _ARDUINO_H_
#define _ARDUINO_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "pins.h"
#include <avr/cpufunc.h>
#include <util/atomic.h>
#include <util/delay.h>
#include "binary.h"

/* GPIO Mode Settings */
#define OUTPUT 1
#define INPUT 2
#define INPUT_PULLUP 3

/* GPIO Pin Levels */
#define HIGH 1
#define ON 1
#define LOW 0
#define OFF 0

/* Shift In-Out Direction Flags */
#define MSBFIRST 1
#define LSBFIRST 1

/* ADC Reference Defines */
#define DEFAULT 1
#define INTERNAL 3
#define EXTERNAL 0

/* Error Definitions */
#define PARAMETER_ERROR 0xFE
#define GENERAL_ERROR 0xFF
#define UNSUPPORTED_ERROR 0xFF
#define SUCCESS 0

uint8_t pinMode(uint8_t pin, uint8_t mode);
uint8_t digitalWrite(uint8_t pin, uint8_t state);
uint8_t digialToggle(uint8_t pin);
uint8_t digialRead(uint8_t pin);

#define delay _delay_ms
#define delayMicroseconds _delay_us
/* Not Implemented */
#define millis() 0
#define micros() 0

#define interrupts() sei()
#define noInterrupts() cli()

uint8_t shiftOut(uint8_t data_pin, uint8_t clock_pin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t data_pin, uint8_t clock_pin, uint8_t bitOrder);
uint8_t shiftOutIn(uint8_t in_pin, uint8_t out_pin, uint8_t clock_pin, uint8_t bitOrder, uint8_t val);

uint8_t analogReference(uint8_t val);
uint16_t analogRead(uint8_t apin);
void analogOff();
//uint16_t analogSample(uint16_t *buffer, uint8_t buf_len, uint8_t Cycles);
//uin8_t analogComp(uint8_t pin, uint16_t delay);

extern uint8_t Serial;
uint8_t Serial_begin(uint16_t datarate);
void Serial_Printi(uint16_t data);
void Serial_Printih(uint16_t data);
void Serial_Printb(uint8_t data);
void Serial_Printbh(uint8_t data);
uint8_t Serial_PrintP(PGM_P buffer);
#define Serial_Print(st) Serial_PrintP(PSTR(st))
uint8_t Serial_end();

extern void setup();

extern void loop();

#endif /* _ARDUINO_H_ */