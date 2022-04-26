//
// Created by Administrator on 2022/4/25.
//

#ifndef DATA_STRUCT_BSTREE_H
#define DATA_STRUCT_BSTREE_H
#include <iostream>
#include <queue>
using namespace std;

template<class T>
class BSTNode {
private:
    T data;
    int key;
    BSTNode<T> *left, *right;
public:
    BSTNode() : left(nullptr), right(nullptr) { ; }

    BSTNode(T d) : data(d), left(nullptr), right(nullptr) { ; }
};

template<class T>
class BSTree {
private:
    BSTNode<T> *root;

    //递归搜索x 内部调用
    BSTNode<T> *Search(const T &x, BSTNode<T> *root);

    //迭代搜索
    BSTNode<T> *newSearch(const T &x, BSTNode<T> *root);

    //递归释放空间 内部调用
    void makeEmpty(BSTNode<T> *root);

    //递归打印树 内部调用
    void PrintTree(BSTNode<T> *root);

    //插入元素 内部调用
    bool Insert(const T &elem, BSTNode<T> *root);

    //更好的插入方式
    bool newInsert(const T &elem, BSTNode<T> *&root);

    //删除元素 内部调用
    bool Remove(const T &x, BSTNode<T> *&root);

public:
    BSTree() : root(nullptr) { ; }

    //按照输入建立二叉搜索树 end结束标记
    BSTree(T end);

    ~BSTree() {
        makeEmpty(root);
    }

    //搜索x
    BSTNode<T> *Search(const T &x) {
        return Search(x, root);
    }

    //打印树 外部调用
    void PrintTree() {
        PrintTree(root);
    }

    //插入新元素
    bool Insert(const T &elem) {
        return Insert(elem, root);
    }

    //删除含x的结点
    bool Remove(const T &x) {
        return Remove(x, root);
    }

};

//根据输入建立树 输入end结束
template<class T>
BSTree<T>::BSTree(T end) {
    T tmp;
    while(true) {
        cin >> tmp;
        if(tmp == end)
            break;
        Insert(tmp, root);
    }
}


//递归法搜索x 返回其指针
template<class T>
BSTNode<T> *BSTree<T>::Search(const T &x, BSTNode<T> *root) {
    if (root == nullptr) //递归终点
        return nullptr;
    if (root->data == x) //x在根找到了
        return root;
    else if (x < root->data) { //x在左子树
        return Search(x, root->left);
    } else { //x在右子树
        return Search(x, root->right);
    }
}

//迭代法搜索x 返回其指针
template<class T>
BSTNode<T> *BSTree<T>::newSearch(const T &x, BSTNode<T> *root) {
    if (root == nullptr)
        return nullptr;
    auto tmp = root;
    while (tmp) {
        if (x == tmp->data)
            return tmp;
        else if (x < tmp->data) //x比根节点tmp小 在其左子树
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    return tmp; //最后的tmp一定为nullptr
}

//释放root子树的内存 先释放左右子树 root才能安全释放 后序框架
template<class T>
void BSTree<T>::makeEmpty(BSTNode<T> *root) {
    if(root == nullptr)
        return;
    makeEmpty(root->left);
    makeEmpty(root->right);
    delete root;
}

//层序遍历
template<class T>
void BSTree<T>::PrintTree(BSTNode<T> *root) {
    if(root == nullptr)
        return;
    queue<BSTNode<T> *>que;
    que.push(root);
    int level_count = 0; //每一层的个数
    while(!que.empty()) {
        if(level_count == 0) //新的一层 记录其个数
            level_count = que.size();
        //输出队首
        auto it = que.front();
        que.pop();
        cout << it->data << ' ';
        if(--level_count == 0)
            cout << endl;
        //输入下一层的结点
        if(it->left) que.push(it->left);
        if(it->right) que.push(it->right);
    }
}

// 向root中插入elem 如果已经存在则返回false 不存在则插入 形成一个新的叶结点
// 这个方法不太好 是先调用了Search搜索 并且由于root为值传递 对于递归终点的判断不得不为!root->left这样子
template<class T>
bool BSTree<T>::Insert(const T &elem, BSTNode<T> *root) {
    if (Search(elem, root) != nullptr) //已经存在不能插入
        return false;
    if (!root->left && elem < root->data) { //递归终点 成为左叶子
        BSTNode<T> *tmp = new BSTNode<T>(elem);
        root->left = tmp;
        return true;
    }
    if (!root->right && elem > root->data) { //递归终点 成为右叶子
        BSTNode<T> *tmp = new BSTNode<T>(elem);
        root->right = tmp;
        return true;
    }
    //递归子问题
    if (elem > root->data) { //应该插入到右子树
        return Insert(elem, root->right);
    }
    if (elem < root->data) { //应该插入到左子树中
        return Insert(elem, root->left);
    }
}

// 插入元素 不再显示Search搜索 并且递归终点的判断也更漂亮一些 注意root为引用参数
template<class T>
bool BSTree<T>::newInsert(const T &elem, BSTNode<T> *&root) {
    if(root == nullptr) { //到达叶结点 直接修改其本身
        root = new BSTNode<T>(elem);
        return true;
    }
    if(elem == root->data) //已经存在了
        return false;
    else if(elem < root->data) { //应该插入root的左子树
        return newInsert(elem, root->left);
    }
    else { //应该插入root的右子树
        return newInsert(elem, root->right);
    }
}

// 在root子树下删除键为x的结点
template<class T>
bool BSTree<T>::Remove(const T &x, BSTNode<T> *&root) {
    if(root == nullptr) //根本找不到键为x的结点
        return false;
    if(x == root->data) { //需要删除root
        if(root->left && root->right) { //左右子都不为空
            auto tmp = root->right;
            while(tmp->left)
                tmp = tmp->left; //找到右子树中序下第一个结点
            root->data = tmp->data; //覆盖root的值
            return Remove(tmp->data, root->right); //在右子树下删掉中序下的第一个结点
            //根据我们的分析 这个递归只可能有两种情况 即两个子树都为空 和 左空右不空
        }
        else { //至少一个子树为空
            auto tmp = root;
            if(!root->left)
                root = root->right;
            else
                root = root->left;
            delete tmp; //确实删掉了结点
            return true;
        }
    }
    else if(x > root->data) { //在右子树下面删
        return Remove(x, root->right);
    }
    else { //在左子树下面删
        return Remove(x, root->left);
    }
}

#endif //DATA_STRUCT_BSTREE_H
