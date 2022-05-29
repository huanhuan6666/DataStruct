//
// Created by Administrator on 2022/5/28.
//

#ifndef DATA_STRUCT_INSERTSORT_H
#define DATA_STRUCT_INSERTSORT_H
/*
 * 插入排序的三种算法：直接插入排序、折半插入排序、希尔排序（缩小增量排序）
 */

// 直接插入排序
void InsertSort(int *a, int n) {
    for (int i = 1; i < n; i++) { // 插入元素a[i]到已排序的a[0~i-1]中
        int each = a[i], j;
        for (j = i - 1; j >= 0; j--) {
            if (a[j] > each) { // 比a[i]大的向后移动
                a[j + 1] = a[j];
            } else { // a[j]<=a[i] 找到了插入位置
                a[j + 1] = each;
                break;
            }
        }
        if (j < 0) // 最后j<0说明应该插到a[0]位置
            a[0] = each;
    }
}

// 折半插入排序
void BinaryInsertSort(int *a, int n) {
    for (int i = 1; i < n; i++) { // 插入a[i]元素到已排序的a[0~i-1]中
        int left = 0, right = i, each = a[i];
        while (left < right) { // 为了保证稳定性 在a[0~i-1]中寻找a[i]的右边界
            int mid = left + (right - left) / 2;
            if (a[mid] <= each) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        for (int k = i; k >= right + 1; k--) // 空出right的位置
            a[k] = a[k - 1];
        a[right] = each; // right为第一个比a[i]大的元素下标 之前的都比a[i]小 因此插到right这里
    }
}

// 希尔排序(缩小增量排序)
void ShellSort(int *nums, int n) {
    for (int gap = n / 2; gap >= 1; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int tmp = nums[i], j; //a[i]每一子表中直接插入的元素
            for (j = i - gap; j >= 0; j -= gap) {
                if (tmp < nums[j]) { //在该子表中后移
                    nums[j + gap] = nums[j];
                } else { //a[i]在该子表中找到了插入位置
                    nums[j + gap] = tmp;
                    break;
                }
            }
            if (j < 0) nums[i % gap] = tmp; //j<0说明应该插到该子表的0号位置
        }
    }
}

#endif //DATA_STRUCT_INSERTSORT_H
