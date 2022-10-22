#include "API.h"

ChargerInfo mycharger;  //存储电池信息
ChargerInfo enemycharger; 

Trace trace;
Node* foodlist;
Block block[10];

//函数功能：获得小车当前的前进方向
//返回值：小车行进方向的绝对极坐标角度
//返回值范围:0~359
uint16_t GetDegree(){
    return 0;
}


//函数功能：获得己方小车当前的位置
//返回值：无，用结构体指针来返回结果
void GetMyPos(Position* pos){

}

//函数功能：控制小车向相对目前行进角度的多少度方向行进
//参数：degree,相对角度，范围-179~180，逆时针为正向
//     speed,车速,范围0~255,0表示停止
void MoveRelaDeg(int16_t degree,uint8_t speed){

}

//函数功能：控制小车向绝对角度degree方向行进
//参数：degree,极坐标绝对角度，范围0~359
//     speed,车速，同上
void MoveSoliDeg(int16_t degree,uint8_t speed){

}

//获得己方充电站位置
//参数：坐标结构体指针，用来返回结果
void GetMyChargerPos(Position* pos[]){

}

//获得敌方充电站位置
//参数：坐标结构体指针，用来返回结果
void GetEnemyChargerPos(Position* pos[]){

}

//获得续航，返回续航值
uint32_t GetEnergy(){
    return 0;
}

//获得之前的第number个点（第一个为前一个点）
Position GetPrevPos(uint8_t number){
    Position t;
    return t;
}

//设置充电站
void SetCharger(void){

}
