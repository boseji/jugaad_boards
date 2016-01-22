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

uint8_t shiftOut(uint8_t data_pin, uint8_t clock_pin, uint8_t bitOrder, uint8_t val)
{
    volatile uint8_t *pd, *pc;
    uint8_t bs, i, bitd, bitc, initc;
    if((data_pin > NUM_DIGITAL_PINS)||(clock_pin > NUM_DIGITAL_PINS))
        return PARAMETER_ERROR; 
    /* Initialize the Variables to begin */
    bs = val;
    bitd = pin2bit(data_pin);
    bitc = pin2bit(clock_pin);
    pd = pin2out(data_pin);
    /* Read Initial Value of the Clock pin to Determine State while sending */
    pc = pin2inp(clock_pin);
    initc = (*pc & bitc);
    pc = pin2out(clock_pin);
    /* Check bit order to Run the Loop */
    if(bitOrder == LSBFIRST)
    {
        /* Check Initial Clock Condition */
        if(initc)
        {
            for(i=0;i<8;i++)
            {
                if(bs & 0x01) *pd |= bitd;
                else *pd &= ~bitd;

                *pc &= ~bitc;
                *pc |= bitc;
                bs >>= 1;
            }
        }
        else
        {
            for(i=0;i<8;i++)
            {
                if(bs & 0x01) *pd |= bitd;
                else *pd &= ~bitd;

                *pc |= bitc;
                *pc &= ~bitc;
                bs >>= 1;
            }
        }   
        
    }
    else /* MSBFIRST */
    {
        /* Check Initial Clock Condition */
        if(initc)
        {
            for(i=0;i<8;i++)
            {
                if(bs & 0x80) *pd |= bitd;
                else *pd &= ~bitd;

                *pc &= ~bitc;
                *pc |= bitc;
                bs <<= 1;
            }
        }
        else
        {
            for(i=0;i<8;i++)
            {
                if(bs & 0x80) *pd |= bitd;
                else *pd &= ~bitd;

                *pc |= bitc;
                *pc &= ~bitc;
                bs <<= 1;
            }
        }   
    }
    return SUCCESS;
}

uint8_t shiftIn(uint8_t data_pin, uint8_t clock_pin, uint8_t bitOrder)
{
    volatile uint8_t *pd, *pc;
    uint8_t bs, i, bitd, bitc, initc;
    if((data_pin > NUM_DIGITAL_PINS)||(clock_pin > NUM_DIGITAL_PINS))
        return 0; /* As Cant use the Error Codes */
    /* Initialize the Variables to begin */
    bs = 0;
    bitd = pin2bit(data_pin);
    bitc = pin2bit(clock_pin);
    pd = pin2inp(data_pin);
    /* Read Initial Value of the Clock pin to Determine State while sending */
    pc = pin2inp(clock_pin);
    initc = (*pc & bitc);
    pc = pin2out(clock_pin);
    /* Check bit order to Run the Loop */
    if(bitOrder == LSBFIRST)
    {
        /* Check Initial Clock Condition */
        if(initc)
        {
            for(i=0;i<8;i++)
            {
                bs >>= 1;
                *pc &= ~bitc;
                _NOP();
                if(*pd & bitd) bs |= 0x80;
                *pc |= bitc;    
            }
        }
        else
        {
            for(i=0;i<8;i++)
            {
                bs >>= 1;
                *pc |= bitc;
                _NOP();
                if(*pd & bitd) bs |= 0x80;
                *pc &= ~bitc;
            }
        }   
        
    }
    else /* MSBFIRST */
    {
        /* Check Initial Clock Condition */
        if(initc)
        {
            for(i=0;i<8;i++)
            {
                bs <<= 1;
                *pc &= ~bitc;
                _NOP();
                if(*pd & bitd) bs |= 0x01;
                *pc |= bitc;    
            }
        }
        else
        {
            for(i=0;i<8;i++)
            {
                bs <<= 1;
                *pc |= bitc;
                _NOP();
                if(*pd & bitd) bs |= 0x01;
                *pc &= ~bitc;   
            }
        }   
    }
    return bs;
}

uint8_t shiftOutIn(uint8_t in_pin, uint8_t out_pin, uint8_t clock_pin, uint8_t bitOrder, uint8_t val)
{
    volatile uint8_t *po, *pc, *pi;
    uint8_t bs, data, i, bito, biti, bitc, initc;
    if((in_pin > NUM_DIGITAL_PINS)||(out_pin > NUM_DIGITAL_PINS)||(clock_pin > NUM_DIGITAL_PINS))
        return 0; /* As Cant use the Error Codes */
    /* Initialize the Variables to begin */
    data = val;
    bs = 0;
    bito = pin2bit(out_pin);
    biti = pin2bit(in_pin);
    bitc = pin2bit(clock_pin);
    po = pin2out(out_pin);
    pi = pin2inp(in_pin);
    /* Read Initial Value of the Clock pin to Determine State while sending */
    pc = pin2inp(clock_pin);
    initc = (*pc & bitc);
    pc = pin2out(clock_pin);
    /* Check bit order to Run the Loop */
    /* Check bit order to Run the Loop */
    if(bitOrder == LSBFIRST)
    {
        /* Check Initial Clock Condition */
        if(initc)
        {
            for(i=0;i<8;i++)
            {
                if(data & 0x80) *po |= bito;
                else *po &= ~bito;

                bs >>= 1;
                *pc &= ~bitc;
                _NOP();
                if(*pi & biti) bs |= 0x80;
                *pc |= bitc;    
                data <<= 1;         
            }
        }
        else
        {
            for(i=0;i<8;i++)
            {
                if(data & 0x80) *po |= bito;
                else *po &= ~bito;

                bs >>= 1;
                *pc |= bitc;
                _NOP();
                if(*pi & biti) bs |= 0x80;
                *pc &= ~bitc;
                data <<= 1;     
            }
        }   
        
    }
    else /* MSBFIRST */
    {
        /* Check Initial Clock Condition */
        if(initc)
        {
            for(i=0;i<8;i++)
            {
                if(data & 0x01) *po |= bito;
                else *po &= ~bito;

                bs <<= 1;
                *pc &= ~bitc;
                _NOP();
                if(*pi & biti) bs |= 0x01;
                *pc |= bitc;    
                data >>= 1; 
            }
        }
        else
        {
            for(i=0;i<8;i++)
            {
                if(data & 0x01) *po |= bito;
                else *po &= ~bito;

                bs <<= 1;
                *pc |= bitc;
                _NOP();
                if(*pi & biti) bs |= 0x01;
                *pc &= ~bitc;   
                data >>= 1;             
            }
        }   
    }
    return bs;
}