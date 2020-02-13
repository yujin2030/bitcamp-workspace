//wbmessage.h

#include <WinSock2.h>				//소켓 API 함수의 선언부 
#pragma comment(lib, "ws2_32.lib")	//소켓 API 함수의 구현부

int wbserver_init();
void wbserver_exit();
int wbserver_start(int port);

unsigned int __stdcall listen_thread(void* value);
unsigned int __stdcall com_thread(void* value);

SOCKET acceptclient();
void logmessage(int flag, SOCKET sock);
int recvdata(SOCKET sock, char *buf, int size);
int senddata(SOCKET sock, char *buf, int size);
void sendAlldata(SOCKET sock, char *buf, int size);

int recvn(SOCKET s, char *buf, int len, int flags);