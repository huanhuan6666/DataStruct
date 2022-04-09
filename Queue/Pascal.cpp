//
// Created by Administrator on 2022/3/11.
//
#include "LinkedQueue.h"
#include <iostream>

using namespace std;

int main1(){
    int first = 0, second = 0;
    LinkedQueue<int> mq;
    mq.push(0);
    mq.push(1);
    mq.push(1);
    int i = 10;
    while(!mq.IsEmpty() && i>0){
        mq.pop(first);
        mq.getFront(second);

        if(first == 0){ //弹出一个输出一个 0不输出
            cout << endl;
            mq.push(0);
            i--;
        }
        else
            cout << first << ' ';
        mq.push(first + second);
    }
    return 0;
}