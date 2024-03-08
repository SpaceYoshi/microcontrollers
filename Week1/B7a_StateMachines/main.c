#define F_CPU 8e6

#include <avr/io.h>

int main(void)
{
	if (!pressed)
	{
		if (state == S_START)
		{
			// If the button for pin D.5 is pressed
			if (PIND & 1 << 5)
			{
				state = S_S2;
				PORTC = 0b0000011;
				pressed = 1;
			}
			// If the button for pin D.6 is pressed
			else if (PIND & 1 << 6)
			{
				state = S_S1;
				PORTC = 0b00000001;
				pressed = 1;
			}
		}
		else if (state == S_S1)
		{
			// If the button for pin D.5 is pressed
			if (PIND & 1 << 5)
			{
				state = S_S2;
				PORTC = 0b00000011;
				pressed = 1;
			}
			// If the button for pin D.7 is pressed
			else if (PIND & 1 << 7)
			{
				state = S_START;
				PORTC = 0b0;
				pressed = 1;
			}
		}
		else if (state == S_S2)
		{
			// If the button for pin D.6 is pressed
			if (PIND & 1 << 6)
			{
				state = S_S1;
				PORTC = 0b00000001;
				pressed = 1;
			}
			// If the button for pin D.5 is pressed
			else if (PIND & 1 << 5)
			{
				state = S_S3;
				PORTC = 0b00000111;
				pressed = 1;
			}
		}
		else if (state == S_S3)
		{
			// If the button for pin D.7 is pressed
			if (PIND & 1 << 7)
			{
				state = S_START;
				PORTC = 0b0;
				pressed = 1;
			}
			// If the button for pin D.5 or pin D.6 is pressed
			else if (PIND & 1 << 5 || PIND & 1 << 6)
			{
				state = S_END;
				PORTC = 0b00001111;
				pressed = 1;
			}
		}
	}
	// If neither button (D.5, D.6 or D.7) was pressed
	else if (!(PIND & 1 << 5) && !(PIND & 1 << 6) && !(PIND & 1 << 7))
	{
		pressed = 0;
	}
}
