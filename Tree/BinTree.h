//
// Created by Administrator on 2022/4/9.
//

#ifndef DATA_STRUCT_BINTREE_H
#define DATA_STRUCT_BINTREE_H

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//二叉树结点
template<class T>
struct BinTreeNode {
    T data;
    BinTreeNode<T> *left;
    BinTreeNode<T> *right;

    BinTreeNode() : left(nullptr), right(nullptr) { ; }

    explicit BinTreeNode(T x) : data(x), left(nullptr), right(nullptr) { ; }
};

//二叉树 root==nullptr表示为空树
template<class T>
class BinTree {
    friend istream &operator>>(istream& in, BinTree<T>&x){
        x.CreateBinTree(in, x.root);
    }
private:
    BinTreeNode<T> *root;

    BinTreeNode<T> *Copy(BinTreeNode<T> *src); //深拷贝src
    void Destory(BinTreeNode<T> *r); //释放root表示的树空间
    int GetHeight(BinTreeNode<T> *r); //获取root为根的树的高度
    int GetSize(BinTreeNode<T> *r); //获取root为根的树的结点个数
    BinTreeNode<T> *GetParent(BinTreeNode<T> *r, BinTreeNode<T> *t); //在root树中找t的父结点
    void preOrder(BinTreeNode<T> *r); //前序遍历
    void inOrder(BinTreeNode<T> *r); //中序遍历
    void postOrder(BinTreeNode<T> *r); //后序遍历
    void preOrder_new(BinTreeNode<T> *r); //前序遍历
    void inOrder_new(BinTreeNode<T> *r); //中序遍历
    void postOrder_new(BinTreeNode<T> *r); //后序遍历
    bool Insert(BinTreeNode<T> *root, T item); //向root中插入item元素
    BinTreeNode<T> *Find(BinTreeNode<T> *r, T item); //寻找item元素
public:
    BinTree() : root(nullptr) { ; }

    //拷贝构造函数
    BinTree(const BinTree<T> &t) { root = Copy(t.root); }

    ~BinTree() { Destory(root); } //析构函数
    //判断树是否为空
    bool IsEmpty() { return root == nullptr; }

    //获取树的高度
    int Height() { return GetHeight(root); }

    //获取树的结点个数
    int Size() { return GetSize(root); }

    //获取t的父结点
    BinTreeNode<T> *Parent(BinTreeNode<T> *t) { return GetParent(root, t); }

    //获取t的左子树
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *t) { return t == nullptr ? t : t->left; }

    //获取t的右子树
    BinTreeNode<T> *RightChild(BinTreeNode<T> *t) { return t == nullptr ? t : t->right; }

    //获取根
    BinTreeNode<T> *GetRoot() const { return root; }

    //前序遍历
    void preOrder() { preOrder(root); }

    //中序遍历
    void inOrder() { inOrder(root); }

    //后序遍历
    void postOrder() { postOrder(root); }

    //下面是非递归访问
    void preOrder_new() { postOrder_new(root); }
    void inOrder_new()  { inOrder_new(root); }
    void postOrder_new() { postOrder_new(root); }
    //层次遍历
    void levelOrder();

    //插入新元素
    int Insert(const T item);

    //搜索元素
    BinTreeNode<T> *Find(T item) const;

    //根据输入内容创建二叉树
    void CreateBinTree(istream& in, BinTreeNode<T>* &r);
};

//深拷贝src到root 本质是个后序遍历 先拷贝完成左右子树 才能完成拷贝根节点
template<class T>
BinTreeNode<T> *BinTree<T>::Copy(BinTreeNode<T> *src) {
    BinTreeNode<T> *res = nullptr;
    if (src == nullptr)
        return res;
    res = new BinTreeNode<T>;
    res->data = src->data;
    res->left = Copy(src->left);
    res->right = Copy(src->right);

    return res;
}

//释放堆区空间 同样是后序遍历 只有释放完左右子树后才能安全释放根
template<class T>
void BinTree<T>::Destory(BinTreeNode<T> *r) {
    if (r == nullptr)
        return;
    Destory(r->left);
    Destory(r->right);
    delete r;
}

//获取高度 空树高为0 最深的子树+1就是树高 因此同样是后序遍历
template<class T>
int BinTree<T>::GetHeight(BinTreeNode<T> *r) {
    if (r == nullptr)
        return 0;
    int l_h = GetHeight(r->left);
    int r_h = GetHeight(r->right);
    return max(l_h, r_h) + 1;
}

//空树结点数为0 直到左右子树个数和 + 根即为结构 同样为后序遍历
template<class T>
int BinTree<T>::GetSize(BinTreeNode<T> *r) {
    if (r == nullptr)
        return 0;
    int l_s = GetSize(r->left);
    int r_s = GetSize(r->right);
    return l_s + r_s + 1;
}

