/*******************************************************************************
 *   Filename:       bsp_dataconversion.c
 *   Revised:        All copyrights reserved to Roger-WY.
 *   Revision:       v1.0
 *   Writer:	     Roger-WY.
 *
 *   Description:    各种数据转换函数
 *
 *
 *
 *   Notes:
 *     				 E-mail:261313062@qq.com
 *
 *******************************************************************************/
#include "bsp_dataconversion.h"

//============================================================================//
#if 1 /* 不使用CRC16校验时，可关闭 */
// CRC 高位字节值表
static const uint8_t s_CRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;
// CRC 低位字节值表
static const uint8_t s_CRCLo[] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
	0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
	0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
	0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
	0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
	0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
	0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
	0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
	0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
	0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
	0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
	0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
	0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
	0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
	0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
	0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
	0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
	0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

/*******************************************************************************
 * 名    称： CRC16_Modbus
 * 功    能： 计算CRC16。 用于Modbus协议。
 * 入口参数：  _pBuf : 参与校验的数据
 *			  _usLen : 数据长度
 * 出口参数： 16位整数值。 对于Modbus ，此结果高字节先传送，低字节后传送。
 * 作　　者： Roger-WY
 * 创建日期： 2016-01-08
 * 修    改：
 * 修改日期：
 * 备    注： 所有可能的CRC值都被预装在两个数组当中，当计算报文内容时可以简单的索引即可；
 *   一个数组包含有16位CRC域的所有256个可能的高位字节，另一个数组含有低位字节的值；
 *   这种索引访问CRC的方式提供了比对报文缓冲区的每一个新字符都计算新的CRC更快的方法；
 *
 *  注意：此程序内部执行高/低CRC字节的交换。此函数返回的是已经经过交换的CRC值；
 *        也就是说，该函数的返回值可以直接放置于报文用于发送；
 *******************************************************************************/
uint16_t CRC16_Modbus(uint8_t *_pBuf, uint16_t _usLen)
{
	uint8_t ucCRCHi = 0xFF; /* 高CRC字节初始化 */
	uint8_t ucCRCLo = 0xFF; /* 低CRC 字节初始化 */
	uint16_t usIndex;       /* CRC循环中的索引 */

    while (_usLen--) {
		usIndex = ucCRCHi ^ *_pBuf++; /* 计算CRC */
		ucCRCHi = ucCRCLo ^ s_CRCHi[usIndex];
		ucCRCLo = s_CRCLo[usIndex];
    }
    return ((uint16_t)ucCRCHi << 8 | ucCRCLo);
}

#endif


/*******************************************************************************
 * 名    称： BEBufToUint16
 * 功    能： 将2字节数组(大端Big Endian次序，高字节在前)转换为16位整数
 * 入口参数： _pBuf : 数组
 * 出口参数： 16位整数值
 * 作　　者： Roger-WY
 * 创建日期： 2009-01-08
 * 修    改：
 * 修改日期：
 * 备    注： 大端(Big Endian)与小端(Little Endian)
 *******************************************************************************/
uint16_t BEBufToUint16(uint8_t *_pBuf)
{
    return (((uint16_t)_pBuf[0] << 8) | _pBuf[1]);
}

/*******************************************************************************
 * 名    称： LEBufToUint16
 * 功    能： 将2字节数组(小端Little Endian，低字节在前)转换为16位整数
 * 入口参数： _pBuf : 数组
 * 出口参数： 16位整数值
 * 作　　者： Roger-WY
 * 创建日期： 2009-01-08
 * 修    改：
 * 修改日期：
 * 备    注：
 *******************************************************************************/
uint16_t LEBufToUint16(uint8_t *_pBuf)
{
    return (((uint16_t)_pBuf[1] << 8) | _pBuf[0]);
}

/*******************************************************************************
 * 名    称： BEBufToUint32
 * 功    能： 将4字节数组(大端Big Endian次序，高字节在前)转换为32位整数
 * 入口参数： _pBuf : 数组
 * 出口参数： 32位整数值
 * 作　　者： Roger-WY
 * 创建日期： 2009-01-08
 * 修    改：
 * 修改日期：
 * 备    注：大端(Big Endian)与小端(Little Endian)
 *******************************************************************************/
uint32_t BEBufToUint32(uint8_t *_pBuf)
{
    return (((uint32_t)_pBuf[0] << 24) | ((uint32_t)_pBuf[1] << 16) | ((uint32_t)_pBuf[2] << 8) | _pBuf[3]);
}

