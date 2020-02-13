#include <windows.h>
#include <iostream>
using namespace std;

void WorkFunc()
{
	for (int i = 0; i < 10000000; i++);   //시간 지연 함수
}       
//공유 자원
int g_x = 0;
int g_x1 = 0;
//======================================
CRITICAL_SECTION       g_cs;      //전역
//======================================

DWORD WINAPI Func(PVOID p)
{
	EnterCriticalSection(&g_cs);               //임계영역 시작
	for (int i = 0; i < 20; i++)
	{
		g_x = 200;
		WorkFunc();
		g_x++;
		cout << "         Func : " << g_x << endl;
	}
	LeaveCriticalSection(&g_cs);              //임계영역 끝
	return 0;
}

void main()
{
	InitializeCriticalSection(&g_cs);              //초기화

	DWORD tid;
	HANDLE hThread = CreateThread(NULL, 0, Func, 0, NORMAL_PRIORITY_CLASS, &tid);
	//Sleep(1);
	
	EnterCriticalSection(&g_cs);              //임계영역 시작
	for (int i = 0; i < 20; i++)
	{
		g_x = 200;
		WorkFunc();
		g_x--;
		cout << "         Main : " << g_x << endl;
	}
	LeaveCriticalSection(&g_cs);                               //임계영역 끝

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	DeleteCriticalSection(&g_cs);                         //파괴
}