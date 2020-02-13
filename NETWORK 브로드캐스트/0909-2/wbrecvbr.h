//wbrecvbr.h

int wbrecvber_start(int port);

int socketinit(int port);

unsigned int __stdcall recvthread(void * value);