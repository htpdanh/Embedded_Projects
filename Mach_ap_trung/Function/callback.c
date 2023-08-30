#include "main.h"
#include "variable.h"

//uint32_t time_display_count=0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) //1ms
{
	if (htim->Instance == TIM3 && mode == RUN)
	{
		pointer_run++;
		if (pointer_run > 3)
		{
			pointer_run = 0;
		}
	}
}

uint32_t button_timout =0;
uint32_t pre_button_timout =0;

BT_STATUS bt_press;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_0) 
	{
		button_timout = HAL_GetTick();
		if (button_timout - pre_button_timout > 200)
		{
			pre_button_timout = button_timout;
			bt_press = BT_MODE;
		}
	}
	else if (GPIO_Pin == GPIO_PIN_1)
	{
		button_timout = HAL_GetTick();
		if (button_timout - pre_button_timout > 200)
		{
			pre_button_timout = button_timout;
			bt_press = BT_UP;
		}		
	}
	else if (GPIO_Pin == GPIO_PIN_2)
	{
		button_timout = HAL_GetTick();
		if (button_timout - pre_button_timout > 200)
		{
			pre_button_timout = button_timout;
			bt_press = BT_DOWN;
		}	
	}
	else if (GPIO_Pin == GPIO_PIN_3)
	{
		button_timout = HAL_GetTick();
		if (button_timout - pre_button_timout > 200)
		{
			pre_button_timout = button_timout;
			bt_press = BT_ENTER;
		}			
	}
}

