#define F_CPU 8e6

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	D5,
	D6,
	D7
} EVENT;

typedef enum {
	START,
	S1,
	S2,
	S3,
	END
} STATE_ENUM;

typedef struct {
	void (*handle)(EVENT);
	void (*init)(void);
	void (*exit)(void);
	STATE_ENUM state;
} STATE;

void start(EVENT);
void s1(EVENT);
void s2(EVENT);
void s3(EVENT);
void end(EVENT);


void wait( int ms )
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

STATE_ENUM currentState;

STATE states[5] = {
	{ start, NULL, NULL, START },
	{ s1,	NULL, NULL, S1 },
	{ s2,	NULL, NULL, S2 },
	{ s3,	NULL, NULL, S3 },
	{ end, NULL, NULL, END },
};

void start(EVENT event) {
	switch(event){
		case D5:
		stateSwitch(S2);
		break;
		case D6:
		stateSwitch(S1);
		break;
	}
}

void s1(EVENT event) {
	switch(event){
		case D5:
		stateSwitch(S2);
		break;
		case D7:
		stateSwitch(START);
		break;
	}
}

void s2(EVENT event) {
	switch(event){
		case D5:
		stateSwitch(S3);
		break;
		case D6:
		stateSwitch(START);
		case D7:
		stateSwitch(START);
		break;
	}
}

void s3(EVENT event) {
	switch(event){
		case D5:
		case D6:
		stateSwitch(END);
		break;
		case D7:
		stateSwitch(START);
		break;
	}
}

void end(EVENT event) {
	switch(event){
		case D7:
		stateSwitch(START);
		break;
	}
}

void stateSwitch(STATE_ENUM toStart) {
	states[currentState].exit();
	states[toStart].init();
	currentState = toStart;
}

int main(void)
{
	DDRD = 0b11111111; // All pins of PORTD to output.
	
	currentState = START;
	states[currentState].init();
	
	while (1) {
		// Logic here.
	}
	
	states[currentState].exit();
	
	return 1;
}