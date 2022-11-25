#ifndef API_H
#define API_H

#include "stdint.h"

//map数组的值：
#define Empty 0         //啥也没有的位置
#define Blocks 1        //障碍物区域
#define Mycharger 2     //我方充电站
#define Enemycharger 3  //敌方充电站
#define Begins 4        //外卖起点
#define Ends 5          //外卖终点


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
extern Block block[20];
extern uint8_t blocknum;


//函数功能：获得小车当前的前进方向
//返回值：小车行进方向的绝对极坐标角度
//返回值范围:0~359
uint16_t GetDegree();


//函数功能：获得己方小车当前的位置
//返回值：无，用结构体指针来返回结果
void GetMyPos(Position* pos);

//获得己方充电站位置
//参数：无
//仅在第二轮游戏中调用
void GetMyChargerPos();

//获得敌方充电站位置
//参数：无
//仅在第二轮游戏中调用
void GetEnemyChargerPos();

//获得续航，返回续航值
uint32_t GetEnergy();

//获得之前的第number个点（第一个为前一个点）
Position GetPrevPos(uint8_t number);

//设置充电站
void SetCharger(void);

//初始化地图
void InitMap();

//刷新障碍物，一般需要经常调用判断是否有障碍物更新或者取消
void UpdateBlocks(void);

#endif