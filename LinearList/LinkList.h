//
// Created by Administrator on 2022/3/6.
//

#ifndef DATA_STRUCT_LINKLIST_H
#define DATA_STRUCT_LINKLIST_H
#include "LinearList.h"
#include <iostream>

using namespace std;

template<class T>
struct ListNode{
    T data;
    ListNode<T>* next;
    ListNode<T>(ListNode<T>* ptr = nullptr){
        next = ptr;
    }
    ListNode<T>(const T& x, ListNode<T>* ptr = nullptr){
        next = ptr;
        data = x;
    }
};
template<class T> //带有dummy哑结点的链表
class List : public LinearList<T>
{
public:
    ListNode<T> *head; //链表头指针
public:
    List(){
        head = new ListNode<T>;
    }
    List(const List<T>& l){
        head = l.head;
    }
    int Size() const;
    int Length() const; //求大小
    ListNode<T>* Search(const T &x) const; //搜索给定值
    ListNode<T>* Locate(int i) const; //定位第i个元素的下标
    bool getData(int i, T &x) const; //获取第i个元素
    void setData(int i, const T &x); //设置第i个元素
    bool Insert(int i, const T &x); //在位置i上插入x
    bool Remove(int i, T &x); //删除第i个元素并通过x返回
    bool IsEmpty(); //是否为空
    bool IsFull(); //是否为满
    void Sort();  //排序
    void Input(); //输入
    void Output(); //输出
};

template<class T>
int List<T>::Size() const {
    int size = 0;
    ListNode<T> *tmp = head;
    while (tmp->next != nullptr){
        size ++;
        tmp = tmp->next;
    }
    return size;
}

template<class T>
int List<T>::Length() const {
    return Size();
}

template<class T>
ListNode<T>* List<T>::Search(const T &x) const {
    ListNode<T>* tmp = head->next;
    while (tmp != nullptr){
        if(*tmp == x){
            return tmp;
        }
        tmp = tmp->next;
    }
    return nullptr;
}

template<class T>
ListNode<T>* List<T>::Locate(int i) const {
    ListNode<T>* tmp = head;
    int index = 0;
    while(tmp != nullptr){
        if(index == i)
            return tmp;
        tmp = tmp->next;
        index++;
    }
    return nullptr;
}

template<class T>
bool List<T>::getData(int i, T &x) const {
    if(i <= 0) {
        cout << "index is too small" << endl;
        return false;
    }
    ListNode<T>* tmp = head;
    int index = 0;
    while(tmp != nullptr){
        if(index == i){
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
    if(i <= 0) {
        cout << "index is too small" << endl;
        return;
    }
    ListNode<T>* tmp = head;
    int index = 0;
    while(tmp != nullptr){
        if(index == i){
            *tmp = x;
            return;
        }
        tmp = tmp->next;
        index++;
    }
}

template<class T>
bool List<T>::Insert(int i, const T &x) {
    if(i <= 0) {
        cout << "index is too small" << endl;
        return false;
    }
    ListNode<T>* newnode = new ListNode<T>(x);
    ListNode<T>* tmp = head;
    int index = 1;
    while(tmp != nullptr){
        if(index == i){
            newnode->next = tmp->next;
            tmp->next = newnode;
            return true;
        }
        tmp = tmp->next;
        index++;
    }
    return false;
}

template<class T>
bool List<T>::Remove(int i, T &x) {
    if(i <= 0) {
        cout << "index is too small" << endl;
        return false;
    }
    ListNode<T>* delnode = nullptr;
    ListNode<T>* tmp = head;
    int index = 1;
    while(tmp != nullptr){
        if(index == i){
            delnode = tmp->next;
            x = delnode->data;
            tmp->next = delnode->next;
            delete delnode;
            return true;
        }
        tmp = tmp->next;
        index++;
    }
    return false;
}


template<class T>
bool List<T>::IsEmpty() {
    return head->next == nullptr;
}

template<class T>
bool List<T>::IsFull() {
    return false;
}

template<class T>
void List<T>::Sort() {
    cout << "tobe continued..." << endl;
}

template<class T>
void List<T>::Input() {
    int size;
    while(true) {
        cout << "please input size: ";
        cin >> size;
        if(size <= 0){
            cout << "size is too small !" << endl;
            continue;
        }
        break;
    }
    T each;
    for(int i = 0; i<size; i++){
        cout << "please input " << i << " element: ";
        cin >> each;
        Insert(1, each);
    }
}

template<class T>
void List<T>::Output() {
    ListNode<T>* tmp = head->next;
    while(tmp){
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
}

#endif //DATA_STRUCT_LINKLIST_H
