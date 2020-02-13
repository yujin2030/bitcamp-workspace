//wbsenderbr.cpp
#include "std.h"

SOCKET send_sock;
SOCKADDR_IN remoteaddr;

int wbsenderbr_start(int port)
{
	int ssocket_init(port);
	return 1;
}

int ssocket_init(int port)
{
	// socket()
	send_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (send_sock == INVALID_SOCKET) 
		wbcommon_errquit((LPSTR)"socket()");


	// ��ε�ĳ���� Ȱ��ȭ
	BOOL      bEnable = TRUE;
	int retval = setsockopt(send_sock, SOL_SOCKET, SO_BROADCAST,
		(char*)&bEnable, sizeof(bEnable));
	if (retval == SOCKET_ERROR)
		wbcommon_errquit((LPSTR)"setsockopt()");


	// ���� �ּ� ����ü �ʱ�ȭ
	ZeroMemory(&remoteaddr, sizeof(remoteaddr));
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_port = htons(9000);
	//-------------------------------------------------------
	remoteaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	//-------------------------------------------------------
	return 1;
}

int wbsenderbr_senddata(char* buf, int size)
{
	// ������ ������
	int retval = sendto(send_sock, buf, strlen(buf), 0,
		(SOCKADDR*)&remoteaddr, sizeof(remoteaddr));
	if (retval == SOCKET_ERROR)
	{
		wbcommon_errdisplay((LPSTR)"sendto");
		return 0;
	}
	return  retval;
}

void wbsenderbr_close()
{
	closesocket(send_sock);
}