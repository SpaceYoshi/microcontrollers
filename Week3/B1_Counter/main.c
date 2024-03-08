#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <string.h>

#define BIT(x) (1 << (x))

int main(void)
{
	init_4bits_mode();
	
	// Set PD.7 to inpput
	DDRD &= ~BIT(7);

	// Set the clock source to external,
	// increment the counter on the rising edge.
	TCCR2 = 0b00000111;

	// Set the initial value of the counter to zero
	TCNT2 = 0x00;

	char buffer[100];

	while (1) {
		// Clear the display
		lcd_command(0x01);

		// Convert TCNT2's value to a string
		// and display it on the LCD.
		sprintf(buffer, "%d", TCNT2);
		display_text(buffer);

		_delay_ms(150);
	}

	return 1;
}

