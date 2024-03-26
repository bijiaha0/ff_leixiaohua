#include "stdafx.h"

int main()
{
    //Complex a(1.0, 2.0);
    //cout << a.GetReal() << endl;     // 1.0
    //cout << a.GetImage() << endl;  // 2.0

    //a.SetImage(2.0);
    //a.SetReal(3.0);
    //cout << a.GetReal() << endl;     // 3.0
    //cout << a.GetImage() << endl;  // 2.0

    Complex a(3.0, 2.0);
    Complex b(2.0, 3.0);
    //Complex c(a + b);
    Complex c;
    c = a+b;
    //会调用拷贝构造
    //Complex d(c);

    //Complex e;
    //e = d++;
    //cout << e << endl;
    //cout << d << endl;
    //e = ++d;
    //cout << e << endl;
    //cout << d << endl;
    //cout << (e == d) << endl;  // 1
    //cout << (e == a) << endl;  // 0
    //cout << (e != d) << endl;   // 0
    //cout << (e != a) << endl;   // 1
    //
    //cin >> e;
    //cout << e << endl;
    //e += a;
    //cout << e << endl;

    // 测试各个运算符重载
    //Complex a(2, 3);
    //Complex b(3, 4);
    //Complex c1 = a + b;
    //cout << c1 << endl;
    //Complex c2 = a - b;
    //cout << c2 << endl;
    //Complex c3 = a * b;
    //cout << c3 << endl;
    //Complex c4 = a / b;
    //cout << c4 << endl;
    //cout << endl;
    //
    //cout << (a == b) << endl;
    //cout << (a != b) << endl;
    //cout << (a > b) << endl;
    //cout << (a >= b) << endl;
    //cout << (a < b) << endl;
    //cout << (a <= b) << endl;
    //cout << endl;
    //
    //c1 = a;
    //cout << c1 << endl;
    //c2 = a++;
    //cout << c2 << endl;
    //cout << a << endl;
    //c3 = ++a;
    //cout << c3 << endl;
    //cout << a << endl;
    //cout << endl;
    //
    //c2 = b;
    //cout << c2 << endl;
    //c3 = b--;
    //cout << c3 << endl;
    //cout << b << endl;
    //c3 = --b;
    //cout << c3 << endl;
    //cout << b << endl;

    return 0;
}

