#include "fnd.h"
#include "extern.h"

void fnd_elevator_display(void);
void fnd_elevator_datashift(uint8_t data);


volatile uint8_t fnd_font_digit[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x7f};

volatile uint8_t fnd_font1[] = {0xFF,0xff,0xA1}; //     D
volatile uint8_t fnd_font2[] = {0xFF,0xC1,0xC0}; // N U O
volatile uint8_t fnd_font3[] = {0x8E,0x8C,0xD5}; // F P W
volatile uint8_t fnd_font4[] = {0xFF,0xFF,0xAB}; //     N

void fnd_elevator_display(void)
{
	static uint8_t digit_select=0;  // static를 쓰면 전역 변수 처럼 함수가 빠져 나갔다가 다시 들어 오더라도 값을 유지

	if(FND_update_counter > 5)
	{
		FND_update_counter = 0;

	switch(digit_select) // FND2 출력용 Switch - case 함수
	{
		case 0: // common anode D1
		HAL_GPIO_WritePin(FND_D1_GPIO_Port, FND_D1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(FND_D2_GPIO_Port, FND_D2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FND_D3_GPIO_Port, FND_D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FND_D4_GPIO_Port, FND_D4_Pin, GPIO_PIN_RESET);
		fnd_elevator_datashift(fnd_font1[stepmotor_state]);
		break;

		case 1: // common anode D2
		HAL_GPIO_WritePin(FND_D1_GPIO_Port, FND_D1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FND_D2_GPIO_Port, FND_D2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(FND_D3_GPIO_Port, FND_D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FND_D4_GPIO_Port, FND_D4_Pin, GPIO_PIN_RESET);
		if(stepmotor_state == IDLE)
			fnd_elevator_datashift(fnd_font_digit[current_floor]);
		else
			fnd_elevator_datashift(fnd_font2[stepmotor_state]);
		break;

		case 2: // common anode D3
		HAL_GPIO_WritePin(FND_D1_GPIO_Port, FND_D1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FND_D2_GPIO_Port, FND_D2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FND_D3_GPIO_Port, FND_D3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(FND_D4_GPIO_Port, FND_D4_Pin, GPIO_PIN_RESET);
		fnd_elevator_datashift(fnd_font3[stepmotor_state]);
		break;

		case 3: // common anode D4
		HAL_GPIO_WritePin(FND_D1_GPIO_Port, FND_D1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FND_D2_GPIO_Port, FND_D2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FND_D3_GPIO_Port, FND_D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FND_D4_GPIO_Port, FND_D4_Pin, GPIO_PIN_SET);
		fnd_elevator_datashift(fnd_font4[stepmotor_state]);
		break;
	}

	digit_select++;
	digit_select %= 4;
	}
}

void fnd_elevator_datashift(uint8_t data)
{
	for(int i = 0; i < 8; i++)
	{
		if(data & (0x80 >> i))  // MSB부터 전송
			HAL_GPIO_WritePin(FND_74HC595_SER_GPIO_Port, FND_74HC595_SER_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(FND_74HC595_SER_GPIO_Port, FND_74HC595_SER_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(FND_74HC595_CLK_GPIO_Port, FND_74HC595_CLK_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(FND_74HC595_CLK_GPIO_Port, FND_74HC595_CLK_Pin, GPIO_PIN_RESET);
	}

	// 래치 신호: 한 번만 주면 됨
	HAL_GPIO_WritePin(FND_74HC595_LATCH_GPIO_Port, FND_74HC595_LATCH_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FND_74HC595_LATCH_GPIO_Port, FND_74HC595_LATCH_Pin, GPIO_PIN_SET);
}
