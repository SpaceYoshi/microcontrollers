#ifndef F_CPU
#define F_CPU 8e6
#endif

#include "simple_lcd.h"
#include "avr/io.h"
#include "util/delay.h"

#define LCD_ENABLE 0b1000
#define LCD_REG_SELECT 0b100

void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_clear();
void send_ready_signal();

int word_len = 0;

void init() {
	DDRC = 0xFF;
	PORTC = 0x20;
	send_ready_signal();
	
	PORTC = 0x20;   // function set
	send_ready_signal();
	PORTC = 0x80;
	send_ready_signal();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	send_ready_signal();
	PORTC = 0xF0;
	send_ready_signal();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	send_ready_signal();
	PORTC = 0x60;
	send_ready_signal();
	
	_delay_ms(10);
	
	lcd_clear();
}

void display_text(char *str) {
	for(; *str; str++) {
		lcd_write_data(*str);
	}
}

void set_cursor(unsigned char position) {
	if (position < word_len) {
		lcd_write_cmd(0x80 | position);
		_delay_ms(1);
	}
}

void lcd_write_data(unsigned char byte) {
	PORTC = byte;
	PORTC |= LCD_REG_SELECT;
	send_ready_signal();
	
	PORTC = byte << 4;
	PORTC |= LCD_REG_SELECT;
	send_ready_signal();
	
	word_len++;
}

void lcd_write_cmd(unsigned char byte) {
	PORTC = byte;
	PORTC &= ~LCD_REG_SELECT;
	send_ready_signal();
	
	PORTC = byte << 4;
	PORTC &= ~LCD_REG_SELECT;
	send_ready_signal();
}

void lcd_clear() {
	lcd_write_cmd(0x01);
	word_len = 0;
	_delay_ms(2);
}

void send_ready_signal() {
	PORTC |= LCD_ENABLE;
	_delay_ms(1);
	PORTC &= ~LCD_ENABLE;
	_delay_ms(1);
}
