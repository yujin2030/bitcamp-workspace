//wbclient.h

#include <WinSock2.h>				//소켓 API 함수의 선언부 
#pragma comment(lib, "ws2_32.lib")	//소켓 API 함수의 구현부

int wbclient_init();
void wbclient_exit();
int wbclient_start(const char* ip, int port);
int wbclient_senddata(SOCKET sock, char *buf, int size);
void wbclient_sockclose(SOCKET sock);

unsigned int __stdcall com_thread(void* value);

int recvdata(SOCKET sock, char *buf, int size);

void logmessage(int flag, SOCKET sock);
int recvn(SOCKET s, char *buf, int len, int flags);