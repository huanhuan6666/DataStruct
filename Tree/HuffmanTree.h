//
// Created by Administrator on 2022/4/11.
//

#ifndef DATA_STRUCT_HUFFMANTREE_H
#define DATA_STRUCT_HUFFMANTREE_H
#include "Heap.h"
#include <iostream>
#include <queue>
using namespace std;

struct HuffmanNode{
    float data;
    HuffmanNode *left, *right, *parent; //左右子女和父指针
    HuffmanNode() : data(0), left(nullptr), right(nullptr), parent(nullptr) { ; }
    explicit HuffmanNode(float d) : data(d), left(nullptr), right(nullptr), parent(nullptr) { ; }
    bool operator<(const HuffmanNode& r) const{
        return data < r.data;
    }
    bool operator<=(const HuffmanNode& r) const{
        return data <= r.data;
    }
    bool operator>(const HuffmanNode& r) const{
        return data > r.data;
    }
    bool operator>=(const HuffmanNode& r) const{
        return data >= r.data;
    }
};

//套皮指针 因为堆中存的是HuffmanNode的指针
//堆需要结点之间的比较 然而我们无法重载指针之间的比较函数（C++规定）
//因此只能让堆中存储套皮指针 比较类
class PointerWrapper{
public:
    HuffmanNode *p;
    PointerWrapper(): p(nullptr) { ; }
    explicit PointerWrapper(HuffmanNode *a) : p(a) { ; }

    bool operator<(const PointerWrapper&r) const{
        return p->data < r.p->data;
    }
    bool operator<=(const PointerWrapper&r) const{
        return p->data <= r.p->data;
    }
    bool operator>(const PointerWrapper&r) const{
        return p->data > r.p->data;
    }
    bool operator>=(const PointerWrapper&r) const{
        return p->data >= r.p->data;
    }
};
class HuffmanTree {
private:
    HuffmanNode *root; //霍夫曼树根
    void deleteTree(HuffmanNode *r); //删除以r为根的子树
    void mergeTree(HuffmanNode *t1, HuffmanNode *t2, HuffmanNode* &p); //合并两棵霍夫曼树
public:
    HuffmanTree(float* w, int n); //w就是权值数组 利用其生成霍夫曼树
    ~HuffmanTree() { deleteTree(root); }
    void show(); //层次遍历查看树结构
};


//w给出权值数组 我们的做法是 不断找出根结点权值最小的两个霍夫曼树合并
//初始化时 每个权值对应一个霍夫曼树即一个单独的根结点
//为了方便每次找权值最小的两个根  使用一个最小堆 存放某一时刻的所有霍夫曼树的根结点
HuffmanTree::HuffmanTree(float *w, int n) {
    MinHeap<PointerWrapper> hp; //存放当前所有树的根结点的堆
    HuffmanNode *cur;
    for(int i = 0; i < n; i++){ //初始化为n个根结点 全部插入堆中
        cur = new HuffmanNode(w[i]);
        PointerWrapper wp(cur);
        hp.Insert(wp); //堆中的是套皮指针
    }
    HuffmanNode *first, *second, *parent;
    PointerWrapper f, s;
    for(int i = 0; i < n-1; i++){ //合并n-1次
        hp.Remove(f); //取出两个最小根
        hp.Remove(s);
        first = f.p; second = s.p;
        mergeTree(first, second, parent); //parent成为合并first和second后的子树

        PointerWrapper wp(parent);
        hp.Insert(wp); //插入合并后的根
    }
    //hp.Remove(root); //最后堆里只剩一个就是最终结果
    root = parent;
}

//合并t1和t2为根结点的两棵树 成为p的子树 p的权值等于t1 t2的权值之和
void HuffmanTree::mergeTree(HuffmanNode* t1, HuffmanNode* t2, HuffmanNode *&p) {
    p = new HuffmanNode(t1->data + t2->data);
    t1->parent = t2->parent = p; //别忘了父指针
    p->left = t1;
    p->right = t2;
}

//释放r为根的霍夫曼树 其实就是递归释放二叉树喽
void HuffmanTree::deleteTree(HuffmanNode *r) {
    if(r == nullptr)
        return;
    deleteTree(r->left);
    deleteTree(r->right);
    delete r; //释放完左右子才能放心释放自己 后序框架
}

//层次遍历
void HuffmanTree::show() {
    if(root == nullptr) //defensive
        return;
    queue<HuffmanNode *> que;
    que.push(root);
    int level_size = 0; //每一层的结点数
    while(!que.empty()){
        if(level_size == 0)
            level_size = que.size(); //本层个数
        auto cur = que.front();
        que.pop();
        cout << cur->data << ' ';
        level_size--; //本层余下的结点数
        if(level_size == 0) //这一层输完了
            cout << endl;
        if(cur->left) que.push(cur->left);
        if(cur->right) que.push(cur->right);
    }
}


#endif //DATA_STRUCT_HUFFMANTREE_H
