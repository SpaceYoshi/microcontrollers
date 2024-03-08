#define F_CPU 8e6

#include "lcd.h"

int main(void) {
	init_4bits_mode();

	display_text("Hello world!");

	set_cursor(5);
	
	return 0;
}
