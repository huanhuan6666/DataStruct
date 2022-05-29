//
// Created by Administrator on 2022/5/29.
//

#include "ExchangeSort.h"
#include "SelectSort.h"
#include "MergeSort.h"
#include <iostream>

using namespace std;

int main() {
    int nums[] = {49, 27, 38, 65, 97, 76, 27, 49};
//     QuickSort(nums, 0, 7);
//     SelectSort(nums, 8);
//    HeapSort(nums, 8);
    int *help = new int[8];
    MergeSort(nums, help, 0, 7);
    for(int i = 0; i < 8; i++)
        cout << nums[i] << " ";
}

