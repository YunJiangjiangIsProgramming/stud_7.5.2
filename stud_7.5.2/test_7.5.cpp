#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include"string.h"

int main()
{
	/*try
	{
		luow::test_string10();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}*/

	luow::string s1;
	std::string s2;
	cout << sizeof(s1) << endl; //12
	cout << sizeof(s2) << endl; // 28 


	luow::string s3("11111");  // 12 
	std::string s4("1111111"); // 28
	std::string s5("111111111111111111111111111111111"); // 28

	cout << sizeof(s3) << endl;
	cout << sizeof(s4) << endl;


	return 0;
}