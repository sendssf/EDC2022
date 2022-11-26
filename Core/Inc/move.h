#ifndef MOVE_H
#define MOVE_H

#include "stdint.h"

//绝对值
#define abs (x<0?-x:x)

//每转一圈编码盘计数
#define CountPerRound 13
//pid所在中断的频率（单位Hz）
#define pidFeq 20
//限制pid输出值的绝对值
#define pidLimit 1000
//控制dErr的平滑程度，范围0~1，当等于1时只采用最新计算出的dErr，否则考虑与上一次的dErr进行加权平均，一般取值0.6~1
#define dErrLastRaio 0.9
//控制pwm输出的平滑程度，范围0~1，等于1时计算pwm只考虑当次的pid输出，否则考虑与上一次的pwm加权平均后再输出，一般取值0.6~1
#define pwmLastRatio 0.9
//限制积分变量的绝对值
#define IntegralLimit 600
//最大转速绝对值
#define Maxrpm 2000

//转向速度增益
#define RotateSpeedGain 1

//此结构体存储pid系数
typedef struct
{
    float kp;
    float kd;
    float ki;
}pidParms;

//此结构体存储pid变量
typedef struct
{
    float rpm;
    float pwm;
    float Err;
    float dErr;
    float ErrSum;
    int8_t DEMActive;
}pidVars;

//基本移动函数，分别控制前后、左右、旋转分量来控制移动
void MoveBasic(float onPitchAxis, float onRollAxis, float rotateYawAxis);

void MoveByPCLDeg();

#endif