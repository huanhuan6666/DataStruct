//
// Created by Administrator on 2022/3/6.
//

#ifndef DATA_STRUCT_SEQLIST_H
#define DATA_STRUCT_SEQLIST_H

#include "LinearList.h"
#include <iostream>
using namespace std;

//顺序表继承线性表接口
template<class T>
class SeqList : public LinearList<T> {
public:
    T *data; //存放数组
    int maxSize; //容量
    int last; //已存表项的最后下标
public:
    explicit SeqList(int size = 100); //默认构造函数
    SeqList(SeqList<T> &L); //拷贝构造函数
    ~SeqList(); //析构函数
    SeqList<T> &operator=(const SeqList<T>& L); //重载等号操作符

    int Size() const;
    int Length() const; //求大小
    int Search(const T &x) const; //搜索给定值
    int Locate(int i) const; //定位第i个元素的下标
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
SeqList<T>::SeqList(int size) {
    maxSize = size;
    last = -1; //初始化为空
    data = new T[size];
    if(data == nullptr){
        cout << "Error: new T failed!" << endl;
        exit(1);
    }
}

template<class T>
SeqList<T>::SeqList(SeqList<T> &L) {
    maxSize = L.maxSize;
    data = new T[maxSize];
    if(data == nullptr){
        cout << "Error: new T failed!" << endl;
        exit(1);
    }
    last = L.last;
    for(int i = 0; i<=L.last;i++){
        data[i] = L.data[i];
    }
}

template<class T>
SeqList<T>::~SeqList() {
    if (data != nullptr) {
        delete[] data;
    }
    data = NULL;
}

template<class T>
int SeqList<T>::Size() const {
    return maxSize;
}

template<class T>
int SeqList<T>::Length() const {
    return last + 1;
}

template<class T>
int SeqList<T>::Search(const T &x) const {
    int i = 0;
    for (i = 0; i <= last; i++) {
        if (data[i] == x) {
            return i;
        }
    }
    if (i == last + 1) {
        cout << "Error: can't find!" << endl;
    }
    return -1;
}

template<class T>
int SeqList<T>::Locate(int i) const {
    if (i >= 1 && i <= last + 1) {
        return i - 1;
    } else {
        cout << "Error: out of index!" << endl;
        return -1;
    }
}

template<class T>
bool SeqList<T>::getData(int i, T &x) const {
    if (i >= 1 && i <= last + 1) {
        x = data[i - 1];
        return true;
    }
    return false;
}

template<class T>
void SeqList<T>::setData(int i,const T &x) {
    if (i >= 1 && i <= last + 1) {
        data[i - 1] = x;
        return;
    }
}

template<class T>
bool SeqList<T>::Insert(int i, const T &x) {
    if (last + 1 >= maxSize) {
        cout << "list is full!" << endl;
        return false;
    }
    if(i >= 1 && i <= last + 1) {
        int j = last + 1;
        for (; j >= i + 1; j--) {
            data[j] = data[j - 1];
        }
        data[i] = x;
        last += 1;
        return true;
    }
    cout << "index out of list!" << endl;
    return false;
}

template<class T>
bool SeqList<T>::Remove(int i, T &x) {
    if(last == -1){
        cout << "list is empty!" << endl;
        return false;
    }
    if (i >= 1 && i <= last + 1) {
        int j = i;
        for (; j <= last - 1; j++) {
            data[j] = data[j + 1];
        }
        last -= 1;
        return true;
    }
    cout << "index out of list!" << endl;
    return false;
}

template<class T>
bool SeqList<T>::IsEmpty() {
    return last == -1;
}

template<class T>
bool SeqList<T>::IsFull() {
    return last + 1 == maxSize;
}

template<class T>
void SeqList<T>::Sort() {
    for (int i = 0; i <= last - 1; i++)
        for (int j = i + 1; j <= last; j++) {
            if (data[i] > data[j]) {
                T tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }
        }
}

template<class T>
void SeqList<T>::Input() {
    int size = 0;
    while(true) {
        cout << "please input size: ";
        cin >> size;
        if (size <= maxSize)
            break;
        else{
            cout << "size can't over " << maxSize << "!" << endl;
            continue;
        }
    }
    int i = 0;
    for(; i<size; i++){
        cout << "please input the " << i << " element:";
        cin>>data[i];
    }
    maxSize = size;
    last = size - 1;
}

template<class T>
void SeqList<T>::Output() {
    cout << "the list is:" << endl;
    for(int i = 0; i<=last ;i++){
        cout << data[i] << " ";
    }
}

template<class T>
SeqList<T>& SeqList<T>::operator=(const SeqList<T> &L) {
    if(data != nullptr){
        delete []data;
    }
    maxSize = L.maxSize;
    last = L.last;
    data = new T[maxSize];
    for(int i = 0; i<=last;i++){
        data[i] = L.data[i];
    }
    return *this;
}


#endif //DATA_STRUCT_SEQLIST_H
