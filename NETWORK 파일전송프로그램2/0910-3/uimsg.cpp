//uimsg.cpp
//wbserver.cpp
#include <stdio.h>
#include <process.h> // _beginthread
#include <vector>
using namespace std;
#include "wbmsg.h"

static SOCKET listenSock;
unsigned int handle;
vector<SOCKET> clientlist;

//약속된 함수 =======================================
//void logmessage(int flag, const char *msg);
//void recvmessage(unsigned int sock, char *msg, int size);
//===================================================

int wbserver_init()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 0;
	return 1;
}

void wbserver_exit()
{
	WSACleanup();
}

int wbserver_start(int port)
{
	//1. 소켓 생성
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSock == INVALID_SOCKET)	//-1
	{
		return 0;
	}

	//2. 주소 할당
	SOCKADDR_IN serveraddr = { 0 };
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);		//네트웤 인지 안된다.
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int retval = bind(listenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		return 0;
	}

	//3. 개통
	retval = listen(listenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		return 0;
	}

	//=============== 수신 처리 =================
	handle = _beginthreadex(0, 0, listen_thread, 0, 0, 0);

	return 1;
}

unsigned int __stdcall listen_thread(void* value)
{
	while (1)
	{
		//1. 접속처리
		SOCKET clientsock = acceptclient();
		if (clientsock == 0)
			continue;

		//2. 클라이언트 정보 출력(사용자에게 전달)
		logmessage(1, clientsock);

		//저장
		clientlist.push_back(clientsock);

		//3. 통신 스레드 생성page36
		unsigned int h = _beginthreadex(0, 0, com_thread,
			(void*)clientsock, 0, 0);
		CloseHandle((HANDLE)h);
	}
}

unsigned int __stdcall com_thread(void* value)
{
	SOCKET clientsock = (SOCKET)value;
	while (1)
	{
		//3. 데이터 수신 
		char buf[1024] = "";
		int retval = recvdata(clientsock, buf, sizeof(buf));
		if (retval == 0)
			break;

		//4. 사용자에게 전달
//		recvmessage(clientsock, buf, retval);

		//4.클라이언트에게 재송신(1대 다통신)
		/*for (int i = 0; i < (int)clientlist.size(); i++)
		{
		SOCKET sock = clientlist[i];
		senddata(sock, buf, retval);
		}*/

	}
	//소켓 제거
	for (int i = 0; i < (int)clientlist.size(); i++)
	{
		SOCKET sock = clientlist[i];
		if (sock == clientsock)
		{
			clientlist.erase(clientlist.begin() + i);
		}
	}

	//클라이언트 접속 해제	
	logmessage(2, clientsock);
	closesocket(clientsock);
	return 0;
}

SOCKET acceptclient()
{
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);	//반드시 초기화....
	SOCKET clientSock = accept(listenSock, (SOCKADDR*)&clientaddr, &addrlen);
	if (clientSock == INVALID_SOCKET)
		return 0;
	return clientSock;
}

void logmessage(int flag, SOCKET sock)
{
	char msg[100];
	SOCKADDR_IN clientaddr;
	int length = sizeof(clientaddr);
	getpeername(sock, (SOCKADDR*)&clientaddr, &length);
	sprintf_s(msg, "%s:%d", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	//	logmessage(flag, msg);
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

int senddata(SOCKET sock, char *buf, int size)
{
	send(sock, (char*)&size, sizeof(int), 0);
	return send(sock, buf, size, 0);
}

void sendAlldata(SOCKET sock, char *buf, int size)
{
	for (int i = 0; i < (int)clientlist.size(); i++)
	{
		SOCKET s = clientlist[i];

		send(s, (char*)&size, sizeof(int), 0);
		send(s, buf, size, 0);
	}
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