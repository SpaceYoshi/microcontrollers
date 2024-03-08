#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

/**
* Delay wrapper for using variables known at runtime
*/
void wait(unsigned int millis) {
	for (int i = 0; i < millis; i++)
		_delay_ms(1);
}

int main(void)
{
	// Set port D to be output
	DDRD = 0xFF;
	int wait_time = 1000;
	
	// Keeps track of whether the button was pressed
	int state = 0;

	while (1)
	{
		// Check if the button is pressed
		if (PINC & 0x01 && !state)
		{
			// Toggle wait time
			wait_time = (wait_time == 1000 ? 250 : 1000);
			state = 1;
		}

		// Check if the button is released
		if (state && !(PINC & 0x01))
		{
			state = 0;
		}

		// Toggle port D.7
		wait(wait_time);
		PORTD = 0b10000000;
		wait(wait_time);
		PORTD = 0x00;
	}
}