/*******************************************************************************
 * 名    称： LEBufToUint32
 * 功    能： 将4字节数组(小端Little Endian，低字节在前)转换为32位整数
 * 入口参数： _pBuf : 数组
 * 出口参数： 32位整数值
 * 作　　者： Roger-WY
 * 创建日期： 2009-01-08
 * 修    改：
 * 修改日期：
 *******************************************************************************/
uint32_t LEBufToUint32(uint8_t *_pBuf)
{
    return (((uint32_t)_pBuf[3] << 24) | ((uint32_t)_pBuf[2] << 16) | ((uint32_t)_pBuf[1] << 8) | _pBuf[0]);
}

/*******************************************************************************
 * 名    称： bcd2Hex
 * 功    能： BCD码转16进制
 * 入口参数：
 * 出口参数： 无
 * 作　　者： Roger-WY
 * 创建日期： 2009-01-08
 * 修    改：
 * 修改日期：
 *******************************************************************************/
uint8_t Bcd2Hex(uint8_t val)
{
    return ((val&0x0f)+(val >> 4)*10);
}

/*******************************************************************************
 * 名    称： hex2Bcd
 * 功    能： 16进制转BCD码
 * 入口参数：
 * 出口参数： 无
 * 作　　者： Roger-WY
 * 创建日期： 2009-01-08
 * 修    改：
 * 修改日期：
 *******************************************************************************/
uint8_t Hex2Bcd(uint8_t val)
{
    return ((val / 10) << 4) + val % 10;
}

/*******************************************************************************
* 名    称： ChartoInt
* 功    能： 将字符转换成整型
* 入口参数： chr：字符串指针 ； lenth：字符串的长度
* 出口参数： 转换之后的整型数
* 作　　者： Roger-WY
* 创建日期： 2014-07-05
* 修    改：
* 修改日期：
*******************************************************************************/
int16_t ChartoInt(uint8_t *chr,uint8_t lenth)
{
    u8 count = 0;
    u16 value = 0;
    for(count = 0 ; count < lenth ; count++) {
        value = value*10 + (chr[count]-0x30);
    }
    return value;
}

/*******************************************************************************
* 名    称： UINTDatToStrings
* 功    能： int转String函数
* 入口参数： 需要转成字符串的整数
* 出口参数： 转换完成的字符串
* 作　　者： Roger-WY
* 创建日期： 2014-07-05
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
uint8_t * UINTDatToStrings(uint16_t temp)
{
    u8 table[10] = {0,1,2,3,4,5,6,7,8,9};
    static uint8_t ret[6] = {0,0,0,0,0,0};
    u16   value = 0;
    u8    DatLength = 1;
    value =  temp;
    while((value / 10) > 0) {
        DatLength++;
        value = value / 10;
        if(DatLength > 5) {
            DatLength = 0;
            break;
        }
    }
    ret[DatLength] = 0;
    value =  temp;
    for(u8 i = DatLength ;i > 0 ; i--) {
        ret[i-1] = table[value % 10];
        value = value/10;
    }
    return ret;
}

/*******************************************************************************
* 名    称： int_to_ascii
* 功    能： 将整数转换为ASCII数组。支持负数。
* 入口参数：  _Number : 整数
*			 _pBuf : 目标缓冲区, 存放转换后的结果。以0结束的字符串。
*			 _len : ASCII字符个数, 字符串长度
* 出口参数： 无
* 作　　者： Roger-WY
* 创建日期： 2014-07-05
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
void int_to_str(int16_t _iNumber, int8_t *_pBuf, uint8_t _len)
{
	uint8_t i;
	int16_t iTemp;

	if (_iNumber < 0) {	/* 负数 */
		iTemp = -_iNumber;	/* 转为正数 */
	} else {
		iTemp = _iNumber;
	}
	//memset(_pBuf, ' ',_len);
    memset(_pBuf, '0',_len);
	/* 将整数转换为ASCII字符串 */
	for (i = 0; i < _len; i++) {
		_pBuf[_len - 1 - i] = (iTemp % 10) + '0';
		iTemp = iTemp / 10;
		if (iTemp == 0) {
			break;
		}
	}
	_pBuf[_len] = 0;

	if (_iNumber < 0) {	/* 负数 */
		for (i = 0; i < _len; i++) {
			if ((_pBuf[i] == ' ') && (_pBuf[i + 1] != ' ')) {
				_pBuf[i] = '-';
				break;
			}
		}
	}
}

