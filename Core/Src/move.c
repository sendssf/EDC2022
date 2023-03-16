#include "move.h"
#include "API.h"
#include "system.h"
//#include "main.h"

PidParms WheelPidParms, YawPidParms;
WheelPidVars WheelPid[4];
YawPidVars YawPid[4];
float SetRpm[4];
int WheelCounts[4];

void InitPid()
{
    for (int i = 0; i < 4; i++)
    {
        WheelPid[i].rpm = 0;
        WheelPid[i].pwm = 0;
        WheelPid[i].Err = 0;
        WheelPid[i].dErr = 0;
        WheelPid[i].ErrSum = 0;
        YawPid[i].Err = 0;
        YawPid[i].dErr = 0;
        YawPid[i].ErrSum = 0;
    }
}

void SetWheelCount(int w1, int w2, int w3, int w4)
{
    WheelCounts[0] = w1;
    WheelCounts[0] = w2;
    WheelCounts[0] = w3;
    WheelCounts[0] = w4;
}

void WheelPidCalucate()
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

        float output = WheelPidParms.kp * WheelPid[i].Err + WheelPidParms.kd * WheelPid[i].dErr + WheelPidParms.ki * WheelPid[i].ErrSum;
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

void MoveBasic(float onPitchAxis, float onRollAxis, float rotateYawAxis)
{
    SetRpm[0] = -(onRollAxis + onPitchAxis - RotateSpeedGain * rotateYawAxis);
    SetRpm[1] = -(onRollAxis - onPitchAxis + RotateSpeedGain * rotateYawAxis);
    SetRpm[2] = -(onRollAxis - onPitchAxis - RotateSpeedGain * rotateYawAxis);
    SetRpm[3] = (onRollAxis + onPitchAxis + RotateSpeedGain * rotateYawAxis);
}

void YawCalibration(float x, float y)
{
    
}

void MoveByAbs(float x, float y)
{
    
}