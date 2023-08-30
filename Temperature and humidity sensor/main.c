#include "main.h"
#include "tempandhumid.h"

/* 	1- set up chan PB12 o dang OUT_PP_OD
		2- DOC DATASHEET CUA DHT11 VA FOLOWS THEO PROCEDURE
*/

int main ()
{
	GPIO_Config();
	Timer2_StandardLibrary();
	Uart_Init();
	while (1)
	{
		//send_number(70);
		//UART_Write(USART2,"dmmm");
		//USART_SendData(USART2,kq+48);
		tempandhumid();
		/*da doc duoc nhiet do va do am*/
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		Delay_Timer2_StandardLibrary_Ms(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		Delay_Timer2_StandardLibrary_Ms(500);
	}
}