/*******************************************************************************
* 名    称： str_to_int
* 功    能： 将ASCII码字符串转换成整数。 遇到小数点自动越过。
* 入口参数：  _pStr :待转换的ASCII码串. 可以以逗号，#或0结束。 2014-06-20 修改为非0-9的字符。
* 出口参数： 二进制整数值
* 作　　者： Roger-WY
* 创建日期： 2014-07-05
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
int16_t str_to_int(int8_t *_pStr)
{
	uint8_t flag;
	int8_t *p;
	int16_t ulInt;
	uint8_t  i;
	uint8_t  ucTemp;

	p = _pStr;
	if (*p == '-') {
		flag = 1;	/* 负数 */
		p++;
	} else {
		flag = 0;
	}

	ulInt = 0;
	for (i = 0; i < 15; i++) {
		ucTemp = *p;
		if (ucTemp == '.')	{  /* 遇到小数点，自动跳过1个字节 */
			p++;
			ucTemp = *p;
		}
		if ((ucTemp >= '0') && (ucTemp <= '9')) {
			ulInt = ulInt * 10 + (ucTemp - '0');
			p++;
		} else {
			break;
		}
	}

	if (flag == 1) {
		return -ulInt;
	}
	return ulInt;
}

/*******************************************************************************
* 名    称： CaculTwoPoint
* 功    能： 根据2点直线方程，计算Y值
* 入口参数：  个点的坐标和x输入量
* 出口参数： x对应的y值
* 作　　者： Roger-WY
* 创建日期： 2016-07-05
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
int32_t  CaculTwoPoint(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x)
{
	return y1 + ((int64_t)(y2 - y1) * (x - x1)) / (x2 - x1);
}

/*******************************************************************************
* 名    称： BcdToChar
* 功    能： 将BCD码转为ASCII字符。 比如 0x0A ==> 'A'
* 入口参数： _bcd   ：输入的二进制数。必须小于16
* 出口参数： 转换结果
* 作　　者： Roger-WY
* 创建日期： 2016-07-05
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
char BcdToChar(uint8_t _bcd)
{
	if (_bcd < 10) {
		return _bcd + '0';
	} else if (_bcd < 16) {
		return _bcd + 'A';
	} else {
		return 0;
	}
}

/*******************************************************************************
* 名    称： HexToAscll
* 功    能： 将二进制数组转换为16进制格式的ASCII字符串。每个2个ASCII字符后保留1个空格。
*            0x12 0x34 转化为 0x31 0x32 0x20 0x33 0x34 0x00  即 "1234"
* 入口参数： _pHex   ：输入的数据，二进制数组
*			_pAscii ：存放转换结果, ASCII字符串，0结束。1个二进制对应2个ASCII字符.
* 出口参数： 转换得到的整数
* 作　　者： Roger-WY
* 创建日期： 2016-07-05
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
void HexToAscll(uint8_t * _pHex, char *_pAscii, uint16_t _BinBytes)
{
	uint16_t i;

	if (_BinBytes == 0)
	{
		_pAscii[0] = 0;
	}
	else
	{
		for (i = 0; i < _BinBytes; i++)
		{
			_pAscii[3 * i]     = BcdToChar(_pHex[i] >> 4);
			_pAscii[3 * i + 1] = BcdToChar(_pHex[i] & 0x0F);
			_pAscii[3 * i + 2] = ' ';
		}
		_pAscii[3 * (i - 1) + 2] = 0;
	}
}

/*******************************************************************************
* 名    称： AsciiToUint32
* 功    能： 变长的 ASCII 字符转换为32位整数  ASCII 字符以空格或者0结束 。 支持16进制和10进制输入
*            0x12 0x34 转化为 0x31 0x32 0x20 0x33 0x34 0x00  即 "1234"
* 入口参数：*pAscii ：要转换的ASCII码
* 出口参数： 转换得到的整数
* 作　　者： Roger-WY
* 创建日期： 2016-07-05
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
uint32_t AsciiToUint32(char *pAscii)
{
	char i;
	char bTemp;
	char bIsHex;
	char bLen;
	char bZeroLen;
	uint32_t lResult;
	uint32_t lBitValue;

	/* 判断是否是16进制数 */
	bIsHex = 0;
	if ((pAscii[0] == '0') && ((pAscii[1] == 'x') || (pAscii[1] == 'X'))) {
		bIsHex=1;
	}

	lResult=0;
	// 最大数值为 4294967295, 10位+2字符"0x" //
	if (bIsHex == 0) { // 十进制 //
		// 求长度 //
		lBitValue=1;

		/* 前导去0 */
		for (i = 0; i < 8; i++) {
			bTemp = pAscii[i];
			if (bTemp != '0')
				break;
		}
		bZeroLen = i;

		for (i = 0; i < 10; i++) {
			if ((pAscii[i] < '0') || (pAscii[i] > '9'))
				break;
			lBitValue = lBitValue * 10;
		}
		bLen = i;
		lBitValue = lBitValue / 10;
		if (lBitValue == 0)
			lBitValue=1;
		for (i = bZeroLen; i < bLen; i++) {
			lResult += (pAscii[i] - '0') * lBitValue;
			lBitValue /= 10;
		}
	} else {	/* 16进制 */
		/* 求长度 */
		lBitValue=1;

		/* 前导去0 */
		for (i = 0; i < 8; i++) {
			bTemp = pAscii[i + 2];
			if(bTemp!='0')
				break;
		}
		bZeroLen = i;
		for (; i < 8; i++) {
			bTemp=pAscii[i+2];
			if (((bTemp >= 'A') && (bTemp <= 'F')) ||
				((bTemp>='a')&&(bTemp<='f')) ||
				((bTemp>='0')&&(bTemp<='9')) ) {
				lBitValue=lBitValue * 16;
			} else {
				break;
			}
		}
		lBitValue = lBitValue / 16;
		if (lBitValue == 0)
			lBitValue = 1;
		bLen = i;
		for (i = bZeroLen; i < bLen; i++) {
			bTemp = pAscii[i + 2];
			if ((bTemp >= 'A') && (bTemp <= 'F')) {
				bTemp -= 0x37;
			} else if ((bTemp >= 'a') && (bTemp <= 'f')) {
				bTemp -= 0x57;
			} else if ((bTemp >= '0') && (bTemp <= '9')) {
				bTemp -= '0';
			}
			lResult += bTemp*lBitValue;
			lBitValue /= 16;
		}
	}
	return lResult;
}

