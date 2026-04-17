#include "my_snack.h"
#include "include.h"
#include "stdlib.h"				//用随机数函数=rand();
#include "FLASH.h"
#include "serial.h"
#include "math.h"

u8 max_score;
static u32 Num = 0;										//使用时把这个放到主函数上 
extern double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter

char snake_x[255];																	//
char snake_y[255];																	//
char snake_food[2];																	//
char fraction = 0;	//分数													//
signed char fraction_temporary = 0;	//分数临时值		//为什么改成int就有问题 @*@
																										//											  -
int Key_Up = 1;

extern struct MAHONY_FILTER_t mahony_filter; // 在文件2.c中使用extern声明结构体变量

char Key_number = Key_Right_number;	//默认向右

void OLED_jpg()
{
	for (int i = 16; i < 21; i++) {
OLED_DrawPoint(i, 8);
}
OLED_DrawPoint(28, 9);
for (int i = 14; i < 18; i++) {
OLED_DrawPoint(i, 9); //蛇眼
}
for (int i = 20; i < 24; i++) {
OLED_DrawPoint(i, 9);
}
OLED_DrawPoint(27, 9);
for (int i = 12; i < 27; i++) {
OLED_DrawPoint(i, 10);
}
for (int i = 11; i < 24; i++) {
OLED_DrawPoint(i, 11);
}
for (int i = 27; i < 29; i++) {
OLED_DrawPoint(i, 11);
}
for (int i = 10; i < 22; i++) {
OLED_DrawPoint(i, 12);
}
for (int i = 10; i < 21; i++) {
OLED_DrawPoint(i, 13);
}
for (int i = 10; i < 21; i++) {
OLED_DrawPoint(i, 14);
}
for (int i = 11; i < 21; i++) {
OLED_DrawPoint(i, 15);
}
for (int i = 12; i < 22; i++) {
OLED_DrawPoint(i, 16);
}
for (int i = 13; i < 23; i++) {
OLED_DrawPoint(i, 17);
}
for (int i = 14; i < 23; i++) {
OLED_DrawPoint(i, 18);
}
for (int i = 15; i < 24; i++) {
OLED_DrawPoint(i, 19);
}
for (int i = 16; i < 25; i++) {
OLED_DrawPoint(i, 20);
}
for (int i = 17; i < 26; i++) {
OLED_DrawPoint(i, 21);
}
for (int i = 17; i < 27; i++) {
OLED_DrawPoint(i, 22);
}
for (int i = 17; i < 27; i++) {
OLED_DrawPoint(i, 23);
}
for (int i = 17; i < 27; i++) {
OLED_DrawPoint(i, 24);
}
for (int i = 16; i < 27; i++) {
OLED_DrawPoint(i, 25);
}
for (int i = 15; i < 26; i++) {
OLED_DrawPoint(i, 26);
}
for (int i = 14; i < 26; i++) {
OLED_DrawPoint(i, 27);
}
for (int i = 13; i < 25; i++) {
OLED_DrawPoint(i, 28);
}
for (int i = 12; i < 24; i++) {
OLED_DrawPoint(i, 29);
}
for (int i = 11; i < 24; i++) {
OLED_DrawPoint(i, 30);
}
for (int i = 11; i < 23; i++) {
OLED_DrawPoint(i, 31);
}
for (int i = 10; i < 21; i++) {
OLED_DrawPoint(i, 32);
}
for (int i = 10; i < 20; i++) {
OLED_DrawPoint(i, 33);
}
for (int i = 10; i < 20; i++) {
OLED_DrawPoint(i, 34);
}
for (int i = 11; i < 20; i++) {
OLED_DrawPoint(i, 35);
}
for (int i = 11; i < 20; i++) {
OLED_DrawPoint(i, 36);
}
for (int i = 12; i < 21; i++) {
OLED_DrawPoint(i, 37);
}
for (int i = 13; i < 22; i++) {
OLED_DrawPoint(i, 38);
}
for (int i = 14; i < 22; i++) {
OLED_DrawPoint(i, 39);
}
for (int i = 15; i < 23; i++) {
OLED_DrawPoint(i, 40);
}
for (int i = 16; i < 24; i++) {
OLED_DrawPoint(i, 41);
}
for (int i = 17; i < 25; i++) {
OLED_DrawPoint(i, 42);
}
for (int i = 18; i < 25; i++) {
OLED_DrawPoint(i, 43);
}
for (int i = 18; i < 25; i++) {
OLED_DrawPoint(i, 44);
}
for (int i = 19; i < 25; i++) {
OLED_DrawPoint(i, 45);
}
for (int i = 19; i < 25; i++) {
OLED_DrawPoint(i, 46);
}
for (int i = 19; i < 25; i++) {
OLED_DrawPoint(i, 47);
}
for (int i = 20; i < 25; i++) {
OLED_DrawPoint(i, 48);
}
for (int i = 20; i < 24; i++) {
OLED_DrawPoint(i, 49);
}
for (int i = 20; i < 24; i++) {
OLED_DrawPoint(i, 50);
}
for (int i = 19; i < 23; i++) {
OLED_DrawPoint(i, 51);
}
for (int i = 19; i < 23; i++) {
OLED_DrawPoint(i, 52);
}
for (int i = 18; i < 22; i++) {
OLED_DrawPoint(i, 53);
}
for (int i = 18; i < 21; i++) {
OLED_DrawPoint(i, 54);
}
for (int i = 17; i < 20; i++) {
OLED_DrawPoint(i, 55);
}
for (int i = 17; i < 19; i++) {
OLED_DrawPoint(i, 56);
}
for (int i = 16; i < 18; i++) {
OLED_DrawPoint(i, 57);
}
for (int i = 16; i < 17; i++) {
OLED_DrawPoint(i, 58);
}

}
void OLED_UI()
{
	int arrow_x = 70,arrow_y = 32;
	OLED_Clear();
	while(1)
	{	
	IicTransmit(I2C1, 0x42, 0x00, 0xf7);//亮蓝灯
	OLED_ShowStr(54, 3, (u8*)"START",12,0);  		//显示分数文字
	OLED_DrawPoint(arrow_x,arrow_y);
	OLED_DrawPoint(arrow_x+1,arrow_y);
	OLED_DrawPoint(arrow_x+2,arrow_y);
	OLED_DrawPoint(arrow_x,arrow_y+1);
	OLED_DrawPoint(arrow_x+1,arrow_y+1);
	OLED_DrawPoint(arrow_x,arrow_y+2);
	OLED_DrawPoint(arrow_x+2,arrow_y+2);
	OLED_DrawPoint(arrow_x+3,arrow_y+3);
	OLED_jpg();

	u8 i, n;
  for (i = 0; i < 8 ; i++)
  {
    OLED_WrCmd(0xb0 + i); // 设置行起始地址,页数
    OLED_WrCmd(0x00);     // 设置低列起始地址
    OLED_WrCmd(0x10);     // 设置高列起始地址
		
		if(i == 3 )
			for (n = 0; n < 54; n++)//由于贪吃蛇的需要 只刷新地图中的 也就是零到96 //正常的范围这里是128 
							OLED_WrDat(OLED_GRAM[n][i]);
		else 
			for (n = 0; n < 128; n++)//正常的范围这里是128 
							OLED_WrDat(OLED_GRAM[n][i]);
  }
		
		if( arrow_x <= 85 && arrow_x >= 55 && arrow_y >= 16 && arrow_y < 40)
		{
			if(Key_MID == 0)
			{
					OLED_ClearPoint (arrow_x,arrow_y);
					OLED_ClearPoint (arrow_x+1,arrow_y);
					OLED_ClearPoint (arrow_x+2,arrow_y);
					OLED_ClearPoint (arrow_x,arrow_y+1);
					OLED_ClearPoint (arrow_x+1,arrow_y+1);
					OLED_ClearPoint (arrow_x,arrow_y+2);
					OLED_ClearPoint (arrow_x+2,arrow_y+2);
					OLED_ClearPoint (arrow_x+3,arrow_y+3);
				for(int i=16;i<21;i++)
					OLED_ClearPoint(i,8);
					OLED_ClearPoint(28,9);
				for(int i=14;i<19;i++)
					OLED_ClearPoint(i,9);
				for(int i=20;i<24;i++)
					OLED_ClearPoint(i,9);
					OLED_ClearPoint(27,9);
				for(int i=12;i<27;i++)
					OLED_ClearPoint(i,10);
				for(int i=11;i<24;i++)
					OLED_ClearPoint(i,11);
				for(int i=27;i<29;i++)
					OLED_ClearPoint(i,11);
				for(int i=10;i<22;i++)
					OLED_ClearPoint(i,12);
				for(int i=10;i<21;i++)
					OLED_ClearPoint(i,13);
				for(int i=10;i<21;i++)
					OLED_ClearPoint(i,14);
				for(int i=11;i<21;i++)
					OLED_ClearPoint(i,15);
				for(int i=12;i<22;i++)
					OLED_ClearPoint(i,16);
				for(int i=13;i<23;i++)
					OLED_ClearPoint(i,17);
				for(int i=14;i<23;i++)
					OLED_ClearPoint(i,18);
				for(int i=15;i<24;i++)
					OLED_ClearPoint(i,19);
				for(int i=16;i<25;i++)
					OLED_ClearPoint(i,20);
				for(int i=17;i<26;i++)
					OLED_ClearPoint(i,21);
				for(int i=17;i<27;i++)
					OLED_ClearPoint(i,22);
				for(int i=17;i<27;i++)
					OLED_ClearPoint(i,23);
				for(int i=17;i<27;i++)
					OLED_ClearPoint(i,24);
				for(int i=16;i<27;i++)
					OLED_ClearPoint(i,25);
				for(int i=15;i<26;i++)
					OLED_ClearPoint(i,26);
				for(int i=14;i<26;i++)
					OLED_ClearPoint(i,27);
				for(int i=13;i<25;i++)
					OLED_ClearPoint(i,28);
				for(int i=12;i<24;i++)
					OLED_ClearPoint(i,29);
				for(int i=11;i<24;i++)
					OLED_ClearPoint(i,30);
				for(int i=11;i<23;i++)
					OLED_ClearPoint(i,31);
				for(int i=10;i<21;i++)
					OLED_ClearPoint(i,32);
				for(int i=10;i<20;i++)
					OLED_ClearPoint(i,33);
				for(int i=10;i<20;i++)
					OLED_ClearPoint(i,34);
				for(int i=11;i<20;i++)
					OLED_ClearPoint(i,35);
				for(int i=11;i<20;i++)
					OLED_ClearPoint(i,36);
				for(int i=12;i<21;i++)
					OLED_ClearPoint(i,37);
				for(int i=13;i<22;i++)
					OLED_ClearPoint(i,38);
				for(int i=14;i<22;i++)
					OLED_ClearPoint(i,39);
				for(int i=15;i<23;i++)
					OLED_ClearPoint(i,40);
				for(int i=16;i<24;i++)
					OLED_ClearPoint(i,41);
				for(int i=17;i<25;i++)
					OLED_ClearPoint(i,42);
				for(int i=18;i<25;i++)
					OLED_ClearPoint(i,43);
				for(int i=18;i<25;i++)
					OLED_ClearPoint(i,44);
				for(int i=19;i<25;i++)
					OLED_ClearPoint(i,45);
				for(int i=19;i<25;i++)
					OLED_ClearPoint(i,46);
				for(int i=19;i<25;i++)
					OLED_ClearPoint(i,47);
				for(int i=20;i<25;i++)
					OLED_ClearPoint(i,48);
				for(int i=20;i<24;i++)
					OLED_ClearPoint(i,49);
				for(int i=20;i<24;i++)
					OLED_ClearPoint(i,50);
				for(int i=19;i<23;i++)
					OLED_ClearPoint(i,51);
				for(int i=19;i<23;i++)
					OLED_ClearPoint(i,52);
				for(int i=18;i<22;i++)
					OLED_ClearPoint(i,53);
				for(int i=18;i<21;i++)
					OLED_ClearPoint(i,54);
				for(int i=17;i<20;i++)
					OLED_ClearPoint(i,55);
				for(int i=17;i<19;i++)
					OLED_ClearPoint(i,56);
				for(int i=16;i<18;i++)
					OLED_ClearPoint(i,57);
				for(int i=16;i<17;i++)
					OLED_ClearPoint(i,58);
				OLED_Clear();
				OLED_snake();
			}
		}
	}
}


