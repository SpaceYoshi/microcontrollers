#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Set all pins on port D to output
	DDRD = 0b11111111;

	while (1)
	{
		// Switch between port D.6 and D.7
		PORTD = 0b01000000;
		_delay_ms(500);
		PORTD = 0b10000000;
		_delay_ms(500);
	}
}
