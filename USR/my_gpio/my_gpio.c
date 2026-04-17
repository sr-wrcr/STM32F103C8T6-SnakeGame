 #include "my_gpio.h"

/**
  * @brief GPIO初始化
  * @param GPIOx ,GPIO_Pin,GPIO_Speed,模式
  * @retval None
  */

void MYGPIOPinInit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed, GPIOMode_TypeDef GPIO_Mode)
{
		GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode;
	/*它定义了GPIO引脚的不同模式，例如模拟输入（AIN），输入浮空（IN_FLOATING），
	输入下拉（IPD），输入上拉（IPU），输出开漏（Out_OD），输出推挽（Out_PP），
	备用功能开漏（AF_OD）和备用功能推挽（AF_PP）。*/
	GPIO_Init(GPIOx, &GPIO_Init_Structure);
}


