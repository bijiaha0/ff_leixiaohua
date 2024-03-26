#include <iostream>

using namespace std;

int main() {
    // T*:  注意*在定义和间接访问上的作用
    //int i = 4;  int* iP = &i;   cout << (*iP) << endl;
    //double d = 3.14; double* dP = &d; cout << (*dP) << endl;
    //char c = 'a';  char* cP = &c; cout << (*cP) << endl;

    // array of pointers和a pointer to an array
    int c[4] = {static_cast<int>(0x80000000), static_cast<int>(0xFFFFFFFF), 0x00000000, 0x7FFFFFFF};
    int *a[4];                          // array of pointers       指针的数组
    int(*b)[4];                         // a pointer to an array 数组的指针
    b = &c;                            // 注意：这里数组个数得匹配

    // 将数组c中元素赋给数组a
    for (unsigned int i = 0; i < 4; i++) {
        a[i] = &(c[i]);
    }

    // 输出看下结果
    cout << *(a[0]) << endl;   // -2147483648
    cout << (*b)[3] << endl;   // 2147483647
    return 0;
}
