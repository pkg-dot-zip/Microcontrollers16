#define F_CPU 8e6
#define SOLETURNON(x) (0b00000001 << (x))
#define SIZE 16

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const int size = SIZE;
const unsigned char Numbers [SIZE] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01111001, // E
};

int index = 0; // Big value so that we can go back as well without entering negative values.

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void display(int digit){
	PORTB = Numbers[digit];
}

ISR( INT1_vect ) {
	if (index > 0) {
		index--;
	}
	
	display(index % size); // Cycle light down.
}

ISR( INT2_vect ) {
	if (index < SIZE - 1) {
		index++;
	}
	
	display(index % size); // Cycle light up.
}

int main( void ) {
	// Init I/O
	PORTD = 0xFF;			// Set all K to output.
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input	
	DDRB = 0xFF;			// PORTD(7:4) output, PORTD(3:0) input	

	// Init Interrupt hardware
	EICRA |= 0x3C;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x06;			// Enable INT1 & INT2
	
	// Init.
	sei();	// Enable global interrupt system.

	PORTD = 0x00; // Set first light on.

	// Empty while(true) loop.
	while (1) {							
	}

	return 1;
}