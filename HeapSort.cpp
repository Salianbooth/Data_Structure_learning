//
// Created by 陈中超 on 2024/4/9.
//
#include <iostream>

void HeapAdjust(int* arr, int start, int end)
{
    int tmp = arr[start];
    for (int i = 2 * start + 1; i <= end; i = i * 2 + 1)
    {
        if (i < end&& arr[i] < arr[i + 1])//有右孩子并且左孩子小于右孩子
        {
            i++;
        }//i一定是左右孩子的最大值
        if (arr[i] > tmp)
        {
            arr[start] = arr[i];
            start = i;
        }
        else
        {
            break;
        }
    }
    arr[start] = tmp;
}
void HeapSort(int* arr, int len)
{
    //第一次建立大根堆，从后往前依次调整
    for(int i=(len-1-1)/2;i>=0;i--)
    {
        HeapAdjust(arr, i, len - 1);
    }
    //每次将根和待排序的最后一次交换，然后在调整
    int tmp;
    for (int i = 0; i < len - 1; i++)
    {
        tmp = arr[0];
        arr[0] = arr[len - 1-i];
        arr[len - 1 - i] = tmp;
        HeapAdjust(arr, 0, len - 1-i- 1);
    }
}
int main()
{
    int arr[] = { 9,5,6,3,5,3,1,0,96,66 };
    HeapSort(arr, sizeof(arr) / sizeof(arr[0]));
    printf("排序后为:");
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}