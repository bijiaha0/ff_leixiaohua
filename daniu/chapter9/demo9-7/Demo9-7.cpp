// Demo9-7.cpp : 定义控制台应用程序的入口点。
//

#include <functional>
#include <stack>
#include <queue>
#include <iostream>

using namespace std;


int main() {
    //stack<int> s;
    //queue<int> q;

    priority_queue<int> pq;  // 默认是最大值优先
    priority_queue<int, vector<int>, less<int> > pq2; //   最大值优先
    priority_queue<int, vector<int>, greater<int> > pq3; // 最小值优先

    pq.push(2);
    pq.push(1);
    pq.push(3);
    pq.push(0);
    while (!pq.empty()) {
        int top = pq.top();
        cout << " top is: " << top << endl;
        pq.pop();
    }
    cout << endl;


    pq2.push(2);
    pq2.push(1);
    pq2.push(3);
    pq2.push(0);
    while (!pq2.empty()) {
        int top = pq2.top();
        cout << " top is: " << top << endl;
        pq2.pop();
    }
    cout << endl;


    pq3.push(2);
    pq3.push(1);
    pq3.push(3);
    pq3.push(0);
    while (!pq3.empty()) {
        int top = pq3.top();
        cout << " top is: " << top << endl;
        pq3.pop();
    }
    cout << endl;

    return 0;
}

