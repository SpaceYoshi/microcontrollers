#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0b11111111;

    while (1)
    {
        PORTD = 0b01000000;
        _delay_ms(500);
        PORTD = 0b10000000;
        _delay_ms(500);
    }
}
