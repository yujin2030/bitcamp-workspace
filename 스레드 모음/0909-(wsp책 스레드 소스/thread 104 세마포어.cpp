#include <windows.h>
#include <stdio.h>

void main()
{
	// �������� ����
	HANDLE hSemaphore = CreateSemaphore(0, 3, 3, TEXT("s"));

	printf("������� ����մϴ�.\n");

	WaitForSingleObject(hSemaphore, INFINITE);

	printf("������� ȹ�� \n");
	MessageBox(0, TEXT("Release??"), TEXT(""), MB_OK);

	LONG old;
	ReleaseSemaphore(hSemaphore, 1, &old);
	CloseHandle(hSemaphore);
}