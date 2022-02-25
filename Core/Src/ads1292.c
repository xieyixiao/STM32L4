//-----------------------------------------------------------------
// 程序描述:
//     ADS1292驱动程序
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "ads1292.h"
#include "stm32l4xx_hal.h"
#include "delay.h"
#include "spi.h"
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// void ADS1292_Init(void)
//-----------------------------------------------------------------
//
// 函数功能: ADS1292初始化
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ADS1292_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  // ADS1292_DRDY -> PB2
  GPIO_InitStruct.Pin   = GPIO_PIN_2;       // 配置ADS1292_DRDY
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;  // 输入
  GPIO_InitStruct.Pull  = GPIO_PULLUP;      // 上拉
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH; 	// 高速
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);  	// 初始化

  // ADS1292_START -> PB0
  // ADS1292_PWDN  -> PB1
  // ADS1292_GPIO1 -> NULL
  // ADS1292_GPIO2 -> NULL
  GPIO_InitStruct.Pin   = GPIO_PIN_0| GPIO_PIN_1;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP; 	// 推挽输出
  GPIO_InitStruct.Pull  = GPIO_PULLUP;         	// 上拉
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;    	// 高速
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);     	// 初始化

  // ADS1292_CS    -> PA4
  GPIO_InitStruct.Pin   = GPIO_PIN_4;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP; 	// 推挽输出
  GPIO_InitStruct.Pull  = GPIO_PULLUP;         	// 上拉
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;    	// 高速
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);     	// 初始化

  SPI1_Init(); // SPI初始化
}

//-----------------------------------------------------------------
// void ADS1292_PowerOnInit(void)
//-----------------------------------------------------------------
//
// 函数功能: ADS1292上电复位
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ADS1292_PowerOnInit(void)
{
     u8 	device_id;
    // ADS1292_START -> PB0
    // ADS1292_PWDN  -> PB1
    // ADS1292_CS    -> PA4
//    ADS1292_START = 1;
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
//    ADS1292_CS = 1;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
//    ADS1292_PWDN = 0; // 进入掉电模式
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
    HAL_Delay(1000);
//    ADS1292_PWDN = 1; // 退出掉电模式
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
    HAL_Delay(1000);   // 等待稳定
//    ADS1292_PWDN = 0; // 发出复位脉冲
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
    delay_us(10);
//    ADS1292_PWDN = 1;
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
    HAL_Delay(1000); // 等待稳定，可以开始使用ADS1292R
//    ADS1292_START = 0;
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
//    ADS1292_CS = 0;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
    SPI1_Send_Byte(SDATAC); // 发送停止连续读取数据命令
    delay_us(10);
//    ADS1292_CS = 1;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	// 获取芯片ID
	device_id = ADS1292_Read_Reg(RREG | ID);
	while(device_id != 0x73)
	{
		printf("ERROR ID:%02x\r\n",device_id);
		device_id = ADS1292_Read_Reg(RREG | ID);
		HAL_Delay(1000);
	}
    delay_us(10);
  ADS1292_Write_Reg(WREG | CONFIG2,  0XE0); // 使用内部参考电压
  delay_ms(10);                            	// 等待内部参考电压稳定
  ADS1292_Write_Reg(WREG | CONFIG1,  0X03); // 设置转换速率为1KSPS
  delay_us(10);
  ADS1292_Write_Reg(WREG | LOFF,     0XF0);	// 该寄存器配置引出检测操作
  delay_us(10);
  ADS1292_Write_Reg(WREG | CH1SET,   0X00); // 增益6，连接到电极
  delay_us(10);
  ADS1292_Write_Reg(WREG | CH2SET,   0X50); // 增益8，连接到电极
  delay_us(10);
  ADS1292_Write_Reg(WREG | RLD_SENS, 0xEF);
  delay_us(10);
  ADS1292_Write_Reg(WREG | LOFF_SENS,0x0F);
  delay_us(10);
  ADS1292_Write_Reg(WREG | LOFF_STAT,0x40);
  delay_us(10);
  ADS1292_Write_Reg(WREG | RESP1,    0xEA); // 开启呼吸检测（ADS1292R特有）
  delay_us(10);
  ADS1292_Write_Reg(WREG | RESP2,    0x03);
  delay_us(10);
  ADS1292_Write_Reg(WREG | GPIO,     0x0C);
  delay_us(10);
}

//-----------------------------------------------------------------
// void ADS1292_Write_Reg(u8 com, u8 data)
//-----------------------------------------------------------------
//
// 函数功能: 对ADS1292的内部寄存器进行写操作
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ADS1292_Write_Reg(u8 addr, u8 data)
{
//	ADS1292_CS = 0;				// 片选拉低
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
    SPI1_Send_Byte(addr);	// 包含命令操作码和寄存器地址
  delay_us(10);
    SPI1_Send_Byte(0x00);	// 要读取的寄存器数+1
  delay_us(10);
    SPI1_Send_Byte(data);	// 写入的数据
	delay_us(10);
//	ADS1292_CS = 1;				// 片选置高
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}

//-----------------------------------------------------------------
// u8 ADS1292_Read_Reg(u8 addr)
//-----------------------------------------------------------------
//
// 函数功能: 对ADS1292的内部寄存器进行读操作
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
u8 ADS1292_Read_Reg(u8 addr)
{
    // ADS1292_CS    -> PA4
  u8 Rxdata;
//	ADS1292_CS = 0;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
    SPI1_Send_Byte(addr); 			// 包含命令操作码和寄存器地址
    delay_us(10);
    SPI1_Send_Byte(0x00); 			// 要读取的寄存器数+1
  delay_us(10);
  Rxdata = SPI1_Read_Byte(); 	// 读取的数据
	delay_us(10);
//	ADS1292_CS = 1;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
  return Rxdata;
}

//-----------------------------------------------------------------
// u8 ADS1292_Read_Data(u8 addr)
//-----------------------------------------------------------------
//
// 函数功能: 读取ADS1292的数据
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void ADS1292_Read_Data(u8 *data)
{
  u8 i;
//	ADS1292_CS = 0;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
    SPI1_Send_Byte(RDATAC);		// 发送启动连续读取数据命令
    delay_us(1);
//	ADS1292_CS = 1;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
//    ADS1292_START = 1; 				// 启动转换
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
  while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1);	// 等待DRDY信号拉低
//  ADS1292_CS = 0;
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
  for (i = 0; i < 9; i++)		// 连续读取9个数据
  {
    *data = SPI1_Read_Byte();
    data++;
  }
//  ADS1292_START = 0;				// 停止转换
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
    SPI1_Send_Byte(SDATAC);		// 发送停止连续读取数据命令
	delay_us(1);
//	ADS1292_CS = 1;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}
//-----------------------------------------------------------------
// End Of File
//----------------------------------------------------------------- 
