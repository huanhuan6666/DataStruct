//
// Created by Administrator on 2022/4/9.
//

#ifndef DATA_STRUCT_THREADTREE_H
#define DATA_STRUCT_THREADTREE_H
#include <iostream>

using namespace std;

//线索二叉树的结点
template<class T>
struct ThreadNode{
    T data;
    char ltag:1, rtag:1;
    ThreadNode<T> *right;
    ThreadNode<T> *left;
    ThreadNode() : ltag(0), rtag(0), right(nullptr), left(nullptr) { ; }
    ThreadNode(T d) : ltag(0), rtag(0), right(nullptr), left(nullptr), data(d) { ; }
};

//线索二叉树
template<class T>
class ThreadTree {
private:
    ThreadNode<T> *root;
    void CreateInThread(ThreadNode<T>* r, ThreadNode<T>* &pre); //中序遍历建立线索二叉树
    ThreadNode<T>* Parent(ThreadNode<T>* r);  //寻找结点t的父结点
public:
    ThreadTree() : root(nullptr) { ; }
    //建立中序线索二叉树 外部接口
    void CreateInThread();
    //寻找子树r中序遍历下的第一个结点
    ThreadNode<T>* InFirst(ThreadNode<T>* r);
    //寻找子树r中序遍历下最后一个结点
    ThreadNode<T>* InLast(ThreadNode<T>* r);
    //寻找中序下 r的后继结点
    ThreadNode<T>* InNext(ThreadNode<T>* r);
    //寻找中序下 r的前驱结点
    ThreadNode<T>* InPre(ThreadNode<T>* r);

};

//寻找以r为根的子树 在中序遍历下的第一个结点  左中右 也就是说第一个结点一定在左 递归完事
template<class T>
ThreadNode<T> *ThreadTree<T>::InFirst(ThreadNode<T> *r) {
    if(r == nullptr) //defensive
        return nullptr;
    if(r->left == nullptr) //实际的递归终点
        return r;
    return InFirst(r->left);
}

//寻找以r为根的子树 在中序遍历下的最后一个结点 左中右 最后一个结点一定在右 还是递归
template<class T>
ThreadNode<T> *ThreadTree<T>::InLast(ThreadNode<T> *r) {
    if(r == nullptr) //defensive
        return nullptr;
    if(r->right == nullptr) //实际递归终点
        return r;
    return InLast(r->right);
}

//找结点r的后继结点 如果是线索的话直接返回右指针
//但是如果右指针是右子树的话 那么根据中序遍历左中右的特点 其直接后续一定为右子树在中序遍历下的第一个结点
template<class T>
ThreadNode<T> *ThreadTree<T>::InNext(ThreadNode<T> *r) {
    if(r->rtag == 1) //线索树的定义
        return r->right;
    return InFirst(r->right); //右指针不是线索的话
}

//找结点r的前驱结点 如果是线索的话直接返回左指针
//但是如果左指针是左子树的话 根据中序遍历左中右的特点 其直接前驱一定是左子树在中序遍历下的最后一个结点
template<class T>
ThreadNode<T> *ThreadTree<T>::InPre(ThreadNode<T> *r) {
    if(r->ltag == 1) //线索树的定义
        return r->left;
    return InLast(r->left); //左指针不是线索的话
}

//对已存在的二叉树r进行线索化 即填写那些nullptr指针为线索 并且修改tag标签为1
//pre总指向中序遍历下上一个刚刚访问的结点 也就是前驱结点
//这个pre用指针的引用 神中神 直接利用中序模板得到了前驱 而不是傻傻Last First
template<class T>
void ThreadTree<T>::CreateInThread(ThreadNode<T> *r, ThreadNode<T> *&pre) {
    if(r == nullptr)
        return;
    CreateInThread(r->left, pre); //递归将左子树线索化
    if(!r->left) { //建立前驱线索 需要线索化
        r->ltag = 1;
        r->left = pre;
    }
    if(!pre->right) { //建立前驱结点的后继线索
        pre->rtag = 1;
        pre->right = r;
    }
    pre = r; //更新pre为r 从而达到pre总指向前驱结点的效果
    CreateInThread(r->right, pre); //将右子树线索化
}

//将二叉树中序线索化的外部接口
template<class T>
void ThreadTree<T>::CreateInThread() {
    ThreadNode<T>* pre = nullptr;
    if(root == nullptr) //defensive
        return;
    CreateInThread(root, pre); //pre最后指向中序的最后一个结点 即InLast(root)
    pre->rtag = 1;
    pre->right = nullptr;
}

//在完成好的中序线索树上寻找结点r的父结点
//线索树的应用
template<class T>
ThreadNode<T> *ThreadTree<T>::Parent(ThreadNode<T> *r) {
    //假设r是其父结点的左指针
    auto p = r;
    while(p->rtag == 0) { //找右子树的最右侧结点 那个结点的后继线索就是r的父结点
        p = p->right;
    }
    //通过最右侧结点的线索 可以判断r是其父左指针还是右指针
    p = p->right;
    if(p == nullptr || p && p->left != r){ //为空说明找到整个树的首结点了 非空且!=说明找到爷爷了 它是爷爷的左节点但不是父亲的
        p = r; //不论怎样 父结点这时可以确定就是左子树首个结点的前驱
        while(p->ltag == 0) {
            p = p->left;
        }
        p = p->left;
    }
    return p;
}


#endif //DATA_STRUCT_THREADTREE_H
