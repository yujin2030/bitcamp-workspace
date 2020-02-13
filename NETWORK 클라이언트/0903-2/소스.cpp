//Client모듈 사용 코드 

#include <stdio.h>
#include "wbclient.h"

#define SERVER_PORT 7000
#define SERVER_IP   "192.168.0.187"
extern unsigned int handle;

//flag 0 : 클라이언트 접속
void logmessage(int flag, const char *msg)
{
	if (flag == 1) //클라이언트 접속
		printf("[클라이언트 접속] %s\n", msg);
	else if (flag == 2)
		printf("[서버 연결 해제 해제] %s\n", msg);
}

void recvmessage(char *msg, int size)
{
	msg[size] = '\0';	//retval => 실제 수신데이터 크기
	printf("[수신데이터] %s\n", msg);
}

int main()
{
	//1. 소켓을 사용하기 위해 반드시 최초 초기화 함수 호출
	if (wbclient_init() == 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		return -1;
	}
	printf("윈도우 소켓 초기화 성공\n");
	//==========================================================

	//2. 클라이언트 소켓 생성 및 서버 접속
	int sock1 = wbclient_start(SERVER_IP, SERVER_PORT);
	if (sock1 == 0)
	{
		printf("연결 실패\n");
		return -1;
	}
	printf("서버 연결 성공\n");

	//전송
	while (1)
	{
		char buf[1024] = "";
		printf(">> ");
		if (fgets(buf, sizeof(buf), stdin) == '\0') //엔터
			break;

		//전송
		wbclient_senddata(sock1, buf, strlen(buf) + 1);
	}
	//===========================================================
	//N. 소켓을 사용종료하기 위해 반드시 프로그램 종료시 호출 
	wbclient_sockclose(sock1);
	wbclient_exit();
	return 0;
}