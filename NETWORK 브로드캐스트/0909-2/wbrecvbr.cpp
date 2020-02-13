//wbrecvbr.cpp
#include "std.h"

SOCKET recv_sock;

extern CRITICAL_SECTION g_cs;

int wbrecvber_start(int port)
{
	socketinit(port);

	unsigned int hthread;
	hthread = _beginthreadex(0, 0, recvthread, 0, 0, 0);
	CloseHandle((HANDLE)hthread);
	return 1;
}

int socketinit(int port)
{
	// socket()
	recv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (recv_sock == INVALID_SOCKET) wbcommon_errquit((LPSTR)"socket()");


	// bind()
	SOCKADDR_IN         localaddr;
	ZeroMemory(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(port);
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int retval = bind(recv_sock, (SOCKADDR*)&localaddr,
		sizeof(localaddr));

	return 1;
}

unsigned int __stdcall recvthread(void * value)
{
	// ������ ��ſ� ����� ����
	SOCKADDR_IN      peeraddr;
	int            addrlen;
	char         buf[BUFSIZE + 1];
	int        retval;

	// ��Ƽĳ��Ʈ ������ �ޱ�
	while (1)
	{
		EnterCriticalSection(&g_cs);    //�ӱ⿵������

		// ������ �ޱ�
		addrlen = sizeof(peeraddr);
		retval = recvfrom(recv_sock, buf, BUFSIZE, 0,
			(SOCKADDR*)&peeraddr, &addrlen);

		if (retval == SOCKET_ERROR)
		{
			wbcommon_errdisplay((LPSTR)"recvfrom");
			continue;
		}

		// ���� ������ ���
		buf[retval] = '\0';
		printf("[UDP/%s:%d] %s\n", inet_ntoa(peeraddr.sin_addr),
			ntohs(peeraddr.sin_port), buf);

		LeaveCriticalSection(&g_cs);         //�ӱ⿵�� ��
		Sleep(1);

	}

	// closesocket()
	closesocket(recv_sock);
}