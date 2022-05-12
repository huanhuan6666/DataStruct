//
// Created by Administrator on 2022/5/10.
//

#ifndef DATA_STRUCT_GRAPH_H
#define DATA_STRUCT_GRAPH_H

#include <iostream>
#include <vector>
const int maxSize = 30;

using namespace std;

// 图的抽象数据类型 T为结点的数据类型 W为边的权的数据类型
template<class T, class W>
class Graph {

protected:
    int maxVertexs; //允许的最大点数
    int numEdges;   //当前边树
    int numVertexs; //当前点数


public:
    int getNumEdges() const { // 返回当前边数
        return numEdges;
    }

    int getNumVertexs() const { // 返回当前顶点数
        return numVertexs;
    }

public:
    explicit Graph(int sz = maxSize) { //建立一个空图
        maxVertexs = sz;
        numEdges = numVertexs = 0;
    }

    //图中没有结点则为空
    bool IsEmpty() {
        if (numVertexs == maxVertexs || numEdges == (maxVertexs - 1) * maxVertexs / 2)
            return true;
        return false;
    }
    //图是否满
    bool IsFull() {
        if (numVertexs == maxVertexs || numEdges == (maxVertexs - 1) * maxVertexs / 2)
            return true;
        return false;
    }

    virtual bool InsertVertex(const T &vertex) = 0; //插入新的点
    virtual bool InsertEdge(int v1, int v2, W weight) = 0; //在图中插入边(v1, v2) 权为w1
    virtual bool removeVertex(int v) = 0; //删除点v 及其关联的所有边
    virtual bool removeEdge(int v1, int v2) = 0;    //删除边(v1, v2)

    virtual W getWeight(int v1, int v2) = 0; //返回边(v1, v2)的权值
    virtual T getValue(int v) = 0;          //返回顶点v的值
    virtual int getVertexPos(T vertex) = 0;      //给出点vertex在内部的下标

    virtual int getFirstNeighbor(int v) = 0; //返回点v的第一个邻居
    virtual int getNextNeighbor(int v, int w) = 0; //返回点v邻居w的下一个邻居


};

// 用邻接矩阵实现图 无向图！！！
template<class T, class W>
class GraphMatrix : public Graph<T, W> {
private:
    vector<T> vertexList;   //顶点表
    vector<vector<W>> edgeMatrix;   //表示边的邻接矩阵

public:
    explicit GraphMatrix(int sz = maxSize) : Graph<T, W>(sz) {
        vertexList.resize(sz);
        edgeMatrix.resize(sz);
        for(auto &each : edgeMatrix) {
            each.resize(sz);
        }
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                edgeMatrix[i][j] = (i == j) ? 0 : INT32_MAX; //INT_MAX表示两点之间没有边
            }
        }
    }

    //插入新的点
    bool InsertVertex(const T &vertex) override {
        if(this->numVertexs == this->maxVertexs)
            return false;
        vertexList[(this->numVertexs)++] = vertex;
        return true;
    }

    //插入新的边v1 v2
    bool InsertEdge(int v1, int v2, W weight) override {
        if(v1 > -1 && v1 < this->numVertexs &&
           v2 > -1 && v2 < this->numVertexs &&
           edgeMatrix[v1][v2] == INT32_MAX) { //只有点的下标合法 且原来(v1, v2)之间没有边才能插入
            edgeMatrix[v1][v2] = edgeMatrix[v2][v1] = weight;
            this->numEdges += 1;
            return true;
        }
        return false;
    }

    //删除点v 及其关联的边
    bool removeVertex(int v) override {
        if(v > -1 && v < this->numVertexs) {
            vertexList[v] = vertexList[this->numVertexs - 1]; //用最后一个点取代该点
            for(int i = 0; i < this->numVertexs; i++) {
                if(edgeMatrix[v][i] > 0 && edgeMatrix[v][i] != INT32_MAX) //删除边的条数
                    this->numEdges -= 1;
            }
            for(int i = 0; i < this->numVertexs; i++) //用最后一行填补v行
                edgeMatrix[v][i] = edgeMatrix[this->numVertexs - 1][i];
            for(int i = 0; i < this->numVertexs; i++) //用最后一列填补v列
                edgeMatrix[i][v] = edgeMatrix[i][this->numVertexs - 1];

            this->numVertexs -= 1;
            return true;
        }
        return false;
    }

    //删除边(v1, v2) 要改矩阵中对称的 e[v1][v2]
    bool removeEdge(int v1, int v2) override {
        if(v1 > -1 && v1 < this->numVertexs &&
           v2 > -1 && v2 < this->numVertexs &&
           edgeMatrix[v1][v2] > 0 &&
           edgeMatrix[v1][v2] < INT32_MAX) {
            edgeMatrix[v1][v2] = edgeMatrix[v2][v1] = INT32_MAX;
            this->numEdges -= 1;
            return true;
        }
        return false;
    }

    //获取边 (v1, v2)的权
    W getWeight(int v1, int v2) override {
        if(v1 > -1 && v1 < this->numVertexs &&
           v2 > -1 && v2 < this->numVertexs) {
            return edgeMatrix[v1][v2];
        }
    }

    // 获取点v的实际值
    T getValue(int v) override {
        if(v > -1 && v < this->numVertexs)
            return vertexList[v];
    }

    // 获取vertex在点列表中的下标
    int getVertexPos(T vertex) override {
        for(int i = 0; i < this->numVertexs; i++) {
            if(vertex == vertexList[i]) //需要重载类T的==
                return i;
        }
        return -1;
    }

    // 获取无向图中v的第一个邻居的下标 没有返回-1
    int getFirstNeighbor(int v) override {
        if(!(v > -1 && v < this->numVertexs))
            return -1;
        for(int i = 0; i < this->numVertexs; i++) {
            if(edgeMatrix[v][i] > 0 && edgeMatrix[v][i] != INT32_MAX) {
                return i;
            }
        }
        return -1;
    }

    //获取v的邻居 且下标在w之后 没有返回-1
    int getNextNeighbor(int v, int w) override {
        if(!(v > -1 && v < this->numVertexs &&
             w > -1 && w < this->numVertexs))
            return -1;
        for(int i = w + 1; i < this->numVertexs; i++) { // 寻找w之后的邻居
            if(edgeMatrix[v][i] > 0 && edgeMatrix[v][i] != INT32_MAX) {
                return i;
            }
        }
    }

};

