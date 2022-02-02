#define F_CPU 8e6
#define SOLETURNON(x) (0b00000001 << (x))

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x01, 150}, {0x02, 150}, {0x03, 150}, {0x04, 150}, {0x05, 150}, {0x06, 150}, {0x07, 150}, {0x08, 150}, {0x09, 150}, {0x0A, 150}, {0x0B, 150}, {0x0D, 150}, {0x0E, 150}, {0x0F, 150},
	{0x11, 150}, {0x12, 150}, {0x13, 150}, {0x14, 150}, {0x15, 150}, {0x16, 150}, {0x17, 150}, {0x18, 150}, {0x19, 150}, {0x1A, 150}, {0x1B, 150}, {0x1D, 150}, {0x1E, 150}, {0x1F, 150},
	{0x21, 150}, {0x22, 150}, {0x23, 150}, {0x24, 150}, {0x25, 150}, {0x26, 150}, {0x27, 150}, {0x28, 150}, {0x29, 150}, {0x2A, 150}, {0x2B, 150}, {0x2D, 150}, {0x2E, 150}, {0x2F, 150},
	{0x31, 150}, {0x32, 150}, {0x33, 150}, {0x34, 150}, {0x35, 150}, {0x36, 150}, {0x37, 150}, {0x38, 150}, {0x39, 150}, {0x3A, 150}, {0x3B, 150}, {0x3D, 150}, {0x3E, 150}, {0x3F, 150},
	{0x41, 150}, {0x42, 150}, {0x43, 150}, {0x44, 150}, {0x45, 150}, {0x46, 150}, {0x47, 150}, {0x48, 150}, {0x49, 150}, {0x4A, 150}, {0x4B, 150}, {0x4D, 150}, {0x4E, 150}, {0x4F, 150},
	{0x00, 0x00}
};

void wait( int ms )
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

int main(void)
{
	DDRD = 0b11111111; // All pins of PORTD to output.
	
	while (1==1) {
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		while( pattern[index].delay != 0 ) {
			// Write data to PORTD
			PORTD = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
	}
	
	return 1;
}