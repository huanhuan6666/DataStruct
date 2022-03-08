//
// Created by Administrator on 2022/3/7.
//

#ifndef DATA_STRUCT_LINKEDSTACK_H
#define DATA_STRUCT_LINKEDSTACK_H
#include <iostream>

using namespace std;
template<class T>
struct StackNode{
    T data;
    StackNode<T> *next;
    explicit StackNode(StackNode<T> *ptr = nullptr): next(ptr) {}
    explicit StackNode(const T &x, StackNode<T> *ptr = nullptr) :data(x), next(ptr) {}
};

template<class T>
class LinkedStack{
    friend ostream &operator<<(ostream &out, const LinkedStack<T> &l){
        int index = 0;
        StackNode<T>* cur = l.top;
        while(cur){
            cout << "the " << index << " element is " << cur->data << endl;
            cur = cur->next;
        }
    }
private:
    StackNode<T> *top; //栈顶指针
public:
    explicit LinkedStack(StackNode<T> *ptr = nullptr) : top(ptr) {}
    ~LinkedStack() {
        makeEmpty();
    }

    //最简单的头插法
    void push(const T &x) {
        auto newnode = new StackNode<T>(x);
        newnode->next = top;
        top = newnode;
    }

    //最简单的删除头结点
    bool pop(T &x) {
        if(IsEmpty()){
            cout << "Stack is empty!" << endl;
            return false;
        }
        x = top->data;
        auto del = top;
        top = top->next;
        delete del;
        return true;
    }

    bool getTop(T &x) {
        if(IsEmpty()){
            cout << "Stack is empty!" << endl;
            return false;
        }
        x = top->data;
        return true;
    }

    bool IsEmpty() const {
        return top == nullptr;
    }

    //清空栈的内容
    void makeEmpty() {
        StackNode<T> *p;
        while(top){
            p = top;
            top = top->next;
            delete p;
        }
    }

};
#endif //DATA_STRUCT_LINKEDSTACK_H
