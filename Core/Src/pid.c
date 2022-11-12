#include "pid.h"

pidParms MypidParms;
pidVars wheelpid[4];

void rpmpid_Init()
{
    MypidParms.kd = 1;
    MypidParms.kd = 1;
    MypidParms.ki = 1;
    for (int i = 0; i < 4; i++)
    {
        wheelpid[i].Err = 0;
        wheelpid[i].dErr = 0;
        wheelpid[i].ErrSum = 0;
    }
}

float Getrpmpid(pidParms* pm, pidVars* pv, int count, float Tagrpm)
{ 
    pv->dErr = LastRatio * (Tagrpm - count * pidFeq / CountPerRound - pv->Err) + (1 - LastRatio) * pv->dErr;
    pv->Err = Tagrpm - count * pidFeq / CountPerRound;
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