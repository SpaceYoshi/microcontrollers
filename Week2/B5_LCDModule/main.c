#define F_CPU 8e6

#include <util/delay.h>
#include "lcd.h"

int main(void) {
	init_4bits_mode();

	_delay_ms(1000);

	display_text("Hello world!");

	_delay_ms(1000);

	set_cursor(5);
	
	return 0;
}
