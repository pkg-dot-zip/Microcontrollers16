#define F_CPU 8e6
#define SOLETURNON(x) (0b00000001 << (x))

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

// Wait. Amount dependent on pressed value.
void waitPressed(int pressed)
{
	if (pressed) {
		wait(250); // 4 hz.
		} else {
		wait(1000); // 1 hz.
	}
}

int main(void)
{
	DDRD = 0b11111111; // All pins of PORTD to output.
	int pressed = 0; // 1 means true, 0 means false.
	int wasReleased = 0; // 1 means true, 0 means false.
	
	while (1) {
		PORTD = SOLETURNON(7); // Set light on pin 7.
		
		// Check if the button was released.
		if (PINC != 0b00000001) {
			wasReleased = 1;
		}
		
		// If a button is pressed we toggle the pressed value.
		if (PINC == 0b00000001 && wasReleased) {
			if (pressed == 0) {
				pressed = 1;
			} else {
				pressed = 0;
			}
			
			wasReleased = 0;
		}
		
		waitPressed(pressed);
		
		PORTD = 0b00000000; // Set all lights off.
		
		waitPressed(pressed);
	}
	
	return 1;
}