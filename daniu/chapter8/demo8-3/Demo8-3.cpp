// Demo8-3.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
using namespace std;

void func(void* i)
{
    cout << "func(void* i)" << endl;
}
void func(int i)
{
    cout << "func(int i)" << endl;
}

int main()
{
    int* pi = NULL;
    int* pi2 = nullptr;
    char* pc = NULL;
    char* pc2 = nullptr;
    func(NULL);                   // func(int i)
    func(nullptr);                 // func(void* i)
    func(pi);                         // func(void* i)
    func(pi2);                       // func(void* i)
    func(pc);                        // func(void* i)
    func(pc2);                      // func(void* i)



    return 0;
}

