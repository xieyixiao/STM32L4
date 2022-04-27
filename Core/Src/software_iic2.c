//
// Created by xieyixiao on 2022/1/5 0005.
//

#include "software_iic2.h"

void SW_I2C2_Init(void)
{
    IIC2_GPIO_CLK_ENABLE();
    GPIOB->OTYPER |= 3<<10; //PB10 PB11 外部上拉开漏输出
    IIC2_SCL_OUT(); //PB10输出模式
    IIC2_SDA_OUT(); //PB11输出模式
    IIC2_SCL(SET);
    IIC2_SDA(SET);
}

/*
 * @brief IIC起始信号
 */
void IIC2_Start(void)
{
    IIC2_SDA_OUT();
    IIC2_SDA(GPIO_PIN_SET); //先拉高SDA再拉高SCL，防止出现错误信号
    IIC2_SCL(GPIO_PIN_SET);
    delay_us(4); //延时保证SCL高电平时，SDA下降沿
    IIC2_SDA(GPIO_PIN_RESET);
    delay_us(4);
    IIC2_SCL(GPIO_PIN_RESET); //钳住I2C总线，准备发送或接收数据
}

/*
 * @brief IIC停止信号
 */
void IIC2_Stop(void)
{
    //IIC1_SCL(GPIO_PIN_RESET); //phph2045
    IIC2_SDA_OUT(); //phph2045
    IIC2_SCL(GPIO_PIN_RESET);
    IIC2_SDA(GPIO_PIN_RESET); //先拉低SDA再拉高SCL，防止出现错误信号
    delay_us(4); //延时保证SCL高电平时，SDA上升沿 //phph2045
    IIC2_SCL(GPIO_PIN_SET);
    IIC2_SDA(GPIO_PIN_SET);
    delay_us(4); //延时保证SCL高电平时，SDA上升沿
    //这里就不用拉低SCL了，因为IIC通讯已经结束
    //IIC1_SCL(GPIO_PIN_RESET); //钳住I2C总线，准备发送或接收数据
}

/*
 * @brief IIC主机等待应答
 * 返回值：0，接收应答成功
 *         -1，接收应答失败
 */
int8_t IIC2_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    IIC2_SDA_IN();
    IIC2_SDA(GPIO_PIN_SET); //一定要先拉高SDA，再拉高SCL，否则就可能变成起始信号和结束信号了
    delay_us(1);
    IIC2_SCL(GPIO_PIN_SET);
    delay_us(1);
    while(IIC2_Read_SDA())
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            IIC2_Stop();
            return -1;
        }
    }
    IIC2_SCL(GPIO_PIN_RESET); //IIC通讯没结束，拉低SCL线
    return 0;
}

//产生ACK应答
void IIC2_Ack(void)
{
    IIC2_SCL(GPIO_PIN_RESET); //phph2047
    IIC2_SDA_OUT(); //SDA设置为输出
    IIC2_SDA(GPIO_PIN_RESET);
    delay_us(2);
    IIC2_SCL(GPIO_PIN_SET);
    delay_us(2);
    IIC2_SCL(GPIO_PIN_RESET); //IIC通讯没结束，拉低SCL线
}

//产生NACK应答
void IIC2_NAck(void)
{
    IIC2_SCL(GPIO_PIN_RESET); //phph2045
    IIC2_SDA_OUT(); //SDA设置为输出
    IIC2_SDA(GPIO_PIN_SET);
    delay_us(2);
    IIC2_SCL(GPIO_PIN_SET);
    delay_us(2);
    IIC2_SCL(GPIO_PIN_RESET); //IIC通讯没结束，拉低SCL线
}

//读1个字节，ack=1时，发送ACk；ack=0，发送NACK
uint8_t IIC2_Read_Byte(uint8_t ack)
{
    uint8_t i = 0;
    uint8_t recv = 0;

    IIC2_SDA_IN(); //SDA设置为输入

    for(i=0; i<8; i++)
    {
        IIC2_SCL(GPIO_PIN_RESET); //拉低时钟线
        delay_us(2);
        IIC2_SCL(GPIO_PIN_SET); //拉高时钟线，接收1位数据
        recv <<= 1;
        if(IIC2_Read_SDA())
            recv |= 0x01;
        delay_us(1);
    }
    if(!ack)
        IIC2_NAck(); //发送NACK
    else
        IIC2_Ack(); //发送ACK
    return recv;
}

/*
 * @brief IIC发送一个字节
 * @para  待写入的字节数据
 * 返回从机有无应答
 *    1，有应答
 *    0，无应答
 */
void IIC2_Write_Byte(uint8_t data)
{
    uint8_t i = 0;

    IIC2_SDA_OUT();
    IIC2_SCL(GPIO_PIN_RESET); //拉低时钟开始数据传输

    for(i=0; i<8; i++)
    {
        //准备数据
        if(data & 0x80)
            IIC2_SDA(GPIO_PIN_SET);
        else
            IIC2_SDA(GPIO_PIN_RESET);
        data <<= 1;
        delay_us(2);
        IIC2_SCL(GPIO_PIN_SET); //拉高时钟线，发送1位数据
        delay_us(2);
        IIC2_SCL(GPIO_PIN_RESET);
        delay_us(2);
    }
}

void IIC2_WriteBytes(u8 WriteAddr,u8* data,u8 dataLength)
{
    u8 i;
    IIC2_Start();

    IIC2_Write_Byte(WriteAddr);	    //发送写命令
    IIC2_Wait_Ack();

    for(i=0;i<dataLength;i++)
    {
        IIC2_Write_Byte(data[i]);
        IIC2_Wait_Ack();
    }
    IIC2_Stop();//产生一个停止条件
    delay_ms(10);
}

void IIC2_ReadBytes(u8 deviceAddr, u8 writeAddr,u8* data,u8 dataLength)
{
    u8 i;
    IIC2_Start();
    IIC2_Write_Byte(deviceAddr);	    //发送写命令
    IIC2_Wait_Ack();
    IIC2_Write_Byte(writeAddr);
    IIC2_Wait_Ack();
    IIC2_Write_Byte(deviceAddr|0X01);//进入接收模式
    IIC2_Wait_Ack();

    for(i=0;i<dataLength-1;i++)
    {
        data[i] = IIC2_Read_Byte(1);
    }
    data[dataLength-1] = IIC2_Read_Byte(0);
    IIC2_Stop();//产生一个停止条件
    delay_ms(10);
}

void IIC2_Read_One_Byte(u8 daddr,u8 addr,u8* data)
{
    IIC2_Start();

    IIC2_Write_Byte(daddr);	   //发送写命令
    IIC2_Wait_Ack();
    IIC2_Write_Byte(addr);//发送地址
    IIC2_Wait_Ack();
    IIC2_Start();
    IIC2_Write_Byte(daddr|0X01);//进入接收模式
    IIC2_Wait_Ack();
    *data = IIC2_Read_Byte(0);
    IIC2_Stop();//产生一个停止条件
}

void IIC2_Write_One_Byte(u8 daddr, u8 addr, u8 data)
{
    IIC2_Start();

    IIC2_Write_Byte(daddr);	    //发送写命令
    IIC2_Wait_Ack();
    IIC2_Write_Byte(addr);//发送地址
    IIC2_Wait_Ack();
    IIC2_Write_Byte(data);     //发送字节
    IIC2_Wait_Ack();
    IIC2_Stop();//产生一个停止条件
    delay_ms(10);
}