// 用邻接链表实现无向图

template<class W>
class Edge {
public:
    W weight;   //边的权值
    int dest;   //终点的下标值

public:
    Edge(W w, int d) : weight(w), dest(d) { ; }

    bool operator!=(Edge<W> &r) { //判断起点确定下的终点是否相同
        return (dest != r.dest);
    }
};

//顶点表中存的东西 <顶点值，vector<Edge>>对
template<class T, class W>
class VertexPiar {
public:
    T data; //该顶点的值
    vector<Edge<W>> destTable;  //出边的终点

    VertexPiar(T d) {
        data = d;
    }
};

template<class T, class W>
class GraphLink : public Graph<T, W>{
private:
    vector<VertexPiar<T, W>> nodeTable;     //顶点表
public:
    GraphLink(int sz = maxSize) {
        nodeTable.resize(sz);
    }

    //插入新点
    bool InsertVertex(const T &vertex) override {
        if(this->numVertexs == this->maxVertexs)
            return false;
        nodeTable[(this->numVertexs)++] = VertexPiar<T, W>(vertex);
    }

    //插入新边
    bool InsertEdge(int v1, int v2, W weight) override {
        if(v1 > -1 && v1 < this->numVertexs &&
           v2 > -1 && v2 < this->numVertexs) {
            nodeTable[v1].destTable.push_back(Edge<W>(v2, weight));
            this->numEdges += 1;
        }
        return false;
    }

    // 删除下标为v的点 懒得写了
    // 需要遍历整个nodeTable的destTable删除所有和v相关的边
    bool removeVertex(int v) override {
        return false;
    }

    // 删除下标(v1, v2)这条边
    bool removeEdge(int v1, int v2) override {
        if(v1 > -1 && v1 < this->numVertexs &&
           v2 > -1 && v2 < this->numVertexs) {
            int neighbor_count = nodeTable[v1].destTable.size();
            for(int i = 0; i > neighbor_count; i++) {
                if(v2 == nodeTable[v1].destTable[i].dest) { //这条边存在
                    return nodeTable[v1].destTable[i].weight;
                }
            }
            for(auto it = nodeTable[v1].destTable.begin(); it != nodeTable[v1].destTable.begin(); ) {
                if((*it).dest == v2) { //找到了这条边则删除
                    nodeTable[v1].destTable.erase(it);
                    this->numEdges -= 1;
                    return true;
                }
                ++it;
            }
        }
        return false;
    }

    // 获取下标(v1, v2)边的权值
    W getWeight(int v1, int v2) override {
        if(v1 > -1 && v1 < this->numVertexs &&
           v2 > -1 && v2 < this->numVertexs)
        {
            int neighbor_count = nodeTable[v1].destTable.size();
            for(int i = 0; i > neighbor_count; i++) {
                if(v2 == nodeTable[v1].destTable[i].dest) { //这条边存在
                    return nodeTable[v1].destTable[i].weight;
                }
            }

        }
        return INT32_MAX; //不存在这条边
    }

    //获取下标为v的顶点的值 下标非法返回-1
    T getValue(int v) override {
        if(v > -1 && v < this->numVertexs) {
            return nodeTable[v].data;
        }
        return -1;
    }

    //获取点值为vertex在顶点表中的下标 找不到返回-1
    int getVertexPos(T vertex) override {
        for(int i = 0; i < this->numVertexs; i++) {
            if(vertex == nodeTable[i].data)
                return i;
        }
        return -1;
    }

    //获取下标为v的顶点的第一个邻居的下标
    int getFirstNeighbor(int v) override {
        if(v > -1 && v < this->numVertexs) {
            int neighbor_count = nodeTable[v].destTable.size();
            if(neighbor_count) {
                return nodeTable[v].destTable[0].dest; //第一个邻居的下标
            }
        }
        return -1;
    }

    //获取下标为v的顶点的 下标为w的邻居之后的邻居的下标
    int getNextNeighbor(int v, int w) override {
        if(v > -1 && v < this->numVertexs) {
            int neighbor_count = nodeTable[v].destTable.size();
            int i;
            for(i = 0; i < neighbor_count; i++) {
                if(w == nodeTable[v].destTable[i].dest) { //找到w了
                    break;
                }
            }
            if(++i < neighbor_count) //v在w之后还有邻居
                return nodeTable[v].destTable[i].dest;
        }
        return -1;
    }
};
#endif //DATA_STRUCT_GRAPH_H
