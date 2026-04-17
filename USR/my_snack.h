#ifndef MY_SNACK_H 
#define MY_SNACK_H

#include "include.h"

#define Key_MID			(IicReceive(I2C1, 0x42, 0x13)&0x02)

#define Key_UP_number 		0
#define Key_DOWN_number 	1
#define Key_Right_number 	2
#define Key_Left_number 	3
//°´¼üºê¶¨Òå

void OLED_snake(void);
void OLED_UI(void);
void OLED_jpg(void);
void Game_Over(void);
void Dirtion(void);

extern u8 max_score ;

#endif
/*
	#define BOTTON_B0 (IicReceive(I2C1, 0x42, 0x13)&0x01)
	#define BOTTON_B1 (IicReceive(I2C1, 0x42, 0x13)&0x02)
	#define BOTTON_B2 (IicReceive(I2C1, 0x42, 0x13)&0x04)
	#define BOTTON_B3 (IicReceive(I2C1, 0x42, 0x13)&0x08)
	#define BOTTON_B4 (IicReceive(I2C1, 0x42, 0x13)&0x10)
	#define BOTTON_B5 (IicReceive(I2C1, 0x42, 0x13)&0x20)
	#define BOTTON_B6 (IicReceive(I2C1, 0x42, 0x13)&0x40)
	#define BOTTON_B7 (IicReceive(I2C1, 0x42, 0x13)&0x80)
	#define BOTTON_A4 (IicReceive(I2C1, 0x42, 0x12)&0x10)
	#define BOTTON_A5 (IicReceive(I2C1, 0x42, 0x12)&0x20)
	#define BOTTON_A6 (IicReceive(I2C1, 0x42, 0x12)&0x40)
	#define BOTTON_A7 (IicReceive(I2C1, 0x42, 0x12)&0x80)

	void checkButton_B1(void);
	void checkButton_B2(void);
	void checkButton_B3(void);
	void checkButton_B4(void);
	void checkButton_B5(void);
	void checkButton_B6(void);
	void checkButton_B7(void);
	void checkButton_B0(void);
	void checkButton_A4(void);
	void checkButton_A5(void);
	void checkButton_A6(void);
	void checkButton_A7(void);


#endif*/
