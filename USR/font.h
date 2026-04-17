/**
* @file  			font.h
* @brief  		×Ö¿â
* @date     	2021-1-21
* @version 	 	V1.0
*/
#ifndef __FONT_H_
#define __FONT_H_	  
#include "include.h"

typedef struct 
{
  unsigned char Msk[32];
  unsigned char Index[2];	
}typFNT_GB16; 

extern  const unsigned char  F6x8[][6];//code
extern  const unsigned char  F8X16[];//code
extern  const typFNT_GB16  tfont16[];//code

unsigned int font_Size(void);

#endif /* __FONT_H_ */
