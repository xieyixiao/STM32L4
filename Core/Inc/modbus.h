//
// Created by xieyixiao on 2022/4/24 0024.
//

#ifndef STM32L4_MODBUS_H
#define STM32L4_MODBUS_H

#include "stm32l475_user.h"
#include "bsp_dataconversion.h";

#define __SWP16(A)   (( ((uint16_t)(A) & 0xff00) >> 8)    | \
(( (uint16_t)(A) & 0x00ff) << 8))

#define __SWP32(A)   ((( (uint32_t)(A) & 0xff000000) >> 24) | \
(( (uint32_t)(A) & 0x00ff0000) >> 8)   | \
(( (uint32_t)(A) & 0x0000ff00) << 8)   | \
(( (uint32_t)(A) & 0x000000ff) << 24))

#pragma pack (1)
typedef struct H{
    uint8_t id;
    uint8_t op;
    uint16_t addr;
    uint16_t n;
    uint8_t len;
    uint16_t hr;
    uint16_t sbp;
    uint16_t dbp;
    float temperature;
    uint16_t crc;
}Modbus_rtu;


void Modbus_Init(Modbus_rtu *M,uint8_t id,uint8_t op,uint16_t addr,uint16_t n,uint8_t len);
void Modbus_Write(Modbus_rtu *M,uint16_t hr,uint16_t sbp,uint16_t dbp,float temperature);

#endif //STM32L4_MODBUS_H
