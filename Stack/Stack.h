//
// Created by Administrator on 2022/3/7.
//

#ifndef DATA_STRUCT_STACK_H
#define DATA_STRUCT_STACK_H

#include <iostream>

using namespace std;

template<class T>
class Stack {
private:
    int top; //栈顶元素下标
    T *data; //栈数组指针
    int maxSize;
    //栈的溢出处理
    void overflowProcess() { //开辟一个二倍大的数组然后复制过去
        T *newarray = new T[2 * maxSize];
        for(int i = 0; i <= top; i++){
            newarray[i] = data[i];
        }
        delete [] data;
        data = newarray;
        maxSize *= 2;
    }

public:
    explicit Stack(int size = 100) { //构造函数
        maxSize = size;
        data = new T[size];
        top = -1; //初始化为空
    }

    ~Stack() {
        delete[]data;
        data = nullptr;
    }

    bool push(const T &x) {
        if (IsFull()) { //栈满了就扩容2倍
            cout << "stack is full! so we make maxSize*2! " << endl;
            overflowProcess();
        }
        ++top;
        data[top] = x;
        return true;
    }

    bool pop(T &x) {//弹出栈顶
        if (IsEmpty()) {
            cout << "stack is empty!" << endl;
            return false;
        }
        x = data[top];
        top--;
        return true;
    }


    bool getTop(T &x) { //获取栈顶
        if (IsEmpty()) {
            cout << "stack is empty!" << endl;
            return false;
        }
        x = data[top];
        return true;
    }


    void MakeEmpty() { //置空栈
        delete[] data;
        top = -1;
        maxSize = 0;
    }


    bool IsEmpty() const {
        return top == -1;
    }

    bool IsFull() const {//是否满
        return top + 1 == maxSize;
    }

};

#endif //DATA_STRUCT_STACK_H
