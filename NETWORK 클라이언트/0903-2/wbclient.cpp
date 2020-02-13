//wbclient.cpp

#include <stdio.h>
#include <process.h> // _beginthread
#include <vector>
using namespace std;
#include "wbclient.h"

static SOCKET sock;

//약속된 함수 =======================================
void logmessage(int flag, const char *msg);
void recvmessage(char *msg, int size);
//===================================================

int wbclient_init()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 0;
	return 1;
}

void wbclient_exit()
{
	WSACleanup();
}

int wbclient_start(const char* ip, int port)
{
	//1. 소켓 생성
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		return 0;
	}

	//2. 서버 연결 요청
	SOCKADDR_IN serveraddr = { 0 };
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);			//네트웤 인지 안된다.
	serveraddr.sin_addr.s_addr = inet_addr(ip);//"127.0.0.1"

	int retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		return 0;
	}

	//수신 스레드 생성
	unsigned int h;
	h = _beginthreadex(0, 0, com_thread, (void*)sock, 0, 0);
	CloseHandle((HANDLE)h);

	return sock;
}

void wbclient_sockclose(SOCKET sock)
{
	closesocket(sock);
}

unsigned int __stdcall com_thread(void* value)
{
	SOCKET clientsock = (SOCKET)value;
	while (1)
	{
		//1. 데이터 수신 
		char buf[1024] = "";
		int retval = recvdata(clientsock, buf, sizeof(buf));
		if (retval == 0)
			break;

		//2. 사용자에게 전달
		recvmessage(buf, retval);
	}

	//클라이언트 접속 해제
	closesocket(clientsock);
	logmessage(2, clientsock);
	return 0;
}


void logmessage(int flag, SOCKET sock)
{
	char msg[100];
	SOCKADDR_IN clientaddr;
	int length = sizeof(clientaddr);
	getpeername(sock, (SOCKADDR*)&clientaddr, &length);
	sprintf_s(msg, "%s:%d", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	logmessage(1, msg);
}

int recvdata(SOCKET sock, char *buf, int size)
{
	int size1;
	int retval = recvn(sock, (char*)&size1, sizeof(int), 0);
	if (retval == SOCKET_ERROR || retval == 0)	// -1
		return 0;

	retval = recvn(sock, buf, size1, 0);
	if (retval == SOCKET_ERROR || retval == 0)	// -1
		return 0;
	return retval;
}

int wbclient_senddata(SOCKET sock, char *buf, int size)
{
	send(sock, (char*)&size, sizeof(int), 0);
	return send(sock, buf, size, 0);
}

int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0)
	{
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}