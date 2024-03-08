#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

// Lookup table containing hex values sent to the seven segment display
int hex_vals[] = {
	0xFF, 0x00, 0x63, 0x43, 0x03, 0x01, 0x63, 0x43, 0x03, 0x01, 0x00, 0x20,
	0x40, 0x02, 0x01, 0x20, 0x40, 0x02, 0x01, 0x00, 0x80, 0x00, 0x80
};

int main(void) {
	// Set all port B pins to output mode (for displaying seven segment)
	DDRB = 0xFF;

	while (1) {
		// Loop over hex_vals and send each value to PORTB
		for (int i = 0; i < 23; i++) {
			PORTB = hex_vals[i];
			_delay_ms(250);
		}
	}

	return 1;
}
