#ifndef PID_H
#define PID_H

#include "stdint.h"

//每转一圈编码盘计数
#define CountPerRound 13
//pid所在中断的频率（单位Hz）
#define pidFeq 20
//限制pid输出值的绝对值
#define pidLimit 1000
//控制pwm输出的平滑程度，范围0~1，等于1时计算pwm只考虑当次的pid输出，否则考虑前后两次的pid输出，一般取值0.6~1
#define pwmLastRatio 0.8
//限制积分变量的绝对值
#define IntegralLimit 500
//最大转速绝对值
#define Maxrpm 2000

//模糊控制（实验性）
//模糊控制作用机制：当误差Err超过设定值时激活控制：当误差降到控制起始点时开始增强阻尼，当误差继续降到控制终止点并在终止点内持续一定周期后阻尼回到正常值
//模糊控制分界点
#define DampingDividingEnableValue 50
#define DampingDividingBeginValue 40
#define DampingDividingEndValue 5
#define MaxOscillatingPeriodNum 4
//增强区内阻尼（kd）增益倍数
//增强函数为 增强倍数/（1+误差）
//注：如有更好的函数模型欢迎修改
#define DampingGain 100

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

extern pidParms MypidParms;
extern pidVars wheelpid[4];

void rpmpid_Init();

float Getrpmpid(pidParms* pm, pidVars* pv, int count, float Tagrpm);

#endif