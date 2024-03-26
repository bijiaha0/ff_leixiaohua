#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <array>
#include <bitset>

using namespace std;

class BitPoint {
public:
    int x: 4;//4bit
    int y: 4;//4bit
    int z: 4;//4bit
    int a: 4;//4bit
    int b: 4;//4bit
    int c: 4;//4bit
    int d: 4;//4bit

    bool t: 1;//1bit
    bool u: 1;//1bit
    bool v: 1;//1bit
    bool w: 1;//1bit
    bool s: 1;//1bit
};


class Point {
public:
    int x; //4Byte
    int y; //4Byte
    int z; //4Byte

    bool t; //1Byte
    bool u; //1Byte
    bool v; //1Byte
    bool w; //1Byte
};


int main() {
    cout<<sizeof(Point)<<endl;
    cout<<sizeof(BitPoint)<<endl;

    BitPoint bp;

    int *p = (int *) alloca(4 * 1024 * 1024);
}

