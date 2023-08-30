#ifndef __VARIABLE_H
#define __VARIABLE_H
#include "main.h"

#include "LED7SEG.h"
#include "DS3231.h"
//#include "DS18B20.h"
#include "DHT.h"
#include "CLCD_I2C.h"
#include "IR.h"
#include "HEATER.h"
#include "FAN.h"
#include "BUZZER.h"
#include "BUTTON.h"
#include "delay_timer.h"

typedef enum
{
	TEMP_SETTING = 0,
	HUMI_SETTING,
	TIME_ROTATE_SETTING,
	TIME_COMPL_SETTING,
}SETTING_POINTER;


typedef enum
{
	TEMP = 0,
	HUMI,
	TIME,
	DATE,
}RUN_POINTER;

typedef enum
{
	BUTTON_TEST = 0,
	DHT_TEST,
	DS3231_TEST,
	FLASH_TEST,
	LED7_TEST,
	FAN_TEST,
	HEATER_TEST,
	BUZZ_TEST,
	SAVE_SETTING_TEST,
}TEST_POINTER;


typedef enum
{
	RUN=0,
	SETTING,
	TEST,
}MACHINE_MODE;

typedef enum 
{
	IDLE = 0,
	BT_MODE,
	BT_UP,
	BT_DOWN,
	BT_ENTER,
}BT_STATUS;

extern BT_STATUS bt_press;
extern RUN_POINTER pointer_run;
extern MACHINE_MODE mode; 

extern DS3231_Name DS3231;
extern DHT_Name DHT;
extern CLCD_I2C_Name LCD1602;
extern BUZZER_Name BUZZER;
extern FAN_Name FAN;
extern HEATER_Name HEATER;
extern IR_Name IR;

extern uint8_t button_count;

void hardware_init(void);
void button_scan(void);
void sensor_read(void);
void sensor_handle(void);
void led7_display(void);
void save_setting(void);
void button_handle(void);
void IR_handle(void);

void LED7_Test(void);
void DHT_Test(void);

#endif