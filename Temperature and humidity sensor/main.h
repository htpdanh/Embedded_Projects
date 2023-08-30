#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stdio.h"
#include "string.h"

void GPIO_Config(void);
void Timer2_StandardLibrary(void);
void Delay_Timer2_StandardLibrary_Ms(uint32_t u32Delay);
void Uart_Init(void);
_Bool UART_Write(USART_TypeDef *USARTx, char *str);


void GPIO_Config(void)
{ 
  GPIO_InitTypeDef  GPIO_InitStructure;  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/*Enable led PC13 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	/* Enable PB12 (data of sensor temp & humidity) */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
		
}

void Timer2_StandardLibrary(void)
{
	TIM_TimeBaseInitTypeDef TimerInit;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TimerInit.TIM_CounterMode=TIM_CounterMode_Up;
	TimerInit.TIM_Period=0xFFFF;
	TimerInit.TIM_Prescaler=72-1;
	
	TIM_TimeBaseInit(TIM2,&TimerInit);
	
	TIM_Cmd(TIM2,ENABLE);
}

void Delay_Timer2_StandardLibrary_Ms(uint32_t u32Delay)
{
	while(u32Delay)
	{
		TIM_SetCounter(TIM2,0U);
		while ((TIM_GetCounter(TIM2))<1000U);
		u32Delay--;
	}
}

void Uart_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFIOEN,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART2EN,ENABLE);
	
	GPIO_InitTypeDef  GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	USART_InitTypeDef USART_Config;
	USART_Config.USART_BaudRate=9600;
	USART_Config.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Config.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_Config.USART_Parity=USART_Parity_No;
	USART_Config.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART2,&USART_Config);
	
	USART_Cmd(USART2,ENABLE);
}
_Bool UART_Write(USART_TypeDef *USARTx, char *str)
{
	 /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(str)); 
	
	/* Transmit Data */
	uint8_t i=0;
	if (strlen(str)<1) return 0;
	for (i=0;i < strlen(str);i++)
	{
		USART_SendData(USARTx,str[i]);
		Delay_Timer2_StandardLibrary_Ms(2);
	}
	return 1;
}
