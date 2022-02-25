//-----------------------------------------------------------------
// 程序描述:
//     SPI驱动程序

//
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "spi.h"

//-----------------------------------------------------------------
SPI_HandleTypeDef SPI1_Handler; // SPI句柄
//-----------------------------------------------------------------
// void SPI1_Init(void)
//-----------------------------------------------------------------
//
// 函数功能: SPI1驱动程序，配置成主机模式
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void SPI1_Init(void){
    SPI1_Handler.Instance               = SPI1;                     // SPI1
  SPI1_Handler.Init.Mode              = SPI_MODE_MASTER;          // 设置SPI工作模式，设置为主模式
  SPI1_Handler.Init.Direction         = SPI_DIRECTION_2LINES;     // 设置SPI单向或者双向的数据模式:SPI设置为双线模式
  SPI1_Handler.Init.DataSize          = SPI_DATASIZE_8BIT;        // 设置SPI的数据大小:SPI发送接收8位帧结构
  SPI1_Handler.Init.CLKPolarity       = SPI_POLARITY_LOW;         // 串行同步时钟的空闲状态为高电平
  SPI1_Handler.Init.CLKPhase          = SPI_PHASE_2EDGE;          // 串行同步时钟的第二个跳变沿（上升或下降）数据被采样
  SPI1_Handler.Init.NSS               = SPI_NSS_SOFT;             // NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
  SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; // 定义波特率预分频的值:波特率预分频值为8
  SPI1_Handler.Init.FirstBit          = SPI_FIRSTBIT_MSB;         // 指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
  SPI1_Handler.Init.CRCPolynomial     = 0;                        // CRC值计算的多项式
HAL_SPI_Init(&SPI1_Handler);                                    // 初始化
  __HAL_SPI_ENABLE(&SPI1_Handler);                                // 使能SPI1
}

//-----------------------------------------------------------------
// void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//-----------------------------------------------------------------
//
// 函数功能: SPI1底层驱动，时钟使能，引脚配置
// 入口参数: SPI_HandleTypeDef *hspi：SPI句柄
// 返 回 值: 无
// 注意事项: 此函数会被HAL_SPI_Init()调用
//
//-----------------------------------------------------------------
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef GPIO_Initure;

  __HAL_RCC_GPIOA_CLK_ENABLE(); // 使能GPIO时钟
  __HAL_RCC_SPI1_CLK_ENABLE();  // 使能SPI1时钟

  // PA5->ADS1292_SCLK, PA6->ADS1292_DOUT, PA7->ADS1292_DIN
  GPIO_Initure.Pin       = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_Initure.Mode      = GPIO_MODE_AF_PP;    // 复用推挽输出
  GPIO_Initure.Pull      = GPIO_PULLUP;        // 上拉
  GPIO_Initure.Speed     = GPIO_SPEED_HIGH;   // 高速
  GPIO_Initure.Alternate = GPIO_AF5_SPI1; // 复用为SPI1
  HAL_GPIO_Init(GPIOA, &GPIO_Initure);    // 初始化
}

//-----------------------------------------------------------------
// void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
//-----------------------------------------------------------------
//
// 函数功能: SPI速度设置函数
// 入口参数: u8 SPI_BaudRatePrescaler：SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
// 返 回 值: 无
// 注意事项: SPI速度=fAPB1/分频系数，fAPB1时钟一般为45Mhz
//
//-----------------------------------------------------------------
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler)); // 判断有效性
  __HAL_SPI_DISABLE(&SPI1_Handler);                               // 关闭SPI
  SPI1_Handler.Instance->CR1 &= 0XFFC7;                           // 位3-5清零，用来设置波特率
  SPI1_Handler.Instance->CR1 |= SPI_BaudRatePrescaler;            // 设置SPI速度
  __HAL_SPI_ENABLE(&SPI1_Handler);                                // 使能SPI
}

//-----------------------------------------------------------------
// u8 SPI5_ReadWriteByte(u8 TxData)
//-----------------------------------------------------------------
//
// 函数功能: SPI5 读写一个字节
// 入口参数: u8 TxData： 要写入的字节
// 返 回 值: u8 Rxdata：读取到的字节
// 注意事项: 无
//
//-----------------------------------------------------------------
u8 SPI1_ReadWrite_Byte(u8 dat)
{
  u8 Rxdata;
  HAL_SPI_TransmitReceive(&SPI1_Handler, &dat, &Rxdata, 1, 1000);
  return Rxdata; // 返回收到的数据
}

//-----------------------------------------------------------------
// void SPI1_Send_Byte(u8 dat)
//-----------------------------------------------------------------
//
// 函数功能: SPI1发送1个字节数据
// 入口参数: u8 dat： 待发送的数据
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void SPI1_Send_Byte(u8 dat)
{
  u8 Rxdata;
  HAL_SPI_TransmitReceive(&SPI1_Handler, &dat, &Rxdata, 1, 1000);
}

//-----------------------------------------------------------------
// void SPI1_Send_Byte(u8 dat)
//-----------------------------------------------------------------
//
// 函数功能: SPI5读取1个字节数据
// 入口参数: u8 dat： 待发送的数据
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
u8 SPI1_Read_Byte(void)
{
  u8 Txdata = 0xFF;
  u8 Rxdata;
  HAL_SPI_TransmitReceive(&SPI1_Handler, &Txdata, &Rxdata, 1, 1000);
  return Rxdata; // 返回收到的数据
}

//-----------------------------------------------------------------
// End Of File
//----------------------------------------------------------------- 
