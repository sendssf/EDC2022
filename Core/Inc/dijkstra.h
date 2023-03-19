#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "API.h"
#include "main.h"
#include "math.h"

#define MaxNum 200

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

extern uint8_t shortest_path[MaxNum];
extern Position Vnode[MaxNum];
extern double distance[MaxNum];
extern uint8_t Visited[MaxNum];
extern uint8_t path[MaxNum];
extern uint8_t steps;
extern uint8_t angles[MaxNum];

void InitNode();
double dis(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void BuildGraph();
void Dijkstra();
void shortest_path1();
void GetAngle();
#endif