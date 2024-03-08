#define F_CPU 8e6

#include <avr/io.h>
#include <avr/delay.h>
#include "lcd.h"

int main(void)
{
	// Ensure port F is set to be input
	DDRF = 0x00;

	// Set port A to be output
	DDRA = 0xFF;
	
	// Voltage reference = internal 2.56V (bit 7, 6),
	// left adjust result (bit 5),
	// target ADC1 (remaining bits).
	ADMUX = 0b11100001;

	// Enable ADC (bit 7),
	// start conversion right away (bit 6),
	// disable Free Running mode (bit 5),
	// don't enable interrupts (bit 3),
	// set prescaler to 64 (bit 2, 1, 0).
	ADCSRA = 0b11000110;

	_delay_ms(1500);
	
	// Set LCD communication to 4-bits mode
	init_4bits_mode();

	while (1)
	{
		// Start ADC conversion by pulling bit 6 high
		ADCSRA |= (1 << 6);

		// Wait while bit 6 is high (until ADC is done processing)
		while (ADCSRA & (1 << 6));

		char buffer[16];

		// Set port A to the 8 least significant bits
		PORTA = ADCH;

		// Convert the result of ADC1 to a string
		sprintf(buffer, "%d", ADCH);

		set_cursor(0);

		_delay_ms(500);

		// Display the result of ADC1
		display_text(buffer);
		
		_delay_ms(500);
	}

	return 1;
}
