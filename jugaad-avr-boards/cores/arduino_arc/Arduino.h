#ifndef _ARDUINO_H_
#define _ARDUINO_H_

#include <stdint.h>
#include <avr/io.h>
#include "pins.h"
#include <util/atomic.h>
#include <util/delay.h>

#define OUTPUT 1
#define INPUT 2
#define INPUT_PULLUP 3

#define HIGH 1
#define ON 1
#define LOW 0
#define OFF 0

#define PARAMETER_ERROR 0xFE
#define GENERAL_ERROR 0xFE
#define SUCCESS 0

uint8_t pinMode(uint8_t pin, uint8_t mode);
uint8_t digitalWrite(uint8_t pin, uint8_t state);
uint8_t digialToggle(uint8_t pin);
uint8_t digialRead(uint8_t pin);

#define delay _delay_ms

extern void setup();

extern void loop();

#endif /* _ARDUINO_H_ */