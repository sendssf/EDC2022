
/*-------------------------jy62.c----------------------------*/
#include "jy62.h"
#include "main.h"

volatile uint8_t jy62Receive[JY62_MESSAGE_LENGTH];  //实时记录收到的信息
volatile uint8_t jy62Message[JY62_MESSAGE_LENGTH];   //确认无误后用于解码的信息
uint8_t initAngle[3] = {0xFF, 0xAA, 0x52};     
uint8_t calibrateAcce[3] = {0xFF, 0xAA, 0x67}; 
uint8_t setBaud115200[3] = {0xFF, 0xAA, 0x63};
uint8_t setBaud9600[3] = {0xFF, 0xAA, 0x64};    
uint8_t setHorizontal[3] = {0xFF, 0xAA, 0x65};  
uint8_t setVertical[3] = {0xFF, 0xAA, 0x66};
uint8_t sleepAndAwake[3] = {0xFF, 0xAA, 0x60};
UART_HandleTypeDef* jy62_huart;

struct Acce Accelerate;//储存加速度
struct Velo Velocity;//储存角速度
struct Angl Angle;  //储存角度值
struct Temp Temperature;  //储存温度值
/***********************接口****************************/

void jy62_Init(UART_HandleTypeDef *huart)
{
  jy62_huart = huart;
  HAL_UART_Receive_DMA(jy62_huart, jy62Receive, JY62_MESSAGE_LENGTH);
}

void jy62MessageRecord(void)
{
  if(jy62Receive[0] == 0x55)
  {
    uint8_t sum = 0x00;
    for (int i = 0; i < JY62_MESSAGE_LENGTH - 1; i++)
    {
      sum += jy62Receive[i];
    }
    if(sum == jy62Receive[JY62_MESSAGE_LENGTH - 1])
    {
      for (int i = 0; i < JY62_MESSAGE_LENGTH; i++)
      {
        jy62Message[i] = jy62Receive[i];
      }
      Decode();
    }
  }
  HAL_UART_Receive_DMA(jy62_huart, jy62Receive, JY62_MESSAGE_LENGTH);
}

void SetBaud(int Baud)
{
  if(Baud == 115200)
  {
    HAL_UART_Transmit(jy62_huart,setBaud115200, 3, HAL_MAX_DELAY);
  }
  else if(Baud == 9600)
  {
    HAL_UART_Transmit(jy62_huart, setBaud115200, 3, HAL_MAX_DELAY);
  }
}

void SetHorizontal()
{
  HAL_UART_Transmit(jy62_huart, setHorizontal, 3, HAL_MAX_DELAY);
}

void SetVertical()
{
  HAL_UART_Transmit(jy62_huart, setVertical, 3, HAL_MAX_DELAY);
}

void InitAngle()
{
  HAL_UART_Transmit(jy62_huart, initAngle, 3, HAL_MAX_DELAY);
}

void Calibrate()
{
  HAL_UART_Transmit(jy62_huart, calibrateAcce, 3, HAL_MAX_DELAY);
}

void SleepOrAwake()
{
  HAL_UART_Transmit(jy62_huart, sleepAndAwake, 3, HAL_MAX_DELAY);
}

