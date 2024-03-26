#include <iostream>

using namespace std;


#include <vector>

int main() {
    // 数组访问
    //int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 0, 0};
    // 推荐方式
    //for (int index = 0; index < 10; ++index)
    //	cout << a[index] << " ";
    //cout << endl;

    // 不推荐方式
    //for (int index = 0; index <= 9; ++index)
    //	cout << a[index] << " ";

    // 数组的查找
    //int a[] = { 1, 2, 3, 4 };
    //int len = sizeof(a) / sizeof(a[0]);//得到数组容量
    //for (int index = 0; index < len; ++index)
    //{
    //	if (a[index] == 5)
    //	{
    //		cout << index << endl;
    //		return 0;
    //	}
    //}

    //二维数组的访问：
    int a[2][4] = {{1, 2, 3, 4},
                   {5, 6, 7, 8}};
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 4; ++col) {
            cout << a[row][col] << " ";
        }
        cout << endl;
    }


    return 0;
}

