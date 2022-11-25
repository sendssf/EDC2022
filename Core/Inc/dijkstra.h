#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "API.h"
#include "main.h"

#define MaxNum 167

typedef struct
{
	int order;
	int info;
}VertexType;
 
typedef struct
{
	uint8_t edges[MaxNum][MaxNum];
	int n, e;//顶点数，和边数
	VertexType vex[MaxNum];//存放结点信息
}Graph;

Position Vnode[MaxNum];

#endif