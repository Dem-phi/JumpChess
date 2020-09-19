#ifndef GRAPH_H
#define GRAPH_H
class Graph{
public:
    int Matrix[183][183];
    Graph();
    ~Graph();
    void init();
    int* ShortestPath(int v0);
private:
    bool S[183];    //记录从源点V0到终点Vi是否已经确定为最短路径，确定了记true，否则记false
    int Path[183];  //记录从源点V0到终点Vi的当前最短路径上终点Vi的直接前驱顶点序号，若V0到Vi之间有边前驱为V0否则为-1
    int D[183];     //记录源点到终点之间最短路径的长度，存在记V0到Vi的边的权值，否则记为MAX
};
#endif // GRAPH_H
