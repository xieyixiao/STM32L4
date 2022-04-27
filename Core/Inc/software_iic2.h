//
// Created by xieyixiao on 2022/1/5 0005.
//

#ifndef STM32L4_SOFTWARE_IIC2_H
#define STM32L4_SOFTWARE_IIC2_H
#include "stm32l475_user.h"
#include "delay.h"

#define BIT_WRITE	0
#define BIT_READ	1

//引脚定义
/*
 * SCL——PB10
 * SDA——PB11
 */
#define IIC2_SDA_IN()	{GPIOB->MODER &= ~(3<<(11*2)); GPIOB->MODER |= 0<<11*2;} //PB11输入模式
#define IIC2_SDA_OUT()	{GPIOB->MODER &= ~(3<<(11*2)); GPIOB->MODER |= 1<<11*2;} //PB11输出模式
#define IIC2_SCL_OUT()	{GPIOB->MODER &= ~(3<<(10*2)); GPIOB->MODER |= 1<<10*2;} //PB10输出模式

#define IIC2_SCL_PIN	GPIO_PIN_10
#define IIC2_SDA_PIN	GPIO_PIN_11
#define IIC2_GPIO_PORT	GPIOB
#define IIC2_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()

//IIC1的IO操作函数
//带参宏，可以像内联函数一样使用
#define IIC2_SCL(a)		HAL_GPIO_WritePin(IIC2_GPIO_PORT, IIC2_SCL_PIN, a)
#define IIC2_SDA(a)		HAL_GPIO_WritePin(IIC2_GPIO_PORT, IIC2_SDA_PIN, a)
#define IIC2_Read_SDA()	HAL_GPIO_ReadPin(IIC2_GPIO_PORT, IIC2_SDA_PIN)

void SW_I2C2_Init(void);
void IIC2_Start(void); //发送IIC1开始信号
void IIC2_Stop(void); //发送IIC1停止信号
void IIC2_Write_Byte(uint8_t data); //IIC发送一个字节
uint8_t IIC2_Read_Byte(uint8_t ack); //IIC读取一个字节
int8_t IIC2_Wait_Ack(void); //IIC等待ACK信号
void IIC2_Ack(void); //IIC发送ACK信号
void IIC2_NAck(void); //IIC发送NACK信号

void IIC2_Write_One_Byte(u8 daddr, u8 addr, u8 data);
void IIC2_Read_One_Byte(u8 daddr,u8 addr,u8* data);
void IIC2_WriteBytes(u8 WriteAddr,u8* data,u8 dataLength);
void IIC2_ReadBytes(u8 deviceAddr, u8 writeAddr,u8* data,u8 dataLength);

#endif //STM32L4_SOFTWARE_IIC2_H
