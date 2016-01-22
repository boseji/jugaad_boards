#include <Arduino.h>

uint8_t Serial;

#define SER_TXBYTE(X)		while ( !( UCSR0A & (1 << UDRE0) ) ) ;	\
  UDR0 = (uint8_t)(X);
#define SER_RXBYTE(X)		while ( !(UCSR0A & (1<<RXC0)) ) ; \
  X = UDR0;
#define SER_RXBYTE_T(X,TM)	TM = SER_RX_TIMEOUT; \
  while ( ( !(UCSR0A & (1<<RXC0)) ) && ((TM) > 0) ) \
  { \
    _delay_us(100); \
    --TM; \
  } \
  X = UDR0;
#define SER_CLR_STATUS()	UCSR0A = 0;
#define SER_CONFIG()		UCSR0B = ( 1 << TXEN0 ) | ( 1 << RXEN0 ); \
  UCSR0C = ( 1 << UCSZ01 ) | ( 1 << UCSZ00 );

#if F_CPU == 16000000L
#define SER_BAUD_2400 \
    UBRR0H = 416>>8;\
    UBRR0L = 416&0xFF;
#define SER_BAUD_4800 \
    UBRR0H = 207>>8;\
    UBRR0L = 207&0xFF;
#define SER_BAUD_9600 \
    UBRR0H = 103>>8;\
    UBRR0L = 103&0xFF;
#define SER_BAUD_14400 \
    UCSR0A = _BV(U2X0);\
    UBRR0H = 0;\
    UBRR0L = 138&0xFF;
#define SER_BAUD_19200 \
    UBRR0H = 0;\
    UBRR0L = 51&0xFF;
#define SER_BAUD_38400 \
    UBRR0H = 0;\
    UBRR0L = 25&0xFF;
#define SER_BAUD_57600 \
    UCSR0A = _BV(U2X0);\
    UBRR0H = 0;\
    UBRR0L = 34&0xFF;
#define SER_BAUD_115200 \
    UCSR0A = _BV(U2X0);\
    UBRR0H = 0;\
    UBRR0L = 16&0xFF;
#elif F_CPU == 11059200L
#define SER_BAUD_2400 \
    UBRR0H = 287>>8;\
    UBRR0L = 287&0xFF;
#define SER_BAUD_4800 \
    UBRR0H = 0;\
    UBRR0L = 143&0xFF;
#define SER_BAUD_9600 \
    UBRR0H = 0;\
    UBRR0L = 71&0xFF;
#define SER_BAUD_14400 \
    UBRR0H = 0;\
    UBRR0L = 47&0xFF;
#define SER_BAUD_19200 \
    UBRR0H = 0;\
    UBRR0L = 35&0xFF;
#define SER_BAUD_38400 \
    UBRR0H = 0;\
    UBRR0L = 17&0xFF;
#define SER_BAUD_57600 \
    UBRR0H = 0;\
    UBRR0L = 11&0xFF;
#define SER_BAUD_115200 \
    UBRR0H = 0;\
    UBRR0L = 5&0xFF;
#elif F_CPU == 14745600L
#define SER_BAUD_2400 \
    UBRR0H = 383>>8;\
    UBRR0L = 383&0xFF;
#define SER_BAUD_4800 \
    UBRR0H = 0;\
    UBRR0L = 191&0xFF;
#define SER_BAUD_9600 \
    UBRR0H = 0;\
    UBRR0L = 95&0xFF;
#define SER_BAUD_14400 \
    UBRR0H = 0;\
    UBRR0L = 63&0xFF;
#define SER_BAUD_19200 \
    UBRR0H = 0;\
    UBRR0L = 47&0xFF;
#define SER_BAUD_38400 \
    UBRR0H = 0;\
    UBRR0L = 23&0xFF;
#define SER_BAUD_57600 \
    UBRR0H = 0;\
    UBRR0L = 15&0xFF;
#define SER_BAUD_115200 \
    UBRR0H = 0;\
    UBRR0L = 7&0xFF;
#elif F_CPU == 8000000L
#define SER_BAUD_2400 \
    UBRR0H = 207>>8;\
    UBRR0L = 207&0xFF;
#define SER_BAUD_4800 \
    UBRR0H = 0;\
    UBRR0L = 103&0xFF;
