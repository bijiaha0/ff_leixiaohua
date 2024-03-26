// demo8-1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main()
{
    Singleton::getInstance()->DoSomething();

    Singleton::getInstance()->DoSomething();

    return 0;
}

