#ifndef __DS3231_H
#define __DS3231_H

#include "stm32f1xx_hal.h"

void FLASH_WritePage(uint32_t startPage, uint32_t endPage, uint32_t data32);
uint32_t FLASH_ReadData32(uint32_t addr);
#endif
