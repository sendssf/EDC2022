#include "qmc5883.h"
#include "i2c.h"

int16_t MagnetRawAd[3];
int16_t X_Buff[CALIBTATE_DATA_NUM],Y_Buff[CALIBTATE_DATA_NUM],
Z_Buff[CALIBTATE_DATA_NUM],CalibrateCnt;

uint8_t QMC5883_ReadReg(uint8_t Reg)
{
    uint8_t RegVal = 0;
    I2C_ReadByte(&RegVal,1,Reg,QMC5883_ADDR);
    return RegVal;
}