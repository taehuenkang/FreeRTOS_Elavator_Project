#define FIRST_FLOOR 	1
#define SECOND_FLOOR 	2
#define THIRD_FLOOR 	3
#define FOURTH_FLOOR 	4

#include "main.h"
#include "button.h"
#include "dotmatrix.h"
#include "extern.h"

const uint8_t num_1[8] = {
		0x00, 0x00, 0x48, 0x44, 0x7e, 0x40, 0x00, 0x00
};

const uint8_t num_2[8] = {
		0x00, 0x00, 0x7a, 0x4a, 0x4a, 0x4e, 0x00, 0x00
};

const uint8_t num_3[8] = {
		0x00, 0x00, 0x4a, 0x4a, 0x4a, 0x7e, 0x00, 0x00
};

const uint8_t num_4[8] = {
		0x00, 0x00, 0x0e, 0x08, 0x08, 0x7e, 0x00, 0x00
};


#if 0

extern SPI_HandleTypeDef hspi2;

void dotmatrix_main_test();
void init_dotmatrix(void);
int dotmatrix_main(void);
int dotmatrix_main_func(void);

uint8_t allon[] = {			// allon 문자 정의
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111
};
uint8_t convex_filled[] = {
    0b00000000,
    0b01111110,
    0b01111110,
    0b01111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b01111110
};

uint8_t smile[] = {			// 스마일 문자 정의
	0b00111100,
	0b01000010,
	0b10010101,
	0b10100001,
	0b10100001,
	0b10010101,
	0b01000010,
	0b00111100 };

uint8_t hart[] = {		// hart
	0b00000000,    // hart
	0b01100110,
	0b11111111,
	0b11111111,
	0b11111111,
	0b01111110,
	0b00111100,
	0b00011000
};

uint8_t one[] =
{0b00011000,
0b00111000,
0b00011000,
0b00011000,
0b00011000,
0b00011000,
0b01111110,
0b01111110};

uint8_t my_name[] =
{0B01111010,
0B00001010,
0B00001010,
0B11111010,
0B00100010,
0B10101110,
0B10000010,
0B11111110};



uint8_t col[4]={0,0,0,0};

void dotmatrix_main_test()
{
  //dotmatrix_main();

  while (1)
  {
        for (int i=0; i < 8; i++)
        {
			col[0] = ~(1 << i);  // 00000001  --> 11111110
			col[1] = hart  [i];
			//col[1] = convex_filled[i];
			HAL_SPI_Transmit(&hspi2, col, 2, 1);
			GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
			GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
			HAL_Delay(1 );
        }
  }
}

uint8_t number_data[20][13] =
{
	{
		0b01001010, // 박
		0b01111010,
		0b01001011,
		0b01111010,
		0b00000000,
		0b01111110,
		0b00000010,
		0b00000010
	},

	{
		0b00000000, // 재
		0b11110101,
		0b00100101,
		0b01100111,
		0b10010101,
		0b00000101,
		0b00000101,
		0b00000000
	},

	{
		0b01111010, // 권
		0b00001010,
		0b00001010,
		0b01111110,
		0b00010010,
		0b00101110,
		0b01010010,
		0b00011111
	},

	{
		0b01110000,	//0
		0b10001000,
		0b10011000,
		0b10101000,
		0b11001000,
		0b10001000,
		0b01110000,
	    0b00000000
	},
	{
		0b01000000,	//1
		0b11000000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b11100000,
	    6   // 점 0b00000110
	},
	{
		0b01110000,	//2
		0b10001000,
		0b00001000,
		0b00010000,
		0b00100000,
		0b01000000,
		0b11111000,
	    6
	},
	{
		0b11111000,	//3
	    0b00010000,
		0b00100000,
		0b00010000,
		0b00001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b00010000,	//4
		0b00110000,
		0b01010000,
		0b10010000,
		0b11111000,
		0b00010000,
		0b00010000,
	    6
	},
	{
		0b11111000,	//5
		0b10000000,
		0b11110000,
		0b00001000,
		0b00001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b00110000,	//6
		0b01000000,
		0b10000000,
		0b11110000,
		0b10001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b11111000,	//7
		0b10001000,
		0b00001000,
		0b00010000,
		0b00100000,
		0b00100000,
		0b00100000,
	    6
	},
	{
		0b01110000,	//8
		0b10001000,
		0b10001000,
		0b01110000,
		0b10001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b01111010,
		0b00001010,
		0b00001010,
		0b00110010,
		0b01000010,
		0b01111110,
		0b01000010,
		0b01111110
	},
	{
		0b00000000,    // hart
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000
	}
};

