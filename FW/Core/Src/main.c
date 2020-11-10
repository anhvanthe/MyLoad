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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
#include "stdlib.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_SPI1_Init(void);
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
	tick_timer_t tick;
	Tick_Timer_Reset(tick);
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
  MX_TIM4_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	
	Tick_Timer_Init();
	
	ILI9341_Init();
	
	HAL_Delay(2000);
//	ILI9341_Fill_Screen(WHITE);
//	ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
//	ILI9341_Draw_Text("FPS TEST, 40 loop 2 screens", 10, 10, BLACK, 1, WHITE);
//	HAL_Delay(2000);
	ILI9341_Fill_Screen(WHITE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		if(Tick_Timer_Is_Over_Ms(tick,500))
			HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		
		ILI9341_Fill_Screen(BLACK);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("FPS TEST, 40 loop 2 screens", 10, 10, RED, 2, BLACK);
		HAL_Delay(5000);
		
		static uint16_t x = 0;
		static uint16_t y = 0;
		
		char Temp_Buffer_text[40];
		
//----------------------------------------------------------COUNTING MULTIPLE SEGMENTS		
		ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Counting multiple segments at once", 10, 10, BLACK, 2, WHITE);
		HAL_Delay(2000);
		ILI9341_Fill_Screen(WHITE);
		
		
		for(uint16_t i = 0; i <= 10; i++)
		{
		sprintf(Temp_Buffer_text, "Counting: %d", i);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 10, BLACK, 2, WHITE);		
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 30, BLUE, 2, WHITE);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 50, RED, 2, WHITE);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 70, GREEN, 2, WHITE);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 90, BLACK, 2, WHITE);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 110, BLUE, 2, WHITE);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 130, RED, 2, WHITE);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 150, GREEN, 2, WHITE);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 170, WHITE, 2, BLACK);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 190, BLUE, 2, BLACK);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 210, RED, 2, BLACK);		
		}
		
		HAL_Delay(1000);

//----------------------------------------------------------COUNTING SINGLE SEGMENT		
		ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Counting single segment", 10, 10, BLACK, 2, WHITE);
		HAL_Delay(2000);
		ILI9341_Fill_Screen(WHITE);
	
		for(uint16_t i = 0; i <= 100; i++)
		{
		sprintf(Temp_Buffer_text, "Counting: %d", i);
		ILI9341_Draw_Text(Temp_Buffer_text, 10, 10, BLACK, 3, WHITE);			
		}
		
		HAL_Delay(1000);
		
//----------------------------------------------------------ALIGNMENT TEST
		ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Rectangle alignment check", 10, 10, BLACK, 1, WHITE);
		HAL_Delay(2000);
		ILI9341_Fill_Screen(WHITE);
		
		ILI9341_Draw_Hollow_Rectangle_Coord(50, 50, 100, 100, BLACK);
		ILI9341_Draw_Filled_Rectangle_Coord(20, 20, 50, 50, BLACK);
		ILI9341_Draw_Hollow_Rectangle_Coord(10, 10, 19, 19, BLACK);
		HAL_Delay(1000);
		
		ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
		ILI9341_Draw_Text("Circles", 10, 20, BLACK, 1, WHITE);
		HAL_Delay(2000);
		ILI9341_Fill_Screen(WHITE);		
		
		
		for(uint32_t i = 0; i < 3000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			uint16_t radiusr = 0;
			uint16_t colourr = 0;
			random_num = abs(rand());
			xr = random_num;
			random_num =  abs(rand());
			yr = random_num;
			random_num =  abs(rand());
			radiusr = random_num;
			random_num =  abs(rand());
			colourr = random_num;
			
			xr &= 0x01FF;
			yr &= 0x01FF;
			radiusr &= 0x001F;			
			//ili9341_drawpixel(xr, yr, WHITE);
			ILI9341_Draw_Hollow_Circle(xr, yr, radiusr*2, colourr);
			HAL_Delay(1);
		}
		HAL_Delay(1000);
		
//----------------------------------------------------------FILLED CIRCLES EXAMPLE		
		ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
		ILI9341_Draw_Text("Filled Circles", 10, 20, BLACK, 1, WHITE);
		HAL_Delay(2000);
		ILI9341_Fill_Screen(WHITE);
		
		for(uint32_t i = 0; i < 1000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			uint16_t radiusr = 0;
			uint16_t colourr = 0;
			random_num = abs(rand());
			xr = random_num;
			random_num = abs(rand());
			yr = random_num;
			random_num = abs(rand());
			radiusr = random_num;
			random_num = abs(rand());
			colourr = random_num;
			
			xr &= 0x01FF;
			yr &= 0x01FF;
			radiusr &= 0x001F;			
			//ili9341_drawpixel(xr, yr, WHITE);
			ILI9341_Draw_Filled_Circle(xr, yr, radiusr/2, colourr);
			HAL_Delay(1);
		}
		HAL_Delay(1000);

