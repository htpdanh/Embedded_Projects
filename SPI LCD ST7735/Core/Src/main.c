/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ST7735_SPI.h"
#include "fonts.h"
#include "DS3231.h"
#include "stdio.h"
#include "string.h"
//#include "clock.h"
//#include "bitmap.h"
//#include "horse_anim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct{
	char Date[10];
	char Day[10];
	char Month[10];
	char Year[10];
	char Second[10];
	char Minute[10];
	char Hours[10];
} TFT_LCD_SHOW;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
DS3231_Name DS3231;
TFT_LCD_SHOW LCD_DS3231;

char *DayOfWeek[]={"MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SARTURDAY","SUNDAY"};
uint8_t Date_previous=0;
uint8_t Date_check=0;
uint32_t CurrentMillis = 0;
uint32_t PreviousMillis = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM4_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void GetDate(){
	DS3231_GetDate(&DS3231);
	if (Date_previous!=DS3231.Date) {
		Date_previous=DS3231.Date;
		Date_check=1;
	}
	if (DS3231.Date<10) sprintf(LCD_DS3231.Date,"0%d",DS3231.Date);
	else sprintf(LCD_DS3231.Date,"%d",DS3231.Date);
	if (DS3231.Month<10) sprintf(LCD_DS3231.Month,"/0%d",DS3231.Month);
	else sprintf(LCD_DS3231.Month,"/%d",DS3231.Month);
	if (DS3231.Year<10) sprintf(LCD_DS3231.Year,"/200%d",DS3231.Year);
	else sprintf(LCD_DS3231.Year,"/20%d",DS3231.Year);
}

void GetTime(){
	DS3231_GetDate(&DS3231);
	DS3231_GetTime(&DS3231);
	if (DS3231.Sec<10) sprintf(LCD_DS3231.Second,":0%d",DS3231.Sec);
	else sprintf(LCD_DS3231.Second,":%d",DS3231.Sec);
	if (DS3231.Min<10) sprintf(LCD_DS3231.Minute,":0%d",DS3231.Min);
	else sprintf(LCD_DS3231.Minute,":%d",DS3231.Min);
	if (DS3231.Hours<10) sprintf(LCD_DS3231.Hours,"0%d",DS3231.Hours);
	else sprintf(LCD_DS3231.Hours,"%d",DS3231.Hours);
}

void Draw_Screen_Frame(){
	ST7735_FillScreen(ST7735_BLACK);
	drawRect(0,0,159,80,ST7735_WHITE);
	ST7735_FillRectangle(0,0,17,80,ST7735_WHITE);
	ST7735_WriteString(5, 15, "L", Font_7x10, ST7735_CYAN, ST7735_BLACK);
	ST7735_WriteString(5, 25, "O", Font_7x10, ST7735_CYAN, ST7735_BLACK);
	ST7735_WriteString(5, 35, "C", Font_7x10, ST7735_CYAN, ST7735_BLACK);
	ST7735_WriteString(5, 45, "A", Font_7x10, ST7735_CYAN, ST7735_BLACK);
	ST7735_WriteString(5, 55, "L", Font_7x10, ST7735_CYAN, ST7735_BLACK);
}
//142 - 
void Draw_Screen_DayofWeek(){
	uint8_t x_pos;
	ST7735_FillRectangle(30,4,128,22,ST7735_BLACK);
	x_pos = 17+(142-strlen(DayOfWeek[DS3231.Day])*11)/2;
	ST7735_WriteString(x_pos, 4,DayOfWeek[DS3231.Day], Font_11x18, ST7735_CYAN, ST7735_BLACK);
}

void Draw_Screen_DateAYear(){
	ST7735_WriteString(33, 27,LCD_DS3231.Date, Font_11x18, ST7735_YELLOW, ST7735_BLACK);
	ST7735_WriteString(55, 27,LCD_DS3231.Month, Font_11x18, ST7735_YELLOW, ST7735_BLACK);
	ST7735_WriteString(88, 27,LCD_DS3231.Year, Font_11x18, ST7735_YELLOW, ST7735_BLACK);
}
void Draw_Screen_Time(){
	ST7735_WriteString(31, 50,LCD_DS3231.Hours, Font_16x26, ST7735_WHITE, ST7735_BLACK);
	ST7735_WriteString(63, 50,LCD_DS3231.Minute, Font_16x26, ST7735_WHITE, ST7735_BLACK);
	ST7735_WriteString(111, 56,LCD_DS3231.Second, Font_11x18, ST7735_WHITE, ST7735_BLACK);
}

void Screen_Init(){
	//DS3231_SetDate(&DS3231,4,27,4,23);
	//DS3231_SetTime(&DS3231,20,13,15);
	Draw_Screen_Frame();
	Draw_Screen_Time();
	Draw_Screen_DateAYear();
	Draw_Screen_DayofWeek();
}

void Screen_show(){
	GetDate();
	CurrentMillis = HAL_GetTick();
	if (CurrentMillis-PreviousMillis>=1000){
		GetTime();
		Draw_Screen_Time();
		PreviousMillis=CurrentMillis;
	}
	if (Date_check) {
		Draw_Screen_DateAYear();
		Draw_Screen_DayofWeek();
		Date_check=0;
	}
	ST7735_WriteString(50, 90,"~DH~", Font_16x26, ST7735_WHITE, ST7735_BLACK);
}
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
  MX_SPI1_Init();
  MX_TIM4_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	ST7735_Init();
	DS3231_Init(&DS3231,&hi2c1);
	Screen_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		Screen_show();
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
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
  htim4.Init.Prescaler = 8000-1;
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin */
  GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
