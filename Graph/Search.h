//
// Created by Administrator on 2022/5/11.
//

#ifndef DATA_STRUCT_SEARCH_H
#define DATA_STRUCT_SEARCH_H

#include "Graph.h"
#include "../Tree/Tree.h"
#include <queue>

using namespace std;

//从顶点vertex开始dfs图G
template<class T, class W>
void DFSearch(Graph<T, W>& G, const T& vertex) {
    int v_count = G.getNumVertexs();
    vector<bool> visited(v_count, false); //设置访问数组
    int v = G.getVertexPos(vertex);
    DFS(G, v, visited); //递归的外部调用
}

//从下标v开始递归DFS访问图G
template<class T, class W>
void DFS(Graph<T, W>& G, int v, vector<bool>& visited) {
    cout << G.getValue(v) << " " << endl; //访问这个点
    visited[v] = true;  //标记访问 防止重复访问
    int neighbor = G.getFirstNeighbor(v);   //邻居的下标
    while(neighbor != -1) { //递归DFS访问v的所有邻居
        if(!visited[neighbor]) //防止重复访问
            DFS(G, neighbor, visited);
        neighbor = G.getNextNeighbor(v, neighbor);
    }
}

//从顶点vertex开始BFS图G
template<class T, class W>
void BFSearch(Graph<T, W>& G, const T& vertex) {
    int v_count = G.getNumVertexs();
    vector<bool> visited(v_count, false); //设置访问数组
    int v = G.getVertexPos(vertex); //v为vertex的下标
    queue<int> que;
    que.push(v);
    while(!que.empty()) {
        //访问队首表示的顶点
        int head = que.front();
        que.pop(); //出队
        visited[head] = true;
        cout << G.getValue(head) << " " << endl;
        //将其所有邻居入队
        int neighbor = G.getFirstNeighbor(head);
        while(neighbor != -1) {
            if(!visited[neighbor])  //保证不会重复访问
                que.push(neighbor);
            neighbor = G.getNextNeighbor(head, neighbor);
        }
    }
}

//用DFS/BFS确定无向图G的所有连通分量
template<class T, class W>
void Components(Graph<T, W>& G) {
    int v_count = G.getNumVertexs();
    vector<bool> visited(v_count, false);
    for(int i = 0; i < v_count; i++) {
        if(!visited[i]) {
            DFS(G, i, visited); //BFS(G, i);
            cout << "-----------------------" << endl;   //每一个连通分量结束后都有分隔线
        }
    }
}

//在图G中生成点v开始的 深度优先生成树 拼到森林中的subTree为根开始的位置
template<class T, class W>
void DFS_tree(Graph<T, W>& G, Tree<T>& forest, TreeNode<T>* subTree, int v, vector<bool>& visited) {
    cout << G.getValue(v) << " " << endl; //访问这个点

    int first_son = G.getFirstNeighbor(v); //第一个未访问的邻居是子女 剩下的邻居是子女的兄弟
    while(first_son != -1 && visited[first_son]) {
        first_son = G.getNextNeighbor(v, first_son);
    }

    if(first_son != -1 && !visited[first_son]) { //找到了长子
        //subTree中插入长子
        visited[first_son] = true;
        auto tmpNode =  forest.InsertLeftChild(subTree, G.getValue(first_son));
        DFS_tree(G, forest, tmpNode, first_son, visited); //递归生成长子为根的森林

        //剩下邻居都是长子的兄弟
        while(first_son != -1) {
            if(!visited[first_son]) {
                visited[first_son] = true;
                auto eachNode = forest.InsertRightSibling(tmpNode, G.getValue(first_son));
                DFS_tree(G, forest, eachNode, first_son, visited); //递归生成长子兄弟为根的森林
            }
            first_son = G.getNextNeighbor(v, first_son);
        }
    }
    else { //找不到邻居 什么也不干 递归终点
        return ;
    }
}

//书上的做法 更简洁一点就是说
template<class T, class W>
void DFS_tree_new(Graph<T, W>& G, Tree<T>& forest, TreeNode<T>* subTree, int v, vector<bool>& visited) {
    visited[v] = true;
    int neighbor = G.getFirstNeighbor(v);
    bool IsFirstSon = true;   //判断该邻居是否为长子 作为subTree的leftson
    TreeNode<T>* firstSon = nullptr;
    while(neighbor != -1) {
        if(!visited[neighbor]) {
            if(IsFirstSon) { //是长子 插入左结点
                firstSon = forest.InsertLeftChild(subTree, G.getValue(neighbor));
                IsFirstSon = false;   //此后的邻居都是长子的兄弟
                DFS_tree_new(G, forest, firstSon, neighbor, visited); //递归建立长子下的森林
            }
            else { //长子的兄弟
                auto sibling = forest.InsertRightSibling(firstSon, G.getValue(neighbor));
                DFS_tree_new(G, forest, sibling, neighbor, visited);  //递归建立结点下的森林
            }
        }
        neighbor = G.getNextNeighbor(v, neighbor);
    }
}


//生成非连通图G的深度优先生成森林 结果在引用参数forest中
//调用时 传入一个空的森林Tree对象即可
template<class T, class W>
void DFS_forest(Graph<T, W>& G, Tree<T>& forest) {
    TreeNode<T> *root, *subTree; //森林的结点指针
    int v_count = G.getNumVertexs();
    vector<bool> visited(v_count, false);

    for(int i = 0; i < v_count; i++) {
        if(!visited[i]) { //一个新的连通分量 即一棵新的生成树
            visited[i] = true;
            if(forest.IsEmpty()) { //生成森林里的第一棵树
                subTree = root = forest.BulitRoot(G.getValue(i)); //建立森林的根
            }
            else { //新的生成树 是兄弟
                subTree = forest.InsertRightSibling(subTree, G.getValue(i));
            }
            DFS_Tree(G, forest, subTree, i, visited);
        }
    }
}
#endif //DATA_STRUCT_SEARCH_H
