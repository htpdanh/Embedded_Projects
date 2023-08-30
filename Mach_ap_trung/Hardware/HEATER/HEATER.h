/******************************************************************************************************************
@File:  	HEATER Module
@Author:  Khue Nguyen
@Website: khuenguyencreator.com
@Youtube: https://www.youtube.com/channel/UCt8cFnPOaHrQXWmVkk-lfvg
Huong dan su dung:
- Su dung thu vien HAL
- Khoi tao Timer cho Heater
- Khoi tao bien luu Heater
HEATER_Name Heater;
- Khoi tao DS3231 do:
HEATER_Init(&HEATER, &htim2, TIM_CHANEL_1);
- Su dung cac ham dieu khien % PWM
HEATER_PWM(&HEATER, 80);

******************************************************************************************************************/
#ifndef __HEATER_H
#define __HEATER_H

#include "stm32f1xx_hal.h"
typedef struct
{
	TIM_HandleTypeDef* Timer;
	uint32_t Channel;
}HEATER_Name;

void HEATER_Init(HEATER_Name* HEATER, TIM_HandleTypeDef* Timer, uint32_t Channel);
void HEATER_PWM(HEATER_Name* HEATER, uint8_t percent); //0-100%

#endif