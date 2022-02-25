//-----------------------------------------------------------------
// ��������:
//     SPI��������

//
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include "spi.h"

//-----------------------------------------------------------------
SPI_HandleTypeDef SPI1_Handler; // SPI���
//-----------------------------------------------------------------
// void SPI1_Init(void)
//-----------------------------------------------------------------
//
// ��������: SPI1�����������ó�����ģʽ
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void SPI1_Init(void){
    SPI1_Handler.Instance               = SPI1;                     // SPI1
  SPI1_Handler.Init.Mode              = SPI_MODE_MASTER;          // ����SPI����ģʽ������Ϊ��ģʽ
  SPI1_Handler.Init.Direction         = SPI_DIRECTION_2LINES;     // ����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
  SPI1_Handler.Init.DataSize          = SPI_DATASIZE_8BIT;        // ����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
  SPI1_Handler.Init.CLKPolarity       = SPI_POLARITY_LOW;         // ����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
  SPI1_Handler.Init.CLKPhase          = SPI_PHASE_2EDGE;          // ����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
  SPI1_Handler.Init.NSS               = SPI_NSS_SOFT;             // NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
  SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; // ���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ8
  SPI1_Handler.Init.FirstBit          = SPI_FIRSTBIT_MSB;         // ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
  SPI1_Handler.Init.CRCPolynomial     = 0;                        // CRCֵ����Ķ���ʽ
HAL_SPI_Init(&SPI1_Handler);                                    // ��ʼ��
  __HAL_SPI_ENABLE(&SPI1_Handler);                                // ʹ��SPI1
}

//-----------------------------------------------------------------
// void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//-----------------------------------------------------------------
//
// ��������: SPI1�ײ�������ʱ��ʹ�ܣ���������
// ��ڲ���: SPI_HandleTypeDef *hspi��SPI���
// �� �� ֵ: ��
// ע������: �˺����ᱻHAL_SPI_Init()����
//
//-----------------------------------------------------------------
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef GPIO_Initure;

  __HAL_RCC_GPIOA_CLK_ENABLE(); // ʹ��GPIOʱ��
  __HAL_RCC_SPI1_CLK_ENABLE();  // ʹ��SPI1ʱ��

  // PA5->ADS1292_SCLK, PA6->ADS1292_DOUT, PA7->ADS1292_DIN
  GPIO_Initure.Pin       = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_Initure.Mode      = GPIO_MODE_AF_PP;    // �����������
  GPIO_Initure.Pull      = GPIO_PULLUP;        // ����
  GPIO_Initure.Speed     = GPIO_SPEED_HIGH;   // ����
  GPIO_Initure.Alternate = GPIO_AF5_SPI1; // ����ΪSPI1
  HAL_GPIO_Init(GPIOA, &GPIO_Initure);    // ��ʼ��
}

//-----------------------------------------------------------------
// void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
//-----------------------------------------------------------------
//
// ��������: SPI�ٶ����ú���
// ��ڲ���: u8 SPI_BaudRatePrescaler��SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
// �� �� ֵ: ��
// ע������: SPI�ٶ�=fAPB1/��Ƶϵ����fAPB1ʱ��һ��Ϊ45Mhz
//
//-----------------------------------------------------------------
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler)); // �ж���Ч��
  __HAL_SPI_DISABLE(&SPI1_Handler);                               // �ر�SPI
  SPI1_Handler.Instance->CR1 &= 0XFFC7;                           // λ3-5���㣬�������ò�����
  SPI1_Handler.Instance->CR1 |= SPI_BaudRatePrescaler;            // ����SPI�ٶ�
  __HAL_SPI_ENABLE(&SPI1_Handler);                                // ʹ��SPI
}

//-----------------------------------------------------------------
// u8 SPI5_ReadWriteByte(u8 TxData)
//-----------------------------------------------------------------
//
// ��������: SPI5 ��дһ���ֽ�
// ��ڲ���: u8 TxData�� Ҫд����ֽ�
// �� �� ֵ: u8 Rxdata����ȡ�����ֽ�
// ע������: ��
//
//-----------------------------------------------------------------
u8 SPI1_ReadWrite_Byte(u8 dat)
{
  u8 Rxdata;
  HAL_SPI_TransmitReceive(&SPI1_Handler, &dat, &Rxdata, 1, 1000);
  return Rxdata; // �����յ�������
}

//-----------------------------------------------------------------
// void SPI1_Send_Byte(u8 dat)
//-----------------------------------------------------------------
//
// ��������: SPI1����1���ֽ�����
// ��ڲ���: u8 dat�� �����͵�����
// �� �� ֵ: ��
// ע������: ��
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
// ��������: SPI5��ȡ1���ֽ�����
// ��ڲ���: u8 dat�� �����͵�����
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
u8 SPI1_Read_Byte(void)
{
  u8 Txdata = 0xFF;
  u8 Rxdata;
  HAL_SPI_TransmitReceive(&SPI1_Handler, &Txdata, &Rxdata, 1, 1000);
  return Rxdata; // �����յ�������
}

//-----------------------------------------------------------------
// End Of File
//----------------------------------------------------------------- 
