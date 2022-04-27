//-----------------------------------------------------------------
// ��������:
//     ADS1292��������
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ͷ�ļ�����
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
// ��������: ADS1292��ʼ��
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ADS1292_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  // ADS1292_DRDY -> PB2
  GPIO_InitStruct.Pin   = GPIO_PIN_2;       // ����ADS1292_DRDY
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;  // ����
  GPIO_InitStruct.Pull  = GPIO_PULLUP;      // ����
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH; 	// ����
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);  	// ��ʼ��

  // ADS1292_START -> PB0
  // ADS1292_PWDN  -> PB1
  // ADS1292_GPIO1 -> NULL
  // ADS1292_GPIO2 -> NULL
  GPIO_InitStruct.Pin   = GPIO_PIN_0| GPIO_PIN_1;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP; 	// �������
  GPIO_InitStruct.Pull  = GPIO_PULLUP;         	// ����
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;    	// ����
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);     	// ��ʼ��

  // ADS1292_CS    -> PA4
  GPIO_InitStruct.Pin   = GPIO_PIN_4;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP; 	// �������
  GPIO_InitStruct.Pull  = GPIO_PULLUP;         	// ����
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;    	// ����
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);     	// ��ʼ��

  SPI1_Init(); // SPI��ʼ��
}

//-----------------------------------------------------------------
// void ADS1292_PowerOnInit(void)
//-----------------------------------------------------------------
//
// ��������: ADS1292�ϵ縴λ
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
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
//    ADS1292_PWDN = 0; // �������ģʽ
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
    HAL_Delay(1000);
//    ADS1292_PWDN = 1; // �˳�����ģʽ
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
    HAL_Delay(1000);   // �ȴ��ȶ�
//    ADS1292_PWDN = 0; // ������λ����
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
    delay_us(10);
//    ADS1292_PWDN = 1;
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
    HAL_Delay(1000); // �ȴ��ȶ������Կ�ʼʹ��ADS1292R
//    ADS1292_START = 0;
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
//    ADS1292_CS = 0;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
    SPI1_Send_Byte(SDATAC); // ����ֹͣ������ȡ��������
    delay_us(10);
//    ADS1292_CS = 1;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	// ��ȡоƬID
	device_id = ADS1292_Read_Reg(RREG | ID);
	while(device_id != 0x73)
	{
		printf("ERROR ID:%02x\r\n",device_id);
		device_id = ADS1292_Read_Reg(RREG | ID);
		HAL_Delay(1000);
	}
    delay_us(10);
  ADS1292_Write_Reg(WREG | CONFIG2,  0XE0); // ʹ���ڲ��ο���ѹ
  delay_ms(10);                            	// �ȴ��ڲ��ο���ѹ�ȶ�
  ADS1292_Write_Reg(WREG | CONFIG1,  0X02); // ����ת������Ϊ500SPS
  delay_us(10);
  ADS1292_Write_Reg(WREG | LOFF,     0XF0);	// �üĴ�����������������
  delay_us(10);
  ADS1292_Write_Reg(WREG | CH1SET,   0X00); // ����6�����ӵ��缫
  delay_us(10);
  ADS1292_Write_Reg(WREG | CH2SET,   0X50); // ����8�����ӵ��缫
  delay_us(10);
  ADS1292_Write_Reg(WREG | RLD_SENS, 0xEF);
  delay_us(10);
  ADS1292_Write_Reg(WREG | LOFF_SENS,0x0F);
  delay_us(10);
  ADS1292_Write_Reg(WREG | LOFF_STAT,0x00);
  delay_us(10);
  ADS1292_Write_Reg(WREG | RESP1,    0xEA); // ����������⣨ADS1292R���У�
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
// ��������: ��ADS1292���ڲ��Ĵ�������д����
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ADS1292_Write_Reg(u8 addr, u8 data)
{
//	ADS1292_CS = 0;				// Ƭѡ����
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
    SPI1_Send_Byte(addr);	// �������������ͼĴ�����ַ
  delay_us(10);
    SPI1_Send_Byte(0x00);	// Ҫ��ȡ�ļĴ�����+1
  delay_us(10);
    SPI1_Send_Byte(data);	// д�������
	delay_us(10);
//	ADS1292_CS = 1;				// Ƭѡ�ø�
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}

//-----------------------------------------------------------------
// u8 ADS1292_Read_Reg(u8 addr)
//-----------------------------------------------------------------
//
// ��������: ��ADS1292���ڲ��Ĵ������ж�����
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
u8 ADS1292_Read_Reg(u8 addr)
{
    // ADS1292_CS    -> PA4
  u8 Rxdata;
//	ADS1292_CS = 0;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
    SPI1_Send_Byte(addr); 			// �������������ͼĴ�����ַ
    delay_us(10);
    SPI1_Send_Byte(0x00); 			// Ҫ��ȡ�ļĴ�����+1
  delay_us(10);
  Rxdata = SPI1_Read_Byte(); 	// ��ȡ������
	delay_us(10);
//	ADS1292_CS = 1;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
  return Rxdata;
}

//-----------------------------------------------------------------
// u8 ADS1292_Read_Data(u8 addr)
//-----------------------------------------------------------------
//
// ��������: ��ȡADS1292������
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ADS1292_Read_Data(u8 *data)
{
  u8 i;
//	ADS1292_CS = 0;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
    SPI1_Send_Byte(RDATAC);		// ��������������ȡ��������
    delay_us(1);
//	ADS1292_CS = 1;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
//    ADS1292_START = 1; 				// ����ת��
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
  while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1);	// �ȴ�DRDY�ź�����
//  ADS1292_CS = 0;
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
  for (i = 0; i < 9; i++)		// ������ȡ9������
  {
    *data = SPI1_Read_Byte();
    data++;
  }
//  ADS1292_START = 0;				// ֹͣת��
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
    SPI1_Send_Byte(SDATAC);		// ����ֹͣ������ȡ��������
	delay_us(1);
//	ADS1292_CS = 1;
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}
//-----------------------------------------------------------------
// End Of File
//----------------------------------------------------------------- 
