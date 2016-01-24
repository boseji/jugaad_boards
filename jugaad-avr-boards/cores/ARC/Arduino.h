#ifndef _ARDUINO_H_
#define _ARDUINO_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "pins.h"
#include <avr/cpufunc.h>
#include <util/atomic.h>
#include <util/delay.h>

/**
 * Only Works if ARC Compilation is used
 */
#ifdef ARC_COMPILE

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

#define SER_RX_BUFFER_MAX 64
uint8_t SerOn(uint16_t datarate);
uint8_t SerOnEx(uint16_t datarate, uint8_t datarate2x, uint8_t config);
uint8_t SerIsReady(void);
void SerOuti(uint16_t data);
void SerOutih(uint16_t data);
void SerOutb(uint8_t data);
void SerOutbh(uint8_t data);
void SerPutc(uint8_t data);
void SerPuts(const char * data);
void SerPutsz(const char * data, uint16_t begin, uint16_t size);
void SerPutsPd(PGM_P buffer);
#define SerOut(st) SerPutsPd(PSTR(st))
uint16_t SerIsAvaialble(void);
uint8_t SerRead(void);
void SerReadBytes(uint8_t *buffer,uint16_t size);
uint16_t SerReadBytesEx(uint8_t *buffer,uint16_t size, uint16_t timeoutms);
uint16_t SerReadBytesUtil(uint8_t termination, uint8_t *buffer,uint16_t size);
uint16_t SerReadBytesUtilEx(uint8_t termination, uint8_t *buffer,uint16_t size, uint16_t timeoutms);
uint8_t SerOff();

extern void setup();

extern void loop();

#endif /* ARC_COMPILE */

#endif /* _ARDUINO_H_ */