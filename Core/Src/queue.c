#include "queue.h"

QNODE q[QUEUE_LEN];
uint16_t hapsize=0;

uint16_t LeftC(uint16_t i){
    int left=2*i+1;
    if(left>=hapsize){
        return -1;
    }
    else {
        return left;
    }
}

uint16_t RightC(uint16_t i){
    int right=2*i+2;
    if(right>=n){
        return -1;
    }
    else {
        return right;
    }
}

uint16_t Parent(uint16_t i){
    if(i==0){
        return -1;
    }
    else {
        return (i-1)/2;
    }
}

void FixUp(uint16_t k){
    uint16_t i=(k-1)/2;
    while(k>0&&q[i].dist>q[k].dist){
        QNODE temp=q[i];
        q[i]=q[k];
        q[k]=temp;
        k=i;
        i=(k-1)/2;
    }
}

void FixDown(uint16_t k){
    int i=2*k+1;
    while(i<hapsize){
        if(i<hapsize-1&&q[i].dist>q[i+1].dist){
            i++;
        }
        if(q[k].dist<q[i].dist){
            break;
        }
        QNODE temp=q[k];
        q[k]=q[i];
        q[i]=temp;
        k=i;
        i=2*k+1;
    }
}

void Qpush(QNODE n){
    q[hapsize]=n;
    FixUp(hapsize);
    hapsize++;
}

uint8_t Qempty(void){
    return !hapsize;
}

QNODE Qtop(){
    return q[0];
}

QNODE Qpop(){
    QNODE temp=q[0];
    q[0]=q[hapsize-1];
    q[hapsize-1]=temp;
    hapsize--;
    FixDown(0);
    return q[hapsize];
}