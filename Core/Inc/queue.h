#ifndef QUEUE_H
#define QUEUE_H

#include "main.h"
#define QUEUE_LEN 100   //队列大小，可更改

typedef struct {
    double dist;
    uint8_t num;
} QNODE;

extern QNODE q[QUEUE_LEN];  //队列，不要尝试直接访问
extern uint16_t hapsize;    //当前队列长度，不要尝试修改

uint16_t LeftC(uint16_t i);
uint16_t RightC(uint16_t i);
uint16_t Parent(uint16_t i);

void FixUp(uint16_t k);
void FixDown(uint16_t k);

uint8_t Qempty(void);   //检查队列是否为空，如果为空返回1，否则返回0
void Qpush(QNODE n);    //插入元素
QNODE Qtop();           //返回堆顶元素（权值最小的），不删去
QNODE Qpop();           //删除堆顶元素并且返回值

#endif