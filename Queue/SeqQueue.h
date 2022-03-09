//
// Created by Administrator on 2022/3/9.
//

#ifndef DATA_STRUCT_SEQQUEUE_H
#define DATA_STRUCT_SEQQUEUE_H

#include <iostream>

using namespace std;

template<class T>
class SeqQueue {
private:
    T *data;
    int head;
    int tail;
    int maxSize;
public:
    //构造函数
    SeqQueue(int size = 10) {
        maxSize = size;
        data = new T[size];
        head = tail = 0; //初始化队列为空
    }

    ~SeqQueue() {
        delete[] data;
    }

    bool push(const T &x) {
        if (IsFull()) {
            cout << "queue is full!" << endl;
            return false;
        }
        data[tail] = x;
        tail = (tail + 1) % maxSize;
        return true;
    }

    bool pop(T &x) {
        if (IsEmpty()) {
            cout << "queue is empty!" << endl;
            return false;
        }
        x = data[head];
        head = (head + 1) % maxSize;
        return true;
    }

    bool getFront(T &x) {
        if (IsEmpty()) {
            cout << "queue is empty!" << endl;
            return false;
        }
        x = data[head];
        return true;
    }

    void makeEmpty() {
        head = tail = 0;
    }

    bool IsEmpty() const {
        return head == tail;
    }

    bool IsFull() const {
        return tail + 1 == head;
    }

    int getSize() const {
        return tail - head;
    }

};

#endif //DATA_STRUCT_SEQQUEUE_H
