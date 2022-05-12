//
// Created by Administrator on 2022/4/10.
//

#ifndef DATA_STRUCT_TREE_H
#define DATA_STRUCT_TREE_H
#include <iostream>
#include <queue>

using namespace std;

template<class T>
struct TreeNode{
    T data;
    TreeNode<T> *firstChd;
    TreeNode<T> *nextSibling;

    TreeNode() : firstChd(nullptr), nextSibling(nullptr) { ; }
    explicit TreeNode(T d): data(d), firstChd(nullptr), nextSibling(nullptr) { ; }
};

template<class T>
class Tree {
private:
    TreeNode<T> *root, *current; //根指针以及当前指针
    int Find(TreeNode<T> *r, T value); //在r为根的树中搜索value
    void RemovesubTree(TreeNode<T> *r); //删除以r为根的子树
    bool FindParent(TreeNode<T> *r, TreeNode<T> *p); //子树r中寻找p的父结点
    void RootFirstOrder(TreeNode<T> *r); //先根次序遍历
    void RootLastOrder(TreeNode<T> *r); //后根次序遍历
    void LevelOrder(TreeNode<T> *r); //层次遍历
public:
    Tree() : root(nullptr), current(nullptr) { ; }
    bool IsEmpty() { return root == nullptr; }
    //置根结点为当前结点
    bool Root();
    //将当前结点的第一个孩子置为当前结点
    bool FirstChild();
    //将当前结点的下一个兄弟置为当前结点
    bool NextSibling();
    //将当前结点的父结点置为当前结点
    bool Parent();
    //寻找值为value的结点并置为当前结点
    bool Find(T value);

    // 建立根 返回新结点的指针
    TreeNode<T> *BulitRoot(T data);
    // 给结点subT插入新的兄弟data 返回新结点的指针
    TreeNode<T> *InsertRightSibling(TreeNode<T>* subT, T data);
    // 给subT插入新的子女data 返回新结点的指针
    TreeNode<T> *InsertLeftChild(TreeNode<T>* subT, T data);


    //先根次序遍历
    void RootFirstOrder() { RootFirstOrder(root); }
    //后根次序遍历
    void RootLastOrder() { RootLastOrder(root); }
    //层次遍历 当前结点代表的子树
    void LevelOrder() { LevelOrder(current); }
};

template<class T>
int Tree<T>::Find(TreeNode<T> *r, T value) {
    return 0;
}

template<class T>
void Tree<T>::RemovesubTree(TreeNode<T> *r) {

}

//在r中找p的双亲结点并置为当前结点
template<class T>
bool Tree<T>::FindParent(TreeNode<T> *r, TreeNode<T> *p) {
    if(!r || !p) //defensive
        return false;
    auto son = r->firstChd;
    while(son){
        if(son == p){
            current = r; //递归终点 找到了r为p的父亲
            return true;
        }
        if(FindParent(son, p)) //子树完成了工作
            return true;
        son = son->nextSibling;
    }
    //到这里就说明所有子树搜了个遍 都没有完成
    current = nullptr;
    return false;
}


//将根结点置为当前结点
template<class T>
bool Tree<T>::Root() {
    if(root == nullptr){
        current = nullptr;
        return false;
    }
    current = root;
    return true;
}

//将当前结点的第一个子女置为当前结点
template<class T>
bool Tree<T>::FirstChild() {
    if(current == nullptr) //defensive
        return false;
    if(current->nextSibling == nullptr){
        current = nullptr;
        return false;
    }
    current = current->nextSibling;
    return true;
}

//将当前结点的下一个兄弟置为当前结点
template<class T>
bool Tree<T>::NextSibling() {
    if(current == nullptr) //defensive
        return false;
    if(current->nextSibling == nullptr) {
        current = nullptr;
        return false;
    }
    current = current->nextSibling;
    return true;
}

//将当前结点的父结点置为当前结点
template<class T>
bool Tree<T>::Parent() {
    if(current == nullptr) //defensive
        return false;
    if(current == root) { //根没有父结点
        current = nullptr;
        return false;
    }
    return FindParent(root, current); //在root树下找 current的父结点 并置为当前结点
}

template<class T>
bool Tree<T>::Find(T value) {
    return false;
}

//先根次序遍历 递归思路 先输出自己 再递归子问题输出所有子树的后根遍历
template<class T>
void Tree<T>::RootFirstOrder(TreeNode<T> *r) {
    if(r == nullptr) //递归终点
        return;
    cout << r->data << ' ';
    auto son = r->firstChd;
    while(son){
        RootFirstOrder(son);
        son = son->nextSibling;
    }
}

//后根次序遍历 递归思路为 先将所有子树都输出 最后输出自己
template<class T>
void Tree<T>::RootLastOrder(TreeNode<T> *r) {
    if(r == nullptr) //递归终点
        return;
    auto son = r->firstChd;
    while (son){
        RootLastOrder(son);
        son = son->nextSibling;
    }
    cout << r->data << ' ';
}

//层次遍历 典中典之队列
template<class T>
void Tree<T>::LevelOrder(TreeNode<T> *r) {
    if(r == nullptr) //defensive
        return;
    queue<TreeNode<T>*> que;
    que.push(r);
    while(!que.empty()){
        auto cur = que.front(); //队首出队
        cout << cur->data << ' ';
        que.pop();
        auto son = cur->firstChd;
        while(son) { //将队首的所有孩子都入队
            que.push(son);
            son = son->nextSibling;
        }
    }
}

//给本森林建立根节点
template<class T>
TreeNode<T> *Tree<T>::BulitRoot(T data) {
    auto new_node = new TreeNode<T>(data);
    root = new_node;
    return root;
}

//给subT插入新的兄弟data 返回新兄第结点
template<class T>
TreeNode<T> *Tree<T>::InsertRightSibling(TreeNode<T> *subT, T data) {
    auto new_node = new TreeNode<T>(data);
    auto tmp = subT;
    while(tmp->nextSibling) //指向兄弟链表的末尾
        tmp = tmp->nextSibling;
    tmp->nextSibling = new_node;
    return new_node;
}

//给subT插入新的子女data 返回新子女结点
template<class T>
TreeNode<T> *Tree<T>::InsertLeftChild(TreeNode<T> *subT, T data) {
    auto new_node = new TreeNode<T>(data);
    auto tmp = subT;
    while(tmp->firstChd) //指向子女链表的末尾
        tmp = tmp->firstChd;
    tmp->firstChd = new_node;
    return new_node;
}


#endif //DATA_STRUCT_TREE_H
