#include "main.h"
void SystemClock_Config(void); 
static void MX_TIM7_Init(void);
void MX_GPIO_Init(void);
TIM_HandleTypeDef htim7;

int press_flag = 0;//
int press_status = 0;

void (*current_operation_index)();

int main(void)
{
	HAL_Init();			  // 
	SystemClock_Config(); // 
	MX_GPIO_Init();
	MX_SPI1_Init();
	delay_init(150);

	Lcd_Init();
	MX_TIM7_Init();
	__HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&htim7);

	uint8_t func_index = 0;
	uint8_t last_index = 2;
	//int test_flag = 0;
	key_table table[30] =
		{
			{0, 0, 0, 1, 0, (*fun_0)}, /*0*/
			// ��1��
			{1, 1, 2, 3, 0, (*fun_a1)}, /*1*/
			{2, 1, 2, 4, 0, (*fun_b1)}, /*2*/
			// ��2��
			{3, 3, 3, 3, 1, (*fun_control)}, /*3*/
			{4, 4, 4, 4, 2, (*fun_set)}};	 /*4*/
	Lcd_Clear(WHITE);

	while (1)
	{
		//test_flag +=1;
		if ((KEYS_PUSHING0 == KEYON) || (KEYS_PUSHING1 == KEYON) || (KEYS_PUSHING2 == KEYON) || (KEYS_PUSHING3 == KEYON))
		{
			//HAL_Delay(5); // ����
			//if(press_flag == 1)
			//{
				delay_ms(20);
				if (KEYS_PUSHING0)
				{
					func_index = table[func_index].up; // ���Ϸ�
					while (KEYS_PUSHING0)
					{
					}
				}
				if (KEYS_PUSHING1)
				{
					func_index = table[func_index].down; // ���·�
					while (KEYS_PUSHING1)
					{
					}
				}
				if (KEYS_PUSHING2)
				{
					func_index = table[func_index].enter; // ȷ��
					while (KEYS_PUSHING2)
					{
					}
				}
				if (KEYS_PUSHING3)
				{
					func_index = table[func_index].back; // ����
					while (KEYS_PUSHING3)
					{
					}
				}
				//press_flag = 0;
			//}
		}
		if (func_index != last_index)
		{
			current_operation_index = table[func_index].current_operation;

			(*current_operation_index)(); // ִ�е�ǰ��������
			if (*current_operation_index == fun_control)
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


static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;//��ʱ����ʱƵ��=ʱ��ԴƵ��/ [(PSC+1)(ARR+1)]=170M/[(71+1)(999+1)]=1000Hz�����Զ�ʱ��ʱ��Ϊ1ms.
  htim7.Init.Prescaler = 849;//PSC
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 199;//ARR
  //htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
 // if (htim->Instance == TIM7) 
  if (htim->Instance == htim7.Instance)

  {
	
	if(press_status == 0)
	{
		if ((KEYS_PUSHING0 == KEYON) || (KEYS_PUSHING1 == KEYON) || (KEYS_PUSHING2 == KEYON) || (KEYS_PUSHING3 == KEYON))
		{
			press_status = 1;
		}
	}
	else if(press_status == 1)
	{
		if ((KEYS_PUSHING0 == KEYON) || (KEYS_PUSHING1 == KEYON) || (KEYS_PUSHING2 == KEYON) || (KEYS_PUSHING3 == KEYON))
		{
			press_flag = 1;
			press_status = 2;
		}
		else
		{
			press_status = 0;

		}
	}
	else
	{
		if ((KEYS_PUSHING0 == KEYOFF) || (KEYS_PUSHING1 == KEYOFF) || (KEYS_PUSHING2 == KEYOFF) || (KEYS_PUSHING3 == KEYOFF))
		{
			press_status = 0;
		}
	}
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin == GPIO_PIN_0)  // 假设使用PA0作为触发中断的引脚
   {
		Lcd_Clear(WHITE);
       // do something when the external interrupt event occurs
   }
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
