#include <string>
#include<map>
#include <algorithm>
#include <iostream>

using namespace std;

struct Display {
    void operator()(pair<string, double> info) {
        cout << info.first << ": " << info.second << endl;
    }
};

int main() {
    map<string, double> studentSocres;
    studentSocres["LiMing"] = 95.0;
    studentSocres["LiHong"] = 98.5;
    studentSocres.insert(pair<string, double>("zhangsan", 100.0));
    studentSocres.insert(pair<string, double>("Lisi", 98.6));
    studentSocres.insert(pair<string, double>("wangwu", 94.5));
    studentSocres.insert(map<string, double>::value_type("zhaoliu", 95.5));
    studentSocres["wangwu"] = 88.5;
    for_each(studentSocres.begin(), studentSocres.end(), Display());
    cout << endl;

    map<string, double>::iterator iter;
    iter = studentSocres.find("zhaoliu");
    if (iter != studentSocres.end()) {
        cout << "Found the score is: " << iter->second << endl;
    } else {
        cout << "Didn't find the key." << endl;
    }

    // 使用迭代器完成遍历查找的过程
    iter = studentSocres.begin();
    while (iter != studentSocres.end()) {
        if (iter->second < 98.0)  // 去除不是优秀的同学
        {
            studentSocres.erase(iter++);  // 注意：迭代器失效问题
        } else {
            iter++;
        }
    }
    for_each(studentSocres.begin(), studentSocres.end(), Display());
    cout << endl;


    for (iter = studentSocres.begin(); iter != studentSocres.end();) {
        if (iter->second <= 98.5) {
            iter = studentSocres.erase(iter);  // 注意：迭代器失效问题
        } else{
            iter++;
        }
    }
    for_each(studentSocres.begin(), studentSocres.end(), Display());
    cout << endl;

    // find得到并删除元素
    //iter = studentSocres.find("LiHong");
    //studentSocres.erase(iter);
    //for_each(studentSocres.begin(), studentSocres.end(), Display());

    //int n = studentSocres.erase("LiHong1");
    //cout << n << endl;
    //for_each(studentSocres.begin(), studentSocres.end(), Display());

    studentSocres.erase(studentSocres.begin(), studentSocres.end());
    for_each(studentSocres.begin(), studentSocres.end(), Display());
    cout << endl;

    return 0;
}

