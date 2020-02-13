#include <iostream>
#include <process.h>
#include <windows.h>
using namespace std;

unsigned int __stdcall foo(void *p)
{
	cout << "foo" << endl;     //#include <iostream>
	Sleep(1000);
	cout << "foo finish" << endl;
	return 0;
}

void main()
{
	unsigned long h = _beginthreadex(0, 0, foo, 0, 0, 0);
	WaitForSingleObject((HANDLE)h, INFINITE);
	CloseHandle((HANDLE)h);
}

