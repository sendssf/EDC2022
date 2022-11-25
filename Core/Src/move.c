#include "move.h"

float Setrpm[4];
float tanPCLDeg;

void MoveBasic(float onPitchAxis, float onRollAxis, float rotateYawAxis)
{
    Setrpm[0] = -(FrontBackSpeedGain * onRollAxis + RightLeftSpeedGain * onPitchAxis - RotateSpeedGain * rotateYawAxis);
    Setrpm[1] = -(FrontBackSpeedGain * onRollAxis - RightLeftSpeedGain * onPitchAxis + RotateSpeedGain * rotateYawAxis);
    Setrpm[2] = -(FrontBackSpeedGain * onRollAxis - RightLeftSpeedGain * onPitchAxis - RotateSpeedGain * rotateYawAxis);
    Setrpm[3] = (FrontBackSpeedGain * onRollAxis + RightLeftSpeedGain * onPitchAxis + RotateSpeedGain * rotateYawAxis);
}

void MoveByPCLDeg(float tanValue, bool isTurn)
{
    if (isTurn)
    {
        MoveBasic(0.8 * sinf(radian) * speed, 0.8 * cosf(radian) * speed, 0);
    }
    else{
        MoveBasic(sinf(radian) * speed, cosf(radian) * speed, 0);
    }
}