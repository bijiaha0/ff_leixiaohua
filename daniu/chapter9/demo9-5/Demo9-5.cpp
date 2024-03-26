// Demo9-5.cpp : 定义控制台应用程序的入口点。
//


#include <algorithm>
#include <iostream>
using namespace std;

// 输入一个不存在重复字符的字符串，打印出字符串中字符的全排列。
//比如：
//输入: "123"   3*2*1 = 3!
//输出:  123
//          132
//          213
//          231
//          321
//          312
//f(123) = 1+f(23), f(23) = 2+f(3), f(3)  = 3  递归
void swap(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}
void Permutation(char* pStr, char* pPostion)
{
    // 基准点
    if (*pPostion == '\0')
    {
        cout << pStr << endl;
    }
    else
    {
        for (char* pChar = pPostion; *pChar != '\0'; pChar++)
        {
            // 依次和后面的字符交换
            swap(*pChar, *pPostion);

            Permutation(pStr, pPostion + 1);

            // 换回来
            swap(*pChar, *pPostion);
        }
    }
}


int main()
{
    char test[] = "132";
    Permutation(test, test);
    cout << endl;

    // 用STL输出全排列
    // 注意：必须要保证数组顺序，
    do
    {
        cout << test[0] << test[1] << test[2] << endl;
    } while (next_permutation(test, test + 3));
    cout << endl;

    char test2[] = "321";
    // 注意：必须要保证数组顺序，
    do
    {
        cout << test2[0] << test2[1] << test2[2] << endl;
    } while (prev_permutation(test2, test2 + 3));

    return 0;
}

