//
// Created by Administrator on 2022/5/13.
//

#ifndef DATA_STRUCT_SHORTESTPATH_H
#define DATA_STRUCT_SHORTESTPATH_H
#include "Graph.h"
#include "MinSpanTree.h"

// 从给定起点begin_vertex找到达其他所有点的最短路径
// Dijkstra算法 只能适用于边的权值非负的无向图
// 结果路径长度放在dist中 path存放每个点到源点的路径的上一步
template<class T, class W>
void Dijkstra(Graph<T, W>& G, const T& begin_vertex, vector<W>& dist, vector<int>& path) {
    int n = G.getNumVertexs();
    int source = G.getVertexPos(begin_vertex);

    dist.resize(n);
    for(int i = 0; i < n; i++) { //初始距离
        dist[i] = G.getWeight(source, i);
        if(dist[i] < maxValue) {
            path[i] = source;   //路径的上一步
        }
    }
    vector<bool> Seen(n, false);   //判断点是否在MST中
    Seen[source] = true;   //初始第一个点
    dist[source] = 0;

    for(int i = 0; i < n - 1; i++) { //再向Seen中加入n-1个点即可
        int weight = maxValue, best_fringe = -1;
        for(int j = 0; j < n; j++) { //寻找最优的Fringe
            if(!Seen[j] && dist[j] < weight) {
                weight = dist[j];
                best_fringe = j;
            }
        }
        if(best_fringe != -1) { //将最优的Fringe加入到Seen中
            Seen[best_fringe] = true;
            int neighbor = G.getFirstNeighbor(best_fringe);
            while (neighbor != -1) { // 更新邻居的dist和path
                if(!Seen[neighbor] &&
                    dist[best_fringe] + G.getWeight(best_fringe, neighbor) < dist[neighbor]) {
                    dist[neighbor] = dist[best_fringe] + G.getWeight(best_fringe, neighbor);
                    path[neighbor] = best_fringe;
                }
                neighbor = G.getNextNeighbor(best_fringe, neighbor);
            }
        }

    }
}

// 计算任意权值的从给定起点begin_vertex出发到其他所有点的最短路径 Bellman-Ford算法
// 同样结果路径长度放在dist 路径中上一步放在path中
template<class T, class W>
void Bellman_Ford(Graph<T, W>& G, const T& begin_vertex, vector<W>& dist, vector<int>& path) {
    int n = G.getNumVertexs();
    int source = G.getVertexPos(begin_vertex);

    //初始化规模为1的问题 即dist1[u]
    dist.resize(n, INT32_MAX);
    path.resize(n, -1);
    int neighbor = G.getFirstNeighbor(source);
    while(neighbor != -1) { //如果有直接到达source的边则更新一下
        dist[neighbor] = G.getWeight(source, neighbor);
        path[neighbor] = source;
        neighbor = G.getNextNeighbor(source, neighbor);
    }
    dist[source] = 0; //source到自己距离为0

    //迭代n-2次 最终求出dist n-1[u]规模为n-1的问题
    for(int size = 0; size < n-2; size++) {
        for(int i = 0; i < n; i++) { //求更大规模的dist[i]
            if (i != source) {
                for (int j = 0; j < n; j++) { //遍历所有从j到i的边 找出最小
                    int edge = G.getWeight(j, i);
                    if (i != j && edge != INT32_MAX) { //存在从j到i的边
                        if (dist[j] + edge < dist[i]) { //更小
                            dist[i] = dist[j] + edge;
                            path[i] = j;
                        }
                    }
                }
            }
        }
    }
}

// 获取图G中任意两点的最短路径 Floyd-Warshall算法
// 结果最短路径长度放在二维数组dist中  路径中上一个顶点下标放在二维数组path中
template<class T, class W>
void Floyd_Warshall(Graph<T, W>& G, vector<vector<W>>& dist, vector<vector<int>>& path) {
    int n = G.getNumVertexs();
    dist.resize(n);
    for(int i = 0; i < n; i++) {
        dist[i].resize(n);
        for(int j = 0; j < n; j++) {
            dist[i][j] = G.getWeight(i, j);
            if(i != j && dist[i][j] != INT32_MAX) {
                path[i][j] = i;
            }
            else
                path[i][j] = -1;
        }
    }

    for(int k = 0; k < n; k++) { //点的下标是从0开始的 最终的区间簇为(v0, v2...vn-1)
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][j] > dist[i][k]+dist[k][j]) { //经过点k的路径更短
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];    //更新path
                }
            }
        }
    }

}
#endif //DATA_STRUCT_SHORTESTPATH_H
