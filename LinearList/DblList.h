//
// Created by Administrator on 2022/3/7.
//

#ifndef DATA_STRUCT_DBLLIST_H
#define DATA_STRUCT_DBLLIST_H

#include <iostream>

using namespace std;

template<class T>
struct DblNode {
    T data;
    DblNode<T> *rLink, *lLink;

    DblNode(const T &x, DblNode<T> *lptr = nullptr, DblNode<T> *rptr = nullptr) : data(x), rLink(lptr), lLink(rptr) {}

    DblNode(DblNode<T> *lptr = nullptr, DblNode<T> *rptr = nullptr) : rLink(lptr), lLink(rptr) {}
};

template<class T>
class DblList {
private:
    DblNode<T> *first;
public:
    DblList(T val) { //设置初始结点，即附加头结点
        first = new DblNode<T>(val);
        first->lLink = first;
        first->rLink = first;
    }

    ~DblList() { //析构函数
        T x;
        while (first->rLink != first) {
            Remove(1, x, 0);
            cout << "delete element: " << x << " ";
        }
    }

    int Length() const {
        int len = 0;
        DblNode<T> *cur = first->rLink;
        while (cur != first){
            ++len;
            cur = cur->rLink;
        }
        return len;
    }

    bool IsEmpty() const {
        return first == first->rLink;
    }

    DblNode<T> *getHead() const {
        return first;
    }

    void setHead(DblNode<T> *ptr) {
        first = ptr;
    }

    DblNode<T> *Search(const T &x) {
        DblNode<T> *cur = first->rLink;
        while (cur != first) {
            if (cur->data == x) {
                return cur;
            }
            cur = cur->rLink;
        }
        return nullptr;
    }

    DblNode<T> *Locate(int i, int d) {
        if(IsEmpty() || i == -1) //如果找-1结点或者链表为空
            return first;
        if (d == 0) { //从前到后，下标从0开始
            int index = 0;
            DblNode<T> *cur = first->rLink;
            while (cur != first) {
                if (i == index) {
                    return cur;
                }
                cur = cur->rLink;
                ++index;
            }
            return nullptr;
        } else {
            int index = 0;
            DblNode<T> *cur = first->lLink;
            while (cur != first) {
                if (i == index) {
                    return cur;
                }
                cur = cur->lLink;
                ++index;
            }
            return nullptr;
        }
    }

    //返回序号为i的结点指针，d=0按照前驱方向 !=0按照后续方向
    bool Insert(int i, const T &x, int d) {
        DblNode<T> *cur = Locate(i, d);
        if (cur == nullptr)
            return false;
        DblNode<T> *pre;
        auto *newnode = new DblNode<T>(x);
        if (d == 0) { //从前到后，插到cur的左边
            pre = cur->lLink;
            newnode->rLink = cur;
            newnode->lLink = pre;
            cur->lLink = newnode;
            pre->rLink = newnode;
        } else { //从后到前，查到cur的右边
            pre = cur->rLink;
            newnode->lLink = cur;
            newnode->rLink = pre;
            cur->rLink = newnode;
            pre->lLink = newnode;
        }
        return true;
    }

    bool Remove(int i, const T &x, int d) {
        DblNode<T> *cur = Locate(i, d);
        if (cur == nullptr)
            return false;
        x = cur->data;
        cur->rLink->lLink = cur->lLink;
        cur->lLink->rLink = cur->rLink;
        delete cur;
        return true;
    }
};

#endif //DATA_STRUCT_DBLLIST_H
