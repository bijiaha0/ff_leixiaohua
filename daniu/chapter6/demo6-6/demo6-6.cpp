#include "stdafx.h"

//指针函数

int main() {
    int (*p)(int);
    p = test;

    int result = (*p)(1);

    result = quickzhao::test(1);

    result = test(2.0);
    result = test(1, 2.0);
    return 0;
}

