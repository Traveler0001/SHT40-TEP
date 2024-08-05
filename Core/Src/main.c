/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// double Temperature = 0;
// double Humidity = 0;
// uint8_t writeData[1] = {0xFD};
// uint8_t readData[6] = {0};
uint8_t read_flag = 0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SHT40_Write (0x44 << 1)      // 写入地址
#define SHT40_Read ((0x44 << 1) + 1) // 读出地址

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  uint16_t num = 0;
  uint8_t writeData[1] = {0xFD};
  uint8_t readData[6] = {0};
  uint16_t Temp = 0, Humi = 0;
  double Temperature = 0;
  double Humidity = 0;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(100);
  SN74HC595_Send_Data(SN_DIG, 0x00);
  SN74HC595_Send_Data(SN_LED1, 0x00);
  SN74HC595_Send_Data(SN_LED2, 0x00);

  HAL_Delay(100);
  HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SHT40_Write, (uint8_t *)writeData, 1, HAL_MAX_DELAY);
  HAL_Delay(10);
  HAL_I2C_Master_Receive(&hi2c1, (uint16_t)SHT40_Read, (uint8_t *)readData, 6, HAL_MAX_DELAY);

  // Temperature = (1.0 * 175 * (readData[0] * 256 + readData[1])) / 65535.0 - 45;
  // Humidity = (1.0 * 125 * (readData[3] * 256 + readData[4])) / 65535.0 - 6.0;

  // Temp = (uint16_t)(Temperature * 10);
  // Humi = (uint16_t)(Humidity * 10);

  HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if (read_flag == 1)
    {
      read_flag = 0;
      HAL_Delay(10);
      HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SHT40_Write, (uint8_t *)writeData, 1, HAL_MAX_DELAY);
      HAL_Delay(10);
      HAL_I2C_Master_Receive(&hi2c1, (uint16_t)SHT40_Read, (uint8_t *)readData, 6, HAL_MAX_DELAY);
      Temperature = (1.0 * 175 * (readData[0] * 256 + readData[1])) / 65535.0 - 45;
      Humidity = (1.0 * 125 * (readData[3] * 256 + readData[4])) / 65535.0 - 6.0;

      Temp = (uint16_t)(Temperature * 10);
      Humi = (uint16_t)(Humidity * 10);
    }

    num++;
    if (num < 100)
    {
      ShowNum(1, 1, Temp / 100);
      ShowNum(1, 2, Temp / 10 % 10);
      ShowNum(1, 3, Temp % 10);
    }
    else if (num < 200)
    {
      ShowNum(2, 1, Humi / 100);
      ShowNum(2, 2, Humi / 10 % 10);
      ShowNum(2, 3, Humi % 10);
    }
    else
    {
      num = 0;
      ShowNum(1, 1, Temp / 100);
      ShowNum(1, 2, Temp / 10 % 10);
      ShowNum(1, 3, Temp % 10);
    }

    // ShowNum(2,1,6);
    // ShowNum(2,2,6);
    // ShowNum(2,3,6);

    // HAL_Delay(500);
    // HAL_GPIO_TogglePin(TEST_LED_GPIO_Port, TEST_LED_Pin);
    // HAL_Delay(100);
    // HAL_GPIO_TogglePin(GPIO_TEST_GPIO_Port, GPIO_TEST_Pin);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
