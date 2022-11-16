#include "API.h"

ChargerInfo mycharger;  //存储电池信息
ChargerInfo enemycharger; 

Trace trace;
Node* foodlist;
Block block[10];
uint8_t map[255][255];      //地图数组

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
    Position t1;
    return t1;
}

//设置充电站
void SetCharger(void){

}


