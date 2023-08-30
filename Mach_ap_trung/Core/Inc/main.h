/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
#include <stdio.h>
//#define DEBUG 1
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZ_Pin GPIO_PIN_13
#define BUZZ_GPIO_Port GPIOC
#define DHT_Pin GPIO_PIN_14
#define DHT_GPIO_Port GPIOC
#define MODE_Pin GPIO_PIN_0
#define MODE_GPIO_Port GPIOA
#define MODE_EXTI_IRQn EXTI0_IRQn
#define UP_Pin GPIO_PIN_1
#define UP_GPIO_Port GPIOA
#define UP_EXTI_IRQn EXTI1_IRQn
#define DOWN_Pin GPIO_PIN_2
#define DOWN_GPIO_Port GPIOA
#define DOWN_EXTI_IRQn EXTI2_IRQn
#define ENTER_Pin GPIO_PIN_3
#define ENTER_GPIO_Port GPIOA
#define ENTER_EXTI_IRQn EXTI3_IRQn
#define A_Pin GPIO_PIN_4
#define A_GPIO_Port GPIOA
#define B_Pin GPIO_PIN_5
#define B_GPIO_Port GPIOA
#define C_Pin GPIO_PIN_6
#define C_GPIO_Port GPIOA
#define D_Pin GPIO_PIN_7
#define D_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_0
#define LED3_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_1
#define LED4_GPIO_Port GPIOB
#define F_Pin GPIO_PIN_10
#define F_GPIO_Port GPIOB
#define G_Pin GPIO_PIN_12
#define G_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_8
#define E_GPIO_Port GPIOA
#define H_Pin GPIO_PIN_4
#define H_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
