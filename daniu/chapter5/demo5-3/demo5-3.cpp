#include <iostream>

using namespace std;
unsigned int MAX_LEN = 11;

int main() {
    char strHelloworld[] = {"helloworld"};
    char const *pStr1 = "helloworld";             // const char*
    char *const pStr2 = strHelloworld;
    char const *const pStr3 = "helloworld";  // const char* const
    pStr1 = strHelloworld;
    //pStr2 = strHelloworld;                            // pStr2不可改
    //pStr3 = strHelloworld;                            // pStr3不可改

    unsigned int len = strnlen(pStr2, MAX_LEN);
    cout << len << endl;

    for (unsigned int index = 0; index < len; ++index) {
        //pStr1[index] += 1;                               // pStr1里的值不可改
        pStr2[index] += 1;
        //pStr3[index] += 1;                               // pStr3里的值不可改
    }

    return 0;
}
