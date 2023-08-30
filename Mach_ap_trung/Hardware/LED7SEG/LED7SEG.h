#ifndef __LED7SEG_H
#define __LED7SEG_H

#include "stm32f1xx_hal.h"

typedef enum
{
  ANODE = 0u,
  CATHODE
} LED7TYPE;

typedef struct {  
	uint8_t TenOfThousands;
	uint8_t Thousands;
	uint8_t Hundreds;
	uint8_t Dozens;
	uint8_t Uints;
}LED7SEG_NumberInt;


void LED7SEG_WriteOneNumber(uint8_t number);
LED7SEG_NumberInt LED7SEG_ConvertInt(uint32_t number);
void LED7SEG_Scan4Led(uint16_t number);
void LED7SEG_STATE (GPIO_PinState LED1_State, GPIO_PinState LED2_State, GPIO_PinState LED3_State, GPIO_PinState LED4_State );
void LED7SEG_Scan4Led2(uint16_t number);
#endif
