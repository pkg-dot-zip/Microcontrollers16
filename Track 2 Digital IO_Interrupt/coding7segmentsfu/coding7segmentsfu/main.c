#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef struct {
	unsigned char data;
	unsigned int delay;
} lightEffectStruct; 

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main( void ) {
	// Init I/O
	DDRB = 0xFF;			// PORTD(7:4) output, PORTD(3:0) input	

	lightEffectStruct lightEffect[] = {
		{ 0x01, 1000 },
		{ 0x02, 1000 },
		{ 0x04, 1000 },
		{ 0x08, 1000 },
		{ 0x10, 1000 },
		{ 0x08, 1000 },
		{ 0x04, 1000 },
		{ 0x02, 1000 },
		{ 0x01, 1000 },
		{ 0x00, 0    }
	};
	
	while (1) {
		int index = 0;
		int arraySize = sizeof(lightEffect) / sizeof(lightEffect[0]);
		while (lightEffect[index].delay != 0) {
			PORTB = lightEffect[index].data;
			wait(lightEffect[index].delay);
			index++ % arraySize - 1;
		}
	}

	return 1;
}