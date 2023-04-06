#include "main.h"

void (*current_operation_index)();

int main(void)
{
	HAL_Init();			  // 初始化HAL库
	SystemClock_Config(); // 设置时钟
	MX_GPIO_Init();
	MX_SPI1_Init();
	Lcd_Init();
	uint8_t func_index = 0;
	uint8_t last_index = 2;
	key_table table[30] =
		{
			{0, 0, 0, 1, 0, (*fun_0)}, /*0*/
			// 第1层
			{1, 1, 2, 3, 0, (*fun_a1)}, /*1*/
			{2, 1, 2, 4, 0, (*fun_b1)}, /*2*/
			// 第2层
			{3, 3, 3, 3, 1, (*fun_mine)}, /*3*/
			{4, 4, 4, 4, 2, (*fun_set)}}; /*4*/
	Lcd_Clear(WHITE);
	while (1)
	{
		if ((KEYS_PUSHING0 == KEYON) || (KEYS_PUSHING1 == KEYON) || (KEYS_PUSHING2 == KEYON) || (KEYS_PUSHING3 == KEYON))
		{
			HAL_Delay(5); // 消抖
			if (KEYS_PUSHING0)
			{
				func_index = table[func_index].up; // 向上翻
				while (KEYS_PUSHING0)
				{
				}
			}
			if (KEYS_PUSHING1)
			{
				func_index = table[func_index].down; // 向下翻
				while (KEYS_PUSHING1)
				{
				}
			}
			if (KEYS_PUSHING2)
			{
				func_index = table[func_index].enter; // 确认
				while (KEYS_PUSHING2)
				{
				}
			}
			if (KEYS_PUSHING3)
			{
				func_index = table[func_index].back; // 返回
				while (KEYS_PUSHING3)
				{
				}
			}
		}

		if (func_index != last_index)
		{
			current_operation_index = table[func_index].current_operation;

			(*current_operation_index)(); // 执行当前操作函数
			if (*current_operation_index == fun_mine)
			{
				func_index = 1;
				current_operation_index = table[func_index].current_operation;
				(*current_operation_index)();
			}
			if (*current_operation_index == fun_set)
			{
				func_index = 2;
				current_operation_index = table[func_index].current_operation;
				(*current_operation_index)();
			}
			last_index = func_index;
		}
	}
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
	RCC_OscInitStruct.PLL.PLLN = 85;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		Error_Handler();
	}
}

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

#ifdef USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
