/*
- **（编码器计数）__HAL_TIM_GetCounter(&htim)**
    - 参数：定时器的编号。

- **（计数寄存器置零）__HAL_TIM_SetCounter(&htim, 0)**
    - 这是在TIM内部的一个计数器置零

- **（判断马达转向）__HAL_TIM_IS_TIM_COUNTING_DOWN（&htim）**
    - 获得当前电机的转向， 0为正、1为负。

- **（使能定时器x的通道n，设定为PWM输出）HAL_TIM_PWM_Start(&htimx, TIM_CHANNEL_n)**
    - 用于给PWM输出时钟使能，在主循环之前使用。
- （**PWM波输出）__HAL_TIM_SetCompare(&htimx,TIM_CHANNEL_1, pwm)**
    - 参数从左到右分别是：定时器编号+通道编号+pwm输出时间（和之前设置的period计数周期有关） 比如，我们之前如果设计数周期是置的是1000-1，那么如果要60占空比，则将pwm输出为1000*60%=600

*/

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

float Getrpmpid(pidParms* pm, pidVars* pv, int count, float Tagrpm);

#endif