unsigned char display_data[8];  // 최종 8x8 출력할 데이터
unsigned char scroll_buffer[50][8] = {0};  // 스코롤할 데이타가 들어있는 버퍼
int number_of_character = 14;  // 출력할 문자 갯수

// 초기화 작업
// 1. display_data에 number_data[0]에 있는 내용 복사
// 2. number_data를 scroll_buffer에 복사
// 3. dotmatrix의 led를 off
void init_dotmatrix(void)
{
	for (int i=0; i < 8; i++)
	{
		display_data[i] = number_data[i];
	}
	for (int i=1; i < number_of_character+1; i++)
	{
		for (int j=0; j < 8; j++) // scroll_buffer[0] = blank
		{
			scroll_buffer[i][j] = number_data[i-1][j];
		}
	}
}

// scroll 문자 출력 프로그램
int dotmatrix_main(void)
{
	static int count=0;  // 컬럼 count
	static int index=0;  // scroll_buffer의 2차원 index값
	static uint32_t past_time=0;  // 이전 tick값 저장


	uint32_t now = HAL_GetTick();  // 1ms
	// 1.처음시작시 past_time=0; now: 500 --> past_time=500
	if (now - past_time >= 500) // 500ms scroll
	{
		past_time = now;
		for (int i=0; i < 8; i++)
		{

			display_data[i] = (scroll_buffer[index][i] >> count) |
					(scroll_buffer[index+1][i] << 8 - count);
		}
		if (++count == 8) // 8칼람을 다 처리 했으면 다음 scroll_buffer로 이동
		{
			count =0;
			index++;  // 다음 scroll_buffer로 이동
			if (index == number_of_character+1) index=0;
			// 11개의 문자를 다 처리 했으면 0번 scroll_buffer를 처리 하기위해 이동
		}
	}
/*
 		0b00000000,    // hart
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000
 */
	for (int i=0; i < 8; i++)
	{
		// 공통 양극 방식
		// column에는 0을 ROW에는 1을 출력해야 해당 LED가 on된다.
		col[0] = ~(1 << i);  // 00000001  --> 11111110
		col[1] = display_data[i];
		HAL_SPI_Transmit(&hspi2, col, 2, 1);
		GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
		GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
		HAL_Delay(1);
	}
}

// scroll 문자 출력 프로그램
int dotmatrix_main_func(void)
{
	static int count=0;  // 컬럼 count
	static int index=0;  // scroll_buffer의 2차원 index값
	static uint32_t past_time=0;  // 이전 tick값 저장

	init_dotmatrix();

	while(1)
	{
		uint32_t now = HAL_GetTick();  // 1ms
		// 1.처음시작시 past_time=0; now: 500 --> past_time=500
		if (now - past_time >= 500) // 500ms scroll
		{
			past_time = now;
			for (int i=0; i < 8; i++)
			{

				display_data[i] = (scroll_buffer[index][i] >> count) |
						(scroll_buffer[index+1][i] << 8 - count);
			}
			if (++count == 8) // 8칼람을 다 처리 했으면 다음 scroll_buffer로 이동
			{
				count =0;
				index++;  // 다음 scroll_buffer로 이동
				if (index == number_of_character+1) index=0;
				// 11개의 문자를 다 처리 했으면 0번 scroll_buffer를 처리 하기위해 이동
			}
		}
		for (int i=0; i < 8; i++)
		{
			// 공통 양극 방식
			// column에는 0을 ROW에는 1을 출력해야 해당 LED가 on된다.
			col[0] = ~(1 << i);  // 00000001  --> 11111110
			col[1] = display_data[i];
			HAL_SPI_Transmit(&hspi2, col, 2, 1);
			GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
			GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
			HAL_Delay(1);
		}
	}
	return 0;
}

#endif

#if 1



uint8_t allon[] = {			// allon 문자 정의
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111
};
uint8_t convex_filled[] = {
    0b00000000,
    0b01111110,
    0b01111110,
    0b01111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b01111110
};

uint8_t smile[] = {			// 스마일 문자 정의
	0b00111100,
	0b01000010,
	0b10010101,
	0b10100001,
	0b10100001,
	0b10010101,
	0b01000010,
	0b00111100 };



uint8_t one[] =
{0b00011000,
0b00111000,
0b00011000,
0b00011000,
0b00011000,
0b00011000,
0b01111110,
0b01111110};

