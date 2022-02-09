/*
 * main.c
 *
 * Created: 2/9/2022 2:09:41 PM
 *  Author: dutch
 */ 

#define F_CPU 8e6


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <xc.h>
#include "lcd.h"

/******************************************************************
short:			Writes 8 bits COMMAND to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/

void wait( int ms )
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	DDRC = 0xFF;

	init();
		
	char text[] = "Test Text 2";
	display_text(text);	
	
	char text2[] = "Yoo";
	display_text(text2);
    while(1)
    {
    }
	
	return 1;
}