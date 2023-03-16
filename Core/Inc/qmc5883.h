#ifndef QMC5883_H
#define QMC5883_H

#include "stdint.h"
#define MAT_N  10
#define QMC5883_ADDR               0x1a 
#define fabs(x)                    (x < 0 ? -x : x)

#define CALIBTATE_DATA_NUM 10   //数据保留个数
#define TIME_DELAY 0X02

void qmc5883_WriteReg(uint8_t Val,uint8_t Reg);
uint8_t qmc5883_ReadReg(uint8_t Reg);
uint8_t qmc5883_InitConfig(void);
void qmc5883_GetData(float *Magnet);

#endif
