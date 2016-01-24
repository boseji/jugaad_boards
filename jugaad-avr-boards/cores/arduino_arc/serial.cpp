#include <Arduino.h>
#include "cq.h"

#define SER_ISR_MASK 0b00010000
#define SER_EN_MASK 0b00000001
#define SER_UNSUPPORTED 0b01010101

static uint8_t g_Ser_En = 0;
static uint8_t g_Ser_Rx_Buffer[SER_RX_BUFFER_MAX];
volatile cqueue_t g_Ser_Rx_Queue;
volatile uint16_t g_Ser_Rx_Ctr;

#define SER_TXBYTE(X)   while ( !( UCSR0A & (1 << UDRE0) ) ) ;  \
  UDR0 = (uint8_t)(X);
#define SER_RXBYTE(X)   while ( !(UCSR0A & (1<<RXC0)) ) ; \
  X = UDR0;
#define SER_RXBYTE_T(X,TM)  TM = SER_RX_TIMEOUT; \
  while ( ( !(UCSR0A & (1<<RXC0)) ) && ((TM) > 0) ) \
  { \
    _delay_us(100); \
    --TM; \
  } \
  X = UDR0;
#define SER_CLR_STATUS()  UCSR0A |= _BV(TXC0)

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

uint8_t SerOn(uint16_t datarate)
{
  if(g_Ser_En != 0)
    return GENERAL_ERROR;
  UCSR0A = 0;
  g_Ser_En = 0;
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
  
#if defined(__AVR_ATmega8__)
  /* Set frame format: 8 data, 2 stop bit */
  UCSR0C = _BV(URSEL)|_BV(USBS0)|(3<<UCSZ00);
#else
  UCSR0C = _BV(USBS0)|(3<<UCSZ00);
#endif
  g_Ser_Rx_Ctr = 0; // Initialize the RX Byte Counter
  /* Enable receiver and transmitter */
  if(cqueue_init((cqueue_t *)&g_Ser_Rx_Queue, g_Ser_Rx_Buffer, SER_RX_BUFFER_MAX) == CQ_STATUS_SUCCESS)
  {
    UCSR0B = _BV(RXEN0)|_BV(TXEN0)|_BV(RXCIE0);  
    g_Ser_En = SER_EN_MASK|SER_ISR_MASK; /* Serial Enabled */
  }
  else /* In case we fail to make the Buffer Available */
  {
    UCSR0B = _BV(RXEN0)|_BV(TXEN0);  
    g_Ser_En = SER_EN_MASK; /* Serial Enabled */
  }
  return SUCCESS;
}

uint8_t SerOnEx(uint16_t datarate, uint8_t datarate2x, uint8_t config)
{
  if(g_Ser_En != 0)
    return GENERAL_ERROR;
  /* Set 2X Multiplier */
  if(datarate2x)
    UCSR0A = _BV(U2X0);
  else
    UCSR0A = 0;
  /* Set Data Rate */
  UBRR0H = datarate >> 8;
  UBRR0L = datarate & 0xFF;
  /* Set Configuration */
  UCSR0C = config;
  g_Ser_Rx_Ctr = 0; // Initialize the RX Byte Counter
  /* Enable receiver and transmitter */
  if(cqueue_init((cqueue_t *)&g_Ser_Rx_Queue, g_Ser_Rx_Buffer, SER_RX_BUFFER_MAX) == CQ_STATUS_SUCCESS)
  {
    UCSR0B = _BV(RXEN0)|_BV(TXEN0)|_BV(RXCIE0);  
    g_Ser_En = SER_EN_MASK|SER_ISR_MASK; /* Serial Enabled */
  }
  else /* In case we fail to make the Buffer Available */
  {
    UCSR0B = _BV(RXEN0)|_BV(TXEN0);  
    g_Ser_En = SER_EN_MASK; /* Serial Enabled */
  }
  return SUCCESS;
}

uint8_t SerIsReady(void)
{
  return g_Ser_En;
}

void SerPutsPd(PGM_P buffer)
{
  if (buffer != 0 && g_Ser_En != 0)  // Check buffer size and data pointer
  {
    char * tmp;
    uint8_t data;

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
  }
}

void SerOutb(uint8_t data)
{
  if(g_Ser_En != 0)
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
}
void SerOuth(uint8_t data)
{
  if(g_Ser_En != 0)
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
}

void SerOuti(uint16_t data)
{
  if(g_Ser_En != 0)
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
}

void SerOutih(uint16_t data)
{
  if(g_Ser_En != 0)
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
}

uint16_t SerIsAvaialble(void)
{
  if(g_Ser_En != 0)
  {
    return g_Ser_Rx_Ctr;
  }
  return 0;
}

