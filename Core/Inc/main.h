/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define JY_BUF_SIZE 33
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define calcAngle(L, H) ((float)(((uint16_t)(H) << 8) | (uint16_t)(L)) / 8192.0f * 45.0f)
#define calAcc(L,H) ((float)(((uint16_t)(H) << 8) | (uint16_t)(L))* g / 2048)

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern uint8_t rxData[JY_BUF_SIZE << 1];
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ROLL1_IN2_Pin GPIO_PIN_14
#define ROLL1_IN2_GPIO_Port GPIOC
#define ROLL3_IN2_Pin GPIO_PIN_1
#define ROLL3_IN2_GPIO_Port GPIOC
#define ROLL4_IN1_Pin GPIO_PIN_2
#define ROLL4_IN1_GPIO_Port GPIOC
#define ROLL4_IN2_Pin GPIO_PIN_3
#define ROLL4_IN2_GPIO_Port GPIOC
#define COUNTER3A_Pin GPIO_PIN_0
#define COUNTER3A_GPIO_Port GPIOA
#define COUNTER3B_Pin GPIO_PIN_1
#define COUNTER3B_GPIO_Port GPIOA
#define ROLL2_IN2_Pin GPIO_PIN_12
#define ROLL2_IN2_GPIO_Port GPIOB
#define ROLL2_IN1_Pin GPIO_PIN_13
#define ROLL2_IN1_GPIO_Port GPIOB
#define ROLL1_IN1_Pin GPIO_PIN_15
#define ROLL1_IN1_GPIO_Port GPIOB
#define COUNTER4A_Pin GPIO_PIN_6
#define COUNTER4A_GPIO_Port GPIOC
#define COUNTER4B_Pin GPIO_PIN_7
#define COUNTER4B_GPIO_Port GPIOC
#define PWM1_Pin GPIO_PIN_8
#define PWM1_GPIO_Port GPIOA
#define PWM2_Pin GPIO_PIN_9
#define PWM2_GPIO_Port GPIOA
#define PWM3_Pin GPIO_PIN_10
#define PWM3_GPIO_Port GPIOA
#define PWM4_Pin GPIO_PIN_11
#define PWM4_GPIO_Port GPIOA
#define COUNTER1A_Pin GPIO_PIN_15
#define COUNTER1A_GPIO_Port GPIOA
#define COUNTER1B_Pin GPIO_PIN_3
#define COUNTER1B_GPIO_Port GPIOB
#define COUNTER2A_Pin GPIO_PIN_6
#define COUNTER2A_GPIO_Port GPIOB
#define COUNTER2B_Pin GPIO_PIN_7
#define COUNTER2B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
