//wbcommon.h

#define BUFSIZE 512

int wbcommon_init();
int wbcommon_exit();

void wbcommon_errquit(char *msg);
void wbcommon_errdisplay(char *msg);