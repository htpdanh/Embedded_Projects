#include "BUZZER.h"

void BUZZER_Init(BUZZER_Name* BUZZER, GPIO_TypeDef* BUZZER_PORT, uint16_t BUZZER_Pin)
{
	BUZZER->BUZZER_PORT = BUZZER_PORT;
	BUZZER->Pin = BUZZER_Pin;
}	
void BUZZER_BEEP(BUZZER_Name* BUZZER, uint32_t time, uint8_t repeat)
{
	//HAL_GetTick();
	while (repeat>0)
	{
		HAL_GPIO_WritePin(BUZZER->BUZZER_PORT, BUZZER->Pin, 1);
		HAL_Delay(time);
		HAL_GPIO_WritePin(BUZZER->BUZZER_PORT, BUZZER->Pin, 0);
		HAL_Delay(time);
		repeat--;
	}
	
}