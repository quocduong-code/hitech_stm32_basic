/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for
  *                      the gpio
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define LED3_ORANGE_GPIOx  LED_ORGANGE_GPIO_Port
#define LED4_GREEN_GPIOx   LED_GREEN_GPIO_Port
#define LED5_RED_GPIOx     LED_RED_GPIO_Port
#define LED6_BLUE_GPIOx    LED_BLUE_GPIO_Port


#define LED3_ORANGE_PinNumber   LED_ORGANGE_Pin
#define LED4_GREEN_PinNumber    LED_GREEN_Pin
#define LED5_RED_PinNumber      LED_RED_Pin
#define LED6_BLUE_PinNumber     LED_BLUE_Pin
  
#define LED3_ORANGE_ID	1
#define LED4_GREEN_ID	2
#define LED5_RED_ID	3
#define LED6_BLUE_ID	4

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void control_led_using_stdlib(void);
void gpio_led_state(uint8_t LED_ID, uint8_t state);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
