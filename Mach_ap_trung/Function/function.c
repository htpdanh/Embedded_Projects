#include "variable.h"
#include "main.h"

DS3231_Name DS3231;
DHT_Name DHT;
CLCD_I2C_Name LCD1602;
IR_Name IR;
FAN_Name FAN;
HEATER_Name HEATER;
BUZZER_Name BUZZER;

MACHINE_MODE mode; //0 run, setting

SETTING_POINTER pointer_setting = 0;
RUN_POINTER pointer_run = 0;
TEST_POINTER pointer_test = 0;
uint8_t temp;
uint8_t temp_setting=25;

uint8_t humi;
uint8_t humi_setting=30;

uint8_t time_rotate = 5; 
uint8_t time_rotate_setting=10; //hours
uint8_t time_cur_rotate;

uint8_t time_complete = 5; 
uint8_t time_complete_setting=10; //hours
uint8_t time_cur_complete;

void LED7_Test(void)
{	
	LED7SEG_Scan4Led(1231);
//	HAL_Delay(500);
//	LED7SEG_Scan4Led(3222);
//	HAL_Delay(500);
//	LED7SEG_Scan4Led(3231);
//	HAL_Delay(500);
}	

void BUTTON_Test(void)
{

}	

void DHT_Test(void)
{
	DHT_ReadTempHum(&DHT);
	if ((uint8_t)DHT.Humi==0 || (uint8_t) DHT.Temp==0)
	{
		BUZZER_BEEP(&BUZZER,100,1);
	}
}

//App Funct
void hardware_init(void)
{
	
}	

void button_scan(void)
{
	
}	

uint8_t button_count = 0;
void button_handle(void)
{
	switch(bt_press)
	{	
		case IDLE:
		{
			//no action
		}	
		break;
		case BT_MODE:
		{
			if(mode == RUN)
			{
				mode = SETTING;
			}				
			else if(mode == SETTING)
			{
				button_count++;
				if (button_count > 7)
				{
					mode = TEST;
					button_count = 0;
				}
				pointer_setting++;
				if(pointer_setting > TIME_COMPL_SETTING) pointer_setting = 0;
			}
			else if (mode == TEST) 
			{
				mode = RUN;
			}
			bt_press = IDLE;			
		}			
		break;
		case BT_UP:
		{
			if(mode == SETTING)
			{
				if(pointer_setting == TEMP_SETTING)
				{
					temp_setting++;
				}
				else if(pointer_setting == HUMI_SETTING)
				{
					humi_setting++;
				}
				else if(pointer_setting == TIME_ROTATE_SETTING)
				{
					time_rotate_setting++;
				}
				else if(pointer_setting == TIME_COMPL_SETTING)
				{
					time_complete_setting++;
				}
			}
			
			if(mode == TEST)
			{
				pointer_test++;
			}	
			bt_press = IDLE;		
		}			
		break;
		case BT_DOWN:
		{
			if(mode == SETTING)
			{
				if(pointer_setting == TEMP_SETTING)
				{
					temp_setting--;
				}
				else if(pointer_setting == HUMI_SETTING)
				{
					humi_setting--;
				}
				else if(pointer_setting == TIME_ROTATE_SETTING)
				{
					time_rotate_setting--;
				}
				else if(pointer_setting == TIME_COMPL_SETTING)
				{
					time_complete_setting--;
				}
			}
			bt_press = IDLE;		
		}			
		break;
		case BT_ENTER:
		{
			if(mode == SETTING)
			{
				mode = RUN;
				save_setting();
				DS3231_SetTime(&DS3231,0,0,0);
				DS3231_SetDate(&DS3231,0,0,0,0);
				button_count = 0;
			}
			bt_press = IDLE;		
		}			
		break;
	}
//	#ifdef DEBUG
//		printf("button handle done");
//	#endif
}

void IR_handle(void)
{
	IR_ReadCode(&IR);
	switch (IR.command)
	{
		case IR_MODE:
			bt_press = BT_MODE;
			IR.command = 0x0;
			break;
		case IR_UP:
			bt_press = BT_UP;
			IR.command = 0x0;
			break;
		case IR_DOWN:
			bt_press = BT_DOWN;
			IR.command = 0x0;
			break;
		case IR_ENTER:
			bt_press = BT_ENTER;
			IR.command = 0x0;
			break;
	}
}

void save_setting(void)
{
	temp = temp_setting;
	humi = humi_setting;
	time_rotate = time_rotate_setting;
	time_complete = time_complete_setting;
	
//	#ifdef DEBUG
//		printf("save setting done");
//	#endif
}	

void sensor_read(void)
{
	DHT_ReadTempHum(&DHT);
	DS3231_GetTime(&DS3231);
	DS3231_GetDate(&DS3231);
//	#ifdef DEBUG
//		printf("sensor read done");
//	#endif
}

void sensor_handle(void)
{
	time_cur_rotate = DS3231.Day*24+DS3231.Hours;
	time_cur_complete = DS3231.Day*24+DS3231.Hours;
	
	if(DHT.Temp > (temp+1)) //error
	{
		FAN_PWM(&FAN, 100);
	} else if(DHT.Temp < temp)
	{
		FAN_PWM(&FAN, 0);
		HEATER_PWM(&HEATER,100);
	}

	if (DHT.Humi < humi) {
		HEATER_PWM(&HEATER,100);
		FAN_PWM(&FAN, 100);
	}
	
	if (DHT.Humi > humi && DHT.Temp > temp)
	{
		HEATER_PWM(&HEATER,0);
	}
	
	if (time_cur_rotate>time_rotate)
	{
		//turn the egg tray
		time_rotate = time_cur_rotate + time_rotate;
	}
	
	if (time_cur_complete>time_complete)
	{
		BUZZER_BEEP(&BUZZER,1000,1);
	}
}

void led7_display(void)
{
	if(mode == RUN)
	{
		if(pointer_run == TEMP)
		{
			LED7SEG_Scan4Led(DHT.Temp);
		}	
		else if(pointer_run == HUMI)
		{
			LED7SEG_Scan4Led(DHT.Humi);
		}
		else if(pointer_run == TIME)
		{
			LED7SEG_Scan4Led(DS3231.Hours*100+DS3231.Min);
		}
		else if(pointer_run == DATE)
		{
			LED7SEG_Scan4Led(DS3231.Day*100 + DS3231.Month);
		}
	}	
	else if(mode == SETTING)
	{
		if(pointer_setting == TEMP_SETTING)
		{
			LED7SEG_Scan4Led(temp_setting);
		}
		else if(pointer_setting == HUMI_SETTING)
		{
			LED7SEG_Scan4Led(humi_setting);
		}		
		else if(pointer_setting == TIME_ROTATE_SETTING)
		{
			LED7SEG_Scan4Led(time_rotate_setting);
		}	
		else if(pointer_setting == TIME_COMPL_SETTING)
		{
			LED7SEG_Scan4Led(time_complete_setting);
		}	
	}
}