#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0xFF;

    while (1)
    {
        if (PINC & 0b00000001)
        {
            PORTD = 0b10000000;
            _delay_ms(100);
            PORTD = 0x00;
            _delay_ms(100);
        }
        else
        {
            PORTD = 0x00;
        }
    }
}
