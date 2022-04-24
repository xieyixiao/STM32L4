/*******************************************************************************
 *   Filename:       bsp_dataconversion.h
 *   Revision:       v1.0
 *   Description:    各种数据转换函数 头文件
 *******************************************************************************/
#ifndef __BSP_DATACONVERSION_H__
#define __BSP_DATACONVERSION_H__


#include <string.h>
#include "stm32l475_user.h"
/*  参数过滤
*   Dpar ：目标参数  Spar：输入的参数  Min：参数最小值  Max:参数最大值  Default：参数默认值
*   如果输入的参数在最小值和最大值的范围内，直接将输入的参数赋值给目标参数；
*   否则，就将默认参数赋值给目标参数。
*/
//#define  APP_PARFILTER(Dpar,Spar,Min,Max,Default)  (((Spar >= Min) && (Spar <= Max)) ? (Dpar = Spar): (Dpar = Default))

/***********************************************
* 描述： 供外部调用的函数申明
*/

uint8_t Bcd2Hex(uint8_t val);
uint8_t Hex2Bcd(uint8_t val);

uint16_t BEBufToUint16(uint8_t *_pBuf);
uint16_t LEBufToUint16(uint8_t *_pBuf);

uint32_t BEBufToUint32(uint8_t *_pBuf);
uint32_t LEBufToUint32(uint8_t *_pBuf);

uint8_t * UINTDatToStrings(uint16_t temp);
int16_t ChartoInt(uint8_t*chr,uint8_t lenth);
void int_to_str(int16_t _iNumber, int8_t *_pBuf, uint8_t _len);
int16_t str_to_int(int8_t *_pStr);
uint32_t AsciiToUint32(char *pAscii);
char BcdToChar(uint8_t _bcd);
void HexToAscll(uint8_t * _pHex, char *_pAscii, uint16_t _BinBytes);
int32_t  CaculTwoPoint(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x);
uint32_t AsciiToUint32(char *pAscii);

uint16_t CRC16_Modbus(uint8_t *_pBuf, uint16_t _usLen) ;

#endif

/*****************************  (END OF FILE) *********************************/