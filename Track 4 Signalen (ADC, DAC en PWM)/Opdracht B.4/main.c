/*
 * main.c
 *
 * Created: 3/16/2022 11:16:02 AM
 *  Author: stijn
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "stdlib"

#define BIT(x)	(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC: 
void adcInit( void )
{
	ADMUX = 0b11100011;			// AREF=2,56 V, result left adjusted
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no free running, division by 64
}


// Main program: Counting on T1
int main( void )
{
	DDRF = 0x00;					// set PORTF for input (ADC)
	DDRA = 0xFF;					// set PORTA for output 
	adcInit();						// initialize ADC
	lcd_init();
	
	char *string = malloc(sizeof(char) * 5);
	
	while (1)
	{
		ADCSRA |= BIT(6);				// Start ADC
		while ( ADCSRA & BIT(6) );		// Wait for completion
		PORTA = ADCH;					// Show MSB (bit 9:2) of ADC
		char i = ADCH;
		sprintf(string, "%d", i);
		lcd_clear();
		display_text(string);
		wait(100);						// every 50 ms (busy waiting)
	}
}