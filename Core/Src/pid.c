#include "pid.h"

#define ROLL1_IN1 PBout(15)

pidParms MypidParms;
pidVars wheelpid[4];

void rpmpid_Init()
{
    MypidParms.kp = 1.2;
    MypidParms.kd = 3.8;
    MypidParms.ki = 0.8;
    for (int i = 0; i < 4; i++)
    {
        wheelpid[i].rpm = 0;
        wheelpid[i].pwm = 0;
        wheelpid[i].Err = 0;
        wheelpid[i].dErr = 0;
        wheelpid[i].ErrSum = 0;
    }
}

float Getrpmpid(pidParms* pm, pidVars* pv, int count, float Tagrpm)
{ 
    if (count > 65535 - Maxrpm)
    {
        count -= 65535;
    }
    pv->rpm = count * pidFeq / CountPerRound;
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
        output = pidLimit;
    }
    else if (output < -pidLimit)
    {
        output = -pidLimit;
    }
    pv->pwm = pwm_LastRatio * output + (1 - pwm_LastRatio) * pv->pwm;
    return pv->pwm;
}