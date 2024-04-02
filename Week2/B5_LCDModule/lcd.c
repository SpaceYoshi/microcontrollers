#define F_CPU 8e6

#include "avr/io.h"
#include <util/delay.h>
#include "lcd.h"

/**
* Toggles the ENABLE pin to signal the readiness of a command
*/
void lcd_send_ready() {
	PORTC |= (1 << LCD_ENABLE);
	_delay_ms(1);
	PORTC &= ~(1 << LCD_ENABLE);
	_delay_ms(1);
}

/**
* Sends a command to the LCD assuming 4-bits mode is enabled.
*/
void lcd_write_cmd(unsigned char data) {
	// Send most significant nibble
	PORTC = data & 0xF0;
	lcd_send_ready();
	
	// Send least significant nibble
	PORTC = 0x04;
	PORTC = (data & 0xF0) << 4;
	lcd_send_ready();

	// Reset port C
	PORTC = 0x00;
}

/**
* Tells the LCD display to work in 4-bits mode.
*/
void init_4bits_mode() {
	// Port C is set to output and is reset
	DDRC = 0xFF;
	PORTC = 0x00;
	
	// Table 12 step 2
	PORTC = 0x20;
	lcd_send_ready();
	
	// Table 12 step 3 (function set)
	PORTC = 0x20;
	lcd_send_ready();
	PORTC = 0x80;
	lcd_send_ready();
	
	// Table 12 step 4
	// Display on/off control
	PORTC = 0x00;
	lcd_send_ready();
	PORTC = 0xF0;
	lcd_send_ready();
	// Entry mode set
	PORTC = 0x00;
	lcd_send_ready();
	PORTC = 0x60;
	lcd_send_ready();
	
	// Clear LCD display
	lcd_write_cmd(0x01);
}

/**
* Sets the cursor on the LCD display to a non-negative
* position, assuming 4-bits mode is enabled.
*/
void set_cursor(unsigned int pos) {
	lcd_write_cmd(0x80 + pos);
}

/**
* Displays a string on the LCD display at the cursor's
* position, assuming 4-bits mode is enabled.
*/
void display_text(char *str) {
	for (; *str; str++) {
		// Send most significant nibble
		PORTC = *str & 0xF0;
		PORTC |= (1 << LCD_REG_SELECT);
		lcd_send_ready();
		
		// Send least significant nibble
		PORTC = (*str & 0x0F) << 4;
		PORTC |= (1 << LCD_REG_SELECT);
		lcd_send_ready();
	}
}
