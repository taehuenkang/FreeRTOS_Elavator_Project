#include "button.h"
#include "extern.h"

void button_led_toggle_test(void);
int get_button( GPIO_TypeDef *GPIO, int GPIO_Pin, int button_num);
void button_pull_up(void);

void button_led_toggle_test(void)
{
	// 버튼을 한번 눌렀다 떼먼 led가 toggle되도록 code를 구현
	if (get_button(BTN0_GPIO_Port, BTN0_Pin, BTN0 ) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	}
	if (get_button(BTN1_GPIO_Port, BTN1_Pin, BTN1 ) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
	}
	if (get_button(BTN2_GPIO_Port, BTN2_Pin, BTN2 ) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
	}
	if (get_button(BTN3_GPIO_Port, BTN3_Pin, BTN3 ) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	}
	if (get_button(GPIOC, GPIO_PIN_13, BTN4 ) == BUTTON_PRESS)   // Demo b'd
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}
}

void button_pull_up(void)
{
	*(unsigned int*)BTN_PUPDR = 0b01010101;
}

int get_button(GPIO_TypeDef *GPIO, int GPIO_Pin, int button_num)
{
	static unsigned char button_status[BUTTON_NUMBER] =
	{BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE};
	// 	지역 변수에 static을 쓰면 전역 변수처럼 함수를 빠져 나갔다 다시 들어 와도 값을 유지 한다.
	unsigned int current_state;

	// 1110 1101 1011 0111
	// 0xfffe 0x1111 .... 1110
	//                       1 GPION_PIN0
	//                       0
	current_state = *(unsigned int*)BTN_IDR;   // 버튼을 읽는다.

	if (!(current_state & GPIO_Pin) && button_status[button_num] == BUTTON_RELEASE)  // 버튼이 처음 눌려진 noise high
	{
		if(Button_counter >= 60)
		{
			Button_counter = 0;
			button_status[button_num] = BUTTON_PRESS;   // noise가 지나간 상태의 High 상태
			return BUTTON_RELEASE;   // 아직은 완전히 눌렸다 떼어진 상태가 아니다.
		}
	}
	else if (current_state & GPIO_Pin && button_status[button_num] == BUTTON_PRESS)
	{
		if(Button_counter >= 60)
		{
			Button_counter = 0;
			button_status[button_num] = BUTTON_RELEASE;   // 다음 버튼 체크를 위해서 초기화
			return BUTTON_PRESS;   // 완전히 1번 눌렸다 떼어진 상태로 인정
		}
	}

	return BUTTON_RELEASE;   // 버튼이 open상태
}

