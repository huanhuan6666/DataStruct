//
// Created by Administrator on 2022/4/10.
//

#ifndef DATA_STRUCT_HEAP_H
#define DATA_STRUCT_HEAP_H

#include <iostream>

const int defaultsize = 10;
using namespace std;

//最小堆
template<class T>
class MinHeap {
private:
    T *data; //动态分配数组内存
    int curSize; //当前堆中实际结点数
    int maxSize; //堆的最大容量

    void siftDown(int start, int m); //调整算法
    void siftUp(int start); //调整算法
public:
    MinHeap(int size = defaultsize) : maxSize(size), curSize(0) {
        data = new T[size]; //动态分配内存
    }

    MinHeap(T *a, int n); //将已存在的数组放入堆中 由于数组情况未知 需要调整成小顶堆

    ~MinHeap() {
        delete[] data;
    }

    //向堆中插入新数据
    bool Insert(T &x);

    //删除数据
    bool Remove(T &x);

    //判断是否为空
    bool IsEmpty() { return curSize == 0; }

    //判断是否为满
    bool IsFull() { return curSize == maxSize; }

    //置空堆 不用释放结点 只需标记未使用即可
    void MakeEmpty() { curSize = 0; }

    void display() {
        for(int i = 0; i < curSize; i++)
            cout << data[i] << ' ';
    }
};


//将已存在的数组放入堆中 由于数组情况未知 需要调整成小顶堆
template<class T>
MinHeap<T>::MinHeap(T *a, int n) {
    int size = max(defaultsize, n);
    data = new T[size];

    for (int i = 0; i < n; i++) { //先原封不动搬入堆中
        data[i] = a[i];
    }
    this->data = data;
    curSize = n;
    maxSize = size;
    //将毫无章法的数组调整成堆
    int cur = (n - 1 - 1) / 2; //最后一个结点的父结点
    while (cur >= 0) { //从下到上逐步调整 动归思想
        siftDown(cur, n - 1);
        cur--;
    }
}

//从数组的start开始 m为数组最大下标 用来判断算出来的子女结点下标是否实际存在
template<class T>
void MinHeap<T>::siftDown(int start, int m) {
    int i = start, j = 2 * i + 1; //i始终指向需要调整的那个结点的位置即the_data 左节点下标为j 右结点下标为j+1
    T the_data = data[start];
    while (j <= m) { //不断下滑
        if (j < m && data[j] > data[j + 1])  //保证右结点存在 j指向二者的小者
            j = j + 1;
        if (the_data <= data[j]) //当前结点比左右子结点都小 调整结束
            break;
        else { //需要下滑
            data[i] = data[j]; //当前结点和小者j结点交换
            data[j] = the_data;
            i = j; //更新i和j
            j = 2 * i + 1;
        }
    }
}

//向堆中插入新元素是插到数组末尾再调整数组 因此需要这个上滑调整函数
template<class T>
void MinHeap<T>::siftUp(int start) {
    T the_data = data[start];
    int i = start, j = (i - 1) / 2; //i指向本结点的当前位置 j指向此时的父结点
    while(i > 0){ //i为父结点时直接跳出
        if(the_data < data[j]){ //比父结点小 需要交换
            data[i] = data[j];
            data[j] = the_data;
            i = j; //更新本结点指针 和 此时父结点指针
            j = (i - 1) / 2;
        }
        else //不比父结点小 调整结束
            break;
    }
}

template<class T>
bool MinHeap<T>::Insert(T &x) {
    if(IsFull()) {
        cout << "堆已经满了！" << endl;
        return false;
    }
    data[curSize] = x;
    curSize++; //当前大小增大
    siftUp(curSize - 1); //参数为新结点的下标 就是数组的最后一个结点

    return true;
}

//删除堆顶 为了不破化堆序 取数组末尾放到堆顶位置 然后下滑调整
template<class T>
bool MinHeap<T>::Remove(T &x) {
    if(IsEmpty()){
        cout << "堆为空 ！" << endl;
        return false;
    }
    x = data[0]; //保存堆顶到x
    data[0] = data[curSize - 1]; //取末尾放到堆顶
    curSize--;
    siftDown(0, curSize - 1); //参数m为当前数组的最大下标
    return true;
}


#endif //DATA_STRUCT_HEAP_H
