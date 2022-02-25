//
// Created by xieyixiao on 2022/1/6 0006.
//

#ifndef STM32L4_ADXL345_H
#define STM32L4_ADXL345_H
#include "software_iic1.h"
#include "stm32l475_user.h"

#define DEVICE_ID       0X00 //器件ID
#define THRESH_TAP      0X1D
#define OFSX            0X1E
#define OFSY            0X1F
#define OFSZ            0X20
#define DUR             0X21
#define Latent          0X22
#define Window          0X23
#define THRESH_ACK      0X24
#define THRESH_INACT    0X25
#define TIME_INACT      0X26
#define ACT_INACT_CTL   0X27
#define THRESH_FF       0X28
#define TIME_FF     0X29
#define TAP_AXES        0X2A
#define ACT_TAP_STATUS  0X2B
#define BW_RATE     0X2C
#define POWER_CTL       0X2D

#define INT_ENABLE      0X2E
#define INT_MAP     0X2F
#define INT_SOURCE      0X30
#define DATA_FORMAT 0X31
#define DATA_X0     0X32
#define DATA_X1     0X33
#define DATA_Y0     0X34
#define DATA_Y1     0X35
#define DATA_Z0     0X36
#define DATA_Z1     0X37
#define FIFO_CTL        0X38
#define FIFO_STATUS 0X39

#define ADXL_READ    0XA7 //读指令
#define ADXL_WRITE   0XA6 //写指令

typedef enum
{
    X, //与x轴的角度
    Y, //与y轴的角度
    Z  //与z轴的角度
}DIR_t;

void ADXL345_init();
void ADXL345_write(u8 addr, u8 data);
void ADXL345_read_XYZ(short *x, short *y, short *z);
void ADXL345_read_times(short *x, short *y, short *z, u8 times);
short ADXL345_get_result(float x, float y, float z, u8 dir); //计算角度
void ADXL345_main();
u8 ADXL345_read(u8 addr);

#endif //STM32L4_ADXL345_H
