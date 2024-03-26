// AboutNumberOverflow.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
using namespace std;

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

int main()
{
	// 例子1
	//int i = 2147483640;
	//for (; i > 0; i++)
	//{
	//	cout << "adding " << i << endl;
	//}
	//cout << "exit " << i << endl;

	// boost version
	//cpp_int i2 = 2147483640;
	//for (; i2 > 0; i2++)
	//{
	//	cout << "adding " << i2 << endl;
	//}
	//cout << "exit " << i2 << endl;


	// 例子2
	int a = 500;
	int b = 400;
	int c = 300;
	int d = 200;
	cout << a * b * c * d << endl;

	// boost version
	cpp_int ba = 500;
	int bb = 400;
	int bc = 300;
	int bd = 200;
	cout << ba * bb * bc * bd << endl;

}