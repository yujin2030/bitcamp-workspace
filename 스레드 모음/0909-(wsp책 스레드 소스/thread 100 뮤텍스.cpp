#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	//���ؽ� ����
	HANDLE hMutex = CreateMutex(NULL, FALSE, TEXT("mutex"));

	cout << "���ؽ��� ��ٸ��� �ִ�." << endl;

	DWORD d = WaitForSingleObject(hMutex, INFINITE);             //���

	if(d==WAIT_TIMEOUT)
		MessageBox(NULL, TEXT("WAIT_TIMEOUT"), TEXT(""), MB_OK);
	else if (d == WAIT_OBJECT_0)
		MessageBox(NULL, TEXT("WAIT_OBJECT_0"), TEXT(""), MB_OK);
	else if (d == WAIT_ABANDONED_0)
		MessageBox(NULL, TEXT("WAIT_ABANDONED_0"), TEXT(""), MB_OK);

	cout << "���ؽ� ȹ��" << endl;
	MessageBox(NULL, TEXT("���ؽ��� ���´�"), TEXT(""), MB_OK);

	//RealeaseMutex(hMutex);                //���ؽ� �ı� (������ �ݳ�)

}