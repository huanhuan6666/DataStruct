//
// Created by Administrator on 2022/3/9.
//

#ifndef DATA_STRUCT_LINKEDQUEUE_H
#define DATA_STRUCT_LINKEDQUEUE_H
#include <iostream>

using namespace std;

template<class T>
struct QueueNode{
    T data;
    QueueNode<T> *next;
    QueueNode(const T& x, QueueNode<T> *ptr = nullptr): next(ptr), data(x) { ; }
};

template<class T>
class LinkedQueue{
private:
    QueueNode<T> *head; //头尾指针都有方便push pop
    QueueNode<T> *tail;
public:
    LinkedQueue(QueueNode<T> *ptr = nullptr) : head(ptr), tail(ptr){
        //初始化队列为空
    }

    ~LinkedQueue() {
        makeEmpty();
        head = tail = nullptr;
    }

    bool push(const T&x) {
        auto newnode = new QueueNode<T>(x);
        tail->next = newnode;
        tail = newnode;
        return true;
    }

    bool pop(T &x) {
        if(IsEmpty()){
            cout << "queue is empty!" << endl;
            return false;
        }
        x = head->data;
        auto del = head;
        head = head->next;
        delete del;
        return true;
    }

    bool getFront(T &x) const {
        if(IsEmpty()){
            cout << "queue is empty!" << endl;
            return false;
        }
        x = head->data;
        return true;
    }

    void makeEmpty() {
        while(head){
            auto del = head;
            head = head->next;
            delete del;
        }
    }

    bool IsEmpty() const {
        return head == nullptr;
    }
};
#endif //DATA_STRUCT_LINKEDQUEUE_H
