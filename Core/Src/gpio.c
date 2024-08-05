/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
//0~9，外加一个小数点
uint16_t sgh_value[11]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x80};

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED2_SER_Pin|LED2_RCLK_Pin|LED2_SCLK_Pin|DIG_SER_Pin
                          |DIG_RCLK_Pin|DIG_SCLK_Pin|POWER_EN_Pin|LDO_WAKE_Pin
                          |LED1_RCLK_Pin|LED1_SCLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_SER_GPIO_Port, LED1_SER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIO_TEST_GPIO_Port, GPIO_TEST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = LED2_SER_Pin|LED2_RCLK_Pin|LED2_SCLK_Pin|DIG_SER_Pin
                          |DIG_RCLK_Pin|DIG_SCLK_Pin|LED1_RCLK_Pin|LED1_SCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = POWER_EN_Pin|LDO_WAKE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED1_SER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED1_SER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = WAKE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(WAKE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = GPIO_TEST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIO_TEST_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 2 */
void SN74HC595_Send_Data(unsigned char sn_num,unsigned int sendValue)
{
	uint8_t i = 0;
	if(sn_num == SN_LED1)	//µÚÒ»¸öÊýÂë¹Ü
	{
		for(i = 0;i < 8;i++)
		{
			if(((sendValue << i)&0x80)!=0)	//Èç¹ûÊý¾ÝµÚÒ»Î»ÊÇ1
			{
				HAL_GPIO_WritePin(LED1_SER_GPIO_Port,LED1_SER_Pin,GPIO_PIN_SET);		//¸ßµçÆ½
			}
			else
			{
				HAL_GPIO_WritePin(LED1_SER_GPIO_Port,LED1_SER_Pin,GPIO_PIN_RESET);	//µÍµçÆ½
			}
			HAL_GPIO_WritePin(LED1_SCLK_GPIO_Port,LED1_SCLK_Pin,GPIO_PIN_RESET);	//²úÉúÒ»¸öSCLKÉÏÉýÑØ
			HAL_GPIO_WritePin(LED1_SCLK_GPIO_Port,LED1_SCLK_Pin,GPIO_PIN_SET);
			}
		HAL_GPIO_WritePin(LED1_RCLK_GPIO_Port,LED1_RCLK_Pin,GPIO_PIN_RESET);	//²úÉúÒ»¸öRCLKÉÏÉýÑØ
		HAL_GPIO_WritePin(LED1_RCLK_GPIO_Port,LED1_RCLK_Pin,GPIO_PIN_SET);
	}
	else if(sn_num == SN_LED2)
	{
    
		for(i = 0;i < 8;i++)
		{
			if(((sendValue << i)&0x80)!=0)
			{
				HAL_GPIO_WritePin(LED2_SER_GPIO_Port,LED2_SER_Pin,GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(LED2_SER_GPIO_Port,LED2_SER_Pin,GPIO_PIN_RESET);
			}
			HAL_GPIO_WritePin(LED2_SCLK_GPIO_Port,LED2_SCLK_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED2_SCLK_GPIO_Port,LED2_SCLK_Pin,GPIO_PIN_SET);
			}
		HAL_GPIO_WritePin(LED2_RCLK_GPIO_Port,LED2_RCLK_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_RCLK_GPIO_Port,LED2_RCLK_Pin,GPIO_PIN_SET);	
	}
	else if(sn_num == SN_DIG)
	{
		for(i = 0;i < 8;i++)
		{
			if(((sendValue << i)&0x80)!=0)
			{
				HAL_GPIO_WritePin(DIG_SER_GPIO_Port,DIG_SER_Pin,GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIG_SER_GPIO_Port,DIG_SER_Pin,GPIO_PIN_RESET);
			}
			HAL_GPIO_WritePin(DIG_SCLK_GPIO_Port,DIG_SCLK_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DIG_SCLK_GPIO_Port,DIG_SCLK_Pin,GPIO_PIN_SET);
			}
		HAL_GPIO_WritePin(DIG_RCLK_GPIO_Port,DIG_RCLK_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DIG_RCLK_GPIO_Port,DIG_RCLK_Pin,GPIO_PIN_SET);	
	}
}

void ShowNum(uint8_t row, uint8_t column, uint8_t value)
{
	if(row == 1)
	{
		switch(column)
		{
			case 1:	
					SN74HC595_Send_Data(SN_DIG,0xFE);	//Èç¹ûÊÇµÚÒ»ÅÅµÚÒ»¸ö
					SN74HC595_Send_Data(SN_LED1,sgh_value[value]);	//ÏÔÊ¾Öµ¶ÔÓ¦16½øÖÆÊý
				break;
			case 2:
					SN74HC595_Send_Data(SN_DIG,0xFD);
					SN74HC595_Send_Data(SN_LED1,(sgh_value[value]|0x80));	//Ä¬ÈÏÔÚµÚ¶þÎ»ÉÏ¼ÓÈëÒ»¸öÐ¡Êýµã
				break;
			case 3:
					SN74HC595_Send_Data(SN_DIG,0xFB);
					SN74HC595_Send_Data(SN_LED1,sgh_value[value]);
				break;
			default:
				break;
		}
		SN74HC595_Send_Data(SN_LED1,0x00);	//ÏûÓ°£¬·ÀÖ¹´íÎ»
	}
	else
	{
		switch(column)
		{
			case 1:
					SN74HC595_Send_Data(SN_DIG,0xF7);
					SN74HC595_Send_Data(SN_LED2,sgh_value[value]);
				break;
			case 2:
					SN74HC595_Send_Data(SN_DIG,0xEF);
					SN74HC595_Send_Data(SN_LED2,(sgh_value[value]|0x80));
				break;
			case 3:
					SN74HC595_Send_Data(SN_DIG,0xDF);
					SN74HC595_Send_Data(SN_LED2,sgh_value[value]);
				break;
			default:
				break;
		}
		SN74HC595_Send_Data(SN_LED2,0x00);
	}
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_5)
	{
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) == GPIO_PIN_RESET)
		{
			//执行翻转LED函数，在中断服务函数中不建议做死循环或长时间等待操作
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_7);
		}
	}
}
/* USER CODE END 2 */
