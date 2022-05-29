//
// Created by Administrator on 2022/5/29.
//

#ifndef DATA_STRUCT_EXCHANGESORT_H
#define DATA_STRUCT_EXCHANGESORT_H

// 冒泡排序
void BubbleSort(int *nums, int n) {
    for (int i = 0; i < n - 1; i++) { //第i轮起泡
        int flag = false;
        for (int j = 1; j < n - i; j++) {
            if (nums[j] < nums[j - 1]) { // 发现逆序对
                flag = true;
                int tmp = nums[j];
                nums[j] = nums[j - 1];
                nums[j - 1] = tmp;
            }
        }
        if (!flag) // 没有发现逆序对则排序完成
            return;
    }
}

// 快速排序

void QuickSort(int *nums, int left, int right) {
    if (left >= right) // 区间只有一个元素或者为空
        return;
    int pivot = nums[left], low = left, high = right;
    while (low < high) {
        while (low < high && nums[high] >= pivot) high--;
        nums[low] = nums[high];
        while (low < high && nums[low] <= pivot) low++;
        nums[high] = nums[low];
    }
    nums[low] = pivot;
    QuickSort(nums, left, low - 1);
    QuickSort(nums, low + 1, right);
}

#endif //DATA_STRUCT_EXCHANGESORT_H