#define SER_BAUD_9600 \
    UBRR0H = 0;\
    UBRR0L = 51&0xFF;
#define SER_BAUD_14400 \
    UBRR0H = 0;\
    UBRR0L = 34&0xFF;
#define SER_BAUD_19200 \
    UBRR0H = 0;\
    UBRR0L = 25&0xFF;
#define SER_BAUD_38400 \
    UBRR0H = 0;\
    UBRR0L = 12&0xFF;
#define SER_BAUD_57600 \
    UBRR0H = 0;\
    UBRR0L = 8&0xFF;
#define SER_BAUD_115200 \
    UCSR0A = _BV(U2X0);\
    UBRR0H = 0;\
    UBRR0L = 8&0xFF;
#else
    #error Unsupported Frequency for Baudrate
#endif

uint8_t Serial_begin(uint16_t datarate)
{
  UCSR0A = 0;
  switch(datarate)
  {
    case 2400:
      SER_BAUD_2400;
      break;
    case 4800:
      SER_BAUD_4800;
      break;
    case 9600:
      SER_BAUD_9600;
      break;
    case 14400:
      SER_BAUD_14400;
      break;
    case 19200:
      SER_BAUD_19200;
      break;
    case 38400:
      SER_BAUD_38400;
      break;
    case 57600:
      SER_BAUD_57600;
      break;
    case 115200:
      SER_BAUD_115200;
      break;
    default:
      return PARAMETER_ERROR;
  }

	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
#if defined(__AVR_ATmega8__)
	/* Set frame format: 8 data, 2 stop bit */
	UCSR0C = (1<<URSEL)|(1<<USBS0)|(3<<UCSZ00);
#else
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
#endif
}

uint8_t Serial_PrintP(PGM_P buffer)
{
  char * tmp;
  uint8_t data;

  if (buffer != 0)	// Check buffer size and data pointer
  {
    // Perform length computation
    tmp = (char *) buffer;
    data = (uint8_t) pgm_read_byte((uint16_t) tmp);
    SER_CLR_STATUS();// Clear the Interrupt Status
    while (data != '\0')// Iterate till the null is found
    {
      SER_TXBYTE(data);
      ++tmp;
      data = (uint8_t) pgm_read_byte((uint16_t) tmp);
    }
    return SUCCESS;
  }
  return GENERAL_ERROR;
}

void Serial_Printb(uint8_t data)
{
  uint8_t clc, dig[3];
  clc = data;
  dig[2] = '0' + (clc%10);
  clc /= 10;
  dig[1] = '0' + (clc%10);
  clc /= 10;
  dig[0] = '0' + (clc%10);
  for(clc = 0; clc < 3; clc++)
  {
    SER_TXBYTE(dig[clc]);
  }
}
void Serial_Printbh(uint8_t data)
{
  uint8_t clc, dig[4];
  clc = data;
  dig[3] = clc&0x0F;
  dig[3] += ((dig[3]) < 0x0A)?('9'+1):'A';
  dig[3] -= 0x0A;
  clc >>= 4;
  dig[2] = clc&0x0F;
  dig[2] += ((dig[2]) < 0x0A)?('9'+1):'A';
  dig[2] -= 0x0A;
  dig[1] = 'x';
  dig[0] = '0';
  for(clc = 0; clc < 4; clc++)
  {
    SER_TXBYTE(dig[clc]);
  }
}

void Serial_Printi(uint16_t data)
{
  uint16_t clc;
  uint8_t dig[5],i;
  for(i = 0,clc = data; i < 5; i++,clc /= 10)
  {
    dig[4-i] = '0' + clc%10;
  }
  for(i = 0; i < 5; i++)
  {  
    SER_TXBYTE(dig[i]);
  }
}

void Serial_Printih(uint16_t data)
{
  uint16_t clc;
  uint8_t dig[6],i;
  for(i = 2,clc = data; i < 6; i++,clc >>= 4)
  {
    dig[5 - i + 2] = clc&0x0F;
    dig[5 - i + 2] += ((dig[5 - i + 2]) < 0x0A)?('9'+1):'A';
    dig[5 - i + 2] -= 0x0A;
  }
  dig[1] = 'x';
  dig[0] = '0';
  for(i=0;i<6;i++)
  {
    SER_TXBYTE(dig[i]);
  }
}