uint8_t my_name[] =
{0B01111010,
0B00001010,
0B00001010,
0B11111010,
0B00100010,
0B10101110,
0B10000010,
0B11111110};



uint8_t col[4]={0,0,0,0};

void dotmatrix_main_test()
{
	uint8_t temp;
	static int i = 0;

#if 1
	col[0] = ~(1 << i);  // 00000001  --> 11111110
	col[1] = smile[i];
	// HAL_SPI_Transmit(&hspi2, col, 2, 1);
	for(int j = 0; j < 2; j++)
	{
		for(int k = 0; k < 8; k++)
		{
			temp = col[j];
			if(temp & (1 << k))
			{
				HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 1);
			}
			else
			{
				HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 0);
			}
			HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 1); // CLK 을 상승에서
			HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 0); // CLK 을 하강으로
		}
	}
	GPIOB->ODR &= ~GPIO_PIN_13;   // latch 핀을 pull-down
	GPIOB->ODR |= GPIO_PIN_13;    // latch 핀을 pull-up

	i++;
	i %= 8;
#endif


#if 0
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10 | GPIO_PIN_13 | GPIO_PIN_15, 0);
  HAL_Delay(5); // 핀을 LOW로 떨구고 안정화 10ms

  while (1)
  {




        for (int i = 0; i < 8; i++)
        {
			col[0] = ~(1 << i);  // 00000001  --> 11111110
			//col[1] = hart[i];
			col[1] = arrow_up[i];
			// col[1] = convex_filled[i];
			// HAL_SPI_Transmit(&hspi2, col, 2, 1);
			for(int j = 0; j < 2; j++)
			{
				for(int k = 0; k < 8; k++)
				{
					temp = col[j];
					if(temp & (1 << k))
					{
						HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 1);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 0);
					}
					HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 1); // CLK 을 상승에서
					HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 0); // CLK 을 하강으로
				}
			}
			GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
			GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
			HAL_Delay(1);
        }
  }
#endif
}

uint8_t number_data[20][8] =
{
		{
		0x00, 0x0e, 0x28, 0x2e, 0xe0, 0x1e, 0x04, 0x00
		}, //박

		{
		0x00, 0x24, 0x1c, 0x14, 0x24, 0x7e, 0x08, 0x7e
		},

		{
		0x00, 0xca, 0xba, 0x8e, 0xa8, 0xa0, 0x3e, 0x00
		},
	   {//강
	   0x11, 0x09, 0x45, 0xa3, 0xa0, 0x5f, 0x04, 0x04
	   },
	   {//태
	   0x00, 0x7e, 0x4a, 0x4a, 0x4a, 0x7e, 0x08, 0x7e
	   },
	   {//곰
	   0x00, 0x11, 0xd1, 0xdd, 0xdd, 0xd1, 0x17, 0x00
	   },


	{
		0b01110000,	//0
		0b10001000,
		0b10011000,
		0b10101000,
		0b11001000,
		0b10001000,
		0b01110000,
	    0b00000000
	},
	{
		0b01000000,	//1
		0b11000000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b11100000,
	    6   // 점 0b00000110
	},
	{
		0b01110000,	//2
		0b10001000,
		0b00001000,
		0b00010000,
		0b00100000,
		0b01000000,
		0b11111000,
	    6
	},
	{
		0b11111000,	//3
	    0b00010000,
		0b00100000,
		0b00010000,
		0b00001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b00010000,	//4
		0b00110000,
		0b01010000,
		0b10010000,
		0b11111000,
		0b00010000,
		0b00010000,
	    6
	},
	{
		0b11111000,	//5
		0b10000000,
		0b11110000,
		0b00001000,
		0b00001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b00110000,	//6
		0b01000000,
		0b10000000,
		0b11110000,
		0b10001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b11111000,	//7
		0b10001000,
		0b00001000,
		0b00010000,
		0b00100000,
		0b00100000,
		0b00100000,
	    6
	},
	{
		0b01110000,	//8
		0b10001000,
		0b10001000,
		0b01110000,
		0b10001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b01111010, //9
		0b00001010,
		0b00001010,
		0b00110010,
		0b01000010,
		0b01111110,
		0b01000010,
		0b01111110
	},
	{
		0b00000000,  //hart
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000
	}
};

