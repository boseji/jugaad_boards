#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/atomic.h>

#include <Arduino.h>

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }

int main(void)
{
	//init();

	//initVariant();

//#if defined(USBCON)
//	USBDevice.attach();
//#endif
	
	setup();
    
	for (;;) {
		loop();
		//if (serialEventRun) serialEventRun();
	}
        
	return 0;
}
