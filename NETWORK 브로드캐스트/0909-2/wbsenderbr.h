//wbsender.h

int wbsenderbr_start(int port);

int ssocket_init(int port);

int wbsenderbr_senddata(char* buf, int size);

void wbsenderbr_close();