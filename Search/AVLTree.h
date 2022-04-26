//
// Created by Administrator on 2022/4/26.
//

#ifndef DATA_STRUCT_AVLTREE_H
#define DATA_STRUCT_AVLTREE_H
template<class T>
class AVLNode {
private:
    T data;
    int bf; //平衡因子
    AVLNode<T> *left, *right;
public:
    AVLNode() : left(nullptr), right(nullptr), bf(0) { ; }
    AVLNode(T &d) : data(d), left(nullptr), right(nullptr), bf(0) { ; }
};

template<class T>
class AVLTree {
private:
    AVLNode<T>* root;
    //左单旋转
    void RotateL(AVLNode<T> *&root);
    //右单旋转
    void RotateR(AVLNode<T> *&root);
    //先左后右双旋转
    void RotateLR(AVLNode<T> *&root);
    //先右后左双旋转
    void RotateRL(AVLNode<T> *&root);
public:
    AVLTree() : root(nullptr) { ; }
    ~AVLTree();
    //搜索x
    AVLNode<T> *Search(T x);
    //插入x
    bool Insert(T &x) {
        return Insert(root, x);
    }
    //删除x
    bool Remove(T x) {

    }
};

//左单旋转 参数root为三层结点的最高的那一个 右子树比左子树高 左单旋转后新根在root处
template<class T>
void AVLTree<T>::RotateL(AVLNode<T> *&root) {
    auto subL = root; //root最终成为新根的左子树
    root = root->right; //左旋转
    subL->right = root->left;
    root->left = subL;
    root->bf = subL->bf = 0;
}

//右单旋转 参数root为三层结点的最高的那一个 左子树比右子树高 最终新根在root处
template<class T>
void AVLTree<T>::RotateR(AVLNode<T> *&root) {
    auto subR = root; //root最终成为新根的右子树
    root = root->left;
    subR->left = root->right;
    root->right = subR;
    root->bf = subR->bf = 0;
}

//先左单旋转再右单旋转 root初始为 '<' 的右上角
template<class T>
void AVLTree<T>::RotateLR(AVLNode<T> *&root) {
    //先左单旋转
    auto tmp = root->left; //tmp指向<的尖尖 即将被<的右下角代替
    root->left = root->left->right;
    tmp->right = root->left->left; //原来的尖尖 的右子树指向原来<右下角的左子树
    root->left->left = tmp;

    //再右单旋转
    auto subR = root; //最后的root变成新根的右子树
    root = root->left;
    subR->left = root->right;
    root->right = subR;

    root->bf = 0;
}

template<class T>
void AVLTree<T>::RotateRL(AVLNode<T> *&root) {

}

#endif //DATA_STRUCT_AVLTREE_H
