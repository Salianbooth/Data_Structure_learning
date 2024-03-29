//
// Created by 陈中超 on 2024/3/28.
//
#include <stdio.h>
#include <stdlib.h>


// 生成一个指定大小和范围的非递减有序数组
void sortedArray(int *arr, int size, int min_val, int max_val) {
    for (int i = 0; i < size; i++) {
        arr[i] = min_val + rand() % (max_val - min_val + 1); // 生成随机数
    }
    // 对数组进行排序，使其成为非递减有序
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 归并两个非递减有序数组
void mergeArrays(int *arr1, int size1, int *arr2, int size2, int *mergedArr) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            mergedArr[k++] = arr1[i++];
        } else {
            mergedArr[k++] = arr2[j++];
        }
    }
    while (i < size1) {
        mergedArr[k++] = arr1[i++];
    }
    while (j < size2) {
        mergedArr[k++] = arr2[j++];
    }
}

int main() {
    //la,lb 的大小
    const int size_a = 5;
    const int size_b = 8;
    const int min_val = 1;
    const int max_val = 100;

    // 为两个数组和归并后的数组分配内存
    int *la = (int *)malloc(size_a * sizeof(int));
    int *lb = (int *)malloc(size_b * sizeof(int));
    int *lc = (int *)malloc((size_a + size_b) * sizeof(int));

    // 生成两个非递减有序数组
    sortedArray(la, size_a, min_val, max_val);
    sortedArray(lb, size_b, min_val, max_val);

    // 打印原始数组
    printf("Array la: ");
    for (int i = 0; i < size_a; i++) {
        printf("%d ", la[i]);
    }
    printf("\n");

    printf("Array lb: ");
    for (int i = 0; i < size_b; i++) {
        printf("%d ", lb[i]);
    }
    printf("\n");

    // 归并两个数组
    mergeArrays(la, size_a, lb, size_b, lc);

    // 打印归并后的数组
    printf("Merged array lc: ");
    for (int i = 0; i < size_a + size_b; i++) {
        printf("%d ", lc[i]);
    }
    printf("\n");

    // 释放内存
    free(la);
    free(lb);
    free(lc);

    return 0;
}