//
// Created by Administrator on 2022/5/29.
//

#ifndef DATA_STRUCT_MERGESORT_H
#define DATA_STRUCT_MERGESORT_H

// [left, mid]和[mid+1, right]是相邻的有序子数组
// 需要借助help数组改变nums数组使其有序
void Merge(int *nums, int* help, int left, int mid, int right) {
    for(int i = left; i <= right; i++)
        help[i] = nums[i];
    int p1 = left, p2 = mid + 1, index = left;
    while(p1 <= mid && p2 <= right) { // 有一个子数组结束即可
        if(help[p1] <= help[p2]) { // 为了保证稳定 <=使得左侧的元素优先在左侧
            nums[index++] = help[p1++];
        }
        else {
            nums[index++] = help[p2++];
        }
    }
    while(p1 <= mid) nums[index++] = help[p1++];
    while(p2 <= right) nums[index++] = help[p2++];
}

// 归并排序 功能为将[left, right]区间内数组排序
void MergeSort(int *nums, int *help, int left, int right) {
    if(left >= right) // 数组只有一个元素则结束
        return;
    int mid = left + (right - left)/2;
    MergeSort(nums, help, left, mid);
    MergeSort(nums, help, mid+1, right);
    Merge(nums, help, left, mid, right);
}
#endif //DATA_STRUCT_MERGESORT_H
