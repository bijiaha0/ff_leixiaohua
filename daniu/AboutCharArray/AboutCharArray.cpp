#include <iostream>
#include <vector>
using namespace std;


double average1(int* arr)
{
    double result = 0.0;
    int len = sizeof(arr) / sizeof(arr[0]);
    //cout << "In average1:  " << len << endl;

    for (int i = 0; i < len; i++)
    {
        result += arr[i];
    }

    return result / len;
}

double average2(int* arr, int len)
{
    double result = 0.0;
    //int len = sizeof(arr) / sizeof(arr[0]);
    //cout << "In average1:  " << len << endl;

    for (int i = 0; i < len; i++)
    {
        result += arr[i];
    }

    return result / len;
}

double average3(vector<int>& v)
{
    double result = 0.0;
    vector<int>::iterator it = v.begin();
    //auto it = v.begin();

    for (; it != v.end();  ++it)
    {
        result += *it;
    }

    return result / v.size();
}

double average2DV(vector<vector<int> >& vv)
{
    double result = 0.0;
    unsigned int size = 0;

    for (unsigned int i = 0; i < vv.size(); ++i)
    {
        for (unsigned int j = 0; j < vv[i].size(); ++j)
        {
            result += vv[i][j];
            size += 1;
            cout << vv[i][j] << " ";
        }
        cout << endl;
    }

    return result / size;
}
int main()
{
    int array1[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110 };
    int len = sizeof(array1) / sizeof(array1[0]);
    //cout << "In main:  " << len << endl;
    cout << average1(array1) << endl;
    cout << average2(array1, len) << endl;

    vector<int> vt{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110 };
    cout << average3(vt);

    cout << endl;

    vector<vector<int> > vv2D{8, vector<int>(12,3) };
    cout << average2DV(vv2D);


    return 0;
}
