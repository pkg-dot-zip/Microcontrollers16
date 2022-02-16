/*
 * main.c
 *
 * Created: 2/16/2022 10:05:12 AM
 *  Author: stijn
 */ 

#define F_CPU 8e6
#include <xc.h>
#include <util/delay.h>
#include "lcd.h"


#define BIT(x)			(1 << (x))

void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

int parseByte(unsigned char byte) {
	return (int) byte;
}


int main(void)
{
	init();
	    	DDRD &= ~BIT(7);		// PD7 op input: DDRD=xxxx xxx0
	    	TCCR2 = 0b00000111;		// counting via PD7, rising edge
	    
    while(1)
    {
		char count[16] = "0";
		sprintf(count, "%d", TCNT2);
		display_text(count);
		set_cursor(0);
		wait(100);
		
    }
}