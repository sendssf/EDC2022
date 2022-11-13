#ifndef MOVE_H
#define MOVE_H

#include <stdbool.h>
#include <math.h>

//标准速度值
#define StandardSpeed 100
//前后方向速度增益
#define FrontBackSpeedGain 1
//左右方向速度增益
#define RightLeftSpeedGain 1
//转向速度增益
#define RotateSpeedGain 1


extern float Setrpm[4];

//基本移动函数，分别控制前后、左右、旋转分量来控制移动
void MoveBasic(float onPitchAxis, float onRollAxis, float rotateYawAxis);

//一次封装，通过输入相对角度和速度来控制移动，当isTurn为true时将会一边旋转一边以指定角度平移
void MoveReleDeg(float radian, float speed, bool isTurn);

//二次封装，
void MoveSoliDeg(float radian, float distance, bool isTurn);

#endif