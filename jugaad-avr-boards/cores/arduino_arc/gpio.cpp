#include <Arduino.h>

uint8_t pinMode(uint8_t pin,uint8_t mode)
{
	volatile uint8_t *p;
	if(pin > NUM_DIGITAL_PINS)
		return PARAMETER_ERROR;
	/* Get the Direction Register Address */
	p = pin2dir(pin);
	switch(mode)
	{
		case OUTPUT:
			*p |= pin2bit(pin);
			break;
		case INPUT:
			*p &= ~pin2bit(pin);
			break;
		case INPUT_PULLUP:
			*p &= ~pin2bit(pin);
			/* Get output Register Address for Configuration */
			p = pin2out(pin);
			*p |= pin2bit(pin);
			break;
		default:
			return GENERAL_ERROR;
	}
	return SUCCESS;
}

uint8_t digitalWrite(uint8_t pin, uint8_t state)
{
	volatile uint8_t *p;
	if(pin > NUM_DIGITAL_PINS)
		return PARAMETER_ERROR;
	/* Get the Output Register Address */
	p = pin2out(pin);
	switch(state)
	{
		case HIGH:
			*p |= pin2bit(pin);
			break;
		case LOW:
			*p &= ~pin2bit(pin);
			break;
		default:
			return GENERAL_ERROR;			
	}
	return SUCCESS;
}

uint8_t digialToggle(uint8_t pin)
{
	volatile uint8_t *p;
	if(pin > NUM_DIGITAL_PINS)
		return PARAMETER_ERROR;
	/* Get the Output Register Address */
	p = pin2out(pin);
	/* Toggle the Pin */
	*p ^= pin2bit(pin);
	return SUCCESS;
}

uint8_t digialRead(uint8_t pin)
{
	volatile uint8_t *p;
	if(pin > NUM_DIGITAL_PINS)
		return 0; /* As Cant use the Error Codes */
	/* Get Input Register Address */
	p = pin2inp(pin);
	return ((*p & pin2bit(pin)) > 0);
}