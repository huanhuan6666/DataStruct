//
// Created by Administrator on 2022/4/9.
//

#include <iostream>
#include "BinTree.h"
#include "Heap.h"
#include "HuffmanTree.h"

using namespace std;

int main01() {
    //测试根据前序遍历构建二叉树 如：ABC@@DE@G@@F@@@;
    //构建成功输出中序遍历如下：C B E G D F A
    cout << "----------------BinTree test---------------" << endl;
    BinTree<char> test;
    cin >> test;
    test.postOrder_new(); // 基于栈的非递归
    cout << endl;
    test.postOrder(); //基于递归
    cout << endl;
    test.levelOrder(); //层次遍历
    return 0;
}

int main(){
    cout << "------------MinHeap test-------------" << endl;
    int i[] = {2, 4, 5, 6, 1};
    MinHeap<int> hp(i, 5);
    int p;
    hp.display(); //层次打印堆
    cout << endl;
    hp.Remove(p);
    hp.display();
    cout << endl;
    p = 0;
    hp.Insert(p);
    hp.display();
    cout << endl;
    cout << "-------------Huffman test-------------" << endl;
    float w[] = {0.12, 0.08, 0.15, 0.25, 0.40};
    HuffmanTree test(w, 5); //根据权值数组w构建霍夫曼树
    test.show(); //层次打印霍夫曼树
}