//在r树中 找t的父结点返回 只有左右子树都找不到 根也不对才返回nullptr 因此也必须得知左右子树的情况后才能解决问题 是后序遍历
template<class T>
BinTreeNode<T> *BinTree<T>::GetParent(BinTreeNode<T> *r, BinTreeNode<T> *t) {
    if (r == nullptr)
        return nullptr;
    if (r->left == t || r->right == t) //找到了
        return r;
    auto l_res = GetParent(r->left, t);
    if(l_res) return l_res; //左边找到了就直接返回 避免不必要的递归
    auto r_res = GetParent(r->right, t);
    if(r_res) return r_res;

    return nullptr; //两边都找不到
}

//先序遍历
template<class T>
void BinTree<T>::preOrder(BinTreeNode<T> *r) {
    if(r == nullptr)
        return;
    cout << r->data << ' ';
    preOrder(r->left);
    preOrder(r->right);
}

//中序遍历
template<class T>
void BinTree<T>::inOrder(BinTreeNode<T> *r) {
    if(r == nullptr)
        return;
    inOrder(r->left);
    cout << r->data << ' ';
    inOrder(r->right);
}

//后序遍历
template<class T>
void BinTree<T>::postOrder(BinTreeNode<T> *r) {
    if(r == nullptr)
        return;
    postOrder(r->left);
    postOrder(r->right);
    cout << r->data << ' ';
}

template<class T>
bool BinTree<T>::Insert(BinTreeNode<T> *root, T item) {
    return false;
}

//在r树中找item
template<class T>
BinTreeNode<T> *BinTree<T>::Find(BinTreeNode<T> *r, T item) {
    if(r == nullptr)
        return nullptr;
    if(r->data == item)
        return r;
    auto l_res = Find(r->left, item);
    if(l_res) return l_res;
    auto r_res = Find(r->right, item);
    if(r_res) return r_res;

    return nullptr;
}

//根据输入前序遍历顺序 创建二叉树 先创建根 再创建左右子树 即先序遍历
template<class T>
void BinTree<T>::CreateBinTree(istream &in, BinTreeNode<T> *&r) {
    T chr;
    in >> chr;
    if(chr == ';')
        return;
    if(chr == '@') { //表示空
        r = nullptr;
        return;
    }
    //不为空则创建 根结点
    r = new BinTreeNode<T>;
    r->data = chr;
    CreateBinTree(in, r->left);
    CreateBinTree(in, r->right);
}


//基于栈的非递归遍历
template<class T>
void BinTree<T>::preOrder_new(BinTreeNode<T> *r) {
    if(r == nullptr)
        return;
    vector<BinTreeNode<T>* > S;
    BinTreeNode<T*> p = r;
    S.push_back(nullptr);
    while(p){ //压入栈的就是左子树递归之后还需要被访问的参数 即右子树指针
        cout << p.data << ' ';
        if(p.right)
            S.push_back(p.right);
        if(p.left) //进左子树
            p = p.left;
        else{ //左子树为空
            p = S[S.size() - 1];
            S.pop_back();
        }
    }
}


template<class T>
void BinTree<T>::inOrder_new(BinTreeNode<T> *r) {
    if(r == nullptr)
        return;
    vector<BinTreeNode<T>*> S;
    BinTreeNode<T>* p = r;
    do{
        while(p){ //压入栈中的是左指针 其实本质是由于我们需要这些指针来访问其右结点 因此本质上还是压入的之后用到的右指针
            S.push_back(p);
            p = p->left;
        }
        if(!S.empty()){
            p = S[S.size()-1]; //通过栈保存的结点指针 访问其本身和其right
            S.pop_back();
            cout << p->data << ' ';
            p = p->right;
        }
    }while(p || !S.empty());
}

template<class T>
void BinTree<T>::postOrder_new(BinTreeNode<T> *r) {
    vector<pair<BinTreeNode<T>*, char>> S; //标记指针代表的是左子树还是右子树
    BinTreeNode<T>* p = r;
    do{
        while(p){ //先左递归 一直压入左指针 直到不能压
            S.push_back(make_pair(p, 'L'));
            p = p->left;
        }
        int flag = 1;
        while(flag && !S.empty()){
            auto w = S[S.size() - 1];
            S.pop_back();
            p = w.first; //获取其指针
            switch (w.second) {
                case 'L': //栈顶为左指针 改为右压入并跳出循环 作为新的起点再一直压左指针
                    w.second = 'R';
                    S.push_back(w); //注意压入时 p没有改变
                    flag = 0;
                    p = p->right; //p变成右指针 作为新一个起点 下面就是跳出循环 压入新起点的一系列左指针
                    break;
                case 'R': //右指针访问完 才该输出根了
                    cout << p->data << ' ';
                    break;
                default:
                    break;
            }
        }
    }while(!S.empty());
}

//层次遍历root
template<class T>
void BinTree<T>::levelOrder() {
    if(root == nullptr)
        return;
    queue<BinTreeNode<T>*> que;
    que.push(root);
    while(!que.empty()){
        auto p = que.front();
        que.pop(); //队首出队并访问
        cout << p->data << ' ';
        if(p->left) que.push(p->left); //将其左右子加入 即下一层
        if(p->right) que.push(p->right);
    }
}


#endif //DATA_STRUCT_BINTREE_H
