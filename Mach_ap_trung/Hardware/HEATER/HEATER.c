#include "HEATER.h"
#define MIN_PERIOD 100
#define MAX_PERIOD 200

#define MIN_PERCENT 0
#define MAX_PERCENT 100

uint32_t map_heater(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void HEATER_Init(HEATER_Name* HEATER, TIM_HandleTypeDef* Timer, uint32_t Channel)
{
	HEATER->Timer = Timer;
	HEATER->Channel = Channel;
	HAL_TIM_PWM_Start(HEATER->Timer, HEATER->Channel);
}

void HEATER_PWM(HEATER_Name* HEATER, uint8_t percent)
{
	uint16_t duty = map_heater(percent, MIN_PERCENT, MAX_PERCENT, MIN_PERIOD, MAX_PERIOD);
	__HAL_TIM_SetCompare(HEATER->Timer,HEATER->Channel, duty);
}