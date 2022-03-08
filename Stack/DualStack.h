//
// Created by Administrator on 2022/3/7.
//

#ifndef DATA_STRUCT_DUALSTACK_H
#define DATA_STRUCT_DUALSTACK_H
#include <iostream>
using namespace std;

template<class T>
class DualStack{
private:
    T *data;
    int top[2]; //两个栈的栈顶下标，top[0]表示从低到高生长的那个栈
    int maxSize; //数组的大小
public:
    DualStack(int size = 100) {
        data = new T[size];
        maxSize = size;
        top[0] = -1;
        top[1] = maxSize; //初始时栈为空，栈顶均在数组下标外
    }

    ~DualStack() {
        delete [] data;
        top[0] = top[1] = 0;
        maxSize = 0;
    }

    //i = 0表示使用从低到高生长
    bool push(const T& x, int i) {
        if(IsFull()){
            cout << "stack is full!" << endl;
            return false;
        }
        if(i == 0){
            ++top[0];
            data[top[0]] = x;
        }else{
            --top[1];
            data[top[1]] = x;
        }
        return true;
    }

    bool pop(T &x, int i) {
        if(IsEmpty(i)){
            cout << "stack " << i << " is empty!" << endl;
            return false;
        }
        if(i == 0){
            x = data[top[0]];
            top[0]--;
        }else{
            x = data[top[1]];
            top[1]++;
        }
        return true;
    }

    bool getTop(T &x, int i) {
        if(IsEmpty(i)){
            cout << "stack " << i << " is empty!" << endl;
            return false;
        }
        x = data[top[i]];
        return true;
    }

    void makeEmpty(int i) {
        top[0] = -1;
        top[1] = maxSize;
    }

    bool IsEmpty(int i) {
        if(i == 0){
            return top[0] == -1;
        }else{
            return top[1] == maxSize;
        }
    }

    bool IsFull() {
        return top[0] + 1 == top[1];
    }

};
#endif //DATA_STRUCT_DUALSTACK_H
