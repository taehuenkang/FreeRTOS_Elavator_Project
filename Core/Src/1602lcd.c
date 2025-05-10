#include "main.h"
#include "stm32f4xx_hal.h"
#include "1602lcd.h"
#include "extern.h"
#include <string.h>
#include <stdio.h>

void lcd_1602_init(void);
void lcd_1602_main(void);
void lcd_1602_pulse(void);
void lcd_1602_send_string(uint8_t *str);
void lcd_1602_clear(void);
void lcd_1602_set_cursor(uint8_t row, uint8_t col);
void lcd_1602_4bit_send(uint8_t data);
void lcd_1602_8bit_send(uint8_t data);

	/* 예시 데이터 전송 과정
	// 상위 4비트 전송 (0x2)
	RS = 1;            // 데이터
	D4~D7 = 0010;      // 상위 4비트
	EN = 1;            // Rising edge
	delay_us(1)
	EN = 0;            // Falling edge → 여기서 latch 됨
	delay_us(40)

	// 하위 4비트 전송 (0x8)
	RS = 0;
	D4~D7 = 1000;
	EN = 1;
	delay_us(1)
	EN = 0;
	delay_us(40)

	#define GPIOB_ODR *(unsigned int*)0x40020414
  	  	  	  	PORTB 6   5   4   3   2   1   0
					  D7  D6  D5  D4  D3  EN  RS
	                          1   1   x   1   x     8 bit mode EN High
	                          1   1   x   0   x     8 bit mode EN Low
	                          1   0   x   1   x     4 bit mode EN High
	                          1   0   x   0   x     4 bit mode EN Low

	*/

#if 0
void lcd_1602_main(void)
{
	int value = 0;
	char buffer[16];
	lcd_1602_init();		   				// LCD init

	while(1)
	{
		lcd_1602_set_cursor(0, 0); 				// 커서 0,0 이동
		lcd_1602_send_string("Hello! World");

		lcd_1602_set_cursor(1, 0); // 커서 1,0 이동
		sprintf(buffer,"count : %d",value);
		lcd_1602_send_string(buffer);
		value++;
		if(value>9) value=0;
		HAL_Delay(1000);
	}
}

void lcd_1602_init(void)
{
	// 1. 전원 넣고 50 ms 대기(안정화)
	HAL_Delay(50);
	// 2. RS LOW : Instruction Input, RW LOW : Input Mode
	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, INSTRUCTION_INPUT);
	//    0x03, Enable High -> LOW 3번 반복, 8bit mode로 3번설정
	//    첫번째 명령 이후 5ms 딜레이, 이후 2번은 delay 1ms


	lcd_1602_4bit_send(0b0011); // 8bit mode로 set
	HAL_Delay(5);

	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, INSTRUCTION_INPUT);
	lcd_1602_4bit_send(0b0011); // 8bit mode로 set
	HAL_Delay(1);

	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, INSTRUCTION_INPUT);
	lcd_1602_4bit_send(0b0011); // 8bit mode로 set
	HAL_Delay(1);
	// 3. 4bit Mode로 진입시킴 0x02, delay 1ms(명령간 최소딜레이)

	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, INSTRUCTION_INPUT);
	lcd_1602_4bit_send(0b0010); // 4bit mode로 set
	HAL_Delay(1);


	// Display Initializing
    // LCD_CLEAR 			0b0000_0001  // SCREEN CLEAR
    // FUNTION_SET 	    	0b0010_1000  // DL = 0, N = 1, F = 0, 4bit / 2line / 5*7 dot
	// DISPLAY_SWITCH_OFF	0b0000_1000  // D = 0, C = 0, B = 0, 디스플레이 OFF / 커서 OFF / 블링크 OFF
	// DISPLAY_SWITCH_ON	0b0000_1100  // D = 1, C = 0, B = 0, 디스플레이 ON  / 커서 OFF / 블링크 OFF
 	// INPUT_SET 			0b0000_0110  // I/D = 1, S = 0, 커서 방향 더하기, SHIFT X

	lcd_1602_8bit_send(FUNTION_SET);
	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, INSTRUCTION_INPUT);
	HAL_Delay(1);	// 명령 실행시간 0.04ms 이상 대기 (안정화)

	lcd_1602_8bit_send(DISPLAY_SWITCH_OFF);
	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, INSTRUCTION_INPUT);
	HAL_Delay(1);	// 명령 실행시간 0.04ms 이상 대기 (안정화)

	lcd_1602_8bit_send(LCD_CLEAR);
	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, INSTRUCTION_INPUT);
	HAL_Delay(1);	// 명령 실행시간 0.04ms 이상 대기 (안정화)

	lcd_1602_8bit_send(INPUT_SET);
	HAL_Delay(1);	// 명령 실행시간 0.04ms 이상 대기 (안정화)

	// Display Init Finish, Display On
	lcd_1602_8bit_send(DISPLAY_SWITCH_ON);
	HAL_Delay(1);
}

// 1. 원하는 Data 전송
// 2. 데이터간 딜레이설정 상위 4bit - delay 1us - 하위 4bit - delay 40us
// 3. 만약 Clear, Home 같은 명령일 경우 상위 4bit - delay 1us - 하위 4bit - delay 2ms

void lcd_1602_send_string(uint8_t *str)
{
	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, DATA_INPUT); // Data 전송 모드

	while(*str)
	{
		lcd_1602_8bit_send(*str++);
	}
}

void lcd_1602_clear(void)
{
	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, INSTRUCTION_INPUT); // 명령어 전송모드
	lcd_1602_8bit_send(LCD_CLEAR); // Screen Clear 명령 -> 디스플레이 내용 지움
	HAL_Delay(2); // 명령어 실행시간 1.64ms 이상 대기
}

void lcd_1602_set_cursor(uint8_t row, uint8_t col)
{
	HAL_GPIO_WritePin(LCD_1602_RS_GPIO_Port, LCD_1602_RS_Pin, INSTRUCTION_INPUT); // 명령어 전송모드

	switch(row)
	{
		case 0 :
			col |= 0x80;
			break;
		case 1 :
			col |= 0xC0;
			break;
	}
	lcd_1602_8bit_send(col);  // DDRAM AD Set 명령
	HAL_Delay(1);
}

void lcd_1602_8bit_send(uint8_t data)
{
	lcd_1602_4bit_send((data >> 4) & 0x0F); // 상위 nibble 4비트 전송
	lcd_1602_4bit_send(data & 0x0F); 		// 하위 nibble 4비트 전송
}

void lcd_1602_4bit_send(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_1602_D4_GPIO_Port, LCD_1602_D4_Pin, (data >> 0) & 0x01);
	HAL_GPIO_WritePin(LCD_1602_D5_GPIO_Port, LCD_1602_D5_Pin, (data >> 1) & 0x01);
	HAL_GPIO_WritePin(LCD_1602_D6_GPIO_Port, LCD_1602_D6_Pin, (data >> 2) & 0x01);
	HAL_GPIO_WritePin(LCD_1602_D7_GPIO_Port, LCD_1602_D7_Pin, (data >> 3) & 0x01);
	lcd_1602_pulse();
}
void lcd_1602_pulse(void)
{
	HAL_GPIO_WritePin(LCD_1602_EN_GPIO_Port, LCD_1602_EN_Pin, EN_HIGH); // EN HIGH
	delay_us(20);
	HAL_GPIO_WritePin(LCD_1602_EN_GPIO_Port, LCD_1602_EN_Pin, EN_LOW); // EN LOW
	delay_us(20);
}

#endif
