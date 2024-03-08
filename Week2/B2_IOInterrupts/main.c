#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>

int main(void) {
	// Configure D.0 to D.3 to ouput mode (for button presses)
	DDRD = 0x0F;

	// Configure all A.n pins to output mode (for displaying LED)
	DDRA = 0xFF;

	// Set INT0 and INT1 to rising edge detection
	EICRA = 0x0F;
	
	// Enable interrupts INT0 and INT1
	EIMSK = 0x03;

	// Enable global interrupts
	sei();

	PORTA = 1;

	while (1) {}
	
	return 1;
}

// When interruption INT0 fires, shifts the burning LED one place forward.
ISR(INT0_vect) {
	PORTA <<= 1;

	// If value has overflown, reset it to 1;
	if (!PORTA)
	PORTA = 1;
}

// When interruption INT1 fires, shifts the burning LED one place backward.
ISR(INT1_vect) {
	PORTA >>= 1;

	// If value has overflown, reset it to 1;
	if (!PORTA)
	PORTA = 1 << 7;
}
