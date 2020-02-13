//���� ��� �ڵ� sample
#define WIN32_LEAN_AND_MEAN   //windows.h�� winsock2.h �浹 ����
#include <stdio.h>
#include <Windows.h>
#include <vector>
using namespace std;
#include "wbserver.h"
#include "packet.h"

#define SERVER_PORT 7000
extern unsigned int handle;

//flag 0 : Ŭ���̾�Ʈ ����
void logmessage(int flag, const char *msg)
{
	if (flag == 1) //Ŭ���̾�Ʈ ����
		printf("[Ŭ���̾�Ʈ ����] %s\n", msg);
	else if (flag == 2)
		printf("[Ŭ���̾�Ʈ ����] %s\n", msg);
}

void recvmessage(unsigned int sock, char *msg, int size)
{
	int *flag = (int*)msg;
	if (*flag == PACK_DRAW)
	{
		DRAW *packet = (DRAW*)msg;
		DRAW data = *packet;

		DRAW pack = pack_draw(data.color, data.pt);
		sendAlldata(sock, (char*)&pack, sizeof(pack));
	}
	else if (*flag == PACK_MESSAGE)
	{
		MESSAGE *packet = (MESSAGE*)msg;
		MESSAGE data = *packet;

		MESSAGE pack = pack_message(data.msg);
		sendAlldata(sock, (char*)&pack, sizeof(pack));
	}
}

int main()
{
	//1. ������ ����ϱ� ���� �ݵ�� ���� �ʱ�ȭ �Լ� ȣ��
	if (wbserver_init() == 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		return -1;
	}
	printf("������ ���� �ʱ�ȭ ����\n");
	//==========================================================

	//2. ���� ���� ���� 
	if (wbserver_start(SERVER_PORT) == 0)
	{
		printf("���� ���� ���� ����\n");
		return -1;
	}
	printf("���� ���� ���� ����\n");
	printf("192.168.0.52:7000\n");

	WaitForSingleObject((HANDLE)handle, INFINITE);

	//===========================================================
	//N. ������ ��������ϱ� ���� �ݵ�� ���α׷� ����� ȣ�� 
	wbserver_exit();
	return 0;
}