//���� ��� �ڵ� sample
#include <stdio.h>
#include <vector>
using namespace std;
#include "wbserver.h"
#include "packet.h"
#define maxSit 19
#define SERVER_PORT 7000
extern unsigned int handle;

vector<INSERT> g_memberlist;
vector<TIME> g_Vtime;
vector<LIST> g_Vlist;
vector<CONCERTMANAGER> g_ConcertM;
int g_listsit[maxSit] = { 0 };


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
	printf("====================================\n");
	int i;
	int maxsit = 18;
	int *flag = (int*)msg;
	//printf("[Ŭ���̾�Ʈ ����] %s\n", msg);
	if (*flag == PACK_INSERT)						//�ϼ� �׷��� Ȯ���� ����
	{
		INSERT *packet = (INSERT*)msg;
		INSERT data = *packet;
		g_memberlist.push_back(data);

		for (int i = 0; i < g_memberlist.size(); i++)
		{
			INSERT data2 = g_memberlist[i];
			printf("%s %s %s %s\n",
				data2.id, data2.pw, data2.name, data2.phone);
		}

		SELECT pack = pack_insert(data.name);
		senddata(sock, (char*)&pack, sizeof(pack));
	}

	else if (*flag == PACK_LOGIN)						//�ϼ� �׷��� Ȯ���� ����
	{
		LOGIN *packet = (LOGIN*)msg;
		LOGIN data = *packet;

		int check = 0;
		for (i = 0; i < (int)g_memberlist.size(); i++)
		{
			INSERT data = g_memberlist[i];
			if (strcmp(packet->id, data.id) == 0)	//for���� ���鼭 ��Ŷid�� ���� ����Ʈ id�� �´°� ������ ����.
			{
				if (strcmp(packet->pw, data.pw) == 0)	//�׸��� pw���� ������ check�� 1�� ������ break;
				{
					check = 1;
					break;
				}
			}
		}

		if (check == 0)
		{
			INSERT pack = pack_LOGINF(packet->id);			//���� �𸣰ڴ�. insert�� ���� ��Ŷȭ �ϴ°ǵ�
			senddata(sock, (char*)&pack, sizeof(pack));
		}
		else
		{
			INSERT pack = pack_LOGINS(g_memberlist[i]);
			senddata(sock, (char*)&pack, sizeof(pack));
		}
	}

	else if (*flag == PACK_SELECT)						//�ϼ� �׷��� Ȯ���� ����
	{
		SELECT *packet = (SELECT*)msg;

		int check = 0;
		for (i = 0; i < (int)g_memberlist.size(); i++)
		{
			INSERT data = g_memberlist[i];
			if (strcmp(packet->name, data.name) == 0)
			{
				check = 1;
				break;
			}
		}

		//��ã�Ҵ�.
		if (check == 0)
		{
			SELECT pack = pack_SelectF(packet->name);
			senddata(sock, (char*)&pack, sizeof(pack));
		}
		else
		{
			INSERT pack = pack_SelectS(g_memberlist[i]);
			senddata(sock, (char*)&pack, sizeof(pack));
		}

	}

	else if (*flag == PACK_UPDATE)			// ������Ʈ �̸��� ��ȭ��ȣ�� �ް� �̸��� ���� �� �̸��� ��ȭ��ȣ�� ������ �ؼ� ����
	{										//�ϼ� �׷��� Ȯ���� ����
		UPDATE *packet = (UPDATE*)msg;

		int check = 0;
		for (i = 0; i < (int)g_memberlist.size(); i++)
		{
			INSERT data = g_memberlist[i];
			if (strcmp(packet->name, data.name) == 0) // strcmp(a,b)    a, b�� ���ڿ� ���� ������ 0���� �׸��� == 0 �� ������ ����.
			{
				check = 1;
				strcpy_s(g_memberlist[i].name, data.name);
				strcpy_s(g_memberlist[i].phone, data.phone);
				break;
			}
		}

		//��ã�Ҵ�.
		if (check == 0)
		{
			SELECT pack = pack_UpdateF(packet->name);		//�̸��� ȸ��
			senddata(sock, (char*)&pack, sizeof(pack));
		}
		else
		{
			INSERT pack = pack_UpdateS(g_memberlist[i]);	//��ü ���� ȸ��
			senddata(sock, (char*)&pack, sizeof(pack));
		}
	}

	else if (*flag == PACK_TIME)						//���� Ŭ���̾�Ʈ ���� �޾Ƶ��̴� ������ �ָ��ؼ� ����
	{
		TIME *pack = (TIME*)msg;
		TIME data = *pack;
		g_Vtime.push_back(data);

		for (int i = 0; i < g_Vtime.size(); i++)
		{
			TIME data2 = g_Vtime[i];
			printf("%s %s \n",
				data2.date, data2.info);
		}

		senddata(sock, (char*)&pack, sizeof(pack));
	}

	else if (*flag == PACK_LIST)
	{
		LIST *pack = (LIST*)msg;

		for (int i = 0; i < g_ConcertM.size(); i++)
		{
			CONCERTMANAGER data3 = g_ConcertM[i];
			printf("%s %s %s\n",
				data3.date, data3.info, data3.choice);
		}

		senddata(sock, (char*)&pack, sizeof(pack));

	}

	else if (*flag == PACK_CONNETED)					//���� Ȯ�κҰ�
	{
		printf("!!!");
		for (i = 0; i < maxSit; i++)
		{
			CONNECTED_R pack = pack_Connected_R(g_listsit[i]);
			senddata(sock, (char*)&pack, sizeof(pack));
		}
	}
	else if (*flag == PACK_TICKET)						//1�� ������ 1�� �ڸ��� ���� �����ϴ°� �ȴ�.
	{
		TICKETING *pack = (TICKETING*)msg;
		TICKETING data = *pack;

		g_listsit[data.Sit] = data.Sit;

		for (int i = 0; i < maxSit; i++)
		{
			//INSERT data = g_memberlist[i];
			//INSERT data = g_listsit[i];

			printf("%d\n",
				g_listsit[i]);
		}

	}



	//=============���� ��� ==============
	//system("cls");


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
	printf("192.168.0.22:7000\n");

	WaitForSingleObject((HANDLE)handle, INFINITE);

	//===========================================================
	//N. ������ ��������ϱ� ���� �ݵ�� ���α׷� ����� ȣ�� 
	wbserver_exit();
	return 0;
}