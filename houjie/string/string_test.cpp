#include "string.h"
#include <iostream>

using namespace std;
//作为一个经验还不是非常多的人。
int main() {
    String s1("hello");
    String s2("world");

    //拷贝构造
    String s3(s2);
    cout << s3 << endl;

    //拷贝赋值
    s3 = s1;
    cout << s3 << endl;
    cout << s2 << endl;
    cout << s1 << endl;
}
