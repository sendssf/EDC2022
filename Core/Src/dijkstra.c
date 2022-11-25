#include "dijkstra.h"

double dis(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) { // 计算两个二维点坐标距离
        return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool judge(uint8_t Ax1,uint8_t Ay1,uint8_t Ax2,uint8_t Ay2,uint8_t Bx1,uint8_t By1,uint8_t Bx2,uint8_t By2)//判断两线段是否相交
{
    if(
       ( max(Ax1,Ax2)>=min(Bx1,Bx2)&&min(Ax1,Ax2)<=max(Bx1,Bx2) )&&  //判断x轴投影
       ( max(Ay1,Ay2)>=min(By1,By2)&&min(Ay1,Ay2)<=max(By1,By2) )    //判断y轴投影
      )
    {
        if(
            ( (Bx1-Ax1)*(Ay2-Ay1)-(By1-Ay1)*(Ax2-Ax1) ) *          //判断B是否跨过A
            ( (Bx2-Ax1)*(Ay2-Ay1)-(By2-Ay1)*(Ax2-Ax1) ) <=0 &&
            ( (Ax1-Bx1)*(By2-By1)-(Ay1-By1)*(Bx2-Bx1) ) *          //判断A是否跨过B
            ( (Ax2-Bx1)*(By2-By1)-(Ay2-By1)*(Bx2-Bx1) ) <=0
          )
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool valid(uint8_t x, uint8_t y) { // 判断当前点是否合法，即是否越界或者是否在障碍物中
    if (x < 0 && x >= 255)
        return false;
    if (y < 0 && y >= 255)//判断点是否越界
        return false;
    if (map[x][y] == Blocks)//点是否在障碍物中
        return false;
    return true;
}

bool checkline(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2){//判断两点是否合理且判断其间是否有障碍物
    if(valid(x1,y1) && valid(x2,y2)){
        for(uint8_t i = 0;i < blocknum; i++){
            if(
                judge(x1,y1,x2,y2,block[i].upleft.x,block[i].upleft.y,block[i].downright.x,block[i].downright.y) ||
                judge(x1,y1,x2,y2,block[i].upleft.x,block[i].downright.y,block[i].downright.x,block[i].upleft.y)
            )
                return false;
        }
        return true;
    }
    return false;
}
void connectNei() { // 邻居连边
        edge.resize(rows * cols);
        for (auto [x, y] : point) {
            for (auto [nx, ny] : point) {
                if (nx == x && ny == y)
                    continue;
                if (dis(x, y, nx, ny) < neiDis && checkLine(x, y, nx, ny)) {
                    e dge[two2one(x, y)].push_back(two2one(nx, ny));
                    edge[two2one(nx, ny)].push_back(two2one(x, y));
                }
            }
        }
    }

 
typedef struct
{
	int num;
	char info;
}VertexType;
 
typedef struct
{
	int edges[maxSize][maxSize];
	int n, e;//顶点数，和边数
	VertexType vex[maxSize];//存放结点信息
}MGraph;
 
MGraph G;
int visit[maxSize];
 
void BuildGraph()
{
	int i,j;
	int v1, v2,w;
 
	//Create Graph
	scanf("%d",&G.n);
	for (i = 0; i < G.n; ++i)
		for (j = 0; j < G.n; j++)
			G.edges[i][j] = 0;//若为有向边则赋值为INF
 
	scanf("%d", &G.e);
	for (i = 0; i < G.e; i++)
	{
		scanf("%d%d%d", &v1, &v2, &w);
		//Insert Edges
		G.edges[v1][v2] = w;
		G.edges[v2][v1] = w;//若为无向边，则对称位置权值相等
	}
 
	/*顶点有数据的话，则读入数据*/
	for ( i = 0; i < G.n; i++)
	{
		G.vex[i].num = i;//顶点编号
		getchar();//消化输入的换行符
		scanf("%c", &G.vex[i].info);//顶点其他信息
	}
 
}

void build_graph(){

}