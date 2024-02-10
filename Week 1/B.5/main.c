int main(void)
{
    int states[] = {0b00000011, 0b00110011, 0b00001100, 0b11001100, 0b00110000, 0b11000000, 0b10000000};

    DDRD = 0xFF;

    while (1)
    {
        for (int i = 0; i < 7; i++)
        {
            PORTD = states[i];
            _delay_ms(200);
        }
    }
}
