#include "dijkstra.h"

Graph G;

int two2one(int x, int y) { // 将二维坐标转换成一维
    return x * 255 + y;
}

pair<int, int> one2two(int id) { // 将一维坐标转换成二维
    return { id / 255, id % 255 };
}

void InitNode(){//初始化节点表（不包含充电站，第一个点为自己位置）
    uint8_t i = 1;
    GetMyPos(Vnode[0]);
    Node* food1 = foodlist;
    while (food1)
    {
        Vnode[i++] = food1->food.start;
        Vnode[i++] = food1->food.end;
    }
    for(uint8_t j = 0; j < blocknum; j++){
        Vnode[i+j].x = block[j].upleft.x - 1;
        Vnode[i+j].y = block[j].upleft.y - 1;
        i++;
        Vnode[i+j].x = block[j].downright.x + 1;
        Vnode[i+j].y = block[j].upleft.y - 1;
        i++;
        Vnode[i+j].x = block[j].upleft.x - 1;
        Vnode[i+j].y = block[j].downright.y + 1;
        i++;
        Vnode[i+j].x = block[j].downright.x + 1;
        Vnode[i+j].y = block[j].downright.y + 1;
        i++;
    }
    G.n = i+blocknum;
}

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
 
void BuildGraph(){ 
	//Create Graph
	for (uint8_t i = 0; i < G.n; i++)
		for (uint8_t j = 0; j < G.n; j++)
			G.edges[i][j] = 1e7 + 7;
            
	for (uint8_t i = 0; i < G.n; i++){
		for (uint8_t j = 0; j < G.n; j++){
            uint8_t x = Vnode[i].x, y = Vnode[i].y,nx = Vnode[j].nx,ny = Vnode[j].ny;
		    if (nx == x && ny == y)
                G.edges[i][j] = 0;
            if (checkLine(x, y, nx, ny)) {
                G.edges[i][j] = dis(x, y, nx, ny);
                G.edges[j][i] = dis(x, y, nx, ny);
            }
	    }
    }
}

void dijkstra(){
    vector<int> pre(cols * rows); // 记录点的前驱
    vector<bool> vis(cols * rows, false);
    double oo = 1e9 + 7;
    vector<double> distance(cols * rows, oo);
    priority_queue<pair<double, int>> team;

    uint8_t u;
    double w;
    for (uint8_t i = 0; i < G.n; i++){
        distance[i] = 1e7 + 7;
        visited[i] = false;
    }
    q.push({ 0, 0 });
    distance[0] = 0;
    while (!q.empty()) { // dijkstra主要部分
        u = q.top().second;
        q.pop();
        if (visited[u] == true)
            continue;
        visited[u] = true;
        for (uint8_t i = 0;i < G.n;i++) {
			if( (distance[u] + G.edges[u][i]) < distance[i] && visited[i] == false){
				distance[i]=distance[u] + G.edges[u][i];
		        q.push(()distance[i]*(-1), i);
			}
        }
    }
    if (distance[two2one(ex, ey)] == oo) {
        printf("WARNING: CANNOT Find a path from start point to target point!\n");
        exit(0);
    }
    for (int u = two2one(ex, ey); u != two2one(sx, sy); u = pre[u])
        path.push_back(u);
    path.push_back(two2one(sx, sy));
    reverse(path.begin(), path.end()); // 反转，使第一个点为起点
}
