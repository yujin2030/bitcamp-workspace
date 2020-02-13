#include <windows.h>
#include <stdio.h>

void main()
{
	// 세마포어 선언
	HANDLE hSemaphore = CreateSemaphore(0, 3, 3, TEXT("s"));

	printf("세마포어를 대기합니다.\n");

	WaitForSingleObject(hSemaphore, INFINITE);

	printf("세마포어를 획득 \n");
	MessageBox(0, TEXT("Release??"), TEXT(""), MB_OK);

	LONG old;
	ReleaseSemaphore(hSemaphore, 1, &old);
	CloseHandle(hSemaphore);
}