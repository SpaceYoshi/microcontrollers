#ifndef LCD_H_
#define LCD_H_

#define LCD_EN 3
#define LCD_RS 2

#define BIT(x) (1 << (x))

void lcd_command(void);
void init_4bits_mode(void);
void set_cursor(int position);
void display_text(char *str);

#endif /* LCD_H_ */