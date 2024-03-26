#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include<iostream>
using namespace std;

int main()
{
    // transform和lambda表达式
    int ones[] = { 1, 2, 3, 4, 5 };
    int twos[] = { 10, 20, 30, 40, 50 };
    int results[5];
    transform(ones, ones + 5, twos, results, std::plus<int>()); // 数组元素依次相加并返回
    for_each(results, results + 5,
             [ ](int a)->void {
                 cout << a << endl; } ); // lambda表达式（匿名函数）
    cout << endl;

    // find
    int arr[] = { 0, 1, 22, 3, 3, 4, 4, 5, 6, 6, 7, 7, 7, 8 };
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> iA(arr + 2, arr + 6);   // {2,3,3,4}
    //vector<int> iA;
    //iA.push_back(1);
    //iA.push_back(9); // {1, 9}
    cout << count(arr, arr + len, 6) << endl; // 统计6的个数
    cout << count_if(arr, arr + len, bind2nd(less<int>(),  7) ) << endl; // 统计<7的个数
    cout << binary_search(arr, arr + len, 9) << endl;   // 9找不到
    cout << *search(arr, arr + len, iA.begin(), iA.end()) << endl; // 查找子序列

    cout << endl;

    return 0;
}

