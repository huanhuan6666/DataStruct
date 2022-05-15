//
// Created by Administrator on 2022/5/15.
//

#ifndef DATA_STRUCT_ACTIVITYNETWORK_H
#define DATA_STRUCT_ACTIVITYNETWORK_H

#include "Graph.h"
#include <vector>

using namespace std;

template<class T, class W>
void TopologicalSort(Graph<T, W> &G) {
    int n = G.getNumVertexs();
    vector<int> all_zero;

    //先统计每个点的入度 找到起始时入度为0的点入栈
    vector<int> in_count(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && G.getWeight(j, i) != INT32_MAX) { //存在到点i的边
                in_count[i] += 1;
            }
        }
        if (in_count[i] == 0) //i确实入度为0
            all_zero.push_back(i);
    }

    int count = 0;  //输出顶点计数器
    // 输出顶点后将删除其出边 邻居变成新的入度为0的点入栈
    while (!all_zero.empty()) {
        int tmp = all_zero[all_zero.size() - 1];
        cout << tmp << " ";
        all_zero.pop_back();
        count += 1;
        int neighbor = G.getFirstNeighbor(tmp);
        while (neighbor != -1) {
            in_count[neighbor] -= 1;
            if (in_count[neighbor] == 0)
                all_zero.push_back(neighbor);
            neighbor = G.getNextNeighbor(tmp, neighbor);
        }
    }
    if (count != n) {
        cout << "ERROR: 图中存在有向环" << endl;
    }
}

//寻找关键路径 假设G中点的下标号是按照拓扑排序的
//即下标为0的点就是起点 n-1是终点
template<class T, class W>
void CriticalPath(Graph<T, W> &G) {
    int n = G.getNumVertexs();
    vector<W> Ve(n), Vl(n, INT32_MAX); //事件的Ve和Vl

    Ve[0] = 0; //起点Ve为0
    for (int i = 0; i < n; i++) { //找<i, j>边可能有多条 正向计算Ve[j]
        int j = G.getFirstNeighbor(i);
        while (j != -1) {
            W weight = G.getWeight(i, j);
            if (weight + Ve[i] > Ve[j]) { //Ve[j] = max(Ve[i] + weight(i, j))
                Ve[j] = weight + Ve[i];
            }
            j = G.getNextNeighbor(i, j);
        }
    }

    Vl[n - 1] = Ve[n - 1]; //终点的Vl等于其Ve
    for (int i = n - 2; i >= 0; i--) { //逆向计算Vl[i]
        int j = G.getFirstNeighbor(i);  //找<i, j>边可能有多条
        while(j != -1) {
            W weight = G.getWeight(i, j);
            if(Vl[j] - weight < Vl[i]) //Vl[i] = min(Vl[j] - weight(i, j))
                Vl[i] = Vl[j] - weight;
            j = G.getNextNeighbor(i, j);
        }
    }

    //计算所有的边<i, j>的Ae和Al看看是否为关键活动
    for(int i = 0; i < n; i++) {
        int j = G.getFirstNeighbor(i);
        while(j != -1) {
            W Ae = Ve[i], Al = Vl[j] - G.getWeight(i, j);
            if(Ae == Al) { //是关键活动
                cout << "<" << G.getValue(i) << ", " << G.getValue(j) << ">"
                    << "是关键活动" << endl;
            }
            j = G.getNextNeighbor(i, j);
        }
    }
}

#endif //DATA_STRUCT_ACTIVITYNETWORK_H
