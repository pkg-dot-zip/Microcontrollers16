#define F_CPU 8e6
#define SOLETURNON(x) (0b00000001 << (x))

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
*******************************************************************/
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	DDRD = 0b11111111; // All pins of PORTD to output.
	
	while(1)
	{
		//PORTD = 0b00000001 << 7; // Set pin 7 on, rest off.
		PORTD = SOLETURNON(7); // Set pin 7 on, rest off.
		wait(500);
		PORTD = SOLETURNON(6); // Set pin 6 on, rest off.
		wait(500);
	}
	
	return 1;
}