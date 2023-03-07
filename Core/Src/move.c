#include "move.h"
#include "API.h"
#include "system.h"
//#include "main.h"

pidParms MyPidParms;
pidVars WheelPid[4];
float SetRpm[4];
int WheelCounts[4];
//Position AimPos, CurPos;

extern struct JY62_Data jy62data;

void rpmpid_Init()
{
    MyPidParms.kp = 1.2;
    MyPidParms.kd = 3.8;
    MyPidParms.ki = 1;
    

    for (int i = 0; i < 4; i++)
    {
        WheelPid[i].rpm = 0;
        WheelPid[i].pwm = 0;
        WheelPid[i].Err = 0;
        WheelPid[i].dErr = 0;
        WheelPid[i].ErrSum = 0;
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
    SetRpm[0] = -(onRollAxis + onPitchAxis - RotateSpeedGain * rotateYawAxis);
    SetRpm[1] = -(onRollAxis - onPitchAxis + RotateSpeedGain * rotateYawAxis);
    SetRpm[2] = -(onRollAxis - onPitchAxis - RotateSpeedGain * rotateYawAxis);
    SetRpm[3] = (onRollAxis + onPitchAxis + RotateSpeedGain * rotateYawAxis);
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

float GetYaw()
{
    return jy62_GetYaw();
}

void PidCalucate()
{
    for (int i = 0; i < 4; i++)
    {
        if (WheelCounts[i] > 65535 - Maxrpm)
        {
            WheelCounts[i] -= 65535;
        }
        WheelPid[i].rpm = WheelCounts[i] * pidFeq / CountPerRound;
        WheelPid[i].dErr = dErrLastRaio * (SetRpm[i] - WheelPid[i].rpm - WheelPid[i].Err) + (1 - dErrLastRaio) * WheelPid[i].dErr;
        WheelPid[i].Err = SetRpm[i] - WheelPid[i].rpm;

        if (WheelPid[i].ErrSum > IntegralLimit)
        {
            if (WheelPid[i].Err < 0)
            {
                WheelPid[i].ErrSum += WheelPid[i].Err;
            }
        }
        else if (WheelPid[i].ErrSum < -IntegralLimit)
        {
            if (WheelPid[i].Err > 0)
            {
                WheelPid[i].ErrSum += WheelPid[i].Err;
            }
        }
        else{
            WheelPid[i].ErrSum += WheelPid[i].Err;
        }

        float output = MyPidParms.kp * WheelPid[i].Err + MyPidParms.kd * WheelPid[i].dErr + MyPidParms.ki * WheelPid[i].ErrSum;
        if (output > pidLimit)
        {
            output = pidLimit;
        }
        else if (output < -pidLimit)
        {
            output = -pidLimit;
        }
        WheelPid[i].pwm = pwmLastRatio * output + (1 - pwmLastRatio) * WheelPid[i].pwm;
    }
}

void MoveByAbs(int Forward, int Left)
{
    PidCalucate();
}