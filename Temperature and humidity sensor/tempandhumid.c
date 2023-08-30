#include "tempandhumid.h"
#include "main.h"
#include "stdio.h"
#include "string.h"

void send_number(uint8_t number)
{
	char str[5]="";
	uint16_t d=0;
	uint8_t kq=1;
	if (number==0)
	{
		number+=48;
	}
	else {
		while (kq>0)
		{
			d+=1;
			kq=number/pow(10,d);
		}
		while (d>0)
		{
			str[d-1]=(char) number%10 +48;
			number=number/10;
			d--;
		}
	}
	UART_Write(USART2,str);
}

void tempandhumid(void)
{
	uint16_t u16time;
	uint8_t u8Buff[5];
	uint8_t u8CheckSum;
	uint8_t i;
	uint8_t d=0;
	//char Buff[40];
	
	/*MCU sends out start signal (at least 18 ms to let DHT11 detect the signal) */
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	Delay_Timer2_StandardLibrary_Ms(20);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
	/* Wait until PB12 get value 1 */
	TIM_SetCounter(TIM2,0);
	while (TIM_GetCounter(TIM2)<10)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))
		{
			break;
		}
	}
	u16time=TIM_GetCounter(TIM2);
	if (u16time>=10)
	{
		while (1)
		{}
	}
	
	/* Wait for DHT response (from 20-40 ms) */
	TIM_SetCounter(TIM2,0);
	while (TIM_GetCounter(TIM2)<45)
	{
		if (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))
		{
			break;
		}
	}
	u16time=TIM_GetCounter(TIM2);
	if ((u16time<=5) || (u16time>=45))
	{
		while (1)
		{}
	}
	
	/* DHT sends out response signal and keeps it at least 80us (WAIT UNTIL PB12 GET HIGH) */
	TIM_SetCounter(TIM2,0);
	while (TIM_GetCounter(TIM2)<90)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))
		{
			break;
		}
	}
	u16time=TIM_GetCounter(TIM2);
	if ((u16time<=70) || (u16time>=90))
	{
		while (1)
		{}
	}
	
	/* DHT pulls up votage and keeps it for 80us (WAIT UNTIL PB12 GET LOW) */
	TIM_SetCounter(TIM2,0);
	while (TIM_GetCounter(TIM2)<95)
	{
		if (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))
		{
			break;
		}
	}
	u16time=TIM_GetCounter(TIM2);
	if ((u16time<=75) || (u16time>=95))
	{
		while (1)
		{}
	}
	
/*********************************************************SEND DATA*************************************************************/
	/* DHT11 will send 5 bytes data, which is in order of:
		1 - Byte value of humidity
		2 - decimal part of humidity's value 
		3 - Byte value of temperature
		4 - decimal part of temperature's value
		5 - Byte Parity which is used to check tha data
	*/	
/*-----------------------------------------------------------------------------------------------------------------*/
	
	/*Recieve 5 byte*/
	while (d<5)
	{
		u8Buff[d]=0;
		for (i=0;i<8;i++)
		{
			/* Wait for PB12 get high */
			TIM_SetCounter(TIM2,0);
			while (TIM_GetCounter(TIM2)<65)
			{
				if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))
				{
					break;
				}
			}
			u16time=TIM_GetCounter(TIM2);
			if ((u16time<=45) || (u16time>=65))
			{
				while (1)
				{}
			}
			
			/* Wait for PB12 get LOW */
			TIM_SetCounter(TIM2,0);
			while (TIM_GetCounter(TIM2)<80)
			{
				if (!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))
				{
					break;
				}
			}
			u16time=TIM_GetCounter(TIM2);
			if ((u16time<=10) || (u16time>=80))
			{
				while (1)
				{}
			}
			
	/*---------------------------------------------------*/
			u8Buff[d]<<=1;
			/*check that value = 0 or = 1*/
			if (u16time>45){
				/*nhan duoc bit 1*/
				//Buff[i+8*d]='1';
				u8Buff[d]|=1;
			}
			else {
				/*nhan duoc bit 0*/
				u8Buff[d] &= ~1;
				//Buff[i+8*d]='0';
			}
	/*---------------------------------------------------*/
			/*if (u16time>45){
				Buff[i+8*d]='1';
				u8Buff[d]+=2^(7-i);
			}
			else {
				Buff[i+8*d]='0';
			}
			*/
		}
		d++;
	}
	
	/*Kiem tra xem co dung du lieu hay khong bang cach so sanh byte parity voi 4 byte dau*/
	u8CheckSum=u8Buff[0]+u8Buff[1]+u8Buff[2]+u8Buff[3];
	if (u8CheckSum!=u8Buff[4]){
		while(1)
		{}
	}
	//USART_SendData(USART2,u8Buff[2]);
	//Send_data_measure(u8Buff);
	//send_number((uint8_t)u8Buff[0]);
	Send_data_measure(u8Buff);
	Delay_Timer2_StandardLibrary_Ms(500);
}

/*
current
00110011 00000000 00011100 00000101 01010100
00110011 00000000 00011011 00000101 01010011
then
*/


/*send data of humidity and temperature through USART*/
void Send_data_measure(uint8_t u8Buff[5])
{
	/*HUMIDITY*/
	UART_Write(USART2,"HUMIDITY:\t");
	Delay_Timer2_StandardLibrary_Ms(2);
	send_number((uint8_t)u8Buff[0]);
	Delay_Timer2_StandardLibrary_Ms(2);
	UART_Write(USART2,"%\n");
	Delay_Timer2_StandardLibrary_Ms(2);
	
	/*TEMPERATURE*/
	UART_Write(USART2,"TEMPERATURE:\t");
	Delay_Timer2_StandardLibrary_Ms(2);
	send_number((uint8_t)u8Buff[2]);
	Delay_Timer2_StandardLibrary_Ms(2);
	UART_Write(USART2," DO C\n");
	Delay_Timer2_StandardLibrary_Ms(2);
}
