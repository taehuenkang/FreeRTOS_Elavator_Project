#include "extern.h"
#include "button.h"
#include "elevator.h"
#define FIRST_FLOOR 	1
#define SECOND_FLOOR 	2
#define THIRD_FLOOR 	3
#define FOURTH_FLOOR 	4

#define FORWARD  1
#define BACKWARD 2

#define RUN				1
#define STOP			0

#define FLOOR_NUM		0
#define TARGET_STATE	1
#define TARGET			1
#define N_TARGET		0

volatile uint8_t current_floor = 0;   // 현재 있는 층
volatile uint8_t target_floor = 0;  // 사용자가 목표하는 층(버튼으로 제어)
volatile uint8_t target_floor_num = 0;

volatile uint8_t elevator_destination[4][2] = {
						{1,0},
						{2,0},
						{3,0},
						{4,0}
};

volatile uint8_t elevator_direction = 0; // 엘리베이터 이동방향(up,down)
volatile uint8_t elevator_running = 0;   // 엘리베이터 동작상태
volatile uint8_t stop_signal = 0;
void elevator_main(void)
{
		if(current_floor != target_floor) // 현재층과 누른 층이 같지 않을경우에만 동작
		{
			if(target_floor != IDLE)
			{
				elevator_floor_sel(target_floor);
				target_floor = 0;
			}
		}

		elevator_move();
		elevator_stop();
		elevator_button();
}

void elevator_button(void)
{
	if (get_button(BTN0_GPIO_Port, BTN0_Pin, BTN0 ) == BUTTON_PRESS)
	{
		target_floor = 1;
		printf("current floor : %d, target_floor : %d\n",current_floor, target_floor);

	}
	if (get_button(BTN1_GPIO_Port, BTN1_Pin, BTN1 ) == BUTTON_PRESS)
	{
		target_floor = 2;
		printf("current floor : %d, target_floor : %d\n",current_floor, target_floor);
	}
	if (get_button(BTN2_GPIO_Port, BTN2_Pin, BTN2 ) == BUTTON_PRESS)
	{
		target_floor = 3;
		printf("current floor : %d, target_floor : %d\n",current_floor, target_floor);
	}
	if (get_button(BTN3_GPIO_Port, BTN3_Pin, BTN3 ) == BUTTON_PRESS)
	{
		target_floor = 4;
		printf("current floor : %d, target_floor : %d\n",current_floor, target_floor);
	}
	if (get_button(GPIOC, GPIO_PIN_13, BTN4 ) == BUTTON_PRESS) // 디버깅용 버튼
	{
		printf("current floor : %d\n",current_floor);
		printf("target floor : %d\n",target_floor);
		printf("1 : %d\n",elevator_destination[0][TARGET_STATE]);
		printf("2 : %d\n",elevator_destination[1][TARGET_STATE]);
		printf("3 : %d\n",elevator_destination[2][TARGET_STATE]);
		printf("4 : %d\n",elevator_destination[3][TARGET_STATE]);
		printf("Stop Signal : %d\n",stop_time_signal);
	}
}

void elevator_floor_sel(uint8_t target_floor)
{
		if(elevator_running == STOP) // 엘리베이터가 동작중이 아니라면
		{
			if(target_floor < current_floor) // 목표 층이 현재 층보다 낮다면
			{
				elevator_direction = DOWNWARD; // 아래 방향으로 이동
				elevator_running = RUN;
				elevator_destination[target_floor-1][TARGET_STATE] = !elevator_destination[target_floor-1][TARGET_STATE];
				// TARGET_STATE의 초기값은 0 --> 선택안한상태
				// 한번 더 눌렀을 때 취소할 수 있도록 ! 연산자 사용
			}
			else // 목표 층이 현재 층보다 높다면
			{
				elevator_direction = UPWARD;
				elevator_running = RUN;
				elevator_destination[target_floor-1][TARGET_STATE] = !elevator_destination[target_floor-1][TARGET_STATE];
			}
		}

		else // 엘리베이터가 동작중이라면
		{
			if((target_floor < current_floor) && (elevator_direction == DOWNWARD))
				// 목표 층이 현재 층보다 낮고 현재 아래 방향으로 움직이고 있다면
			{
				elevator_destination[target_floor-1][TARGET_STATE] = !elevator_destination[target_floor-1][TARGET_STATE];
			}
			else if((target_floor < current_floor) && (elevator_direction == UPWARD))
				// 목표 층이 현재 층보다 낮고 현재 위 방향으로 움직이고 있다면
			{
				; // nop
			}
			else if((target_floor > current_floor) && (elevator_direction == DOWNWARD))
				// 목표 층이 현재 층보다 높고 현재 아래 방향으로 움직이고 있다면
			{
				; // nop
			}
			else if((target_floor > current_floor) && (elevator_direction == UPWARD))
				// 목표 층이 현재 층보다 높고 현재 위 방향으로 움직이고 있다면
			{
				elevator_destination[target_floor-1][TARGET_STATE] = !elevator_destination[target_floor-1][TARGET_STATE];
			}
		}
}

void elevator_move(void)
{
	if(elevator_running == RUN) // 엘리베이터 동작중
	{
		if(elevator_direction == UPWARD)
		{
			stepmotor_state = UPWARD;
			// 엘리베이터 상승
			if (current_floor == elevator_destination[current_floor-1][FLOOR_NUM] &&
					elevator_destination[current_floor-1][TARGET_STATE] == TARGET)
			// 현재 층수가 목표층수와 같고 멈춰야 하는 층이라면 멈추고, 해당 층 목표지에서 삭제
			{
				//stepmotor_state = IDLE;
				elevator_destination[current_floor-1][TARGET_STATE] = N_TARGET;
			}

		}
		else if(elevator_direction == DOWNWARD)
		{
			stepmotor_state = DOWNWARD;
			// 엘리베이터 하강
			if (current_floor == elevator_destination[current_floor-1][FLOOR_NUM] &&
					elevator_destination[current_floor-1][TARGET_STATE] == TARGET)
			// 현재 층수가 목표층수와 같고 멈춰야 하는 층이라면 멈추고, 해당 층 목표지에서 삭제
			{
				//stepmotor_state = IDLE;
				elevator_destination[current_floor-1][TARGET_STATE] = N_TARGET;
			}
		}
	}
	else // 엘리베이터 정지중
	{
		;//stepmotor_state = IDLE;
	}
}

void elevator_stop(void)
{
	static int count = 0;

	stop_signal = elevator_destination[0][1] + elevator_destination[1][1] +
			elevator_destination[2][1] + elevator_destination[3][1];
	if((stop_signal == STOP) && elevator_running) // 운행중일때만 멈추도록.
	{
		stepmotor_state = IDLE;
		elevator_running = STOP;
	}
	else if(stop_time_signal)
	{
		stepmotor_state = IDLE;
		if(TIM11_1ms_counter >= 1000)
		{
			TIM11_1ms_counter = 0;
			count++;
			printf("count : %d\n",count);
			if(count == 5)
			{
				count = 0;
				stop_time_signal = 0;
			}
		}
	}
}




