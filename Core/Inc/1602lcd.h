/*
 * 1602lcd.h
 *
 *  Created on: Apr 4, 2025
 *      Author: microsoft
 */

#ifndef INC_1602LCD_H_
#define INC_1602LCD_H_

#include "main.h"



#include "main.h"
#define DATA_INPUT 1
#define INSTRUCTION_INPUT 0
#define READ_MODE 1
#define WRITE_MODE 0
#define EN_HIGH 1
#define EN_LOW 0

#define GPIOB_ODR *(unsigned int*)0x40020414

#define LCD_CLEAR 			0b00000001  // SCREEN CLEAR
#define FUNTION_SET 		0b00101000  // DL = 0, N = 1, F = 0, 4bit / 2line / 5*7 dot
#define DISPLAY_SWITCH_OFF	0b00001000  // D = 0, C = 0, B = 0, 디스플레이 OFF / 커서 OFF / 블링크 OFF
#define DISPLAY_SWITCH_ON	0b00001100  // D = 1, C = 0, B = 0, 디스플레이 ON  / 커서 OFF / 블링크 OFF
#define INPUT_SET 			0b00000110  // I/D = 1, S = 0, 커서 방향 더하기, SHIFT X


#endif /* INC_1602LCD_H_ */
