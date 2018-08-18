#include <iostream>
using namespace std;

template <class t1> t1 dodawanie(t1 a, t1 b);

int main()
{
	cout << dodawanie<double>(7.9898, 9);
	system("pause");
}

template <class t1> t1 dodawanie(t1 a, t1 b)
{
	return a + b;
}