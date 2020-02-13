//서버 사용 코드 sample
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


//flag 0 : 클라이언트 접속
void logmessage(int flag, const char *msg)
{
	if (flag == 1) //클라이언트 접속
		printf("[클라이언트 접속] %s\n", msg);
	else if (flag == 2)
		printf("[클라이언트 해제] %s\n", msg);
}

void recvmessage(unsigned int sock, char *msg, int size)
{
	printf("====================================\n");
	int i;
	int maxsit = 18;
	int *flag = (int*)msg;
	//printf("[클라이언트 접속] %s\n", msg);
	if (*flag == PACK_INSERT)						//완성 그러나 확인은 아직
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

	else if (*flag == PACK_LOGIN)						//완성 그러나 확인은 아직
	{
		LOGIN *packet = (LOGIN*)msg;
		LOGIN data = *packet;

		int check = 0;
		for (i = 0; i < (int)g_memberlist.size(); i++)
		{
			INSERT data = g_memberlist[i];
			if (strcmp(packet->id, data.id) == 0)	//for문이 돌면서 패킷id와 기존 리스트 id가 맞는게 있으면 들어간다.
			{
				if (strcmp(packet->pw, data.pw) == 0)	//그리고 pw까지 맞으면 check를 1로 만든후 break;
				{
					check = 1;
					break;
				}
			}
		}

		if (check == 0)
		{
			INSERT pack = pack_LOGINF(packet->id);			//될지 모르겠다. insert는 전부 패킷화 하는건데
			senddata(sock, (char*)&pack, sizeof(pack));
		}
		else
		{
			INSERT pack = pack_LOGINS(g_memberlist[i]);
			senddata(sock, (char*)&pack, sizeof(pack));
		}
	}

	else if (*flag == PACK_SELECT)						//완성 그러나 확인은 아직
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

		//못찾았다.
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

	else if (*flag == PACK_UPDATE)			// 업데이트 이름과 전화번호만 받고 이름이 같을 시 이름과 전화번호를 재정의 해서 리턴
	{										//완성 그러나 확인은 아직
		UPDATE *packet = (UPDATE*)msg;

		int check = 0;
		for (i = 0; i < (int)g_memberlist.size(); i++)
		{
			INSERT data = g_memberlist[i];
			if (strcmp(packet->name, data.name) == 0) // strcmp(a,b)    a, b의 문자열 비교후 맞으면 0리턴 그리고 == 0 에 맞으면 들어간다.
			{
				check = 1;
				strcpy_s(g_memberlist[i].name, data.name);
				strcpy_s(g_memberlist[i].phone, data.phone);
				break;
			}
		}

		//못찾았다.
		if (check == 0)
		{
			SELECT pack = pack_UpdateF(packet->name);		//이름만 회신
			senddata(sock, (char*)&pack, sizeof(pack));
		}
		else
		{
			INSERT pack = pack_UpdateS(g_memberlist[i]);	//전체 정보 회신
			senddata(sock, (char*)&pack, sizeof(pack));
		}
	}

	else if (*flag == PACK_TIME)						//아직 클라이언트 에서 받아들이는 정보가 애매해서 보류
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

	else if (*flag == PACK_CONNETED)					//아직 확인불가
	{
		printf("!!!");
		for (i = 0; i < maxSit; i++)
		{
			CONNECTED_R pack = pack_Connected_R(g_listsit[i]);
			senddata(sock, (char*)&pack, sizeof(pack));
		}
	}
	else if (*flag == PACK_TICKET)						//1이 들어오면 1번 자리에 숫자 저장하는건 된다.
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



	//=============정보 출력 ==============
	//system("cls");


}

int main()
{
	//1. 소켓을 사용하기 위해 반드시 최초 초기화 함수 호출
	if (wbserver_init() == 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		return -1;
	}
	printf("윈도우 소켓 초기화 성공\n");
	//==========================================================

	//2. 서버 소켓 생성 
	if (wbserver_start(SERVER_PORT) == 0)
	{
		printf("서버 소켓 생성 실패\n");
		return -1;
	}
	printf("서버 소켓 생성 성공\n");
	printf("192.168.0.22:7000\n");

	WaitForSingleObject((HANDLE)handle, INFINITE);

	//===========================================================
	//N. 소켓을 사용종료하기 위해 반드시 프로그램 종료시 호출 
	wbserver_exit();
	return 0;
}