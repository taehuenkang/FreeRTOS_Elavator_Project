/*
 * i2c_lcd.h
 *
 *  Created on: 2019. 9. 4.
 *      Author: k
 */

#ifndef SRC_I2C_LCD_H_
#define SRC_I2C_LCD_H_

#define BACKLIGHT_ON 0x08

/* LCD command   */
#define DISPLAY_ON 0x0C
#define DISPLAY_OFF 0x08
#define CLEAR_DISPLAY 0x01  //Delay 2msec
#define RETURN_HOME 0x02

void lcd_command(uint8_t command);
void lcd_data(uint8_t data);
void i2c_lcd_init(void);
void lcd_string(uint8_t *str);
void move_cursor(uint8_t row, uint8_t column);

#endif /* SRC_I2C_LCD_H_ */
