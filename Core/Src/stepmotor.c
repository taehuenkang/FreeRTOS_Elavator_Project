#include "stepmotor.h"
#include "extern.h"
#include "button.h"

/*
 * RPM(Revolutions Per Minutes : 분당 회전수)
 * 1분 60sec : 1sec(1,000,000us) * 60sec : 60,000,000us
 * 1초 : 1000ms --> 1ms(1,000us) * 1000ms : 10,000,000us
 * 1바퀴 회전 : 4096 step 필요
 * 4096 / 8 ==> 512 sequence : 360도 회전
 * 1 sequence (8step) : 0.70312 도
 * 0.70312 * 512 sequence = 360도 회전
 * ---- RPM 조절 ----
 * 예) 1분에 13회전이 최대 속도
 * 13회전 : 60,000,000us(1분) / 4096 / 13 ==> step 과 step 과의 간격 time : 1126us
 * 1126us x 4096(1회전하는데 필요 스텝) = 4,615,384us
 * 								    = 4,615ms(4.6초)
 * 60초 / 4.6초(1회전 하는데 소요 시간) : 13회전
 */

// BTN0 : idle(stop)
// BTN1 : FW <--> BW
volatile uint8_t stepmotor_state = 0;


void set_rpm(int rpm) // rpm : 1 ~ 13
{
	delay_us(60000000/4096/rpm);
	// 최대 speed기준 (13) : delay_us(1126);
}

// stepmotor demo
void stepmotor_main(void)
{
#if 1	// O/S
	switch(stepmotor_state)
	{
	case IDLE :
		break;

	case UPWARD :
		stepmotor_driver(UPWARD);
		set_rpm(13);	// 1126us wait
		break;

	case DOWNWARD :
		stepmotor_driver(DOWNWARD);
		set_rpm(13);	// 1126us wait
		break;
	}
#endif

#if 0	// none O/S
	while(1)
	{
		switch(stepmotor_state)
		{
		case IDLE :
			if (get_button(BTN1_GPIO_Port, BTN1_Pin, BTN1) == BUTTON_PRESS)
				stepmotor_state = FORWARD;
			break;

		case FORWARD :
			stepmotor_driver(FORWARD);
			set_rpm(13);	// 1126us wait

			if (get_button(BTN0_GPIO_Port, BTN0_Pin, BTN0) == BUTTON_PRESS)
				stepmotor_state = IDLE;
			if (get_button(BTN1_GPIO_Port, BTN1_Pin, BTN1) == BUTTON_PRESS)
				stepmotor_state = BACKWARD;
			break;

		case BACKWARD :
			stepmotor_driver(BACKWARD);
			set_rpm(13);	// 1126us wait

			if (get_button(BTN0_GPIO_Port, BTN0_Pin, BTN0) == BUTTON_PRESS)
				stepmotor_state = IDLE;
			if (get_button(BTN1_GPIO_Port, BTN1_Pin, BTN1) == BUTTON_PRESS)
				stepmotor_state = FORWARD;

			break;
		}
	}
#endif
#if 0 // for demo
	while(1)
	{
		for (int i = 0; i < 512; i++) // 시계 방향 1회전
		{
			for(int j = 0; j < 8; j++) // 1 sequence : 8 step
			{
				stepmotor_driver(j);
				set_rpm(13);	// 1126us wait
			}
		}

		for (int i = 0; i < 512; i++) // 반시계 방향 1회전
		{
			for(int j = 7; j >= 0; j--) // 1 sequence : 8 step
			{
				stepmotor_driver(j);
				set_rpm(13);	// 1126us wait
			}
		}
	}
#endif
}

void stepmotor_driver(int direction)
{
	static int step = 0;

	switch(step){
	case 0 :
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 1);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 0);
		HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 0);
		HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 0);
		break;
	case 1 :
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 1);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 1);
		HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 0);
		HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 0);
		break;
	case 2 :
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 0);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 1);
		HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 0);
		HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 0);
		break;
	case 3 :
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 0);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 1);
		HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 1);
		HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 0);
		break;
	case 4 :
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 0);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 0);
		HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 1);
		HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 0);
		break;
	case 5 :
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 0);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 0);
		HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 1);
		HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 1);
		break;
	case 6 :
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 0);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 0);
		HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 0);
		HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 1);
		break;
	case 7 :
		HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 1);
		HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 0);
		HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 0);
		HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 1);
		break;
	}

	if(direction == UPWARD)
	{
		step++;
		step %= 8;
		// 다음 진행할 step for (i = 0; i < 8; i++)
	}
	else // direction == DOWNWARD
	{
		step--;
		if(step < 0)
			step = 7;
		// 다음 진행할 step for (j = 7; j >= 0; j--)
	}
}
