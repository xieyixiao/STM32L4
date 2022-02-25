//
// Created by xieyixiao on 2022/1/5 0005.
//

#ifndef STM32L4_SOFTWARE_IIC1_H
#define STM32L4_SOFTWARE_IIC1_H
#include "stm32l475_user.h"


#define BIT_WRITE	0
#define BIT_READ	1

//引脚定义
/*
 * SCL——PB8
 * SDA——PB9
 */
#define IIC1_SDA_IN()	{GPIOB->MODER &= ~(3<<(9*2)); GPIOB->MODER |= 0<<9*2;} //PB9输入模式
#define IIC1_SDA_OUT()	{GPIOB->MODER &= ~(3<<(9*2)); GPIOB->MODER |= 1<<9*2;} //PB9输出模式
#define IIC1_SCL_OUT()	{GPIOB->MODER &= ~(3<<(8*2)); GPIOB->MODER |= 1<<8*2;} //PB9输出模式

#define IIC1_SCL_PIN	GPIO_PIN_8
#define IIC1_SDA_PIN	GPIO_PIN_9
#define IIC1_GPIO_PORT	GPIOB
#define IIC1_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()

//IIC1的IO操作函数
//带参宏，可以像内联函数一样使用
#define IIC1_SCL(a)		HAL_GPIO_WritePin(IIC1_GPIO_PORT, IIC1_SCL_PIN, a)
#define IIC1_SDA(a)		HAL_GPIO_WritePin(IIC1_GPIO_PORT, IIC1_SDA_PIN, a)
#define IIC1_Read_SDA()	HAL_GPIO_ReadPin(IIC1_GPIO_PORT, IIC1_SDA_PIN)

void SW_I2C1_Init(void);
void IIC1_Start(void); //发送IIC1开始信号
void IIC1_Stop(void); //发送IIC1停止信号
void IIC1_Write_Byte(uint8_t data); //IIC发送一个字节
uint8_t IIC1_Read_Byte(uint8_t ack); //IIC读取一个字节
int8_t IIC1_Wait_Ack(void); //IIC等待ACK信号
void IIC1_Ack(void); //IIC发送ACK信号
void IIC1_NAck(void); //IIC发送NACK信号

#endif //STM32L4_SOFTWARE_IIC1_H
