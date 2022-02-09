#define F_CPU 8e6
#define SOLETURNON(x) (0b00000001 << (x))

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int index = 1000 * 8; // Big value so that we can go back as well without entering negative values.

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT1_vect ) {
	PORTC = SOLETURNON(index-- % 8); // Cycle light down.
}

ISR( INT2_vect ) {
	PORTC = SOLETURNON(index++ % 8); // Cycle light up.
}

int main( void ) {
	// Init I/O
	DDRC = 0xFF;			// Set all C to output.
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input	

	// Init Interrupt hardware
	EICRA |= 0x3C;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x06;			// Enable INT1 & INT2
	
	// Init.
	sei();	// Enable global interrupt system.

	PORTC = 0b00000001; // Set first light on.

	// Empty while(true) loop.
	while (1) {							
	}

	return 1;
}