// 초기화 작업
// 1. display_data에 number_data[0]에 있는 내용 복사
// 2. number_data를 scroll_buffer에 복사
// 3. dotmatrix의 led를 off
void init_dotmatrix(void)
{
	for (int i=0; i < 8; i++)
	{
		display_data[i] = number_data[i];
	}
	for (int i=1; i < number_of_character+1; i++)
	{
		for (int j=0; j < 8; j++) // scroll_buffer[0] = blank
		{
			scroll_buffer[i][j] = number_data[i-1][j];
		}
	}
}

// scroll 문자 출력 프로그램
int dotmatrix_main(void)
{
	static int count=0;  // 컬럼 count
	static int index=0;  // scroll_buffer의 2차원 index값
	static uint32_t past_time=0;  // 이전 tick값 저장
	uint8_t temp;
	button_pull_up();



	uint32_t now = HAL_GetTick();  // 1ms
	// 1.처음시작시 past_time=0; now: 500 --> past_time=500
	if (now - past_time >= 100) // 500ms scroll
	{
		past_time = now;
		for (int i=0; i < 8; i++)
		{

			display_data[i] = (scroll_buffer[index][i] >> count) |
					(scroll_buffer[index+1][i] << 8 - count);
		}
		if (++count == 8) // 8칼람을 다 처리 했으면 다음 scroll_buffer로 이동
		{
			count =0;
			index++;  // 다음 scroll_buffer로 이동
			if (index == number_of_character+1) index=0;
			// 11개의 문자를 다 처리 했으면 0번 scroll_buffer를 처리 하기위해 이동
		}
	}
/*
 		0b00000000,    // hart
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000
 */
	for (int i=0; i < 8; i++)
	{
		// 공통 양극 방식
		// column에는 0을 ROW에는 1을 출력해야 해당 LED가 on된다.
		col[0] = ~(1 << i);  // 00000001  --> 11111110
		col[1] = display_data[i];
		// HAL_SPI_Transmit(&hspi2, col, 2, 1);

		for(int j = 0; j < 2; j++)
		{
			for(int k = 0; k < 8; k++)
			{
				temp = col[j];
				if(temp & (1 << k))
				{
					HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 1);
				}
				else
				{
					HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 0);
				}
				HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 1); // CLK 을 상승에서
				HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 0); // CLK 을 하강으로
			}
		}

		GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
		GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
		HAL_Delay(1);
	}
}

// scroll 문자 출력 프로그램
int dotmatrix_name_main(void)
{
	init_dotmatrix();
	button_pull_up();

	while(1)
	{
		dotmatrix_state_check(); // button state를 체크하는 함수

		if(!dot_matrix_running) // 버튼이 안눌린 초기 상태
			//dotmatrix_main_test();
			//arrow_dot();
			dotmatrix_main_func(); // 초기상태에서는 이름 출력
		else // dot_matrix_running 가 1, 버튼이 눌린 상태
		{
			arrow_dot(); // 화살표 출력되도록하는 함수

			if(TIM11_1ms_counter > 1000)
			{
				TIM11_1ms_counter = 0;
				running_time++;
				if(running_time == 30)
				{
					dot_matrix_running = 0;
					running_time = 0;
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // 디버깅용
					dot_button_state = 0;
				}
			}
		}
	}
	return 0;
}

// scroll 문자 출력 함수
int dotmatrix_main_func(void) // 왼쪽 -> 오른쪽
{
	static int count=0;  // 컬럼 count
	static int index=0;  // scroll_buffer의 2차원 index값
	static uint32_t past_time=0;  // 이전 tick값 저장
	uint8_t temp;

	uint32_t now = HAL_GetTick();  // 1ms
	// 1.처음시작시 past_time=0; now: 500 --> past_time=500
	if (now - past_time >= 100) // 500ms scroll
	{
		past_time = now;
		for (int i=0; i < 8; i++)
		{

			display_data[i] = (scroll_buffer[index][i] >> count) |
					(scroll_buffer[index+1][i] << 8 - count);
		}
		if (++count == 8) // 8칼람을 다 처리 했으면 다음 scroll_buffer로 이동
		{
			count =0;
			index++;  // 다음 scroll_buffer로 이동
			if (index == number_of_character+1) index=0;
			// 14개의 문자를 다 처리 했으면 0번 scroll_buffer를 처리 하기위해 이동
		}
	}
	for (int i=0; i < 8; i++)
	{
		// 공통 양극 방식
		// column에는 0을 ROW에는 1을 출력해야 해당 LED가 on된다.
		col[0] = ~(1 << i);  // 00000001  --> 11111110
		col[1] = display_data[i];
		// HAL_SPI_Transmit(&hspi2, col, 2, 1);
		for(int j = 0; j < 2; j++)
		{
			for(int k = 0; k < 8; k++)
			{
				temp = col[j];
				if(temp & (1 << k))
				{
					HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 1);
				}
				else
				{
					HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 0);
				}
				HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 1); // CLK 을 상승에서
				HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 0); // CLK 을 하강으로
			}
		}

		GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
		GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
		HAL_Delay(1);
	}

	return 0;
}

