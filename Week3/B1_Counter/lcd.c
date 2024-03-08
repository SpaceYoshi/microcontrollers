#include "avr/io.h"
#include "lcd.h"

void lcd_strobe() {
	PORTC |= (1 << LCD_EN);
	_delay_ms(1);
	PORTC &= ~(1 << LCD_EN);
	_delay_ms(1);
}

void lcd_command(unsigned char data) {
	PORTC = data & 0xF0;
	lcd_strobe();
	
	PORTC = 0x04;
	PORTC = (data & 0xF0) << 4;
	lcd_strobe();

	PORTC = 0x00;
}

void init_4bits_mode() {
	DDRC = 0xFF;
	PORTC = 0x00;
	
	// Table 12 step 2
	PORTC = 0x20;
	lcd_strobe();
	
	// Table 12 step 3
	PORTC = 0x20;
	lcd_strobe();
	PORTC = 0x80;
	lcd_strobe();
	
	// Table 12 step 4
	PORTC = 0x00;
	lcd_strobe();
	PORTC = 0xF0;
	lcd_strobe();
	PORTC = 0x00;
	lcd_strobe();
	PORTC = 0x60;
	lcd_strobe();
	
	lcd_command(0x01);
}

void set_cursor(unsigned int pos) {
	lcd_command(0x80 + pos);
}

void display_text(char *str) {
	for (; *str; str++) {
		PORTC = *str & 0xF0;
		PORTC |= (1 << LCD_RS);
		lcd_strobe();
		
		PORTC = (*str & 0x0F) << 4;
		PORTC |= (1 << LCD_RS);
		lcd_strobe();
	}
}
