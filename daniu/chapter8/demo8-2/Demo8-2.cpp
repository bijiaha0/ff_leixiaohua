// Demo8-2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class News : public Observerable
{
public:
    virtual void GetSomeNews(string str)
    {
        SetChange("News: " + str);
    }
};

class User1:public Observer
{
public:
    virtual void Update(void* pArg)
    {
        cout << "User1 Got News: " << reinterpret_cast<char*>(pArg) <<endl;
    }
};
class User2 :public Observer
{
public:
    virtual void Update(void* pArg)
    {
        cout << "User2 Got News: " << reinterpret_cast<char*>(pArg) <<endl;
    }
};

int main()
{
    User1 u1;
    User2 u2;

    News n1;
    n1.GetSomeNews("T0");
    cout << n1.GetObseverCount() << endl;  // 0

    n1.Attach(&u1);
    n1.Attach(&u2);
    n1.GetSomeNews("T1");
    cout << n1.GetObseverCount() << endl;  // 2

    n1.Detach(&u2);
    n1.GetSomeNews("T2");
    cout << n1.GetObseverCount() << endl;  // 1

    n1.DetachAll();
    n1.GetSomeNews("T3");
    cout << n1.GetObseverCount() << endl;  // 0

    return 0;
}

