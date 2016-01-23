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
	while((ADCSRA & _BV(ADIF)) != _BV(ADIF));	// Wait till conversion is complete
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