void OLED_snake()
{
	int sign = 0;//看看有没有最高分的更新，如果没有就省得再调flash了 
	char a = 1;
	char x = 20,y = 31;	//蛇初始位置
	Key_number = Key_Right_number;	//默认向右

	OLED_Clear();		//清除上一局的残骸//清不了点
	snake_x[0] = x;
	snake_y[0] = y;
	snake_food[0] = 60;
	snake_food[1] = 31;
	OLED_DrawLine(95, 0, 95, 63);
	OLED_DrawLine(0, 0, 95, 0);
	OLED_DrawLine(0, 63, 95, 63);
	
	OLED_DrawPoint_3x3(snake_food[0],snake_food[1]);	//先默认生成出来一个食物
	
	if (max_score == 0xFF)    // 如果Flash中的值为0xFFFF，说明还没有存储最大值
        FLASH_W(FLASH_START_ADDR, 0);   // 将最大值存储到Flash中
	while(1)
	{	
		OLED_ShowStr(96, 0, (u8*)"Score",12,0);  		//显示分数文字
		OLED_ShowStr(96, 4, (u8*)"MAX",12,0);  		//显示历史分数文字
		IicTransmit(I2C1, 0x42, 0x00, 0xf7);//亮蓝灯
		OLED_ShowNum(100, 1, fraction, 3, 16);  		//显示分数
		OLED_ShowNum(100, 6, max_score, 3, 12);  		//显示历史分数
				
		Angle_Calcu();
		calculateAttitude();
		Serial_Printf(" %.2f, %.2f, %.2f \n", mahony_filter.yaw	,kalAngleX, kalAngleY);

		if(Num % 50 == 0)
			Dirtion();
		//把分数值显示出来
		
				switch(Key_number)
					{
						case Key_Right_number:
							x = x + 2;
							y = y;
							break;
						case Key_Left_number:
							x = x - 2;
							y = y;
							break;
						case Key_DOWN_number:
							x = x;
							y = y + 2;
							break;
						case Key_UP_number:
							x = x;
							y = y - 2;
							break;
					}
		OLED_ClearPoint_3x3(snake_x[fraction],snake_y[fraction]);		//把尾巴消除掉
				
		fraction_temporary = fraction;
		for(;fraction_temporary>0;fraction_temporary--)	//通过分数决定循环次数
		{
			snake_x[fraction_temporary] = snake_x[fraction_temporary - 1];
			snake_y[fraction_temporary] = snake_y[fraction_temporary - 1];
		}
		snake_x[0] = x;
		snake_y[0] = y;	//坐标存入数组头
		
		fraction_temporary = fraction;
		for(;fraction_temporary>=0;fraction_temporary--)	
		{
			OLED_DrawPoint_3x3(snake_x[fraction_temporary],snake_y[fraction_temporary]);
		}
		//把蛇的身体完整的显示出来-------------------------------------------------------------
		if(abs(snake_x[0] - snake_food[0]) <= 1 && abs(snake_y[0] - snake_food[1]) <= 1)
		{
			OLED_ClearPoint_3x3(snake_food[0],snake_food[1]);
			fraction++;
			IicTransmit(I2C1,0x42,0x00,0xf1);
			while(a)
			{
				snake_food[0] = rand();
				snake_food[1] = rand();
				if(snake_food[0]>=91 || snake_food[1]>=60 || snake_food[1]<=4 || snake_food[0]<=4)
				{
					a++;
				}
				a--;
			}
			a = 1;
		}
		OLED_DrawPoint_3x3(snake_food[0],snake_food[1]);
		//判断蛇是不是吃到食物
		fraction_temporary = fraction;
		for(;fraction_temporary>0;fraction_temporary--)
		{
			if(snake_x[0] == snake_x[fraction_temporary] && snake_y[0] == snake_y[fraction_temporary])
			{
				Game_Over();
			}
		}
		//判断蛇头是不是跟蛇身体重叠了----------------------------------------------------------

		if(fraction > max_score)
		{
			max_score = fraction;
			sign = 1;
		}
		if(x <= 1)
			x = 93;
		
		if(x >= 94  || y >= 62 || y <= 1)
		{
			if(sign == 1)
			{
		FLASH_W(FLASH_START_ADDR,max_score);
		delay_ms(20);
			}
		Game_Over();
		}
		OLED_Refresh();
	}
}
 
