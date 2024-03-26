// demo7-2.cpp : 定义控制台应用程序的入口点。
//
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

static const int bufferLen = 2048;

bool CopyFile(const string &src, const string &dst) {
    // 打开源文件和目标文件
    // 源文件以二进制读的方式打开
    // 目标文件以二进制写的方式打开
    ifstream in(src.c_str(), ios::in | ios::binary);
    ofstream out(dst.c_str(), ios::out | ios::binary | ios::trunc);

    // 判断文件打开是否成功，失败返回false
    if (!in || !out) {
        return false;
    }

    // 从源文件中读取数据，写到目标文件中
    // 通过读取源文件的EOF来判断读写是否结束
    char temp[bufferLen];
    while (!in.eof()) {
        in.read(temp, bufferLen);
        streamsize count = in.gcount();
        out.write(temp, count);
    }

    // 关闭源文件和目标文件
    in.close();
    out.close();

    return true;
}

int main() {
    cout << CopyFile("Blue Daube.mp3", "Blue Daube2.mp3") << endl;

    //int a;
    //int index = 0;
    //fstream fout;
    //fout.open("testBuffer.txt", ios::app);
    ////if (fout.fail())
    //if (!fout)
    //{
    //	cout << "open file failed" << endl;
    //}
    //while (cin >> a)
    //{
    //	//cout << "The numbers are: " << a << endl;
    //	fout << "The numbers are: " << a << endl;
    //	index++;
    //	if (index == 5)
    //	{
    //		break;
    //	}
    //}
    //cin.ignore(numeric_limits<std::streamsize>::max(), '\n');  // 清空缓存区脏数据
    //char ch;
    //cin >> ch;
    ////cout << "the last char is: " << ch << endl;
    //fout << "the last char is: " << ch << endl;
    //fout.close();



    return 0;

}

