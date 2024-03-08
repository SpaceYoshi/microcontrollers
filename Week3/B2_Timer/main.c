#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>

#define BIT(x) (1 << (x))

// Runs whenever a timer interrupt is triggered
ISR(TIMER_COMP_vect) {
	// Toggle PD.7 to be either high or low
	PORTD ^= BIT(7);
	
	// Toggle OCR2 to be either 15 or 25 milliseconds
	OCR2 = OCR2 == 15 ? 25 : 15;
}

int main(void)
{
	// Set OC2 on compare match.
	// Set clock source to clock frequency
	// divided by 256 (from prescaler).
	TCCR2 = 0b00011100;
	
	// Set the timer's initial value to zero
	TCNT2 = 0x00;

	// Set PD.7 to be output.
	DDRD = BIT(7);
	
	// Setting the MSB to high enables invoking
	// interrupts whenever the timer's value matches
	// with OCR2 (output compare register)
	TIMSK |= BIT(7);
	
	// Initially, set OCR2 (the counter's maximum
	// value) to be 15 for 15 milliseconds.
	OCR2 = 15;
	
	// Enable global interrupts
	sei();
	
	while (1) {}

	return 1;
}

