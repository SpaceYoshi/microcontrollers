#define F_CPU 8e6

#include <avr/delay.h>
#include <avr/io.h>

int main(void) {
	// Ensure pin F.0 is set to to input
	DDRF &= ~(1 << PF0);

	// Set ports A and B to output
	DDRA = 0xFF;
	DDRB = 0xFF;

	// Voltage reference = external at AREF (bit 7, 6),
	// left adjust result (bit 5),
	// target ADC0 (remaining bits).
	ADMUX = 0b01100000;

	// Enable ADC (bit 7),
	// start conversion right away (bit 6),
	// operate in Free Running mode (bit 5),
	// don't enable interrupts (bit 3),
	// set prescaler to 64 (bit 2, 1, 0).
	ADCSRA = 0b11100110;

	while (1) {
		// Set port A to the 2 most significant bits
		PORTA = ADCL;

		// Set port B to the 8 least significant bits
		PORTB = ADCH;
		_delay_ms(100);
	}

	return 1;
}
