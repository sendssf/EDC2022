#include "API.h"
#include "zigbee_edc24.h"

ChargerInfo mycharger;  //存储电池信息
ChargerInfo enemycharger; 

Trace trace;
Node* foodlist;
Block block[20];
uint8_t blocknum;
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
    Position_edc24 ptemp;
    ptemp=getVehiclePos();
    pos->x=(uint8_t)ptemp.x;
    pos->y=(uint8_t)ptemp.y;
}

//获得己方充电站位置
//参数：坐标结构体指针，用来返回结果
void GetMyChargerPos(){
    if(getGameStage()==SecondHalf){
        mycharger.chargernum=getOppChargingPileNum();
        for(uint8_t i=0;i<mycharger.chargernum;i++){
            Position_edc24 ptemp=getOneOwnPile(i);
            mycharger.Charger[i].x=(uint8_t)ptemp.x;
            mycharger.Charger[i].y=(uint8_t)ptemp.y;
        }
    }
}

//获得敌方充电站位置
//参数：坐标结构体指针，用来返回结果
void GetEnemyChargerPos(){
    if(getGameStage()==SecondHalf){
        enemycharger.chargernum=getOppChargingPileNum();
        for(uint8_t i=0;i<enemycharger.chargernum;i++){
            Position_edc24 ptemp=getOneOppPile(i);
            enemycharger.Charger[i].x=(uint8_t)ptemp.x;
            enemycharger.Charger[i].y=(uint8_t)ptemp.y;
        }
    }
}

//获得续航，返回续航值
uint32_t GetEnergy(){
    return getRemainDist();
}

//获得之前的第number个点（第一个为前一个点）
Position GetPrevPos(uint8_t number){
    Position t1;
    return t1;
}

//设置充电站
void SetCharger(void){
    if(mycharger.chargernum<3&&getGameStage()==FirstHalf){
        setChargingPile();
        Position_edc24 ptemp;
        ptemp=getVehiclePos();          //设置充电站的同时存储位置
        uint8_t temp=mycharger.chargernum;
        mycharger.Charger[temp].x=ptemp.x;
        mycharger.Charger[temp].y=ptemp.y;
        mycharger.chargernum++;
    }
}

void InitMap(void){
    for(int x=39;x<=216;x++){   //初始化边界
        map[39][x]=Blocks;
        map[40][x]=Blocks;
        map[215][x]=Blocks;
        map[216][x]=Blocks;
    }
    for(int x=108;x<=147;x++){
        map[39][x]=Empty;
        map[40][x]=Empty;
        map[215][x]=Empty;
        map[216][x]=Empty;
    }
    for(int y=39;y<=216;y++){
        map[y][39]=Blocks;
        map[y][40]=Blocks;
        map[y][215]=Blocks;
        map[y][216]=Blocks;
    }
    for(int y=108;y<=147;y++){
        map[y][39]=Empty;
        map[y][40]=Empty;
        map[y][215]=Empty;
        map[y][216]=Empty;
    }

    //初始化Blocks
    blocknum+=8;

    block[0].upleft.x=39;
    block[0].upleft.y=39;
    block[0].downright.x=107;
    block[0].downright.y=40;

    block[1].upleft=block[0].upleft;
    block[1].downright.x=40;
    block[1].downright.y=107;

    block[2].upleft.x=39;
    block[2].upleft.y=148;
    block[2].downright.x=40;
    block[2].downright.y=216;

    block[3].upleft.x=39;
    block[3].upleft.y=215;
    block[3].downright.x=107;
    block[3].downright.y=216;

    block[4].upleft.x=148;
    block[4].upleft.y=215;
    block[4].downright.x=216;
    block[4].downright.y=216;

    block[5].upleft.x=215;
    block[5].upleft.y=148;
    block[5].downright=block[4].downright;

    block[6].upleft.x=215;
    block[6].upleft.y=39;
    block[6].downright.x=216;
    block[6].downright.y=107;

    block[7].upleft.x=148;
    block[7].upleft.y=39;
    block[7].downright.x=216;
    block[7].downright.y=40;
}

void UpdateBlocks(void){
    
}