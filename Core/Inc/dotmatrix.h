uint8_t dot_button_state = 0; // button state 초기값은 0
uint8_t dot_matrix_running = 0; // dot matrix running 상태
void dotmatrix_state_check(void);
void arrow_dot(void);
int dotmatrix_main_func(void);
int dotmatrix_name_main(void);
int dotmatrix_main(void);
void init_dotmatrix(void);
void dotmatrix_main_test();

unsigned char display_data[8];  // 최종 8x8 출력할 데이터
unsigned char scroll_buffer[50][8] = {0};  // 스코롤할 데이타가 들어있는 버퍼
int number_of_character = 6;  // 출력할 문자 갯수 //강태훈 추가
int running_time = 0; // 30초 세는 카운터변수

/*uint8_t arrow_up[] = {
		0b00000000,
		0b00011000,
		0b00111100,
		0b01111110,
		0b00011000,
		0b00011000,
		0b00011000,
		0b00000000
};*/

/*uint8_t arrow_down[] = {
		0b00000000,
		0b00011000,
		0b00011000,
		0b00011000,
		0b01111110,
		0b00111100,
		0b00011000,
		0b00000000
};*/
uint8_t arrow_down[] =//아래화살표
{
0x10, 0x30, 0x7f, 0xff, 0xff, 0x7f, 0x30, 0x10
};
uint8_t arrow_up[] = //위의화살표
{
0x08, 0x0c, 0xfe, 0xff, 0xff, 0xfe, 0x0c, 0x08
};



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
