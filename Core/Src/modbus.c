//
// Created by xieyixiao on 2022/4/24 0024.
//

#include "modbus.h"

void Modbus_Init(Modbus_rtu *M,uint8_t id,uint8_t op,uint16_t addr,uint16_t n,uint8_t len){
    M->id = id;
    M->op = op;
    M->addr = __SWP16(addr);
    M->n = __SWP16(n);
    M->len = len;
}
void Modbus_Write(Modbus_rtu *M,uint16_t hr,uint16_t sbp,uint16_t dbp,float temperature){
    M->hr = __SWP16(hr);
    M->sbp = __SWP16(sbp);
    M->dbp = __SWP16(dbp);
    M->temperature = temperature;
    M->crc= __SWP16(CRC16_Modbus((uint8_t*)M,17));
}