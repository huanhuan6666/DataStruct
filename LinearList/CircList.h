//
// Created by Administrator on 2022/3/7.
//

#ifndef DATA_STRUCT_CIRCLIST_H
#define DATA_STRUCT_CIRCLIST_H
#include <iostream>

using namespace std;

template<class T>
struct CircLinkNode{
    T data;
    CircLinkNode<T> *next;
    CircLinkNode(CircLinkNode<T> *ptr = nullptr){
        next = ptr;
    }
    CircLinkNode(const T& t, CircLinkNode<T> *ptr = nullptr){
        data = t;
        next = ptr;
    }
};

//同样有一个附加头节点，当first指向自己时说明链表为空
template<class T>
class CircList{
private:
    CircLinkNode<T> *first, *last; //头指针和尾指针
public:
    CircList(const T& x) {
        first = new CircLinkNode<T>(x);
        first->next = first; //初始化为空
    }

    CircList(CircList<T> &L) {

    }

    ~CircList() {

    }

    int Length() const {
        int size = 0;
        CircLinkNode<T> *tmp = first;
        while(first != tmp->next){
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
        while(first != tmp){
            if(tmp->data == x){
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

    CircLinkNode<T> *Locate(int i) { //实际结点下标从1开始
        int size = 0;
        CircLinkNode<T> *tmp = first;
        while(first != tmp->next){
            if(i == size){
                return tmp;
            }
            tmp = tmp->next;
            size++;
        }
        if(i == size) //末尾的结点循环内部没有考虑到
        {
            return tmp;
        }
        return nullptr;
    }

    T* getData(int i) {
        int size = 0;
        CircLinkNode<T> *tmp = first;
        while(first != tmp->next){
            if(i == size){
                return &(tmp->data);
            }
            tmp = tmp->next;
            size++;
        }
        if(i == size){ //同样末尾的结点上面循环没有考虑到
            return &(tmp->data);
        }
        cout << "i is so big!" << endl;
        return nullptr;
    }

    void setData(int i, T&x) {
        int size = 0;
        CircLinkNode<T> *tmp = first;
        while(first != tmp->next){
            if(i == size){
                tmp->data = x;
                return ;
            }
            tmp = tmp->next;
            size++;
        }
        if(i == size){ //同样末尾的结点循环没有考虑到
            tmp->data = x;
            return ;
        }
        cout << "i is so big!" << endl;
        return;
    }

    bool Insert(int i, T&x) { //实际结点下标从1开始
        if(i <= 0){
            cout << "i is so small!" << endl;
            return false;
        }
        int size = 1;
        CircLinkNode<T> *tmp = first;
        CircLinkNode<T> *newnode = new CircLinkNode<T>(x);
        while(first != tmp->next){
            if(i == size){
                newnode->next = tmp->next;
                tmp->next = newnode;
                return true;
            }
            tmp = tmp->next;
            size++;
        }
        if(i == size){ //同样最后一个结点循环没有考虑到
            newnode->next = tmp->next;
            tmp->next = newnode;
            return true;
        }
        cout << "i is too big!" << endl;
        return false;
    }

    bool Remove(int i, T&x) {
        if(i <= 0){
            cout << "i is so small!" << endl;
            return false;
        }
        if(IsEmpty()){
            cout << "list is empty!" << endl;
            return false;
        }
        int size = 1;
        CircLinkNode<T> *tmp = first;
        CircLinkNode<T> *delnode;
        while(first != tmp->next){
            if(i == size){
                delnode = tmp->next;
                x = delnode->data;
                tmp->next = delnode->next;
                delete delnode;
                return true;
            }
            tmp = tmp->next;
            size++;
        }
        //最后一个结点不用考虑，因为tmp就是最后一个结点，难道要删first吗？这个不像insert那样可能插入到tmp后面，因此不用考虑
        cout << "i is too big!" << endl;
        return false;
    }

};
#endif //DATA_STRUCT_CIRCLIST_H