uint8_t SerRead(void)
{
  if(g_Ser_En != 0)
  {
    uint8_t data,i;
    /* Only work if there are few bytes available */
    while(g_Ser_Rx_Ctr > 0)
    {
      /* Try to Read the Queue */
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
      {
        i = cqueue_pop((cqueue_t *)&g_Ser_Rx_Queue, &data);
      }
      /* Check if Reading was successful */
      if( i == CQ_STATUS_SUCCESS)
      {
        /* Decrement the Counter we have Read one Byte */
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
          --g_Ser_Rx_Ctr;
        }
        /* 1 Byte was ready so now Return the data */
        return data;
      }
      _delay_us(10); // Backing off while in Receive
    }// while(SerIsAvaialble())
  }
  return 0;
}

void SerReadBytes(uint8_t *buffer,uint16_t size)
{
  if(g_Ser_En != 0 && buffer != 0 && size != 0)
  {
    uint16_t i;
    uint8_t c;
    i = 0;
    /* Loop Till Filling Up of Buffer */
    while(i<size)
    {
      /* Call Receive only if Data is available */
      if(g_Ser_Rx_Ctr > 0)
      {
        c = SerRead(); // Read the byte
        buffer[i] = c; // Write to Buffer
        ++i; // Increment the Counter
      }
      _delay_us(10); // Backing off while in Receive
    }
  }
}

uint16_t SerReadBytesEx(uint8_t *buffer,uint16_t size, uint16_t timeoutms)
{
  if(g_Ser_En != 0 && buffer != 0 && size != 0)
  {
    uint16_t i, t;
    uint8_t c;
    i = 0;
    /* Loop Till Filling Up of Buffer */
    while(i<size)
    {
      _delay_ms(1); // Backing off while in Receive
      /* Call Receive only if Data is available */
      if(g_Ser_Rx_Ctr > 0)
      {
        c = SerRead(); // Read the byte
        buffer[i] = c; // Write to Buffer
        ++i; // Increment the Counter
        t = 0; // Reset Timeout 
      }
      else /* Increment Timeout */
      {
        if(++t>=timeoutms)
          break;
      }      
    }
    return i;
  }
  return 0;
}

uint16_t SerReadBytesUtil(uint8_t termination, uint8_t *buffer,uint16_t size)
{
  if(g_Ser_En != 0 && buffer != 0 && size != 0)
  {
    uint16_t i;
    uint8_t c;
    i = 0;
    /* Loop Till Filling Up of Buffer */
    while(i<size)
    {
      /* Call Receive only if Data is available */
      if(g_Ser_Rx_Ctr > 0)
      {
        c = SerRead(); // Read the byte
        if(c == termination) // Check for Termination Character
          break;
        buffer[i] = c; // Write to Buffer
        ++i; // Increment the Counter
      }
      _delay_us(10); // Backing off while in Receive
    }
    return i;
  }
  return 0;
}

uint16_t SerReadBytesUtilEx(uint8_t termination, uint8_t *buffer,uint16_t size, uint16_t timeoutms)
{
  if(g_Ser_En != 0 && buffer != 0 && size != 0)
  {
    uint16_t i, t;
    uint8_t c;
    i = 0;
    /* Loop Till Filling Up of Buffer */
    while(i<size)
    {
      _delay_ms(1); // Backing off while in Receive
      /* Call Receive only if Data is available */
      if(g_Ser_Rx_Ctr > 0)
      {
        c = SerRead(); // Read the byte
        if(c == termination) // Check for Termination Character
          break;
        buffer[i] = c; // Write to Buffer
        ++i; // Increment the Counter
        t = 0; // Reset Timeout 
      }
      else /* Increment Timeout */
      {
        if(++t>=timeoutms)
          break;
      }      
    }
    return i;
  }
  return 0;
}

uint8_t SerOff()
{
  if(g_Ser_En != 0)
  {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      UCSR0B = 0;
      UCSR0A = 0;
      UCSR0C = 0;
      g_Ser_En = 0;
    }
  }
  return GENERAL_ERROR;
}

#if defined(USART_RX_vect)
  ISR(USART_RX_vect)
#elif defined(USART0_RX_vect)
  ISR(USART0_RX_vect)
#elif defined(USART_RXC_vect)
  ISR(USART_RXC_vect) // ATmega8
#else
  #error "Don't know what the Data Received vector is called for Serial"
#endif
{
  if ( ((UCSR0A & (_BV(UPE0)|_BV(FE0)|_BV(DOR0))) == 0) && /* Successful Reception */
      (g_Ser_En & (SER_EN_MASK|SER_ISR_MASK)) )
  {
    uint8_t c;
    c = UDR0; // Read the Byte Received
    if(g_Ser_Rx_Ctr<SER_RX_BUFFER_MAX)
    {
      // Put Data to Queue
      if(cqueue_push((cqueue_t *)&g_Ser_Rx_Queue,c) == CQ_STATUS_SUCCESS)
        g_Ser_Rx_Ctr++;
    }
  }
  else
  {
    UDR0; // read byte but discard it for Error
  }
}