uint8_t col_direction[4]={0,0,0,0};


void arrow_dot(void)
{
    static int count = 0;  // 컬럼 count
    static uint32_t past_time = 0;  // 이전 tick값 저장
    static int direction = 1; // 1: 아래로 스크롤, -1: 위로 스크롤
    uint8_t temp;
    uint32_t now = HAL_GetTick();  // 1ms 단위 시간

    if (now - past_time >= 100) // 500ms 스크롤
    {
        past_time = now;
        for (int i = 0; i < 8; i++)
        {
            if (dot_button_state)
                display_data[i] = (arrow_up[i] >> count) | (arrow_up[i] << (8 - count));
            else
                display_data[i] = (arrow_down[i] >> count) | (arrow_down[i] << (8 -  count));
        }

        count += direction;

        if (count == 8 || count == -1) // 범위를 벗어나면 방향 변경
        {
            count = (count == 8) ? 7 : 0;
            direction *= -1;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        col_direction[0] = ~(1 << i);
        col_direction[1] = display_data[i];

        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                temp = col_direction[j];
                if (temp & (1 << k))
                {
                    HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 1);
                }
                else
                {
                    HAL_GPIO_WritePin(GPIOB, SER_74HC595_Pin, 0);
                }
                HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 1);
                HAL_GPIO_WritePin(GPIOB, CLK_74HC595_Pin, 0);
            }
        }

        GPIOB->ODR &= ~GPIO_PIN_13;
        GPIOB->ODR |= GPIO_PIN_13;
        HAL_Delay(1);
    }
}




void dotmatrix_state_check(void)
{
	if (get_button(GPIOC, GPIO_PIN_0, BTN0 ) == BUTTON_PRESS)
	{
		dot_button_state = !dot_button_state; // 0 시계 display, 1 알람시계 세팅화면 display
		//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // 디버깅용
		dot_matrix_running = 1;
		running_time = 0;
	}
}

void elevator_dotmatrix_main(void)
{
   static uint8_t display_data[8] = {0};
   static uint8_t scroll_index = 0;
   static uint32_t past_time = 0;
   static int i = 0;
   uint32_t now = HAL_GetTick();
   const uint8_t* floor_data;

   switch (current_floor)
   {
   case FIRST_FLOOR:  floor_data = num_1; break;
   case SECOND_FLOOR: floor_data = num_2; break;
   case THIRD_FLOOR:  floor_data = num_3; break;
   case FOURTH_FLOOR: floor_data = num_4; break;
   default: return;
   }

   if (now - past_time >= 100)  // 스크롤 주기
   {
      past_time = now;

      for (int i = 0; i < 8; i++)
      {
         if ((elevator_direction == UPWARD) && stepmotor_state != IDLE)
         {
            display_data[i] = (floor_data[i] >> scroll_index) | (floor_data[i] << (8 - scroll_index));
         }
         else if ((elevator_direction == DOWNWARD) && stepmotor_state != IDLE)
         {
            display_data[i] = (floor_data[i] << scroll_index) | (floor_data[i] >> (8 - scroll_index));
         }
         else if(stepmotor_state == IDLE) // STOP
         {
            display_data[i] = floor_data[i];
         }
      }
      scroll_index = (scroll_index + 1) % 8;
   }

   // 출력
      col[0] = ~(1 << i);  // Column
      col[1] = display_data[i];  // Row

      // 시프트레지스터 전송
      for (int j = 0; j < 2; j++)
      {
         for (int k = 0; k < 8; k++)
         {
            HAL_GPIO_WritePin(SER_74HC595_GPIO_Port, SER_74HC595_Pin, (col[j] & (1 << (7 - k))) ? GPIO_PIN_SET : GPIO_PIN_RESET);
            HAL_GPIO_WritePin(CLK_74HC595_GPIO_Port, CLK_74HC595_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(CLK_74HC595_GPIO_Port, CLK_74HC595_Pin, GPIO_PIN_RESET);
         }
      }
      // 래치
      GPIOB->ODR &= ~GPIO_PIN_13;
      GPIOB->ODR |= GPIO_PIN_13;

      i++;
      i %= 8;
}
#endif