/*******************************************************************************
 * 名    称： App_EncryptionAlgorithm
 * 功    能： 加密算法（自拟版）
 * 入口参数： uint8_t* pSendMsg ：需要加密的数据帧
 *			  uint8_t ucLength：  数据帧的长度
 *			  uint8_t ucKey：     加密的密钥
 * 出口参数： 数据帧的长度
 * 作　　者： Roger-WY.
 * 创建日期： 2017-12-25
 * 修    改：
 * 修改日期：
 * 备    注：  以字节为单位，原数据每个字节加上密钥（0xD6），并将高4位与低4位对调。
 *******************************************************************************/
uint8_t App_EncryptionAlgorithm(uint8_t* pSendMsg,uint8_t ucLength, uint8_t ucKey)
{
	uint8_t ucDatabuf[50] = {0};				//临时缓存数据的大小后续根据发送数据量的大小可再调整
	uint8_t ucTemp        = 0;;
	for(uint8_t i = 0;i < ucLength;i++) {
		ucDatabuf[i] = pSendMsg[i] + ucKey;		//在原来数据的基础上加上密钥
		ucTemp = ucDatabuf[i] << 4;				//将该字节的高4位和低4位互换
		ucTemp = ucTemp | (ucDatabuf[i] >> 4);
		ucDatabuf[i] = ucTemp;
	}

	for(uint8_t i = 0;i < ucLength;i++) {
		pSendMsg[i] = ucDatabuf[i];
	}
	return (ucLength);							//返回值为数据包的长度
}
/*******************************************************************************
 * 名    称： App_DecryptAlgorithm
 * 功    能： 解密算法（自拟版）
 * 入口参数： uint8_t* pSendMsg ：需要解密的数据帧
 *			  uint8_t ucLength：  数据帧的长度
 *			  uint8_t ucKey：     解密的密钥
 * 出口参数： 数据帧的长度
 * 作　　者： Roger-WY.
 * 创建日期： 2017-12-25
 * 修    改：
 * 修改日期：
 * 备    注： 以字节为单位，原数据每个字节加上密钥（0xD6），并将高4位与低4位对调。
 *******************************************************************************/
uint8_t  App_DecryptAlgorithm(uint8_t* pSendMsg,uint8_t ucLength, uint8_t ucKey)
{
	uint8_t ucDatabuf[50] = {0};				//临时缓存数据的大小后续根据发送数据量的大小可再调整
	uint8_t ucTemp        = 0;;
	for(uint8_t i = 0;i < ucLength;i++) {
		ucDatabuf[i] = pSendMsg[i];
		ucTemp = ucDatabuf[i] << 4;				//将该字节的高4位和低4位互换
		ucTemp = ucTemp | (ucDatabuf[i] >> 4);
		ucDatabuf[i] = ucTemp - ucKey;			//减去密钥
	}

	for(uint8_t i = 0;i < ucLength;i++) {
		pSendMsg[i] = ucDatabuf[i];
	}
	return (ucLength);							//返回值为数据包的长度
}

/*****************************  (END OF FILE) *********************************/
