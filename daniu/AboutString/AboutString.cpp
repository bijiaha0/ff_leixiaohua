#include <iostream>
#include <string>

using namespace std;

int main() {
    char c1 = 'yes'; // 截断：1.保留第一个字符； 2.保留最后一个字符；
    cout << c1 << endl;         // s
    char c2 = 'y'; //"y" ==> 'y', '\0'
    //char c2 = "yes"; // 字符串赋值给一个字符变量

    const char *slash = "/"; // ==> '/', '\0'
    //const char* slash2 = '/';
    const char *slash2 = &c1;
    cout << *slash2 << endl; // s

    string s1(1, 'yes');
    cout << s1 << endl;         // s
    string s2(3, 'yes');
    cout << s2 << endl;         // sss
    string s3(1, 'y');
    cout << s3 << endl;         // y
    string s4("/");
    cout << s4 << endl;         // /
    string s5(1, '/');
    cout << s5 << endl;         // /
    string s6("yes");
    cout << s6 << endl;         // yes

    return 0;
}