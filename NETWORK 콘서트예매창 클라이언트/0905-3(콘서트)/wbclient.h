//wbclient.h

#include <WinSock2.h>				//���� API �Լ��� ����� 
#pragma comment(lib, "ws2_32.lib")	//���� API �Լ��� ������

int wbclient_init();
void wbclient_exit();
int wbclient_start(const char* ip, int port);
int wbclient_senddata(SOCKET sock, char *buf, int size);
void wbclient_sockclose(SOCKET sock);

unsigned int __stdcall com_thread(void* value);

int recvdata(SOCKET sock, char *buf, int size);

void logmessage(int flag, SOCKET sock);
int recvn(SOCKET s, char *buf, int len, int flags);