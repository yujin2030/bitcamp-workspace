//서버 사용 코드 sample
#define WIN32_LEAN_AND_MEAN   //windows.h과 winsock2.h 충돌 방지
#include <stdio.h>
#include <Windows.h>
#include <vector>
using namespace std;
#include "wbserver.h"
#include "packet.h"

#define SERVER_PORT 7000
extern unsigned int handle;

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
	printf("192.168.0.52:7000\n");

	WaitForSingleObject((HANDLE)handle, INFINITE);

	//===========================================================
	//N. 소켓을 사용종료하기 위해 반드시 프로그램 종료시 호출 
	wbserver_exit();
	return 0;
}