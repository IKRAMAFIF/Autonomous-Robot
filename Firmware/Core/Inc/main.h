/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define LED_ST1_Pin GPIO_PIN_13
#define LED_ST1_GPIO_Port GPIOC
#define LED_ST2_Pin GPIO_PIN_14
#define LED_ST2_GPIO_Port GPIOC
#define LED_ST3_Pin GPIO_PIN_15
#define LED_ST3_GPIO_Port GPIOC
#define BORDER_1_Pin GPIO_PIN_0
#define BORDER_1_GPIO_Port GPIOA
#define BORDER_2_Pin GPIO_PIN_1
#define BORDER_2_GPIO_Port GPIOA
#define LIDAR_TX_Pin GPIO_PIN_2
#define LIDAR_TX_GPIO_Port GPIOA
#define LIDAR_RX_Pin GPIO_PIN_3
#define LIDAR_RX_GPIO_Port GPIOA
#define BORDER_4_Pin GPIO_PIN_4
#define BORDER_4_GPIO_Port GPIOA
#define BORDER_3_Pin GPIO_PIN_5
#define BORDER_3_GPIO_Port GPIOA
#define INT2_ACC_Pin GPIO_PIN_6
#define INT2_ACC_GPIO_Port GPIOA
#define INT1_ACC_Pin GPIO_PIN_7
#define INT1_ACC_GPIO_Port GPIOA
#define BLE_TX_Pin GPIO_PIN_10
#define BLE_TX_GPIO_Port GPIOB
#define BLE_RX_Pin GPIO_PIN_11
#define BLE_RX_GPIO_Port GPIOB
#define REV2_Pin GPIO_PIN_13
#define REV2_GPIO_Port GPIOB
#define REV1_Pin GPIO_PIN_14
#define REV1_GPIO_Port GPIOB
#define ENCOD_B2_Pin GPIO_PIN_6
#define ENCOD_B2_GPIO_Port GPIOC
#define FWD2_Pin GPIO_PIN_8
#define FWD2_GPIO_Port GPIOA
#define FWD1_Pin GPIO_PIN_9
#define FWD1_GPIO_Port GPIOA
#define ENCOD_B1_Pin GPIO_PIN_11
#define ENCOD_B1_GPIO_Port GPIOA
#define ENCOD_A1_Pin GPIO_PIN_12
#define ENCOD_A1_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SWD_TX_Pin GPIO_PIN_10
#define SWD_TX_GPIO_Port GPIOC
#define SWD_RX_Pin GPIO_PIN_11
#define SWD_RX_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define ENCOD_A2_Pin GPIO_PIN_5
#define ENCOD_A2_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_8
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_9
#define SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
