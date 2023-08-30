/******************************************************************************************************************
@File:  	FAN Module
@Author:  Khue Nguyen
@Website: khuenguyencreator.com
@Youtube: https://www.youtube.com/channel/UCt8cFnPOaHrQXWmVkk-lfvg
Huong dan su dung:
- Su dung thu vien HAL
- Khoi tao Timer cho FAN
- Khoi tao bien luu FAN
FAN_Name FAN;
- Khoi tao FAN do:
FAN_Init(&FAN, &htim2, TIM_CHANEL_1);
- Su dung ham dieu khien %
FAN_PWM(&FAN, 80);

******************************************************************************************************************/
#ifndef __FAN_H
#define __FAN_H

#include "stm32f1xx_hal.h"
typedef struct
{
	TIM_HandleTypeDef* Timer;
	uint32_t Channel;
}FAN_Name;

void FAN_Init(FAN_Name* FAN, TIM_HandleTypeDef* Timer, uint32_t Channel);

void FAN_PWM(FAN_Name* FAN, uint8_t percent); //0-100%
#endif