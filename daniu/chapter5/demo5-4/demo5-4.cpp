#include <iostream>

using namespace std;

int main() {

    // 指针的指针
    int a = 123;
    int *b = &a;
    int **c = &b;

    // NULL 的使用
    int *pA = NULL;
    pA = &a;
    if (pA != NULL)  //  判断NULL指针
    {
        cout << (*pA) << endl;
    }
    pA = NULL;       //  pA不用时，置为NULL

    return 0;
}

