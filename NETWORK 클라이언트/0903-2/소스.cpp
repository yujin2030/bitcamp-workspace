//Client��� ��� �ڵ� 

#include <stdio.h>
#include "wbclient.h"

#define SERVER_PORT 7000
#define SERVER_IP   "192.168.0.187"
extern unsigned int handle;

//flag 0 : Ŭ���̾�Ʈ ����
void logmessage(int flag, const char *msg)
{
	if (flag == 1) //Ŭ���̾�Ʈ ����
		printf("[Ŭ���̾�Ʈ ����] %s\n", msg);
	else if (flag == 2)
		printf("[���� ���� ���� ����] %s\n", msg);
}

void recvmessage(char *msg, int size)
{
	msg[size] = '\0';	//retval => ���� ���ŵ����� ũ��
	printf("[���ŵ�����] %s\n", msg);
}

int main()
{
	//1. ������ ����ϱ� ���� �ݵ�� ���� �ʱ�ȭ �Լ� ȣ��
	if (wbclient_init() == 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		return -1;
	}
	printf("������ ���� �ʱ�ȭ ����\n");
	//==========================================================

	//2. Ŭ���̾�Ʈ ���� ���� �� ���� ����
	int sock1 = wbclient_start(SERVER_IP, SERVER_PORT);
	if (sock1 == 0)
	{
		printf("���� ����\n");
		return -1;
	}
	printf("���� ���� ����\n");

	//����
	while (1)
	{
		char buf[1024] = "";
		printf(">> ");
		if (fgets(buf, sizeof(buf), stdin) == '\0') //����
			break;

		//����
		wbclient_senddata(sock1, buf, strlen(buf) + 1);
	}
	//===========================================================
	//N. ������ ��������ϱ� ���� �ݵ�� ���α׷� ����� ȣ�� 
	wbclient_sockclose(sock1);
	wbclient_exit();
	return 0;
}