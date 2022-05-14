//
// Created by Administrator on 2022/5/12.
//

#ifndef DATA_STRUCT_MINSPANTREE_H
#define DATA_STRUCT_MINSPANTREE_H
#include <iostream>
#include <vector>
#include "../Tree/Heap.h"
#include "../Set/UFSets.h"
#include "Graph.h"

using namespace std;

const float maxValue = INT32_MAX;

//最小生成树中的边
template<class W>
struct MSTEdge {
    int begin, end; //边的起点和终点的下标
    W weight;       //边的权值
    MSTEdge() : begin(-1), end(-1) { ; }

    //重载比较运算符 用于最小堆中的调整
    bool operator<(const MSTEdge &rhs) const {
        return weight < rhs.weight;
    }

    bool operator>(const MSTEdge &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const MSTEdge &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const MSTEdge &rhs) const {
        return !(*this < rhs);
    }
};

//最小生成树
template<class W>
class MinSpanTree {
private:
    vector<MSTEdge<W>> edgeList; //生成树边列表
    int maxSize;
    int curSize;
public:
    explicit MinSpanTree(int sz = 30) : maxSize(sz), curSize(0)
    {
        edgeList.resize(maxSize);
    }
    //像生成树中插入新边edge
    int InsertEdge(MSTEdge<W>& edge) {
        edgeList[curSize] = edge;
        curSize += 1;
    }
};

//Kruskal算法生成最小生成树 无向图
template<class T, class W>
void Kruskal(Graph<T, W>& G, MinSpanTree<W>& MST) {
    int e_count = G.getNumEdges(), v_count = G.getNumVertexs();
    MinHeap<MSTEdge<W>> heap(e_count);  //边的最小堆
    MSTEdge<W> each_edge;
    for(int i = 0; i < v_count; i++) { //由于无向图邻接矩阵对称 只看一般就行
        for(int j = i + 1; j < v_count; j++) {
            each_edge.begin = i;
            each_edge.end = j;
            each_edge.weight = G.getWeight(i, j);
            heap.Insert(each_edge); //最小堆中插入边
        }
    }
    int count = 0; //边数统计
    UFSet ufset(v_count);   //并查集 看顶点是否连通 大小即为v_count
    while(count < v_count-1) { //要加入n-1条边
        heap.Remove(each_edge); //取出堆顶到each_edge中
        int begin = each_edge.begin;
        int end = each_edge.end;
        if(ufset.Find(begin) != ufset.Find(end)) { //这条边加到生成树不会成环
            ufset.Union(begin, end);  //连起来
            MST.InsertEdge(each_edge);
            count += 1; //新加一条边到MST
        }
        else { //这条边加入MST会成环
            continue;
        }
    }
}

//Prim算法生成无向图的最小生成树 begin_vertex为规定的起始顶点
template<class T, class W>
void Prim(Graph<T, W>& G, MinSpanTree<W>& MST, const T& begin_vertex) {
    int e_count = G.getNumEdges(), v_count = G.getNumVertexs();
    int new_node = G.getVertexPos(begin_vertex);

    vector<bool> VertexInMst(v_count, false);   //判断点是否在MST中
    VertexInMst[new_node] = true;   //初始第一个点

    MinHeap<MSTEdge<W>> heap(e_count);  //边的最小堆
    MSTEdge<W> each_edge;   //每条桥

    for(int i = 0; i < v_count-1; i++) { //向MST中再加入n-1个点即可
        // 将新加入MST的结点的所有桥加入最小堆中
        int neighbor = G.getFirstNeighbor(new_node);
        while(neighbor != -1) {
            if(!VertexInMst[neighbor]) { //(new_node, neighbor)是桥
                each_edge.begin = new_node;
                each_edge.end = neighbor;
                each_edge.weight = G.getWeight(new_node, neighbor);
                heap.Insert(each_edge); //将桥加入最小堆中
            }
            neighbor = G.getNextNeighbor(new_node, neighbor);  //找下一个桥
        }
        while(!heap.IsEmpty()) {
            heap.Remove(each_edge); //取最小的桥加入MST中
            new_node = each_edge.end;   //边的终点
            if(!VertexInMst[new_node]) {   //确保终点不在MST中
                MST.InsertEdge(each_edge);
                VertexInMst[new_node] = true;
                break;
            }
        }
    }

}
#endif //DATA_STRUCT_MINSPANTREE_H
