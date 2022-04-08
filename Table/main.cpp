//
// Created by Administrator on 2022/4/8.
//

#include <iostream>
#include "GenList.h"

using namespace std;

//测试程序创建和输出广义表 输入格式为A(a,B(b,C(c,d),D(#),e),E(f)); 注意分号结尾 #表示空表
//输出广义表形如: (头a,(头b,(头c,d,),(头),e,),(头f,),)
int main(){
    GenList<char> ls;
    cin >> ls;
    cout << ls;
}