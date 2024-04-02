#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Set all pins on port D to be output
	DDRD = 0xFF;

	while (1)
	{
		// If only the button for pin C.0 was pressed
		if (PINC & 0b00000001)
		{
			// Blink pin D.7
			PORTD = 0b10000000;
			_delay_ms(100);
			PORTD = 0x00;
			_delay_ms(100);
		}
		else
		{
			// Turn off port D
			PORTD = 0x00;
		}
	}
}

