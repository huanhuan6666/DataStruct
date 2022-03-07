//
// Created by Administrator on 2022/3/6.
//

#ifndef DATA_STRUCT_LINKLIST_H
#define DATA_STRUCT_LINKLIST_H

#include "LinearList.h"
#include <iostream>

using namespace std;

template<class T>
struct ListNode {
    T data;
    ListNode<T> *next;

    ListNode<T>(ListNode<T> *ptr = nullptr) {
        next = ptr;
    }

    ListNode<T>(const T &x, ListNode<T> *ptr = nullptr) {
        next = ptr;
        data = x;
    }
};

template<class T> //带有dummy哑结点的链表
class List : public LinearList<T> {
public:
    ListNode<T> *head; //链表头指针
public:
    List() {
        head = new ListNode<T>;
    }

    List(const List<T> &l) {
        head = l.head;
    }

    int Length() const; //求大小
    ListNode<T> *Search(const T &x) const; //搜索给定值返回指针
    ListNode<T> *Locate(int i) const; //定位第i个元素的下标
    bool getData(int i, T &x) const; //获取第i个元素
    void setData(int i, const T &x); //设置第i个元素
    bool Insert(int i, const T &x); //在位置i上插入x
    bool Remove(int i, T &x); //删除第i个元素并通过x返回
    bool IsEmpty(); //是否为空
};

template<class T>
int List<T>::Length() const {
    int size = 0;
    ListNode<T> *tmp = head;
    while (tmp->next != nullptr) {
        size++;
        tmp = tmp->next;
    }
    return size;
}

template<class T>
ListNode<T> *List<T>::Search(const T &x) const {
    ListNode<T> *tmp = head->next;
    while (tmp != nullptr) {
        if (*tmp == x) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return nullptr;
}

template<class T>
ListNode<T> *List<T>::Locate(int i) const {
    if (i < 0) {
        cout << "index is too small!" << endl;
        return nullptr;
    }
    ListNode<T> *tmp = head; //从附加头结点开始
    int index = -1;
    while (tmp != nullptr) {
        if (index == i)
            return tmp;
        tmp = tmp->next;
        index++;
    }
    return nullptr;
}

template<class T>
bool List<T>::getData(int i, T &x) const {
    if (i < 0) {
        cout << "index is too small" << endl;
        return false;
    }
    ListNode<T> *tmp = head; //从附加头结点开始
    int index = -1;
    while (tmp != nullptr) {
        if (index == i) {
            x = tmp->data;
            return true;
        }
        tmp = tmp->next;
        index++;
    }
    return false;
}

template<class T>
void List<T>::setData(int i, const T &x) {
    if (i < 0) {
        cout << "index is too small" << endl;
        return;
    }
    ListNode<T> *tmp = head;
    for (int index = 0; tmp != nullptr && index < i; index++) { //hh感觉for写起来爽点但是while能做的判断更多
        tmp = tmp->next;
    }
    if (tmp != nullptr) { //说明找到了 tmp指向第i个结点
        tmp->data = x;
        return;
    }
    //到头了说明i太大了
    cout << "index is too big!" << endl;
}

template<class T>
bool List<T>::Insert(int i, const T &x) {
    if (i < 0) {
        cout << "index is too small" << endl;
        return false;
    }
    ListNode<T> *cur = head;
    //插入后新节点下标为i因此要找i-1
    for (int index = 0; cur != nullptr && index < i - 1; i++) {
        cur = cur->next;
    }
    if (cur != nullptr) { //找到了
        auto *newnode = new ListNode<T>(x);
        newnode->next = cur->next;
        cur->next = newnode;
        return true;
    }
    cout << "index is too big!" << endl;
    return false;
}

template<class T>
bool List<T>::Remove(int i, T &x) {
    if (i < 0) {
        cout << "index is too small" << endl;
        return false;
    }
    ListNode<T> *tmp = head;
    //同样要找第i-1个结点
    for (int index = 0; tmp!= nullptr && index < i - 1; i++) {
        tmp = tmp->next;
    }
    if(tmp!= nullptr){ //找到了第i-1个结点
        auto del = tmp->next;
        tmp->next = del->next;
        delete del;
        return true;
    }
    cout << "index is too big!" << endl;
    return false;
}


template<class T>
bool List<T>::IsEmpty() {
    return head->next == nullptr;
}

#endif //DATA_STRUCT_LINKLIST_H
