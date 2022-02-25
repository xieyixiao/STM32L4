//
// Created by xieyixiao on 2022/1/5 0005.
//
#include "software_iic1.h"

static void delay_us(vu32 u_sec)
{
    uint16_t cnt = 0;

    while(u_sec--)
    {
        for(cnt=80/5; cnt>0; cnt--);
    }
}

void SW_I2C1_Init(void)
{
    IIC1_GPIO_CLK_ENABLE();
    GPIOB->OTYPER |= 0x3<<8; //PB8 PB9 外部上拉开漏输出
    IIC1_SCL_OUT(); //PB8 输出模式
    IIC1_SDA_OUT(); //PB9输出模式
}

/*
 * @brief IIC起始信号
 */
void IIC1_Start(void)
{
    IIC1_SDA_OUT();
    IIC1_SDA(GPIO_PIN_SET); //先拉高SDA再拉高SCL，防止出现错误信号
    IIC1_SCL(GPIO_PIN_SET);
    delay_us(2); //延时保证SCL高电平时，SDA下降沿
    IIC1_SDA(GPIO_PIN_RESET);
    delay_us(2);
    IIC1_SCL(GPIO_PIN_RESET); //钳住I2C总线，准备发送或接收数据
    delay_us(10);
}

/*
 * @brief IIC停止信号
 */
void IIC1_Stop(void)
{
    //IIC1_SCL(GPIO_PIN_RESET); //phph2045
    IIC1_SDA_OUT(); //phph2045
    IIC1_SDA(GPIO_PIN_RESET); //先拉低SDA再拉高SCL，防止出现错误信号
    delay_us(2); //延时保证SCL高电平时，SDA上升沿 //phph2045
    IIC1_SCL(GPIO_PIN_SET);
    delay_us(2); //延时保证SCL高电平时，SDA上升沿
    IIC1_SDA(GPIO_PIN_SET);
    //这里就不用拉低SCL了，因为IIC通讯已经结束
    //IIC1_SCL(GPIO_PIN_RESET); //钳住I2C总线，准备发送或接收数据
}

/*
 * @brief IIC主机等待应答
 * 返回值：0，接收应答成功
 *         -1，接收应答失败
 */
int8_t IIC1_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;

    IIC1_SDA(GPIO_PIN_SET); //一定要先拉高SDA，再拉高SCL，否则就可能变成起始信号和结束信号了
    delay_us(1);
    IIC1_SDA_IN(); //SDA设置为输入
    delay_us(1); //phph2045
    IIC1_SCL(GPIO_PIN_SET);
    delay_us(2);
    while(IIC1_Read_SDA())
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            IIC1_Stop();
            IIC1_SDA_OUT(); //SDA恢复为输出
            return -1;
        }
    }
    IIC1_SCL(GPIO_PIN_RESET); //IIC通讯没结束，拉低SCL线
    IIC1_SDA_OUT(); //SDA恢复为输出

    return 0;
}

//产生ACK应答
void IIC1_Ack(void)
{
    //IIC1_SCL(GPIO_PIN_RESET); //phph2047
    IIC1_SDA_OUT(); //SDA设置为输出
    //IIC1_SCL(GPIO_PIN_RESET); //phph2046
    IIC1_SDA(GPIO_PIN_RESET);
    delay_us(2);
    IIC1_SCL(GPIO_PIN_SET);
    delay_us(2);
    IIC1_SCL(GPIO_PIN_RESET); //IIC通讯没结束，拉低SCL线
}

//产生NACK应答
void IIC1_NAck(void)
{
    IIC1_SCL(GPIO_PIN_RESET); //phph2045
    IIC1_SDA_OUT(); //SDA设置为输出
    //IIC1_SCL(GPIO_PIN_RESET); //phph2046
    IIC1_SDA(GPIO_PIN_SET);
    delay_us(2);
    IIC1_SCL(GPIO_PIN_SET);
    delay_us(2);
    IIC1_SCL(GPIO_PIN_RESET); //IIC通讯没结束，拉低SCL线
}

//读1个字节，ack=1时，发送ACk；ack=0，发送NACK
uint8_t IIC1_Read_Byte(uint8_t ack)
{
    uint8_t i = 0;
    uint8_t recv = 0;

    IIC1_SDA_IN(); //SDA设置为输入

    for(i=0; i<8; i++)
    {
        IIC1_SCL(GPIO_PIN_RESET); //拉低时钟线
        delay_us(2);
        IIC1_SCL(GPIO_PIN_SET); //拉高时钟线，接收1位数据
        recv <<= 1;
        //phph2045 delay_us(2);
        if(IIC1_Read_SDA())
            recv |= 0x01;
        delay_us(2);
    }
    IIC1_SCL(GPIO_PIN_RESET); //phph2047

    if(!ack)
        IIC1_NAck(); //发送NACK
    else
        IIC1_Ack(); //发送ACK

    IIC1_SDA_OUT(); //SDA恢复为输出

    return recv;
}

/*
 * @brief IIC发送一个字节
 * @para  待写入的字节数据
 * 返回从机有无应答
 *    1，有应答
 *    0，无应答
 */
void IIC1_Write_Byte(uint8_t data)
{
    uint8_t i = 0;

    IIC1_SDA_OUT();
    //phph2045 IIC1_SCL(GPIO_PIN_RESET); //拉低时钟开始数据传输

    for(i=0; i<8; i++)
    {
        IIC1_SCL(GPIO_PIN_RESET); //拉低时钟线
        //准备数据
        if(data & 0x80)
            IIC1_SDA(GPIO_PIN_SET);
        else
            IIC1_SDA(GPIO_PIN_RESET);
        data <<= 1;
        delay_us(2);
        IIC1_SCL(GPIO_PIN_SET); //拉高时钟线，发送1位数据
        delay_us(2);
    }
    IIC1_SCL(GPIO_PIN_RESET); //通讯未结束，拉低SCL
    delay_us(2); //phph2045
}