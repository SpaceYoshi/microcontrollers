#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Define possible states for port D
	int states[] = {0b00000011, 0b00110011, 0b00001100, 0b11001100, 0b00110000, 0b11000000, 0b10000000};

	// Set port D to be output
	DDRD = 0xFF;

	while (1)
	{
		// Cycle between port D states
		for (int i = 0; i < 7; i++)
		{
			PORTD = states[i];
			_delay_ms(200);
		}
	}
}
