#include <Arduino.h>

static uint8_t g_Spim_En = 0;

uint8_t SpimOn(uint8_t spimode, uint8_t datarate, uint8_t bitOrder)
{
  uint8_t setting;
  if (g_Spim_En)
  {
    return GENERAL_ERROR;
  }
  /* Initially Disable SPI */
  SPCR = _BV(MSTR);
  g_Spim_En = 0;
  SPSR; // To Clear the SPIF status
  /* Setup SPI Pins */
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, OUTPUT);
  /* Setup the 2X Speed if Needed as per Data-rate Selected */
  SPSR = (datarate & SPIM_SPEED_MASK2X) >> 4;
  /* Load Configuration */
  if(bitOrder == LSBFIRST)
  {
    setting = _BV(DORD)|(spimode & SPIM_MODE_MASK)|
      (datarate & SPIM_SPEED_MASKLOW);
  }
  else // MSB First 
  {
    setting = (spimode & SPIM_MODE_MASK)|
      (datarate & SPIM_SPEED_MASKLOW);
  }
  pinMode(SS, OUTPUT); // This needs to be Output For any thing to work on SPIM
  // Enable SPI and Load correct Settings
  SPCR = _BV(SPE)|_BV(MSTR)|setting;
  g_Spim_En = 1; // Enable the SPI Setting
  return SUCCESS;
}

uint8_t SpimSend(uint8_t data)
{
  uint8_t ret;
  if (g_Spim_En == 0)
  {
    return 0;
  }
  ret = data;
  // Start transmission
  SPDR = ret;
  // Wait for transmission complete
  while(!(SPSR & _BV(SPIF)));
  ret = SPDR;
  return ret;
}

uint8_t SpimSends(uint8_t *dataOut, uint16_t size)
{
  uint8_t ret;
  uint16_t i = 0;
  if (g_Spim_En == 0 || dataOut == 0 || size == 0)
  {
    return 0;
  }
  /* Make the First Read */
  ret = SpimSend(dataOut[i]);
  /* Perform Subsequent reads */
  while(++i < size)
  {
    SpimSend(dataOut[i]);
  }
  /* Return the First byte read - Generally Status */
  return ret;
}

uint8_t SpimReads(uint8_t *dataIn, uint8_t dummy_dataOut, uint16_t size)
{
  uint16_t i = 0;
  if (g_Spim_En == 0 || dataIn == 0 || size == 0)
  {
    return GENERAL_ERROR;
  }
  /* Make the First Read */
  dataIn[i] = SpimSend(dummy_dataOut);
  /* Perform Subsequent reads */
  while(++i < size)
  {
    dataIn[i] = SpimSend(dummy_dataOut);
  }
  return SUCCESS;
}

uint8_t SpimTrans(uint8_t *dataIn, uint8_t *dataOut, uint16_t size)
{
  uint16_t i = 0;
  if (g_Spim_En == 0 || dataOut == 0 || dataIn == 0 || size == 0)
  {
    return GENERAL_ERROR;
  }
  /* Make the First Read */
  dataIn[i] = SpimSend(dataOut[i]);
  /* Perform Subsequent reads */
  while(++i < size)
  {
    dataIn[i] = SpimSend(dataOut[i]);
  }
  return SUCCESS; 
}

uint8_t SpimOff()
{
  if (g_Spim_En == 0)
  {
    return GENERAL_ERROR;
  }
  /* Initially Disable SPI */
  SPCR = 0;
  g_Spim_En = 0;
  return SUCCESS;
}
