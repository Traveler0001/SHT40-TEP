/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SHT40_SDA_STM32_PB9_Pin GPIO_PIN_9
#define SHT40_SDA_STM32_PB9_GPIO_Port GPIOB
#define LED2_SER_Pin GPIO_PIN_0
#define LED2_SER_GPIO_Port GPIOA
#define LED2_RCLK_Pin GPIO_PIN_1
#define LED2_RCLK_GPIO_Port GPIOA
#define LED2_SCLK_Pin GPIO_PIN_2
#define LED2_SCLK_GPIO_Port GPIOA
#define DIG_SER_Pin GPIO_PIN_3
#define DIG_SER_GPIO_Port GPIOA
#define DIG_RCLK_Pin GPIO_PIN_4
#define DIG_RCLK_GPIO_Port GPIOA
#define DIG_SCLK_Pin GPIO_PIN_5
#define DIG_SCLK_GPIO_Port GPIOA
#define POWER_EN_Pin GPIO_PIN_6
#define POWER_EN_GPIO_Port GPIOA
#define LDO_WAKE_Pin GPIO_PIN_7
#define LDO_WAKE_GPIO_Port GPIOA
#define BAT_DET_Pin GPIO_PIN_1
#define BAT_DET_GPIO_Port GPIOB
#define LED1_SER_Pin GPIO_PIN_2
#define LED1_SER_GPIO_Port GPIOB
#define LED1_RCLK_Pin GPIO_PIN_8
#define LED1_RCLK_GPIO_Port GPIOA
#define LED1_SCLK_Pin GPIO_PIN_11
#define LED1_SCLK_GPIO_Port GPIOA
#define WAKE_Pin GPIO_PIN_5
#define WAKE_GPIO_Port GPIOB
#define WAKE_EXTI_IRQn EXTI4_15_IRQn
#define GPIO_TEST_Pin GPIO_PIN_7
#define GPIO_TEST_GPIO_Port GPIOB
#define SHT40_SCL_STM32_PB8_Pin GPIO_PIN_8
#define SHT40_SCL_STM32_PB8_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
