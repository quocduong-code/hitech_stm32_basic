/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "acc_sensor_driver.h"
#include "afproto_user.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* Macro ON/OFF cac testcase */
#define TEST_UART_TX_RX
#define TEST_ACC_SPI


	

#define DEBOUCING_TIMER_INST    htim2
#define DEBOUCING_VALID_STATE   1

extern volatile uint8_t userBtnPressed;

static __IO uint32_t _debounced_counter = 0;
static uint16_t _active_debouced_pin = 0;


uint8_t _temp_raw_data = 0;
volatile uint8_t  adc_conv_done_flag = 0; // __IO
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define GPIOD_ADDRESS  (0x40020C00) //Dia chi bat dau vung nho thuoc GPIOD
#define BSRR_OFFSET    (0x18) // Dia chi thanh ghi Bit Set/Reset
#define BODR_OFFSET    (0x14) //Dia chi thanh ghi luu trang thai output

#define BSRR_ABS_ADDRESS   (GPIOD_ADDRESS + BSRR_OFFSET)  // Tinh dia chi vat ly thanh ghi Bit Set/ReseOutput
#define BODR_ABS_ADDRESS   (GPIOD_ADDRESS + BODR_OFFSET)  // Tinh dia chi vat ly thanh ghi Output

typedef  unsigned int  my_uint32_t;  // Dinh nghia lai kieu du lieu 32-bit interger

// Tao bien con tro toi thanh ghi bsrr
static my_uint32_t*  bsrr_reg_pointer = (uint32_t*)(BSRR_ABS_ADDRESS); // Tao bien con tro toi vung  nho thanh ghi BSRR
static my_uint32_t*  bodr_reg_pointer = (uint32_t*)(BODR_ABS_ADDRESS); // Tao bien con tro toi vung  nho thanh ghi ODR

static my_uint32_t bsrr_value = 0; // Bien luu gia tri thanh ghi BSRR
static my_uint32_t bodr_value = 0; // Bien luu gia tri thanh ghi ODR

static uint8_t led_state =  0; // Khai bao bien interger 8-bit luu trang thai LED

/* Tao macro port va pin cua chan DK LED */
#define   MY_LED_PORT  		GPIOD
#define   MY_LED_PIN  		GPIO_PIN_12
		
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define USER_USING_STD_LIB  0
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void control_led_using_pointer(void)
{
	// Doc gia tri thanh ghi output
	bodr_value = *(bodr_reg_pointer);
	// Xuat nguoc gia tri output
	*(bsrr_reg_pointer) = ~bodr_value;
}

//extern volatile uint8_t recv_done;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
//  HAL_TIM_Base_Start_IT(&htim2);
	

#ifdef TEST_UART_TX_RX
		/* Test gui nhan 1 byte */
//		uart_send_and_receive(0xAA);
		
		/* Test gui chuoi ky tu qua cong UART*/
	//__sendDebugMsg("adc = %d", 123);
//	afproto_user_run_test();
#endif

#ifdef TEST_ACC_SPI
  acc_sensor_init();
	HAL_Delay(2000);
#endif /* TEST_ACC_SPI */
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
#ifdef TEST_UART_TX_RX		
		/*Test nhan chuoi ky tu*/
//		if (recv_done == 1)
//		{
//			while(1) {};
//		}
#endif  /* TEST_UART_TX_RX */

#ifdef TEST_ACC_SPI
    acc_sensor_reading();
//		memset(_gFrameBuf, 0x00, MAX_FRAME_BUFFER);
//		_gFrameLen = acc_sensor_build_frame(_gFrameBuf);
//		__sendBufferToUart(_gFrameBuf, _gFrameLen);
		HAL_Delay(100);
#endif   /* TEST_ACC_SPI */
#if 0
		static uint32_t _temp_in_votage = 0;
		
		
		if (adc_conv_done_flag)
		{
			adc_conv_done_flag = 0;
			_temp_in_votage = adc_convert_to_voltage(_temp_raw_data);
		}
#endif 
		
		#if 0
#if USER_USING_STD_LIB
		control_led_using_stdlib();
#else
		control_led_using_pointer();
#endif		/* USER_USING_STD_LIB */	
		HAL_Delay(1000); // Tao tre 1s
		#endif
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 64;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void USER_DEBOUNCE_TMR_IRQHandler(void)
{
	/* Stop deboucing timer */
//	HAL_TIM_Base_Stop_IT(&DEBOUCING_TIMER_INST);
	
	/* Check if deboucing pin is in valid state */
	if (HAL_GPIO_ReadPin(USER_BTN_GPIO_Port, _active_debouced_pin) == DEBOUCING_VALID_STATE){
		_debounced_counter += 1;
	}
}

void USER_EXTI_IRQHandler(uint16_t pinNo)
{
	/* Save active GPIO Pin*/
	//_active_debouced_pin = pinNo;
	userBtnPressed = 1;
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
