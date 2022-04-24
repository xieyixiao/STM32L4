//-----------------------------------------------------------------
// ��������:
// 		 ����ͨѶ��������ͷ�ļ�
// �޸�����: 
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//  - V1.0: ���ڳ�ʼ���������ж�
// ˵    ��: 
//    
//-----------------------------------------------------------------
#ifndef _USART_H
#define _USART_H
#include "stm32l475_user.h"
//-----------------------------------------------------------------
// �궨��ͱ�������
//-----------------------------------------------------------------
#define USART_REC_LEN  	200  							// �����������ֽ��� 200
	  	
extern u8  USART_RX_BUF[USART_REC_LEN];  	// ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         				 	// ����״̬���	
extern UART_HandleTypeDef UART_Handler; 	// UART���

#define RXBUFFERSIZE   1 									// �����С
extern u8 aRxBuffer[RXBUFFERSIZE];			 	// HAL��USART����Buffer

//-----------------------------------------------------------------
// USART���Ŷ���
//-----------------------------------------------------------------
#define USARTx                                		 USART1
#define USART_CLK_ENABLE()                         __HAL_RCC_USART1_CLK_ENABLE()

#define USART_RX_PIN                               GPIO_PIN_10
#define USART_RX_GPIO_PORT                         GPIOA
#define USART_RX_AF                         			 GPIO_AF7_USART1
#define USART_RX_GPIO_CLK_ENABLE()                 __HAL_RCC_GPIOA_CLK_ENABLE()  
#define USART_RX_GPIO_CLK_DISABLE()                __HAL_RCC_GPIOA_CLK_DISABLE()  

#define USART_TX_PIN                               GPIO_PIN_9
#define USART_TX_GPIO_PORT                         GPIOA
#define USART_TX_AF                         			 GPIO_AF7_USART1
#define USART_TX_GPIO_CLK_ENABLE()                 __HAL_RCC_GPIOA_CLK_ENABLE()  
#define USART_TX_GPIO_CLK_DISABLE()                __HAL_RCC_GPIOA_CLK_DISABLE()  

#define USART_IRQn																 USART1_IRQn
//-----------------------------------------------------------------
// �ⲿ��������
//-----------------------------------------------------------------
extern void uart_init(u32 bound);
//-----------------------------------------------------------------
#endif
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
