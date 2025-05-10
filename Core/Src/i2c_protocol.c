#include "i2c_protocol.h"
#include "extern.h"

#define I2C_SDA 9
#define I2C_SCL 8

void i2c_start(void);
void i2c_stop(void);
void i2c_send_bit(uint8_t bit);
uint8_t i2c_send_byte(uint8_t data);
void init_i2c(void);

/* 1. SDA를 HIGH --> LOW
 * 2. SCL라인을 통해 CLK을 공급
 * 2.1 SCL이 LOW일 때 : SDA --> 비트신호
 * 2.2 SCL이 HIGH일 때 : 비트신호 --> WRITE TO RAM
 * 3. 2.1과 2.2를 반복
 * 4. 모든 비트의 전송이 끝난 후 SCL이 HIGH가 다면 SDA 신호도 HIGH로 만들어서 정지
 *
 *
 * GPIOB를 일반 출력모드로 설정 후
 *
 * SDA --> PB9 , SCL --> PB8
*/

void i2c_start(void)
{
   // SDA, SCL HIGH
   GPIOB->ODR |= 1 << I2C_SDA | 1 << I2C_SCL;
   delay_us(5);

   // SDA LOW
   GPIOB->ODR &= ~(1 << I2C_SDA);
   delay_us(5);

   // SCL LOW
   GPIOB->ODR &= ~(1 << I2C_SCL);
   delay_us(5);
}

void i2c_stop(void)
{
   // SDA LOW
   GPIOB->ODR &= ~(1 << I2C_SDA);
   delay_us(5);

   // SCL HIGH
   GPIOB->ODR |= 1 << I2C_SCL;
   delay_us(5);

   // SDA HIGH
   GPIOB->ODR |= 1 << I2C_SDA;
   delay_us(5);
}

// I2C 한 비트 전송 함수 (MSB부터 전송)
void i2c_send_bit(uint8_t bit)
{
   if(bit) // 비트가 1일 경우 SDA를 HIGH로
   {
      GPIOB->ODR |= 1 << I2C_SDA;
   }
   else // 비트가 0일 경우 SDA를 LOW로
   {
      GPIOB->ODR &= ~(1 << I2C_SDA);
   }
   delay_us(5);

   // SCL 펄스 : HIGH일 때 슬레이브가 SDA를 샘플링
   GPIOB->ODR |= 1 << I2C_SCL;
   delay_us(5);
   GPIOB->ODR &= ~(1 << I2C_SCL);
   delay_us(5);
}

// I2C로 1바이트 전송 (MSB부터) 후 ACK 읽기
// ACK가 LOW이면 정상으로 간주하고, HIGH이면 NACK
uint8_t i2c_send_byte(uint8_t data)
{

   for(int i=7;i>=0;i--) //MSB부터 전송
   {
      i2c_send_bit((data >> i) & 0x01);
   }

   // ACK를 위한 비트: SDA를 release(high)한 후, 슬레이브가 LOW로 끌어내리는지 확인 (끌어내리면 ACK)
   GPIOB->ODR |= 1 << I2C_SDA; // SDA HIGH
   delay_us(5);

   // ACK 펄스 : SCL HIGH 시점에 SDA 상태를 읽음
   GPIOB->ODR |= 1 << I2C_SCL;
   delay_us(5);
   uint8_t ack = ((GPIOB->IDR >> I2C_SDA) & 1) ? 1 : 0;
   GPIOB->ODR &= ~(1 << I2C_SCL);
   delay_us(5);

   return ack;
}

void init_i2c(void)
{

   // MODER: 핀을 일반 출력 모드("01")로 설정
   GPIOB->MODER &= ~((3 << (I2C_SDA * 2)) | (3 << (I2C_SCL * 2)));
   GPIOB->MODER |= ((1 << (I2C_SDA * 2)) | (1 << (I2C_SCL * 2)));

   // OTYPER: 오픈드레인으로 설정
   GPIOB->OTYPER |= ((1 << I2C_SDA) | (1 << I2C_SCL));

   // PUPDR: 내부 풀업 활성화 (각 핀마다 01)
   GPIOB->PUPDR &= ~((3 << (I2C_SDA*2)) | (3 << (I2C_SCL*2)));
   GPIOB->PUPDR |= ((1 << (I2C_SDA*2)) | (1 << (I2C_SCL*2)));
}
