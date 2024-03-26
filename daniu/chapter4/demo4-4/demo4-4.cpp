#include <string.h>                    //使用C库的头文件
#include <iostream>
using  namespace std;
const unsigned int MAX_LEN_NUM = 16;
const unsigned int STR_LEN_NUM = 7;
const unsigned int NUM_TO_COPY = 2;
int main()
{
    char strHelloWorld1[ ] = { "hello" };
    char strHelloWorld2[STR_LEN_NUM] = { "world1" };
    char strHelloWorld3[MAX_LEN_NUM] = {0};
    strcpy(strHelloWorld3, strHelloWorld1);                                    // hello
    //strcpy_s(strHelloWorld3, MAX_LEN_NUM, strHelloWorld1);
    strncpy(strHelloWorld3, strHelloWorld2, NUM_TO_COPY);      // wollo
    //strncpy_s(strHelloWorld3, MAX_LEN_NUM,  strHelloWorld2, NUM_TO_COPY);
    strcat(strHelloWorld3, strHelloWorld2);                                    //  wolloworld1
    //strcat_s(strHelloWorld3, MAX_LEN_NUM, strHelloWorld2);
    unsigned int len = strlen(strHelloWorld3);
    //unsigned int len = strnlen_s(strHelloWorld3, MAX_LEN_NUM);
    for (unsigned int index = 0; index < len; ++index)
    {
        cout << strHelloWorld3[index] << " ";
    }
    cout << endl;

    // 小心缓冲区溢出
    strcat(strHelloWorld2, "Welcome to C++");
    //strcat_s(strHelloWorld2, STR_LEN_NUM, "Welcome to C++");

    return 0;
}

