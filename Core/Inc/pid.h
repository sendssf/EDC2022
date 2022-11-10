#ifndef PID_H
#define PID_H

//每转一圈编码盘计数
#define CountPerRound 1080
//pid所在中断的频率（单位Hz）
#define pidFeq 100
//限制pid输出值的绝对值
#define pidLimit 1000
//控制dErr平滑程度，范围0~1，等于1时计算dErr只考虑前后两次的Err，否则考虑前后三次的Err，一般取值0.6~1
#define LastRatio 0.9
//限制积分变量的绝对值
#define IntegralLimit 1e5

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
    float Err;
    float dErr;
    float ErrSum;
}pidVars;

extern pidParms MypidParms;
extern pidVars wheelpid[4];

float Getrpmpid(pidParms* pm, pidVars* pv, int count, float Tagrpm);

#endif