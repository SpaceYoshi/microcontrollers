int main(void)
{
    if (!pressed)
    {
        if (state == S_START)
        {
            if (PIND & 1 << 5)
            {
                state = S_S2;
                PORTC = 0b0000011;
                pressed = 1;
            }
            else if (PIND & 1 << 6)
            {
                state = S_S1;
                PORTC = 0b00000001;
                pressed = 1;
            }
        }
        else if (state == S_S1)
        {
            if (PIND & 1 << 5)
            {
                state = S_S2;
                PORTC = 0b00000011;
                pressed = 1;
            }
            else if (PIND & 1 << 7)
            {
                state = S_START;
                PORTC = 0b0;
                pressed = 1;
            }
        }
        else if (state == S_S2)
        {
            if (PIND & 1 << 6)
            {
                state = S_S1;
                PORTC = 0b00000001;
                pressed = 1;
            }
            else if (PIND & 1 << 5)
            {
                state = S_S3;
                PORTC = 0b00000111;
                pressed = 1;
            }
        }
        else if (state == S_S3)
        {
            if (PIND & 1 << 7)
            {
                state = S_START;
                PORTC = 0b0;
                pressed = 1;
            }
            else if (PIND & 1 << 5 || PIND & 1 << 6)
            {
                state = S_END;
                PORTC = 0b00001111;
                pressed = 1;
            }
        }
    }
    else if (!(PIND & 1 << 5) && !(PIND & 1 << 6) && !(PIND & 1 << 7))
    {
        pressed = 0;
    }
}
