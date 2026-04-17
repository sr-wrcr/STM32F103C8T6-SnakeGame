#ifndef __FLASH_H
#define __FLASH_H 			   
#include <stm32f10x.h>
#define FLASH_START_ADDR  0x0801f000	  //写入的起始地址 

void FLASH_W(u32 add,u16 dat);
u16 FLASH_R(u32 add);

#endif
