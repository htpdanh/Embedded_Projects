/******************************************************************************************************************
@File:  	IR Sensor Hong ngoai
@Author:  Khue Nguyen
@Website: khuenguyencreator.com
@Youtube: https://www.youtube.com/channel/UCt8cFnPOaHrQXWmVkk-lfvg
Huong dan su dung:
- Su dung thu vien HAL
- Khoi tao bien IR : IR_Name IR;
- Khoi tao chan IR:
	DS18B20_Init(&DS1, &htim4, DS18B20_GPIO_Port, DS18B20_Pin);
- Su dung cac ham phai truyen dia chi cua DS18B20 do: 
	hex code = DS18B20_ReadTemp(&DS1);
******************************************************************************************************************/
#include "IR.h"

uint16_t Time1 = 0;
uint16_t Time2 = 0;
uint16_t Period = 0;

uint8_t counter_hex = 0; 
uint8_t command = 0;
uint32_t hex_ir = 0;
uint8_t flag_ReadDone = 0;

void IR_Init(IR_Name* IR, TIM_HandleTypeDef* Timer, uint32_t Channel)
{
	IR->Timer = Timer;
	IR->Channel = Channel;
	HAL_TIM_IC_Start_IT(IR->Timer, IR->Channel);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{ 
	Time2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
	Period = Time2 - Time1;
	Time1 = Time2;
	
	if(Period < START_TIME_MAX && Period > START_TIME_MIN)
	{	
		hex_ir = 0;
		counter_hex = 0;
	}
	else if(Period > COMMAND_0 && Period < 2500) //bit 1
	{
		hex_ir |=(1<<(31-counter_hex));
		counter_hex++;
	}
	else if(Period < COMMAND_0 && Period > 800) //bit 0
	{
		counter_hex++;
	}	
	
	if(counter_hex == 32) //ghi 32 lan
	{
		command = hex_ir>>8;
		flag_ReadDone = 1;
		counter_hex = 0;
		hex_ir = 0;
	}
}

void IR_ReadCode(IR_Name* IR)
{
	if(flag_ReadDone)
	{	
		flag_ReadDone = 0;
		IR->command = command;
	}
}