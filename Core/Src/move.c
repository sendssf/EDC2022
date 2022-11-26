#include "move.h"
#include "API.h"
#include "system.h"

pidParms MypidParms;
pidVars wheelpid[4];
float Setrpm[4];
float Xcomponent, Ycomponent;
Position AimPos, CurPos;

void rpmpid_Init()
{
    MypidParms.kp = 1.2;
    MypidParms.kd = 3.8;
    MypidParms.ki = 1;

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

void MoveBasic(float onPitchAxis, float onRollAxis, float rotateYawAxis)
{
    Setrpm[0] = -(onRollAxis + onPitchAxis - RotateSpeedGain * rotateYawAxis);
    Setrpm[1] = -(onRollAxis - onPitchAxis + RotateSpeedGain * rotateYawAxis);
    Setrpm[2] = -(onRollAxis - onPitchAxis - RotateSpeedGain * rotateYawAxis);
    Setrpm[3] = (onRollAxis + onPitchAxis + RotateSpeedGain * rotateYawAxis);
}

void MoveByPCLDeg()
{
    GetMyPos(&CurPos);
    if ((AimPos.x - CurPos.x) ^ 2 + (AimPos.y - CurPos.y) ^ 2 < 60)
    {
        MoveBasic(0, 0, 0);
        PAout(5) = 0;
        return;
    }
}