//----------------------------------------------------------HOLLOW RECTANGLES EXAMPLE		
	ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
		ILI9341_Draw_Text("Rectangles", 10, 20, BLACK, 1, WHITE);
		HAL_Delay(2000);
		ILI9341_Fill_Screen(WHITE);
		
		for(uint32_t i = 0; i < 1000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			uint16_t radiusr = 0;
			uint16_t colourr = 0;
			random_num = abs(rand());
			xr = random_num;
			random_num = abs(rand());
			yr = random_num;
			random_num = abs(rand());
			radiusr = random_num;
			random_num = abs(rand());
			colourr = random_num;
			
			xr &= 0x01FF;
			yr &= 0x01FF;
			radiusr &= 0x001F;			
			//ili9341_drawpixel(xr, yr, WHITE);
			ILI9341_Draw_Hollow_Rectangle_Coord(xr, yr, xr+radiusr, yr+radiusr, colourr);
			HAL_Delay(1);
		}
		HAL_Delay(1000);
		
		//----------------------------------------------------------FILLED RECTANGLES EXAMPLE		
		ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
		ILI9341_Draw_Text("Filled Rectangles", 10, 20, BLACK, 1, WHITE);
		HAL_Delay(2000);
		ILI9341_Fill_Screen(WHITE);
		
		for(uint32_t i = 0; i < 1000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			uint16_t radiusr = 0;
			uint16_t colourr = 0;
			random_num = abs(rand());
			xr = random_num;
			random_num = abs(rand());
			yr = random_num;
			random_num = abs(rand());
			radiusr = random_num;
			random_num = abs(rand());
			colourr = random_num;
			
			xr &= 0x01FF;
			yr &= 0x01FF;
			radiusr &= 0x001F;			
			//ili9341_drawpixel(xr, yr, WHITE);
			ILI9341_Draw_Rectangle(xr, yr, radiusr, radiusr, colourr);
			HAL_Delay(1);
		}
		HAL_Delay(1000);
		
		//----------------------------------------------------------INDIVIDUAL PIXEL EXAMPLE		
		
		ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Slow draw by selecting", 10, 10, BLACK, 1, WHITE);
		ILI9341_Draw_Text("and adressing pixels", 10, 20, BLACK, 1, WHITE);
		HAL_Delay(2000);
		ILI9341_Fill_Screen(WHITE);
			
		
		x = 0;
		y = 0;	
		while (y < 240)
		{
		while ((x < 320) && (y < 240))
		{
			
			if(x % 2)
			{
				ILI9341_Draw_Pixel(x, y, BLACK);
			}
			
			x++;
		}
		
			y++;
			x = 0;
		}
		
		x = 0;
		y = 0;	

		
		while (y < 240)
		{
		while ((x < 320) && (y < 240))
		{
			
			if(y % 2)
			{
				ILI9341_Draw_Pixel(x, y, BLACK);
			}
			
			x++;
		}
		
			y++;
			x = 0;
		}
		HAL_Delay(2000);
		
//----------------------------------------------------------INDIVIDUAL PIXEL EXAMPLE		
		ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Random position and colour", 10, 10, BLACK, 1, WHITE);
		ILI9341_Draw_Text("500000 pixels", 10, 20, BLACK, 1, WHITE);
		HAL_Delay(2000);
		ILI9341_Fill_Screen(WHITE);	
		
				
		for(uint32_t i = 0; i < 500000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			random_num = abs(rand());
			xr = random_num;
			random_num = abs(rand());
			yr = random_num;
			uint16_t color = abs(rand());
			
			xr &= 0x01FF;
			yr &= 0x01FF;
			ILI9341_Draw_Pixel(xr, yr, color);
		}
		HAL_Delay(2000);
		
//----------------------------------------------------------565 COLOUR EXAMPLE, Grayscale		
		ILI9341_Fill_Screen(WHITE);
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Draw_Text("Colour gradient", 10, 10, BLACK, 1, WHITE);
		ILI9341_Draw_Text("Grayscale", 10, 20, BLACK, 1, WHITE);
		HAL_Delay(2000);
		
		
		for(uint16_t i = 0; i <= (320); i++)
		{
			uint16_t Red = 0;
			uint16_t Green = 0;
			uint16_t Blue = 0;
			
			Red = i/(10);
			Red <<= 11;
			Green = i/(5);
			Green <<= 5;
			Blue = i/(10);
			
			
			
			uint16_t RGB_color = Red + Green + Blue;
			ILI9341_Draw_Rectangle(i, x, 1, 240, RGB_color);
			
		}
		HAL_Delay(2000);

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

  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Initializes the CPU, AHB and APB busses clocks 
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

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 71;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DC_Pin|RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_Pin */
  GPIO_InitStruct.Pin = CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DC_Pin RST_Pin */
  GPIO_InitStruct.Pin = DC_Pin|RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

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
