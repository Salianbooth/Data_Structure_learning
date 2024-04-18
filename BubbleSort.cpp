//
// Created by 陈中超 on 2024/4/9.
//
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
void BubbleSort(vector<int> &arr)
{
    int end = arr.size() ;
    while(end)
    {
        int flag = 0;
        for(int i = 1; i <  end ; i ++)
        {
            if(arr[i - 1 ] > arr[i])
            {
                int tem = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1 ] = tem;
                flag = 1;
            }
        }
        if(flag == 0) break;
    }
}
void SelectSort(vector<int> &arr) // 可以直接使用数组作为参数
{
    int begin = 0;
    int end = arr.size() - 1;
    while (begin < end)
    {
        int minIndex = begin;
        int maxIndex = begin;
        for (int i = begin + 1; i <= end; ++i) // 使用++i代替i++，虽然两者在这里没有区别
        {
            if (arr[i] < arr[minIndex])
            {
                minIndex = i;
            }

            if (arr[i] > arr[maxIndex])
            {
                maxIndex = i;
            }
        }

        swap(arr[begin], arr[minIndex]); // 使用引用调用Swap
        if (begin == maxIndex) // 修正maxIndex
        {
            maxIndex = minIndex;
        }
        swap(arr[end], arr[maxIndex]); // 使用引用调用Swap

        begin++;
        end--;
    }
}
void printVector(vector<int>& v) {

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}
int main()
{
    vector<int> arr = {1 ,8,5,3,99,33,62};
    //BubbleSort(arr);
    SelectSort(arr);
    printVector(arr);
    return 1;
}