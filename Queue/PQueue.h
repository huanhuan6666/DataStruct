//
// Created by Administrator on 2022/3/21.
//

#ifndef DATA_STRUCT_PQUEUE_H
#define DATA_STRUCT_PQUEUE_H

#include <iostream>

using namespace std;

template<class T>
class PQueue {
private:
    T *data; //存放元素
    int count; //当前元素个数
    int maxPQsize; //容量
    //调整
    void adjust() {
        T temp = data[count - 1]; //最后一个元素要调整位置
        int i = 0;
        for (i = count - 2; i >= 0; i--) {
            if (data[i] > temp) //比我大的后挪位置
                data[i + 1] = data[i];
            else { //<=我的插到其后面就结束
                data[i + 1] = temp;
                break;
            }
        }
    }

public:
    PQueue(int size = 50) {
        maxPQsize = size;
        data = new T[size];
        count = 0; //初始化队列为空
    }

    ~PQueue() {
        delete[]data;
    }

    bool Insert(T &x) {
        if (isFull()) {
            cout << "queue is full!" << endl;
            return false;
        }
        data[count] = x; //count指向一个待填的位置
        count++;
        adjust(); //调整优先级顺序
    }

    bool RemoveMin(T &x) {
        if (IsEmpty()) {
            cout << "queue is empty!" << endl;
            return false;
        }
        x = data[0];
        for (int i = 0; i < count - 1; i++)
            data[i] = data[i + 1];
        count--;
        return true;
    }

    bool GetFront(T &x) {
        if(IsEmpty()){
            cout << "queue is empty!" << endl;
            return false;
        }
        x = data[0];
        return true;
    }

    void MakeEmpty() {
        count = 0;
    }

    bool IsEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == maxPQsize;
    }

    bool Length() const {
        return count;
    }
};


#endif //DATA_STRUCT_PQUEUE_H
