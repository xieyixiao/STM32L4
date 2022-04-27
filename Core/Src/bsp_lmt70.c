/*******************************************************************************
 *   Filename:       bsp_lmt70.c
 *   Revised:        All copyrights reserved to Roger-WY.
 *   Revision:       v1.0
 *
 *   Description:    LMT70温度传感器驱动（模拟量输出）
 *                   
 *   Notes:          https://www.ti.com.cn/product/cn/LMT70
 *     				
 *
 *******************************************************************************/

#include "bsp_lmt70.h"


//----------------------------------------------------------------------------//
#define TEMPERATURE_ADC_RESOLUTION  		4096	//12位ADC
#define TEMPERATURE_ADC_REFERENCE_VOLTAGE 	3300	//3300mv == 3.3V

//----------------------------------------------------------------------------//
#define LMT7_ENABLE_PIN_PORT    GPIOC
#define LMT7_ENABLE_PIN         GPIO_PIN_1

//----------------------------------------------------------------------------//
void bsp_Lmt70EnablePinInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = LMT7_ENABLE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LMT7_ENABLE_PIN_PORT, &GPIO_InitStruct);
}
    
void bsp_Lmt70Enable(void)
{
    HAL_GPIO_WritePin(LMT7_ENABLE_PIN_PORT,LMT7_ENABLE_PIN,SET);
}

void bsp_Lmt70Disable(void)
{
    HAL_GPIO_WritePin(LMT7_ENABLE_PIN_PORT,LMT7_ENABLE_PIN,RESET);
}

/*******************************************************************************
* 名    称： bsp_Lmt70Init
* 功    能： LMT70的初始化
* 入口参数： 
* 出口参数：
* 创建日期： 2020-09-17
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
int8_t bsp_Lmt70Init(void)                                                                    
{
    /* 使能引脚初始化 */
    bsp_Lmt70EnablePinInit();
    
	/* 该传感器是电压输出型，此处需要初始化对应ADC*/
    
	return 0;
}


/*******************************************************************************
* 名    称： bsp_GetTempBySecondOrderTransfer
* 功    能： 使用两阶传递函数计算温度
* 入口参数： voltageMv: 采集到的温度的电压值（mv）
* 出口参数： 温度值
* 创建日期： 2020-09-17
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
float bsp_GetTempBySecondOrderTransfer(float voltageMv)
{
	double temp = 0.0;
	#if 0
	//-55℃ - 150℃ 最优曲线参数
	temp = ((-8.451576 * pow(10,-6)) * pow(voltageMv,2)) + ((-0.1769281) * voltageMv) + 204.3937;
	#else
	//-10℃ - 110℃ 最优曲线参数
	temp = ((-7.857923 * pow(10,-6)) * pow(voltageMv,2)) + ((-0.1777501) * voltageMv) + 204.6398;  
	#endif
	return ((float)(temp));	
}

/*******************************************************************************
* 名    称： bsp_GetTempByThirdOrderTransfer
* 功    能： 使用三阶传递函数计算温度
* 入口参数： voltageMv: 采集到的温度的电压值（mv）
* 出口参数： 温度值
* 创建日期： 2020-09-17
* 修    改：
* 修改日期：
* 备    注：
*******************************************************************************/
float bsp_GetTempByThirdOrderTransfer(float voltageMv)
{
	double temp = 0.0;
	#if 1
	//-55℃ - 150℃ 最优曲线参数
	temp = ((-1.064200 * pow(10,-9)) * pow(voltageMv,3)) + ((-5.759725 * pow(10,-6)) * pow(voltageMv,2)) +((-0.1789883) * voltageMv) + 204.8570;
	#else
	//-10℃ - 110℃ 最优曲线参数
	temp = ((-1.809628 * pow(10,-9)) * pow(voltageMv,3)) + ((-3.325395 * pow(10,-6)) * pow(voltageMv,2)) +((-0.1814103) * voltageMv) + 205.5894;
	#endif
	return ((float)(temp));	
}

/*******************************************************************************
* 名    称： bsp_AdcToVoltage
* 功    能： 通过采集到的ADC的值计算温度
* 入口参数： ADC的值
* 出口参数： 温度的电压值，单位 mv
* 创建日期： 2020-09-17
* 修    改：
* 修改日期：
* 备    注： 根据不同参考电压和ADC的分辨率修改对应的宏定义
*******************************************************************************/
float bsp_AdcToVoltage(uint32_t adcValue)
{
	float voltage = 0;
	
	voltage = (TEMPERATURE_ADC_REFERENCE_VOLTAGE * adcValue) / TEMPERATURE_ADC_RESOLUTION;

	return (voltage);
}


/*******************************************************************************
* 名    称： bsp_ReadLmt70TemperatureInFloat
* 功    能： 通过采集到的ADC的值计算温度
* 入口参数： pTemperature:温度值(℃ ) 浮点型 , adcValue:采集到的ADC值
* 出口参数： 0：读取成功 -1：读取失败
* 创建日期： 2020-09-17
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
int8_t bsp_ReadLmt70TemperatureInFloat(float *pTemperature,uint32_t adcValue)
{
	float fVoltage = 0;
	float fTemp = 0;
	int8_t ret = -1;
	
	fVoltage = bsp_AdcToVoltage(adcValue);
	#if 1
	fTemp = bsp_GetTempBySecondOrderTransfer(fVoltage);
	#else
	fTemp = bsp_GetTempByThirdOrderTransfer(fVoltage);
	#endif
	
	if((fTemp >= -55) && (fTemp <= 150))
	{
		*pTemperature = fTemp;
		ret = 0;
	}
	
	return (ret);	
}

/*******************************************************************************
* 名    称： bsp_ReadLmt70TemperatureInInt
* 功    能： 通过采集到的ADC的值计算温度
* 入口参数： pTemperature:温度值(℃ ) 放大10倍后的整型 , adcValue:采集到的ADC值
* 出口参数： 0：读取成功 -1：读取失败
* 创建日期： 2020-09-17
* 修    改：
* 修改日期：
* 备    注： 
*******************************************************************************/
int8_t bsp_ReadLmt70TemperatureInInt(int16_t *pTemperature,uint32_t adcValue)
{
	float fTemp = 0;
	int8_t ret = -1;
	
	if(bsp_ReadLmt70TemperatureInFloat(&fTemp,adcValue) == 0)
	{
		*pTemperature = (int16_t)(fTemp * 10);	//温度值放大10倍后转成整型数
		ret = 0;
	}
	return (ret);	
}

