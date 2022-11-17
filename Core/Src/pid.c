#include "pid.h"

pidParms MypidParms;
pidVars wheelpid[4];

void rpmpid_Init()
{
    MypidParms.kp = 1;
    MypidParms.kd = 5;
    MypidParms.ki = 1;
    
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
    pv->dErr = Tagrpm - pv->rpm - pv->Err;
    pv->Err = Tagrpm - pv->rpm;

    float output;
    if (abs(pv->Err) > DampingDividingEnableValue)
    {
        pv->DEMActive = 0;
    }
    if (pv->DEMActive >= 0)
    {
        if (abs(pv->Err) < DampingDividingBeginValue)
        { 
            output = pm->kp * pv->Err + (DampingGain / (abs(pv->Err) + 1)) * pm->kd * pv->dErr;
            if (abs(pv->Err) < DampingDividingEndValue)
            {
                pv->DEMActive += 1;
                if (pv->DEMActive >= MaxOscillatingPeriodNum)
                {
                    pv->DEMActive == -1;
                }
            }
            pv->pwm = pwmLastRatio * output + (1 - pwmLastRatio) * pv->pwm;
            return pv->pwm;
        }
    }
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
    if (abs(pv->Err) > DampingDividingEnableValue)
    {
        pv->DEMActive = 0;
    }
    output = pm->kp * pv->Err + pm->kd * pv->dErr + pm->ki * pv->ErrSum;
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