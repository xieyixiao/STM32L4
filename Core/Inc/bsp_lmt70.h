#ifndef __BSP_LMT70_H__
#define __BSP_LMT70_H__

#include <stdint.h>
#include <math.h>
#include "stm32l475_user.h"

void bsp_Lmt70Enable(void);
void bsp_Lmt70Disable(void);
int8_t bsp_Lmt70Init(void);
int8_t bsp_ReadLmt70TemperatureInFloat(float *pTemperature,uint32_t adcValue);
int8_t bsp_ReadLmt70TemperatureInInt(int16_t *pTemperature,uint32_t adcValue);

#endif
