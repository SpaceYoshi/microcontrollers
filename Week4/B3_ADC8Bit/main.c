#define F_CPU 8e6

#include <avr/delay.h>
#include <avr/io.h>

int main(void) {
	// Ensure port F is set to to input
	DDRF = 0x00;

	// Set ports A and B to output
	DDRA = 0xFF;
	DDRB = 0xFF;

	// Voltage reference = internal 2.56V (bit 7, 6),
	// left adjust result (bit 5),
	// target ADC3 (remaining bits).
	ADMUX = 0b11100011;

	// Enable ADC (bit 7),
	// don't start conversion right away (bit 6),
	// disable Free Running mode (bit 5),
	// don't enable interrupts (bit 3),
	// set prescaler to 64 (bit 2, 1, 0).
	ADCSRA = 0b10000110;

	while (1) {
		// Start ADC conversion by pulling bit 6 high
		ADCSRA |= BIT(6);

		// Wait while bit 6 is high (until ADC is done processing)
		while (ADCSRA & BIT(6));

		// Set port B to the 8 least significant bits
		PORTB = ADCH;
	}

	return 1;
}
