/******************************************************************************************************************
@File:  	BUZZER Module
@Author:  Khue Nguyen
@Website: khuenguyencreator.com
@Youtube: https://www.youtube.com/channel/UCt8cFnPOaHrQXWmVkk-lfvg
Huong dan su dung:
- Su dung thu vien HAL
- Khoi tao Timer cho BUZZER
- Khoi tao bien luu BUZZER
BUZZER_Name BUZZER;
- Khoi tao BUZZER do:
BUZZER_Init(&BUZZER, &htim2, TIM_CHANEL_1);
- Su dung ham dieu khien %
FAN_PWM(&FAN, 80);

******************************************************************************************************************/
#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f1xx_hal.h"

typedef struct
{
	uint16_t Pin;
	GPIO_TypeDef* BUZZER_PORT;
}BUZZER_Name;


void BUZZER_Init(BUZZER_Name* BUZZER, GPIO_TypeDef* BUZZER_PORT, uint16_t BUZZER_Pin);
void BUZZER_BEEP(BUZZER_Name* BUZZER, uint32_t time, uint8_t repeat);
#endif