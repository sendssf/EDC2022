#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "API.h"
#include "main.h"

#define MaxNum 167

typedef struct
{
	uint8_t order;
	uint8_t info;
}VertexType;
 
typedef struct
{
	uint8_t edges[MaxNum][MaxNum];
	uint8_t n, e;//顶点数，和边数
	VertexType vex[MaxNum];//存放结点信息
}Graph;

Position Vnode[MaxNum];
double distance[MaxNum];
bool visited[MaxNum];

#endif