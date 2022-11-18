#include "pid.h"

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
        wheelpid[i].DEMActive = -1;
    }
}

float abs(float num)
{
    if (num < 0)
    {
        return -num;
    }
    return num;
}

float Getrpmpid(pidParms* pm, pidVars* pv, int count, float Tagrpm)
{ 
    if (count > 65535 - Maxrpm)
    {
        count -= 65535;
    }
    pv->rpm = count * pidFeq / CountPerRound;
    pv->dErr = dErrLastRaio * (Tagrpm - pv->rpm - pv->Err) + (1 - dErrLastRaio) * pv->dErr;
    pv->Err = Tagrpm - pv->rpm;

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

    if (abs(pv->Err) > ZoneTriggerErr)
    {
        pv->DEMActive = 0;
    }
    if (pv->DEMActive >= 0)
    {
        pv->dErr = 0;
        if (abs(pv->Err) < ZoneEndErr)
        {
            pv->ErrSum = 0;
            pv->DEMActive = -1;
        }

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
    pv->pwm = pwmLastRatio * output + (1 - pwmLastRatio) * pv->pwm;
    return pv->pwm;
}