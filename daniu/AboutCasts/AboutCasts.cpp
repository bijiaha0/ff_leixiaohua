#include <iostream>
using  namespace std;

// 1+1/2+1/3+1/4+... +1/n
double getSum(int n)
{
	double result = 0.0;
	for (int i = 1; i < n + 1; i++)
	{
		//result += 1.0 / i;
		result += static_cast < double>(1) / i;
	}
	return result;
}

int main()
{
    //例子一
	int array[] = { 1,2,3 };
	cout << sizeof(array) / sizeof(array[0]) << endl;
	int threshold = -1;
	int len = static_cast <int>( sizeof(array) / sizeof(array[0]) ) ;
	//if (  sizeof(array) / sizeof(array[0]) > static_cast<unsigned int>(threshold)  )  //发生了一个隐式的类型转换
	if (len  > threshold)
	{
		cout << "positive number array" << endl;
	}
	else
	{
		cout << "negative number array" << endl;
	}
	cout << static_cast<unsigned int>(threshold) << endl;

	/*
   // 例子二
	// 1+1/2+1/3+1/4+... +1/n 
	int n = 0;
	cin >> n;
	cout << getSum(n) << endl;
	*/
}
