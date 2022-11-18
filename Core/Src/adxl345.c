//
// Created by xieyixiao on 2022/1/6 0006.
//

#include "adxl345.h"


void ADXL345_write(u8 addr, u8 data)
{
    IIC1_Start();
    IIC1_Write_Byte(ADXL_WRITE);
    IIC1_Wait_Ack();
    IIC1_Write_Byte(addr);
    IIC1_Wait_Ack();
    IIC1_Write_Byte(data);
    IIC1_Wait_Ack();
    IIC1_Stop();

    delay_ms(10);
}

u8 ADXL345_read(u8 addr)
{
    u8 d = 0;
    IIC1_Start();
    IIC1_Write_Byte(ADXL_WRITE);
    IIC1_Wait_Ack();
    IIC1_Write_Byte(addr);
    IIC1_Wait_Ack();
    IIC1_Start();
    IIC1_Write_Byte(ADXL_READ);
    IIC1_Wait_Ack();
    d = IIC1_Read_Byte(0);
//    IIC1_NAck();
    IIC1_Stop();

    return d;
}

void ADXL345_init()
{
    u8 d;

    SW_I2C1_Init();

    d = ADXL345_read(DEVICE_ID);

    printf("ADXL345_init\r\n");

    if(d == 0xE5)
    {
        ADXL345_write(DATA_FORMAT, 0x2B); //中断低电平有效，13位全分辨率模式，16g量程
        ADXL345_write(POWER_CTL, 0x28); //链接使能，测量模式
        ADXL345_write(INT_ENABLE, 0x00); //不使用中断
        ADXL345_write(OFSX, 0x00);
        ADXL345_write(OFSY, 0x00);
        ADXL345_write(OFSZ, 0x00);
    }
}

void ADXL345_read_XYZ(short *x, short *y, short *z)
{
    u8 i = 0;
    u16 buf[6] = {0};

    IIC1_Start();
    IIC1_Write_Byte(ADXL_WRITE);
    IIC1_Wait_Ack();
    IIC1_Write_Byte(0x32); //数据首地址
    IIC1_Wait_Ack();
    IIC1_Start();
    IIC1_Write_Byte(ADXL_READ);
    IIC1_Wait_Ack();

    for(i = 0; i < 5; i++) //总共6个
    {
        buf[i] = IIC1_Read_Byte(1);
    }
    buf[5] = IIC1_Read_Byte(0);
    IIC1_Stop();
    *x = (short)((buf[1]<<8) + buf[0]);
    *y = (short)((buf[3]<<8) + buf[2]);
    *z = (short)((buf[5]<<8) + buf[4]);
}

void ADXL345_read_times(short *x, short *y, short *z, u8 times)
{
    u8 i = 0;
    short tx, ty, tz;

    *x = *y = *z = 0;

    for(i = 0; i < times; i++) //读取times次
    {
        ADXL345_read_XYZ(&tx, &ty, &tz);

        *x += tx;
        *y += ty;
        *z += tz;

        delay_ms(1);
    }

    *x /= times; //求平均
    *y /= times;
    *z /= times;
}

short ADXL345_get_result(float x, float y, float z, u8 dir) //计算角度
{
    float t;
    float res;

    switch(dir)
    {
        case X:
            t = x / sqrt(y*y + z*z);
            res = atan(t); //求出弧度
            break;
        case Y:
            t = y / sqrt(x*x + z*z);
            res = atan(t);
            break;
        case Z:
            t = sqrt(x*x + y*y) / z;
            res = atan(t);
            break;
        default:
            break;
    }

    return (res * 180 / 3.14); //求出角度
}

void ADXL345_main()
{
    short x, y, z;
    short rx, ry, rz;

    ADXL345_read_times(&x, &y, &z, 10); //读出x，y，z方向加速度值
    printf("x %d\n", x);
    printf("y %d\n", y);
    printf("z %d\n", z);

    rx = ADXL345_get_result(x, y, z, X);
    ry = ADXL345_get_result(x, y, z, Y);
    rz = ADXL345_get_result(x, y, z, Z);
    printf("rx %d\n", rx);
    printf("ry %d\n", ry);
    printf("rz %d\n", rz);
}