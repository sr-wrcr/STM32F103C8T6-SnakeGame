#include <my_i2c.h>
/**
  * @brief i2c初始化
  * @param 无
  * @retval 无
	* @example 		
  */
void IicInit(I2C_TypeDef* I2Cx)
{
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C; 
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2; 
	I2C_InitStructure.I2C_OwnAddress1 = 0x3a4; 
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; 
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; 
	I2C_InitStructure.I2C_ClockSpeed = 200000; 
	I2C_Init(I2Cx, &I2C_InitStructure);
}

/**
  * @brief i2c输出
  * @param I2CX,io扩展版地址，寄存器地址，数据
  * @retval 无
	* @example 		IicTransmit(I2C1,0x42,0x00,0xf7);亮蓝灯
  */
void IicTransmit(I2C_TypeDef* I2Cx,uint8_t Address, uint8_t register_address, uint8_t data)//
{
	I2C_GenerateSTART(I2Cx, ENABLE); //Start（enable就是开始的意思 I2C1和I2C2随便,根据时钟 ）
	/*I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED (EV1): 当从设备地址匹配时触发，表明主设备正在尝试与从设备通信。
		I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED (EV1): 当从设备作为接收器时地址匹配时触发。
		I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED (EV1): 当从设备的第二个地址匹配时触发，这通常用于具有两个地址的设备。
		I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED (EV1): 当从设备作为第二个地址的接收器时触发。
		I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED (EV1): 当从设备的通用呼叫地址匹配时触发。
		I2C_EVENT_SLAVE_BYTE_RECEIVED (EV2): 当从设备接收到字节时触发。
		I2C_EVENT_SLAVE_BYTE_TRANSMITTED (EV3): 当从设备发送一个字节时触发。
		I2C_EVENT_SLAVE_ACK_FAILURE (EV3_2): 当从设备发送数据后未收到主设备的确认信号时触发。
		I2C_EVENT_SLAVE_STOP_DETECTED (EV4): 当检测到I2C通信的停止条件时触发。
		I2C_EVENT_MASTER_MODE_SELECT (EV5): 当主设备进入模式选择时触发。￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥
		I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED (EV6): 当主设备选择作为发送器模式时触发。￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥
		I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED (EV6): 当主设备选择作为接收器模式时触发。
		I2C_EVENT_MASTER_BYTE_RECEIVED (EV7): 当主设备接收到字节时触发。
		I2C_EVENT_MASTER_BYTE_TRANSMITTING (EV8): 当主设备开始发送一个字节时触发。
		I2C_EVENT_MASTER_BYTE_TRANSMITTED (EV8_2): 当主设备完成字节发送时触发。￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥
		I2C_EVENT_MASTER_MODE_ADDRESS10 (EV9): 当主设备使用10位地址模式时触发。*/
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));//EV5
	I2C_Send7bitAddress(I2Cx, Address, I2C_Direction_Transmitter); //01000010//"外设地址0x42"第三个是0x00(输出)
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//EV6
	I2C_SendData(I2Cx, register_address); //IODIRA寄存器地址（输出）
	/*IODIRA 00 IO7 IO6 IO5 IO4 IO3 IO2 IO1 IO0 1111 1111
		IODIRB 01 IO7 IO6 IO5 IO4 IO3 IO2 IO1 IO0 1111 1111
		IPOLA 02 IP7 IP6 IP5 IP4 IP3 IP2 IP1 IP0 0000 0000
		IPOLB 03 IP7 IP6 IP5 IP4 IP3 IP2 IP1 IP0 0000 0000
		GPINTENA 04 GPINT7 GPINT6 GPINT5 GPINT4 GPINT3 GPINT2 GPINT1 GPINT0 0000 0000
		GPINTENB 05 GPINT7 GPINT6 GPINT5 GPINT4 GPINT3 GPINT2 GPINT1 GPINT0 0000 0000
		GPPUA 0C PU7 PU6 PU5 PU4 PU3 PU2 PU1 PU0 0000 0000
		GPPUB 0D PU7 PU6 PU5 PU4 PU3 PU2 PU1 PU0 0000 0000
		GPIOA 12 GP7 GP6 GP5 GP4 GP3 GP2 GP1 GP0 0000 0000
		GPIOB 13 GP7 GP6 GP5 GP4 GP3 GP2 GP1 GP0 0000 0000
		OLATA 14 OL7 OL6 OL5 OL4 OL3 OL2 OL1 OL0 0000 0000
		OLATB 15 OL7 OL6 OL5 OL4 OL3 OL2 OL1 OL0 0000 0000*/
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//EV8_2	
	I2C_SendData(I2Cx, data);//发送数据（11110111蓝色11111011红色11111101绿色）	colour(GPIOA)---0112日志
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//EV8_2
	I2C_GenerateSTOP(I2Cx, ENABLE); 	//Stop
}
/**
  * @brief 
  * @param 
  * @retval 读取值
  * @example IicReceive(I2C1, 0x42, 0x13)==0xfe B0
  */
uint8_t IicReceive(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t register_address)//uint8_t adress
{
	uint8_t data;
	I2C_GenerateSTART(I2Cx, ENABLE); //Start（enable就是开始的意思 I2C1和I2C2随便,根据时钟 ）
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));//EV5
	I2C_Send7bitAddress(I2Cx, Address, I2C_Direction_Transmitter); //01000010//"外设地址"第三个是0x00
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//EV6
	I2C_SendData(I2Cx, register_address);//寄存器地址（输入）见上
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//EV8_2	
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));//EV5
	
	I2C_Send7bitAddress(I2Cx, Address, I2C_Direction_Receiver); //01000010//"外设地址"//第三个是0x01
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));//EV6
	I2C_AcknowledgeConfig(I2Cx, DISABLE );//*****关
	I2C_GenerateSTOP(I2Cx, ENABLE); 	//Stop
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));//EV7
	data=I2C_ReceiveData(I2Cx);
	I2C_AcknowledgeConfig(I2Cx, ENABLE );	//****开
	return data;
}
