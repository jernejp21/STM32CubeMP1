/**
  ******************************************************************************
  * @file    stm32mp1xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   This file provides code for the MSP Initialization
  *                      and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_HSEM_CLK_ENABLE();

  /* System interrupt init*/

  /* Peripheral interrupt init */
  __HAL_RCC_ENABLE_IT(RCC_IT_WKUP);

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef* hlptim)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hlptim->Instance==LPTIM1)
  {
  /* USER CODE BEGIN LPTIM1_MspInit 0 */

    if(IS_ENGINEERING_BOOT_MODE())
    {
      RCC_OscInitTypeDef RCC_OscInitStruct;
      RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;

      /* Enable LSE clock */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
      RCC_OscInitStruct.LSEState = RCC_LSE_ON;
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
      RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_NONE;
      RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_NONE;
      RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_NONE;
      if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
      {
        Error_Handler();
      }

      /* Select the LSE clock as LPTIM1 peripheral clock */
      RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPTIM1;
      RCC_PeriphCLKInitStruct.Lptim1ClockSelection = RCC_LPTIM1CLKSOURCE_LSE;
      HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);
    }

    /* Force the LPTIM Peripheral Clock Reset */
    __HAL_RCC_LPTIM1_FORCE_RESET();

    /* Release the LPTIM Peripheral Clock Reset */
    __HAL_RCC_LPTIM1_RELEASE_RESET();

  /* USER CODE END LPTIM1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_LPTIM1_CLK_ENABLE();

    /**LPTIM1 GPIO Configuration
    PD12     ------> LPTIM1_IN1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Alternate = GPIO_AF1_LPTIM1;
    PERIPH_LOCK(GPIOD);
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    PERIPH_UNLOCK(GPIOD);

    /* LPTIM1 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM1_IRQn, DEFAULT_IRQ_PRIO, 0);
    HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
  /* USER CODE BEGIN LPTIM1_MspInit 1 */

  /* USER CODE END LPTIM1_MspInit 1 */
  }

}

void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef* hlptim)
{

  if(hlptim->Instance==LPTIM1)
  {
    /* USER CODE BEGIN LPTIM1_MspDeInit 0 */


    /* Force the LPTIM Peripheral Clock Reset */
    __HAL_RCC_LPTIM1_FORCE_RESET();

    /* Release the LPTIM Peripheral Clock Reset */
    __HAL_RCC_LPTIM1_RELEASE_RESET();

    /* USER CODE END LPTIM1_MspDeInit 0 */

    /* Peripheral clock disable */
    __HAL_RCC_LPTIM1_CLK_DISABLE();

    /**LPTIM1 GPIO Configuration
    PD12     ------> LPTIM1_IN1
    */
    PERIPH_LOCK(GPIOD);
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_12);
    PERIPH_UNLOCK(GPIOD);

    /* LPTIM1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(LPTIM1_IRQn);
    /* USER CODE BEGIN LPTIM1_MspDeInit 1 */

    /* USER CODE END LPTIM1_MspDeInit 1 */
  }

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

