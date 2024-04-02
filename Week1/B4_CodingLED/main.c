#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;

	while (1)
	{
		for (int i = 0; i < 8; i++)
		{
			PORTD = 0b00000001 << i;
			_delay_ms(50);
			PORTD = 0b0;
		}
	}
}
