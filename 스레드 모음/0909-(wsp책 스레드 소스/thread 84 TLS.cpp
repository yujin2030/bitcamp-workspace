#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

void goo(char * name)
{
	//TLS 공간에 변수를 생성한다.
	__declspec(thread) static int c = 0;
	//static int c = 0;
	++c;
	printf("%s : %d\n", name, c);
}

DWORD WINAPI foo(void* p)
{
	char* name = (char*)p;
	goo(name);
	goo(name);
	goo(name);
	return 0;
}

void main()
{
	HANDLE h1 = CreateThread(0, 0, foo, (LPSTR)"A", 0, 0);
	HANDLE h2 = CreateThread(0, 0, foo, (LPSTR)"\tB", 0, 0);

	HANDLE h[2] = { h1,h2 };

	WaitForMultipleObjects(2,h,TRUE, INFINITE);
	CloseHandle(h1);
	CloseHandle(h2);
}