/**
 * @file twim.cpp
 *
 * @brief TWI Master mode functions are defined here
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
 * @note Arduino - Copyright owned by Arduino LLC and we are not associated
 *  with them in any what so ever manner. JBF is an independently developed entity
 *  and hence Arduino LLC or Associated collaborators cannot claim ownership
 *  of this work under any legal on permissible context.
 *
 */
#include <Arduino.h>
#include <util/twi.h>

//#define SER_DEBUG


void TwimOn(uint8_t bitrate)
{
  TWCR = 0;
  if(bitrate == TWIM_BITRATE_10K)
  {
#if F_CPU==16000000L
    TWBR = 198;
#elif F_CPU==11059200L
    TWBR = 136;
#elif F_CPU==14745600L
    TWBR = 182;
#elif F_CPU==8000000L
    TWBR = 98;
#elif F_CPU==12000000L
    TWBR = 148;
#else
#error "Frequency not defined for Operation"
#endif
    TWSR = 1;
  }
  else
  {
    if(bitrate == TWIM_BITRATE_100K)
#if F_CPU==16000000L
      TWBR = 72;
#elif F_CPU==11059200L
      TWBR = 48;
#elif F_CPU==14745600L
      TWBR = 66;
#elif F_CPU==8000000L
      TWBR = 32;
#elif F_CPU==12000000L
      TWBR = 52;
#else
#error "Frequency not defined for Operation"
#endif
    else // 400k
#if F_CPU==16000000L
      TWBR = 12;
#elif F_CPU==11059200L
      TWBR = 6;
#elif F_CPU==14745600L
      TWBR = 11;
#elif F_CPU==8000000L
      TWBR = 2;
#elif F_CPU==12000000L
      TWBR = 7;
#else
#error "Frequency not defined for Operation"
#endif
    TWSR = 0;
  }
  TWCR = _BV(TWEN)| _BV(TWEA);
}

void TwimOff(void)
{
  TWCR = 0;
}

uint8_t TwimWriteEx(uint8_t address, uint8_t *buf, uint8_t len, uint8_t sendstop)
{
  uint8_t stat, i, ret = SUCCESS;
  do{ // Error Capture Loop

    if (len == 0)
      return PARAMETER_ERROR;
    // Send the Start Bit
    TWCR = _BV(TWINT)|_BV(TWSTA)|_BV(TWEN)|_BV(TWEA);
    while(!(TWCR&_BV(TWINT)));
    stat = TW_STATUS;
    if(stat != TW_START && stat != TW_REP_START)
    {
#ifdef SER_DEBUG
      SerOut("\nFailed to Start");
      //while(1); // Hang
#endif
      ret = TWIM_STATUS_START_FAILED;
      break;
    }

    // Send out Address
    TWDR = address & 0xFE;
    TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWEA);
    while(!(TWCR&_BV(TWINT)));
    stat = TW_STATUS;
    if(stat != TW_MT_SLA_ACK)
    {
#ifdef SER_DEBUG
      SerOut("\nFailed to Get ACK on Address");
      //while(1); // Hang
#endif
      ret = TWIM_STATUS_ADDRESS_FAILED;
      break;
    }

    // Send out Bytes
    for(i=0;i<len;i++)
    {
      // Send out Byte
      TWDR = buf[i];
      TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWEA);
      while(!(TWCR&_BV(TWINT)));
      stat = TW_STATUS;
      if(stat != TW_MT_DATA_ACK)
      {
#ifdef SER_DEBUG
        SerOut("\nFailed to ACK on Byte ");
        SerOutb(i);
        //while(1); // Hang
#endif
        ret = TWIM_STATUS_DATASEND_FAILED;
        break;
      }// End of if(stat != TW_MT_DATA_ACK)
    }// End of Byte Sending Loop
  }while(0);// End of Error Capture Loop

  // Process the Stop Condition
  if((ret > TWIM_STATUS_START_FAILED)|| (sendstop))
  {
#ifdef SER_DEBUG
    if(ret > TWIM_STATUS_START_FAILED)
      SerOut("\nStop Begin Sent Upon Error");
#endif
    // send stop condition
    TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);
    while(TWCR & _BV(TWSTO));
  }

  // Finally Return the Processed Status
  return ret;
}


uint8_t TwimReadEx(uint8_t address, uint8_t *buf, uint8_t len, uint8_t sendstop)
{
  uint8_t stat, i, ret = SUCCESS;
  do{ // Error Capture Loop

    if (len == 0)
      return PARAMETER_ERROR;
    // Send the Start Bit
    TWCR = _BV(TWINT)|_BV(TWSTA)|_BV(TWEN)|_BV(TWEA);
    while(!(TWCR&_BV(TWINT)));
    stat = TW_STATUS;
    if(stat != TW_START && stat != TW_REP_START)
    {
#ifdef SER_DEBUG
      SerOut("\nFailed to Start");
      //while(1); // Hang
#endif
      ret = TWIM_STATUS_START_FAILED;
      break;
    }

    // Send out Address
    TWDR = address | 1;
    TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWEA);
    while(!(TWCR&_BV(TWINT)));
    stat = TW_STATUS;
    if(stat != TW_MR_SLA_ACK)
    {
#ifdef SER_DEBUG
      SerOut("\nFailed to Get ACK on Address");
      //while(1); // Hang
#endif
      ret = TWIM_STATUS_ADDRESS_FAILED;
      break;
    }

    // Send out len-1 bytes
    i = 0;
    if(len>1)
    {
      for(;i<(len-1);i++)
      {
        // Read one More Byte with ACK
        TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWEA);
        while(!(TWCR&_BV(TWINT)));
        stat = TW_STATUS;
        if(stat != TW_MR_DATA_ACK)
        {
#ifdef SER_DEBUG
          SerOut("\nFailed Receive Byte with ACK ");
          SerOutb(i);
          //while(1); // Hang
#endif
          ret = TWIM_STATUS_DATAREAD_ACK_FAILED;
          break;
        }
        else /* Read the Byte*/
        {
          buf[i] = TWDR;
        }// End of if(stat != TW_MR_DATA_ACK)
      }// End of Loop for Reading Data
    }// End of Higher Length Read
    if(ret > 0) // Eject in Case of Error
      break;

    // Read Last Byte
    TWCR = _BV(TWINT)|_BV(TWEN);
    while(!(TWCR&_BV(TWINT)));
    stat = TW_STATUS;
    if(stat != TW_MR_DATA_NACK)
    {
#ifdef SER_DEBUG
      SerOut("\nFailed Receive Last Byte with NACK");
      //while(1); // Hang
#endif
      ret = TWIM_STATUS_DATAREAD_NACK_FAILED;
      break;
    }
    else /* Read the Byte*/
    {
      buf[i] = TWDR;
    }
  }while(0);// End of Error Capture Loop

  // Process the Stop Condition
  if((ret > TWIM_STATUS_START_FAILED)|| (sendstop))
  {
#ifdef SER_DEBUG
    if(ret > TWIM_STATUS_START_FAILED)
      SerOut("\nStop Begin Sent Upon Error");
#endif
    // send stop condition
    TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);
    while(TWCR & _BV(TWSTO));
  }

  // Finally Return the Processed Status
  return ret;
}
