#include "include.h"

extern struct MAHONY_FILTER_t mahony_filter; // 在文件2.c中使用extern声明结构体变量
static u32 Num = 0;										//使用时把这个放到主函数上 

int main(void)
{	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);        //开启I2c的时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);        //开启I2c的时钟

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);        //开启GPIOC的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);        //开启GPIOB的时钟
	MYGPIOPinInit(GPIOC, GPIO_Pin_13, GPIO_Speed_10MHz, GPIO_Mode_Out_PP);
	MYGPIOPinInit(GPIOB, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_AF_OD);
	MYGPIOPinInit(GPIOB, GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_OD);
	MYGPIOPinInit(GPIOB, GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF_OD);//蓝牙
	MYGPIOPinInit(GPIOB, GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_AF_OD);

	MPU6050_Init();		//MPU6050初始化
	Serial_Init();
	IicInit(I2C1);
	IicInit(I2C2);	
	I2C_Cmd(I2C1, ENABLE);//在函数中，首先对传入的参数进行了参数检查，确保I2Cx是一个有效的I2C外设，并且NewState是一个有效的FunctionalState。然后根据NewState的值来决定是启用还是禁用I2C外设。如果NewState不等于DISABLE，即表示启用外设，将I2Cx的CR1寄存器的对应位设置为1；否则，表示禁用外设，将对应位设置为0。
	I2C_Cmd(I2C2, ENABLE);
	Timer_Init();
	OLED_Init();
	
	mahony_init(&mahony_filter, 2.0f, 0.1f, 0.01f); // 参数根据需求进行调整
	
	max_score = FLASH_R(FLASH_START_ADDR);
	
	delay_ms(500);
	
	OLED_UI();
	
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Num ++;												//Num变量自增，用于测试定时中断
		if(Num > 1000000)
			Num = 0;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//清除TIM2更新事件的中断标志位
															//中断标志位必须清除
															//否则中断将连续不断地触发，导致主程序卡死
	}
}

