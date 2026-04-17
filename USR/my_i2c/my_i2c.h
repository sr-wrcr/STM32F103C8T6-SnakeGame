
#ifndef my_I2C_H 
#define my_I2C_H

#include <include.h>
/*
void my_i2c_init(void);//GPIO
void my_i2c_W_SDA(uint8_t Bit_value);
void my_i2c_W_SCL(uint8_t Bit_value);
uint8_t my_i2c_R_SDA(void);
void my_i2c_start( void);//开始
void my_i2c_over( void);//结束
void my_i2c_sendbite(uint8_t Byte);//发送字节
uint8_t my_i2c_receivebite(void);//接受字节
void my_i2c_sendAck(uint8_t Ack);
uint8_t my_i2c_receiveACK(void);
void I2C_Write(uint8_t device_address, uint8_t register_address, uint8_t data) ;
uint8_t I2C_Read(uint8_t device_address, uint8_t register_address) ;
暂时没用*/
void IicInit(I2C_TypeDef* I2Cx);//iic
void IicTransmit(I2C_TypeDef* I2Cx,uint8_t Address, uint8_t register_address, uint8_t data);//输出
uint8_t IicReceive(I2C_TypeDef* I2Cx,uint8_t Address, uint8_t register_address );

#endif
