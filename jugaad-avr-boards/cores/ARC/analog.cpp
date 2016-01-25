/**
 * @file analog.cpp
 *
 * @brief This file contains the definitions for the Analog interface
 *  functions of the MCU
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

static uint8_t g_analog_reference = DEFAULT;

uint8_t analogReference(uint8_t val)
{
  switch(val)
  {
    case DEFAULT:
    case INTERNAL:
    case EXTERNAL:
      g_analog_reference = val;
      break;
    default:
      return PARAMETER_ERROR;
  }
  return SUCCESS;
}

uint16_t analogRead(uint8_t apin)
{
  uint8_t high = 0, low = 0;
  /* Enable the ADC */
#if defined(ADCSRA)
  // Enable ADC with Slow conversion rate of F_CPU/16
  ADCSRA = 0b10000100;
#endif

#if defined(ADCSRB) && defined(MUX5)
  // the MUX5 bit of ADCSRB selects whether we're reading from channels
  // 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
  ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin2anlog_chan(apin) >> 3) & 0x01) << MUX5);
#endif

  // set the analog reference (high two bits of ADMUX) and select the
  // channel (low 4 bits).  this also sets ADLAR (left-adjust result)
  // to 0 (the default).
#ifdef ADMUX
  ADMUX = (g_analog_reference<<REFS0) | (pin2anlog_chan(apin) & 0x0F);
#endif

#if defined(ADCSRA) && defined(ADCL)
  // start the conversion
  ADCSRA |= _BV(ADSC);

  // ADSC is cleared when the conversion finishes
  while((ADCSRA & _BV(ADIF)) != _BV(ADIF)); // Wait till conversion is complete
  // Clear the Flag
  ADCSRA  |= (1 << ADIF);
  // Read Values
  low  = ADCL;
  high = ADCH;
#else
  // we don't have an ADC, return 0
  low  = 0;
  high = 0;
#endif

  return (high<<8) | low;
}

void analogOff()
{
#ifdef ADMUX
  ADMUX = 0; /* Turn Off All Reference */
#endif
#if defined(ADCSRA)
  ADCSRA = 0; /* Turn Off the ADC */
#endif
}
