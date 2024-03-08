#ifndef LCD_H_
#define LCD_H_

#define LCD_ENABLE 0b11
#define LCD_REG_SELECT 0b10

#define BIT(x) (1 << (x))

void lcd_command(void);
void init_4bits_mode(void);
void set_cursor(int position);
void display_text(char *str);

#endif /* LCD_H_ */