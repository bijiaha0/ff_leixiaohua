// stdafx.cpp : 只包括标准包含文件的源文件
// demo6-6.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

//而不是在此文件中引用
int test(int a)
{
    return a;
}
namespace quickzhao
{
    int test(int a)
    {
        return a+1;
    }
}
int test(double a)
{
    return int(a);
}
int test(int a, double b)
{
    return a + b;
}
