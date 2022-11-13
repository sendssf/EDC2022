#include "pid.h"
#include "system.h"

#define ROLL1_IN1 PBout(15)

pidParms MypidParms;
pidVars wheelpid[4];

void rpmpid_Init()
{
    MypidParms.kp = 1;
    MypidParms.kd = 1;
    MypidParms.ki = 1;
    for (int i = 0; i < 4; i++)
    {
        wheelpid[i].rpm = 0;
        wheelpid[i].Err = 0;
        wheelpid[i].dErr = 0;
        wheelpid[i].ErrSum = 0;
    }
}

float Getrpmpid(pidParms* pm, pidVars* pv, int count, float Tagrpm)
{ 
    pv->rpm = rpm_LastRatio * count * pidFeq / CountPerRound + (1 - rpm_LastRatio) * pv->rpm;
    pv->dErr = dErr_LastRatio * (Tagrpm - pv->rpm - pv->Err) + (1 - dErr_LastRatio) * pv->dErr;
    pv->Err = Err_LastRatio * (Tagrpm - pv->rpm) + (1 - Err_LastRatio) * pv->Err;
    if (pv->ErrSum > IntegralLimit)
    {
        if (pv->Err < 0)
        {
            pv->ErrSum += pv->Err;
        }
    }
    else if (pv->ErrSum < -IntegralLimit)
    {
        if (pv->Err > 0)
        {
            pv->ErrSum += pv->Err;
        }
    }
    else{
        pv->ErrSum += pv->Err;
    }
    float output = pm->kp * pv->Err + pm->kd * pv->dErr + pm->ki * pv->ErrSum;
    if (output > pidLimit)
    {
        return pidLimit;
    }
    else if (output < -pidLimit)
    {
        return -pidLimit;
    }
    else{
        return output;
    }
}