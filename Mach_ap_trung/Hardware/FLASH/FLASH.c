#include "FLASH.h"

#define FLASH_ADDR_PAGE_126 ((uint32_t)0x0801F810)	//Page 126
#define FLASH_ADDR_PAGE_127 ((uint32_t)0x0801FC00)	//Page 127

#define FLASH_USER_START_ADDR   FLASH_ADDR_PAGE_126
#define FLASH_USER_END_ADDR     FLASH_ADDR_PAGE_127 + FLASH_PAGE_SIZE


void FLASH_WritePage(uint32_t startPage, uint32_t endPage, uint32_t data32)
{
  HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInit;
	EraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInit.PageAddress = startPage;
	EraseInit.NbPages = (endPage - startPage)/FLASH_PAGE_SIZE;
	uint32_t PageError = 0;
	HAL_FLASHEx_Erase(&EraseInit, &PageError);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, startPage, data32); //4 byte dau tien
	//HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, startPage + 4, 0x34567890); // 4byte tiep theo
  HAL_FLASH_Lock();
}
uint32_t FLASH_ReadData32(uint32_t addr)
{
	uint32_t data = *(__IO uint32_t *)(addr);
	return data;
}