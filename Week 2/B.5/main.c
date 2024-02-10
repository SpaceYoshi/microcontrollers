#ifndef F_CPU
#define F_CPU 8e6
#endif

#include "simple_lcd.h"

int main() {
	init();

	display_text("Hello world!");

	set_cursor(5);
	
	return 0;
}
