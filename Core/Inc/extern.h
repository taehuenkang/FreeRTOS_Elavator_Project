#include "main.h"
extern uint8_t rx_data;   // uart2 rx byte
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim2;

#define BTN_PUPDR 0x4002080C
#define BTN_IDR 0x40020810
#define IDLE 	 0
#define UPWARD  1
#define DOWNWARD 2

extern volatile int TIM11_1ms_counter;
extern volatile int FND_update_counter;
extern volatile int Buzzer_counter;
extern volatile int Button_counter;
extern volatile uint8_t current_floor;   // 현재 있는 층
extern volatile uint8_t elevator_destination[4][2];
extern volatile uint8_t stepmotor_state;
extern volatile uint8_t elevator_direction;
extern void elavator_buzzer(void);
extern t_print o_prt;
extern void delay_us(int us);
extern void led_main(void);
extern void i2c1_main(void);
extern void button_led_toggle_test(void);
extern int get_button( GPIO_TypeDef *GPIO, int GPIO_Pin, int button_num);
extern void button_pull_up(void);
extern void buzzer_main();
extern void lcd_command(uint8_t command);

extern void ds1302_main(void);
extern void pc_command_processing(void);
extern void set_rtc(char *date_time);
extern volatile uint8_t stop_signal;
extern void flash_main();
extern void flash_set_time(void);

extern void dotmatrix_main_test();
extern int dotmatrix_main(void);
extern int dotmatrix_main_func(void);
extern int dotmatrix_name_main(void);
extern void init_ds1302_elevator(void);
extern void elevator_date_time(void);
extern void display_elevator(void);

extern void servo_motor_main(void);
extern void stepmotor_main(void);
extern void elevator_main(void);
extern void elevator_dotmatrix_main(void);

extern void fnd_elevator_display(void);

extern void led_elevator(void);
extern void i2c_lcd_main(void);
extern void i2c_lcd_init(void);
extern void lcd_string(uint8_t *str);
extern void move_cursor(uint8_t row, uint8_t column);

extern void lcd_command(uint8_t command);
extern volatile uint8_t stop_time_signal;


typedef struct s_ds1302
{
	uint32_t magic;
	uint8_t seconds;   // sec
	uint8_t minutes;
	uint8_t hours;
	uint8_t date;
	uint8_t month;
	uint8_t dayofweek;  // 1: sun 2:mon
	uint8_t year;
	uint8_t ampm;   // 1: pm 0:am
	uint8_t hourmode;   // 0: 24 1: 12
	uint8_t dummy[3];
} t_ds1302;

extern t_ds1302 ds1302;
