//
// Created by Administrator on 2022/4/9.
//

#include <iostream>
#include "BinTree.h"

//测试根据前序遍历构建二叉树 如：ABC@@DE@G@@F@@@;
//构建成功输出中序遍历如下：C B E G D F A
using namespace std;
int main0(){
    BinTree<char> test;
    cin >> test;
    test.postOrder_new(); // 基于栈的非递归
    cout << endl;
    test.postOrder(); //基于递归
    cout << endl;
    test.levelOrder(); //层次遍历
    return 0;
}