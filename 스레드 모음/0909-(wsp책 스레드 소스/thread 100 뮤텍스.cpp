#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	//뮤텍스 생성
	HANDLE hMutex = CreateMutex(NULL, FALSE, TEXT("mutex"));

	cout << "뮤텍스를 기다리고 있다." << endl;

	DWORD d = WaitForSingleObject(hMutex, INFINITE);             //대기

	if(d==WAIT_TIMEOUT)
		MessageBox(NULL, TEXT("WAIT_TIMEOUT"), TEXT(""), MB_OK);
	else if (d == WAIT_OBJECT_0)
		MessageBox(NULL, TEXT("WAIT_OBJECT_0"), TEXT(""), MB_OK);
	else if (d == WAIT_ABANDONED_0)
		MessageBox(NULL, TEXT("WAIT_ABANDONED_0"), TEXT(""), MB_OK);

	cout << "뮤텍스 획득" << endl;
	MessageBox(NULL, TEXT("뮤텍스를 놓는다"), TEXT(""), MB_OK);

	//RealeaseMutex(hMutex);                //뮤텍스 파괴 (소유권 반납)

}