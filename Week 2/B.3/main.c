#ifndef F_CPU
#define F_CPU 8e6
#endif

#include "avr/io.h"
#include "util/delay.h"

int hex_vals[] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, // Numbers 0-9
	0x77, 0x7C, 0x39, 0x5E, 0x7B, 0x71, // Numbers A-F
	0x79 // Error value
};

int display_hex(int number);

int main( void ) {
	int pressed_d0 = 0;
	int pressed_d1 = 0;
	int counter = 0;

	// Set all port B pins to output mode (for displaying seven segment)
	DDRB = 0xFF;

	// Set port D.0 and port D.1 to output mode (for receiving button press)
	DDRD = 0x03;

	display_hex(counter);

	while (1) {
		// Runs when either D.0 wasn't already pressed and output is detected from both D.0 and D.1
		// OR when D.1 wasn't already pressed and output is detected from both D.0 and D.1
		if ((!pressed_d0 && (PIND & 0b11) == 0b11) || (!pressed_d1 && (PIND & 0b11) == 0b11)) {
			pressed_d0 = 1;
			pressed_d1 = 1;

			// Reset counter
			counter = 0;
			display_hex(counter);
		// Else, if D.0 wasn't already pressed and output is detected from D.0
		} else if (!pressed_d0 && PIND & 0b1) {
			pressed_d0 = 1;

			// Increase counter if valid number, otherwise reset it
			counter++;
			if (!display_hex(counter))
				counter = 0;
		// Else, if D.1 wasn't already pressed and output is detected from D.1
		} else if (!pressed_d1 && (PIND & 0b10) >> 1) {
			pressed_d1 = 1;

			// Decrease counter if valid number, otherwise reset it
			counter--;
			if (!display_hex(counter))
				counter = 0;
		}

		// Detect when D.0 was already pressed, but no more output is detected from D.0
		if (pressed_d0 && !(PIND & 0b1))
			pressed_d0 = 0;
		
		// Detect when D.1 was already pressed, but no more output is detected from D.1
		if (pressed_d1 && !((PIND & 0b10) >> 1)) {
			pressed_d1 = 0;
		}
	}
	
	return 1;
}

// Displays a number to a seven segment screen
//
// Returns: 1 if parameter number was: 0 <= number < 16, otherwise returns 0
int display_hex(int number) {
	if (number >= 0 && number < 16) {
		PORTB = hex_vals[number];
		return 1;
	} else {
		// Display error
		PORTB = hex_vals[16];
		return 0;
	}
}
