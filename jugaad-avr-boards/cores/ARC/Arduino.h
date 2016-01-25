/**
 * @file Arduino.h
 *
 * @brief This the Main header file responsible for integrating the A.R.C. Core to
 *  Arduino IDE and Arduino Builder.
 *
 *
 * @version 1.0.0 First Version Release - 25th Jan 2016
 *
 * @author Abhijit Bose (salearj@hotmail.com)
 *
 * @copy Copyright (c) 2016 Abhijit Bose.  All right reserved.
 *
 * @license
 * This file is part of Jugaad Boards Framework (JBF) for A.R.C. Core.
 *
 * JBF is free software: you can redistribute it and / or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *   JBF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with JBF.
 * If not, see <https://www.gnu.org/licenses/lgpl-3.0.txt>.
 * You can also write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * @Attribution
 * This work derives on the previous work done by Arduino Team.
 * We very thankful to them for providing this great piece of software
 * free of cost to the community and we too intend to serve on the same
 * lines.
 *
 * @note Arduino - Copyright owned by Arduino LLC and we are not associated
 *  with them in any what so ever manner. JBF is an independently developed entity
 *  and hence Arduino LLC or Associated collaborators cannot claim ownership
 *  of this work under any legal on permissible context.
 *
 */

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
uint8_t pinMode(uint8_t pin, uint8_t mode);

/* GPIO Pin Levels */
#define HIGH 1
#define ON 1
#define LOW 0
#define OFF 0
uint8_t digitalWrite(uint8_t pin, uint8_t state);
uint8_t digitalToggle(uint8_t pin);
uint8_t digitalRead(uint8_t pin);

/* Shift In-Out Direction Flags */
#define MSBFIRST 1
#define LSBFIRST 1


/* Error Definitions */
#define PARAMETER_ERROR 0xFE
#define GENERAL_ERROR 0xFF
#define UNSUPPORTED_ERROR 0xFF
#define SUCCESS 0

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

/* ADC Reference Defines */
#define DEFAULT 1
#define INTERNAL 3
#define EXTERNAL 0
uint8_t analogReference(uint8_t val);
uint16_t analogRead(uint8_t apin);
void analogOff();
//uint16_t analogSample(uint16_t *buffer, uint8_t buf_len, uint8_t Cycles);
//uin8_t analogComp(uint8_t pin, uint16_t delay);

#define SER_RX_BUFFER_MAX 65
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


#define SPIM_MODE_0 (0)
#define SPIM_MODE_1 (_BV(CPHA))
#define SPIM_MODE_2 (_BV(CPOL))
#define SPIM_MODE_3 (_BV(CPOL)|_BV(CPHA))
#define SPIM_MODE_MASK (_BV(CPOL)|_BV(CPHA))
#define SPIM_MODE_STANDARD SPIM_MODE_0
#define SPIM_MODE_DEFAULT SPIM_MODE_0

#define SPIM_SPEED_DIV2 (_BV(SPI2X)<<4)
#define SPIM_SPEED_DIV4 (0)
#define SPIM_SPEED_DIV8 ((_BV(SPI2X)<<4)|1)
#define SPIM_SPEED_DIV16 (1)
#define SPIM_SPEED_DIV32 ((_BV(SPI2X)<<4)|2)
#define SPIM_SPEED_DIV64 (2)
#define SPIM_SPEED_DIV128 (3)
#define SPIM_SPEED_MASK2X ((_BV(SPI2X)<<4))
#define SPIM_SPEED_MASKLOW (3)
#define SPIM_SPEED_DEFAULT SPIM_SPEED_DIV16

uint8_t SpimOn(uint8_t spimode, uint8_t datarate, uint8_t bitOrder);
uint8_t SpimSend(uint8_t data);
uint8_t SpimSends(uint8_t *dataOut, uint16_t size);
uint8_t SpimReads(uint8_t *dataIn, uint8_t dummy_dataOut, uint16_t size);
uint8_t SpimTrans(uint8_t *dataIn, uint8_t *dataOut, uint16_t size);
uint8_t SpimOff(void);

#define TWIM_BITRATE_10K  1
#define TWIM_BITRATE_100K 10
#define TWIM_BITRATE_400K 40
#define TWIM_BITRATE_DEFAULT TWIM_BITRATE_100K
#define TWIM_READ 1
#define TWIM_WRITE 0
#define TWIM_STATUS_SUCCESS    0
#define TWIM_STATUS_START_FAILED 1
#define TWIM_STATUS_ADDRESS_FAILED 2
#define TWIM_STATUS_DATASEND_FAILED 3
#define TWIM_STATUS_DATAREAD_ACK_FAILED 4
#define TWIM_STATUS_DATAREAD_NACK_FAILED 5

void TwimOn(uint8_t bitrate);
uint8_t TwimWriteEx(uint8_t address, uint8_t *buf, uint8_t len, uint8_t sendstop);
uint8_t TwimReadEx(uint8_t address, uint8_t *buf, uint8_t len, uint8_t sendstop);
#define TwimWrite(ADDR,BUF,LEN) TwimReadEx(ADDR,BUF,LEN,1)
#define TwimRead(ADDR,BUF,LEN) TwimReadEx(ADDR,BUF,LEN,1)
void TwimOff(void);

extern void setup();

extern void loop();

#endif /* ARC_COMPILE */

#endif /* _ARDUINO_H_ */