void Game_Over()
{
	OLED_ShowStr(12,2,(u8*)"GAME_OVER",16,0);

	fraction_temporary = fraction;
	
	while(1)
	{
		IicTransmit(I2C1,0x42,0x00,0xfB);//亮灯
		
			if (Key_MID == 0) 
			{
				
        // 重启游戏
				Num = 0;
				OLED_ClearLine(95, 0, 95, 63);
				OLED_ClearLine(0, 0, 95, 0);
				OLED_ClearLine(0, 63, 95, 63);
        for (; fraction_temporary >= 0; fraction_temporary--)
        {
            OLED_ClearPoint_3x3(snake_x[fraction_temporary], snake_y[fraction_temporary]);
        }
        OLED_ClearPoint_3x3(snake_food[0], snake_food[1]);
        fraction = 0;
        OLED_UI();
				delay_ms (500);
			}
		
	}
}
	
void Dirtion()
{
	if(Key_number == Key_UP_number || Key_number == Key_DOWN_number)		//检测当前的蛇是不是向上或者向下
		{
			if(kalAngleY <= -10 && abs(kalAngleY) > abs(kalAngleX))
			{
				Key_number = Key_Left_number;	//向右
			}else if(kalAngleY >= 10 && abs(kalAngleY) > abs(kalAngleX))
			{
				Key_number = Key_Right_number;		//向左
			}
		}
		if(Key_number == Key_Right_number || Key_number == Key_Left_number)	//检测当前的蛇是不是向左或者向右
		{
			if(kalAngleX <= -10 && abs(kalAngleY) < abs(kalAngleX))
			{
				Key_number = Key_UP_number;
			}else if(kalAngleX >= 10 && abs(kalAngleY) < abs(kalAngleX))
			{
				Key_number = Key_DOWN_number;
			}
		}
}
