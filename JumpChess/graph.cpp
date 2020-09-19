#include "graph.h"
#define MAX 1000
#define VETEX 183
Graph::Graph()
{

}

Graph::~Graph()
{

}
void Graph::init()
{
    for(int i=0;i<183;i++)
    {
        for(int j=0;j<183;j++)
        {
            Matrix[i][j] = MAX;
        }
    }
}
//利用迪杰斯特拉算法求最短路径
int* Graph::ShortestPath(int v0)
{
    //使用迪杰斯特拉算法求有向网G中的V0 定点到其余顶点的最短路径
    for (int v = 0; v < VETEX; v++) //n个顶点依次初始化
    {
        S[v] = false;               //S初始化为空集
        D[v] = Matrix[v0][v];       //将v0到各个终点的最短路径长度初始化为边上的权值
        if (D[v] < MAX)
            Path[v] = v0;           //如果v0和v之间有边，则将v的前驱初始化为v0
        else
            Path[v] = -1;           //如果v0和v之间无边，则将v的前驱初始化为-1
    }
    S[v0] = true;                   //将v0加入s
    D[v0] = 0;                      //源点到源点的权值为0

    //每次求得v0到某个顶点的最短路径，将v加到S数组
    for (int i = 1; i < VETEX; i++) //依次对其余n-1个顶点进行计算
    {
        int min = MAX;
        int v = v0;
        for (int w = 0; w < VETEX; w++)
        {
            if (!S[w] && D[w] < min)
            {
                //选择一条当前最短路径，终点为v
                v = w;
                min = D[w];
            }
            S[v] = true;//将v加到s集合中
            for (int w = 0; w < VETEX; w++)
            {
                //更新从v0出发到集合V-S上所有顶点的最短路径长度
                if (!S[w] && (D[v] + Matrix[v][w] < D[w]))
                {
                    D[w] = D[v] + Matrix[v][w]; //更新D[w]
                    Path[w] = v;                //更改w的前驱为v
                }
            }
        }
    }

    return Path;
}
