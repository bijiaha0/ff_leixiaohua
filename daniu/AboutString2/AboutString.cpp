#include <iostream>
#include <string>

using namespace std;

static const int MAX_LEN = 30;

int main() {
    char str1[] = "string";
    cout << strlen(str1) << endl;
    cout << sizeof(str1) / sizeof(str1[0]) << endl;

    char str2[] = "stri\0ng";
    cout << strlen(str2) << endl;
    cout << sizeof(str2) / sizeof(str2[0]) << endl;

    char str1A[MAX_LEN] = "stringA";
    strcat(str1A, str2);
    cout << str1A << endl;
    cout << strlen(str1A) << endl;
    cout << sizeof(str1A) / sizeof(str1A[0]) << endl;

    cout << endl;
    cout << "Testing C++ String: " << endl;
    string sstr1 = "string";
    cout << sstr1.length() << endl;
    cout << sstr1.capacity() << endl;
    cout << sizeof(sstr1) << endl;

    cout << "sstr2: " << endl;
    string sstr2 = "stri\0ng";
    cout << sstr2.length() << endl;
    cout << sstr2.capacity() << endl;
    cout << sizeof(sstr2) << endl;

    cout << "sstr1: " << endl;
    sstr1 += sstr2;
    cout << sstr1.length() << endl;
    cout << sstr1.capacity() << endl;
    cout << sizeof(sstr1) << endl;
}