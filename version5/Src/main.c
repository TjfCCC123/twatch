/*
* | File      	:   main.h
* | Author      :   TJF
* | Function    :	  STM32F103ZET6 TWATCH
*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "EPD_Test.h"

GPIO_PinState jieguo = 0;
void SystemClock_Config(void);
extern int testFlag;
int main(void)
{
  HAL_Init();

  //Configure the system clock
  SystemClock_Config();
	//origin time
	PAINT_TIME paintTime;
	paintTime.Year = 2022;
	paintTime.Month = 4;
	paintTime.Day = 19;
	paintTime.Hour = 12;
	paintTime.Min = 34;
	paintTime.Sec = 56;
	paintTime.week[0] = "SUN";
	paintTime.week[1] = "MON";
	paintTime.week[2] = "TUE";
	paintTime.week[3] = "WED";
	paintTime.week[4] = "THU";
	paintTime.week[5] = "FRI";
	paintTime.week[6] = "SAT";
	testFlag = 0;
  //Initialize all configured peripherals
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
	
	//set external interrupt BEGIN
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	//PD0 left_up back/function
	GPIO_InitTypeDef test;
	test.Mode = GPIO_MODE_IT_RISING;
	test.Pin = GPIO_PIN_0;
	test.Pull = GPIO_PULLDOWN;
	test.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &test);
	HAL_NVIC_SetPriority(EXTI0_IRQn, 2U, 0U);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
	//PD1 left_down comfirm
	GPIO_InitTypeDef test1;
	test1.Mode = GPIO_MODE_IT_RISING;
	test1.Pin = GPIO_PIN_1;
	test1.Pull = GPIO_PULLDOWN;
	test1.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &test1);
	HAL_NVIC_SetPriority(EXTI1_IRQn, 2U, 0U);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);

	//PD3 right_up up
	GPIO_InitTypeDef test3;
	test3.Mode = GPIO_MODE_IT_RISING;
	test3.Pin = GPIO_PIN_3;
	test3.Pull = GPIO_PULLDOWN;
	test3.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &test3);
	HAL_NVIC_SetPriority(EXTI3_IRQn, 2U, 0U);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
	
	//PD4 right_down down
	GPIO_InitTypeDef test4;
	test4.Mode = GPIO_MODE_IT_RISING;
	test4.Pin = GPIO_PIN_4;
	test4.Pull = GPIO_PULLDOWN;
	test4.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &test4);
	HAL_NVIC_SetPriority(EXTI4_IRQn, 2U, 0U);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	//set external interrupt END
	
	main_interface(paintTime);
	
  while (1) {
		HAL_Delay(1000);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	testFlag = 1;
	//Debug_test("CALLBACK");
	switch (GPIO_Pin)
	{
		case GPIO_PIN_0:
			function_select_interface();
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
			break;
		case GPIO_PIN_1:
			Debug_test("PD1");
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
			break;
		case GPIO_PIN_3:
			white_washed();
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
			break;
		case GPIO_PIN_4:
			Debug_test("PD4");
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
			break;
		default:
			Debug_test("default");
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
			break;
	}
}
	
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while(1) {
			printf("_Error_Handler\r\n");
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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

