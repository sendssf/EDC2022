#include "qmc5883.h"
#include "i2c.h"
#include "delay.h"
#include "stdint.h"

int MagnetRawAd[3];
int16_t X_Buff[CALIBTATE_DATA_NUM],Y_Buff[CALIBTATE_DATA_NUM],
Z_Buff[CALIBTATE_DATA_NUM],CalibrateCnt;

uint8_t QMC5883_ReadReg(uint8_t Reg)
{
    uint8_t RegVal = 0;
    I2C_ReadByte(&RegVal,1,Reg,QMC5883_ADDR);
    return RegVal;
}

void QMC5883_WriteReg(uint8_t Val,uint8_t Reg)
{
    I2C_WriteByte(Val,Reg, QMC5883_ADDR);
}

uint8_t QMC5883_InitConfig(void)
{
	uint8_t Temp;
	
	QMC5883_WriteReg(0x01, 0x0B);
	QMC5883_WriteReg(0x40, 0x20);
	QMC5883_WriteReg(0x01, 0x21);
	QMC5883_WriteReg(0x0D, 0x09);/****OSR=512,RNG=+/-2G,ODR=200Hz,MODE= continuous*******/
	delay_ms(TIME_DELAY);
	Temp = QMC5883_ReadReg(0x09);
	 while(Temp != 0x0D) return 1;
	
    return 0;
}

void QMC5883_GetData(float *Magnet)
{
    uint8_t Buff[6],i;
    uint8_t Temp;
    
    Temp = QMC5883_ReadReg(0x06);
    if (Temp&0x06)
    {
    	//LOG("output data OVL or ERROR!")
    	return;
    }
    else if (Temp&0x00)
    {
    	//LOG("output data not ready!")
    	return;
    }
    
    I2C_ReadByte(Buff,6,0x00,QMC5883_ADDR);
	MagnetRawAd[0] = ((int16_t)Buff[1] << 8) | Buff[0];
	MagnetRawAd[1] = ((int16_t)Buff[3] << 8) | Buff[2];
	MagnetRawAd[2] = ((int16_t)Buff[5] << 8) | Buff[4];

    for(i=0;i<3;i++)
    {
        Magnet[i] = (float)MagnetRawAd[i] / 120.f;//单位uT
		
    }
}