int main(void)
{
    DDRD = 0xFF;
    int wait_time = 1000;
    int state = 0;

    while (1)
    {
        if (PINC & 0x01 && !state)
        {
            wait_time = (wait_time == 1000 ? 250 : 1000);
            state = 1;
        }

        if (state && !(PINC & 0x01))
        {
            state = 0;
        }

        wait(wait_time);
        PORTD = 0b10000000;
        wait(wait_time);
        PORTD = 0x00;
    }
}
