#include "extint.h"
#include "extern.h"

#define IDLE 	 0
#define FORWARD  1
#define BACKWARD 2
#define TARGET_STATE	1
#define TARGET			1
extern volatile uint8_t stepmotor_state;
volatile uint8_t stop_time_signal = 0;
/**
 * move from Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c to here
 * external INT callback function
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin){
	case GPIO_PIN_0 : // PC 0 / BTN 0
		current_floor = 1;
		// 현재 1층이고 3,4층 눌렀을때 2층에서는 멈추면 안됨.
		// elevator_destination[1][1] --> 2층의 정보
		if((elevator_direction == UPWARD) && (elevator_destination[0][TARGET_STATE] == TARGET))
			stop_time_signal = 1;
		else if((elevator_direction == DOWNWARD) && (elevator_destination[0][TARGET_STATE] == TARGET))
			stop_time_signal = 1;
//printf("GPIO_PIN_0\n");
		break;

	case GPIO_PIN_4 : // PC 4 / BTN 1
		current_floor = 2;
		if((elevator_direction == UPWARD) && (elevator_destination[1][TARGET_STATE] == TARGET))
			stop_time_signal = 1;
		else if((elevator_direction == DOWNWARD) && (elevator_destination[1][TARGET_STATE] == TARGET))
			stop_time_signal = 1;
//printf("GPIO_PIN_4\n");
		break;

	case GPIO_PIN_8 : // PC 0 / BTN 0
		current_floor = 3;
		if((elevator_direction == UPWARD) && (elevator_destination[2][TARGET_STATE] == TARGET))
			stop_time_signal = 1;
		else if((elevator_direction == DOWNWARD) && (elevator_destination[2][TARGET_STATE] == TARGET))
			stop_time_signal = 1;
//printf("GPIO_PIN_8\n");
		break;

	case GPIO_PIN_9 : // PC 0 / BTN 0
		current_floor = 4;
		if((elevator_direction == UPWARD) && (elevator_destination[3][TARGET_STATE] == TARGET))
			stop_time_signal = 1;
		else if((elevator_direction == DOWNWARD) && (elevator_destination[3][TARGET_STATE] == TARGET))
			stop_time_signal = 1;
//printf("GPIO_PIN_9\n");
		break;
	}
}
