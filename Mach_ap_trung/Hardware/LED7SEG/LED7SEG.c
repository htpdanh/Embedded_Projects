#include "LED7SEG.h"

#define Led7Type ANODE
//#define Led7Type CATHODE


#define H_Pin GPIO_PIN_15
#define H_GPIO_Port GPIOC
#define A_Pin GPIO_PIN_4
#define A_GPIO_Port GPIOA
#define B_Pin GPIO_PIN_5
#define B_GPIO_Port GPIOA
#define C_Pin GPIO_PIN_6
#define C_GPIO_Port GPIOA
#define D_Pin GPIO_PIN_7
#define D_GPIO_Port GPIOA
#define F_Pin GPIO_PIN_10
#define F_GPIO_Port GPIOB
#define G_Pin GPIO_PIN_12
#define G_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_8
#define E_GPIO_Port GPIOA

#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_0
#define LED3_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_1
#define LED4_GPIO_Port GPIOB

char AnodeNumber[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x80}; //0 - 9,dp
char CathodeNumber[] = {0x3F,0x06,0x5B,0x40,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x7F}; //0 - 9,dp


void LED7SEG_WriteOneNumber(uint8_t number)
{
	if(Led7Type == ANODE)
	{
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, AnodeNumber[number]&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, AnodeNumber[number]&0x02?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, AnodeNumber[number]&0x04?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, AnodeNumber[number]&0x08?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, AnodeNumber[number]&0x10?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, AnodeNumber[number]&0x20?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, AnodeNumber[number]&0x40?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(H_GPIO_Port, H_Pin, AnodeNumber[number]&0x80?GPIO_PIN_SET:GPIO_PIN_RESET);
	}
	else if(Led7Type == CATHODE)
	{
		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, CathodeNumber[number]&0x01?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, CathodeNumber[number]&0x02?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, CathodeNumber[number]&0x04?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, CathodeNumber[number]&0x08?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, CathodeNumber[number]&0x10?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, CathodeNumber[number]&0x20?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, CathodeNumber[number]&0x40?GPIO_PIN_SET:GPIO_PIN_RESET);
		HAL_GPIO_WritePin(H_GPIO_Port, H_Pin, CathodeNumber[number]&0x80?GPIO_PIN_SET:GPIO_PIN_RESET);
	}
}

LED7SEG_NumberInt LED7SEG_ConvertInt(uint32_t number) //12345
{
	LED7SEG_NumberInt numberInt;
	numberInt.Thousands = number/1000; // 1
	numberInt.Hundreds = (number%1000)/100; //2
	numberInt.Dozens = (((number%10000)%1000)%100)/10; //3
	numberInt.Uints = (((number%10000)%1000)%100)%10; //4
	return numberInt;
}

void LED7SEG_STATE (GPIO_PinState LED1_State, GPIO_PinState LED2_State, GPIO_PinState LED3_State, GPIO_PinState LED4_State)
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED1_State);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED2_State);
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED3_State);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED4_State);
}

uint8_t count = 0;
LED7SEG_NumberInt number_convert;

void LED7SEG_Scan4Led(uint16_t number)
{
	if(count == 0)
	{	
		number_convert = LED7SEG_ConvertInt(number);
		
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
		LED7SEG_WriteOneNumber(number_convert.Thousands);
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		count++;
	}
	if(count == 1)
	{	
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		LED7SEG_WriteOneNumber(number_convert.Hundreds);
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		count++;
	}
	if(count == 2)
	{	
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		LED7SEG_WriteOneNumber(number_convert.Dozens);
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
		count++;
	}
	if(count == 3)
	{	
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
		LED7SEG_WriteOneNumber(number_convert.Uints);
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
		count++;
	}
	if(count > 3) 
	{	
		count = 0;
	}	
}	

void LED7SEG_Scan4Led2(uint16_t number) {
	number_convert = LED7SEG_ConvertInt(number);
	
	LED7SEG_STATE(GPIO_PIN_SET,GPIO_PIN_RESET,GPIO_PIN_RESET,GPIO_PIN_RESET);
	LED7SEG_WriteOneNumber(number_convert.Thousands);
	
	LED7SEG_STATE(GPIO_PIN_RESET,GPIO_PIN_SET,GPIO_PIN_RESET,GPIO_PIN_RESET);
	LED7SEG_WriteOneNumber(number_convert.Hundreds);
	
	LED7SEG_STATE(GPIO_PIN_RESET,GPIO_PIN_RESET,GPIO_PIN_SET,GPIO_PIN_RESET);
	LED7SEG_WriteOneNumber(number_convert.Dozens);
	
	LED7SEG_STATE(GPIO_PIN_RESET,GPIO_PIN_RESET,GPIO_PIN_RESET,GPIO_PIN_SET);
	LED7SEG_WriteOneNumber(number_convert.Uints);
}

	