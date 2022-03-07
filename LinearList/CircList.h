//
// Created by Administrator on 2022/3/7.
//

#ifndef DATA_STRUCT_CIRCLIST_H
#define DATA_STRUCT_CIRCLIST_H

#include <iostream>

using namespace std;

template<class T>
struct CircLinkNode {
    T data;
    CircLinkNode<T> *next;

    explicit CircLinkNode(CircLinkNode<T> *ptr = nullptr) {
        next = ptr;
    }

    explicit CircLinkNode(const T &t, CircLinkNode<T> *ptr = nullptr) {
        data = t;
        next = ptr;
    }
};

//同样有一个附加头节点，当first指向自己时说明链表为空
template<class T>
class CircList {
private:
    CircLinkNode<T> *first; //符加头结点指针
public:
    explicit CircList(const T &x) {
        first = new CircLinkNode<T>(x);
        first->next = first; //初始化为空
    }

    CircList(CircList<T> &L) {

    }

    ~CircList() {
        auto cur = first->next;
        while (cur != first) {
            first->next = cur->next;
            delete cur;
            cur = first->next;
        }
    }

    int Length() const {
        int size = 0;
        CircLinkNode<T> *tmp = first;
        while (first != tmp->next) {
            tmp = tmp->next;
            size++;
        }
        return size;
    }

    bool IsEmpty() const {
        return first->next == first;
    }

    CircLinkNode<T> *getHead() const {
        return first;
    }

    void setHead(CircLinkNode<T> *ptr) {
        first = ptr;
    }

    CircLinkNode<T> *Search(T x) {
        CircLinkNode<T> *tmp = first->next;
        while (first != tmp) {
            if (tmp->data == x) {
                return tmp;
            }
            tmp = tmp->next;
        }
        cout << "cna't find in list!" << endl;
        return nullptr;
    }

    CircLinkNode<T> *Locate(int i) { //下标从0开始
        if (i < 0) {
            cout << "index is too small!" << endl;
            return nullptr;
        }
        CircLinkNode<T> *tmp = first->next;
        for (int index = 0; tmp != first && index < i; index++) {
            tmp = tmp->next;
        }
        if (tmp != first) { //找到了第i个结点
            return tmp;
        }
        cout << "index is so big!" << endl;
        return nullptr;
    }

    T *getData(int i) {
        if (i < 0) {
            cout << "index is too small!" << endl;
            return nullptr;
        }
        CircLinkNode<T> *tmp = first->next;
        for (int index = 0; tmp != first && index < i; index++) {
            tmp = tmp->next;
        }
        if (tmp != first) { //找到了第i个结点
            return tmp->data;
        }
        cout << "index is so big!" << endl;
        return nullptr;
    }

    void setData(int i, T &x) {
        if (i < 0) {
            cout << "index is too small!" << endl;
            return;
        }
        CircLinkNode<T> *tmp = first->next;
        for (int index = 0; tmp != first && index < i; index++) {
            tmp = tmp->next;
        }
        if (tmp != first) { //找到了第i个结点
            tmp->data = x;
            return;
        }
        cout << "i is so big!" << endl;
    }

    bool Insert(int i, T &x) {
        if (i < 0) {
            cout << "index is so small!" << endl;
            return false;
        }
        CircLinkNode<T> *tmp = first;
        for (int index = 0; index < i; index++) {
            tmp = tmp->next;
        }
        //找到了第i-1个结点
        auto newnode = new CircLinkNode<T>(x);
        newnode->next = tmp->next;
        tmp->next = newnode;
        return true;
    }

    bool Remove(int i, T &x) {
        if (i < 0) {
            cout << "index is too small!" << endl;
            return false;
        }
        if (IsEmpty()) {
            cout << "list is empty!" << endl;
            return false;
        }
        CircLinkNode<T> *tmp = first->next;
        for (int index = 0; tmp != first && index < i - 1; index++) {
            tmp = tmp->next;
        }
        if (tmp != first) { //找到了第i-1个结点
            auto del = tmp->next;
            x = tmp->data;
            tmp->next = del->next;
            delete del;
            return true;
        }
        cout << "index is too big!" << endl;
        return false;
    }

};

#endif //DATA_STRUCT_CIRCLIST_H
