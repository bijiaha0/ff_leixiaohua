#include <iostream>

using namespace std;

class C1 {
    int i;    //4 Byte
    char c1;  //1 Byte
    char c2;  //1 Byte
};

class C2 {
    char c1;  //4
    int i;    //4
    char c2;  //4
};//12 Byte

class C3 {
    int i1;
    char c1;
    int i2;
    char c2;
    int i3;
    char c3;
    int i4;
    char c4;

};//32 Byte

class C4 {
    int i1; //4 Byte
    int i2;
    int i3;
    int i4;

    char c1;
    char c2;
    char c3;
    char c4;
};//20

int main() {
    cout << sizeof(C1) << endl;// 输出8
    cout << sizeof(C2) << endl;// 输出12
    cout << sizeof(C3) << endl;// 输出32
    cout << sizeof(C4) << endl;// 输出20
}



