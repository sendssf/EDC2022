#ifndef API_H
#define API_H

#include "stdint.h"

//结构体，用来存储点的坐标
typedef struct {
    uint8_t x;
    uint8_t y;
} Position;

//结构体，用来存储充电站信息
typedef struct{
    Position Charger[3];
    uint8_t chargernum;
} ChargerInfo;

//结构体，用来存储小车经过的点，为循环队列
typedef struct{
    uint8_t head;   //删除并访问数据的起点
    uint8_t tile;   //插入数据的起点
    uint8_t len;    //队列长度
    Position pos[11];
}Trace;

//外卖
typedef struct{
    Position start;     //起点
    Position end;       //终点
    uint8_t money;      //金钱
    uint8_t time;       //配送时间
    uint8_t timerest;   //剩余时间
    uint8_t ifpick;     //是否捡到
}Food;

//用链表存储外卖
typedef struct List{
    Food food;
    struct List* next;
}Node;

//障碍物
typedef struct{
    Position upleft;    //左上角点
    Position downright; //右下角点
}Block;

//声明共享的变量
extern ChargerInfo mycharger;  //存储电池信息
extern ChargerInfo enemycharger; 

extern Trace trace;
extern Node* foodlist;
extern Block block[10];


//函数功能：获得小车当前的前进方向
//返回值：小车行进方向的绝对极坐标角度
//返回值范围:0~359
uint16_t GetDegree();


//函数功能：获得己方小车当前的位置
//返回值：无，用结构体指针来返回结果
void GetMyPos(Position* pos);

//函数功能：控制小车向相对目前行进角度的多少度方向行进
//参数：degree,相对角度，范围-179~180，逆时针为正向
//     speed,车速,范围0~255,0表示停止
void MoveRelaDeg(int16_t degree,uint8_t speed);

//函数功能：控制小车向绝对角度degree方向行进
//参数：degree,极坐标绝对角度，范围0~359
//     speed,车速，同上
void MoveSoliDeg(int16_t degree,uint8_t speed);

//获得己方充电站位置
//参数：坐标结构体指针，用来返回结果
void GetMyChargerPos(Position* pos[]);

//获得敌方充电站位置
//参数：坐标结构体指针，用来返回结果
void GetEnemyChargerPos(Position* pos[]);

//获得续航，返回续航值
uint32_t GetEnergy();

//获得之前的第number个点（第一个为前一个点）
Position GetPrevPos(uint8_t number);

//设置充电站
void SetCharger(void);

#endif