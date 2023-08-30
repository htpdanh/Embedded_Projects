#ifndef __IR_H
#define __IR_H

#include "stm32f1xx_hal.h"

#define START_TIME_MAX 15000
#define START_TIME_MIN 12000
#define COMMAND_0  1500

#define IR_UP 0x18
#define IR_DOWN 0x4A
#define IR_ENTER 0x38
#define IR_MODE 0x68

typedef struct
{	
	uint8_t command;
	TIM_HandleTypeDef* Timer;
	uint32_t Channel;
	uint8_t flag_ReadDone;
}IR_Name;

void IR_Init(IR_Name* IR, TIM_HandleTypeDef* Timer, uint32_t Channel);
void IR_ReadCode(IR_Name* IR);
#endif