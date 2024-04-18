//
// Created by 陈中超 on 2024/4/5.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printVector(vector<int>& v) {

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

void Count_sort(vector<int> &arr)
{
    printVector(arr);
    int mn = *min_element(arr.begin(),arr.end());
    int mx = *max_element(arr.begin(),arr.end());

    int range = mx - mn + 1;
    vector<int> countArr(range , 0);
    for (int num : arr) {
        countArr[num - mn]++;
    }
    printVector(countArr);

    vector<int> output;
    for(int i = 0;i < countArr.size();i++)
    {
        if(countArr[i] == 0)
        {
            continue;
        }
        for(int j =countArr[i];j > 0;j--)
        {
            output.push_back(i+mn);
            countArr[i] --;
        }
    }
    /*
    for (int i = 1; i < range; ++i) {
        countArr[i] += countArr[i - 1];
    }*/

/*    for (int i = arr.size() - 1; i >= 0; --i) {
        output[countArr[arr[i] - mn] - 1] = arr[i];
        countArr[arr[i] - mn]--;
    }
    */
    printVector(output);

}


int main()
{
    vector<int> testArray = {4, 2, 2, 8, 3, 3};
    Count_sort(testArray);

    return 0;
}