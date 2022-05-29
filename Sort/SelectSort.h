//
// Created by Administrator on 2022/5/29.
//

#ifndef DATA_STRUCT_SELECTSORT_H
#define DATA_STRUCT_SELECTSORT_H

void SelectSort(int *nums, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) { //寻找i及之后最小的元素nums[min]
            if (nums[j] < nums[min])
                min = j;
        }
        if (i != min) {
            int tmp = nums[i]; // 交换到nums[i]处
            nums[i] = nums[min];
            nums[min] = tmp;
        }
    }
}

// 大顶堆的下滑操作 在区间[start, end] 将nums[start]下滑调整
void siftDown(int *nums, int start, int end) {
    int temp = nums[start];
    int i = start, j = 2 * i + 1; // j指向temp的左子结点
    while (j <= end) {
        if (j < end && nums[j + 1] > nums[j]) j += 1; // j指向两个子结点的大者
        if (nums[j] <= temp) // 两个子结点都比它小则调整成功
            break;
        else {
            nums[i] = nums[j];
            i = j; // 下滑
            j = 2 * i + 1;
        }
    }
    nums[i] = temp;
}

// n为元素个数 第一个父结点下标为(n-1-1)/2
void HeapSort(int *nums, int n) {
    for (int i = (n - 1 - 1) / 2; i >= 0; i--) { // 自底向上将整个数组调整成大顶堆
        siftDown(nums, i, n - 1);
    }

    for (int i = 1; i < n - 1; i++) {
        int tmp = nums[0]; // 将堆顶交换到末尾
        nums[0] = nums[n - i];
        nums[n - i] = tmp;

        siftDown(nums, 0, n - i - 1); // 在区间[0, n-i-1]上下滑调整
    }
}

#endif //DATA_STRUCT_SELECTSORT_H
