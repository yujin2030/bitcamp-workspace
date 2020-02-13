//start.cpp

#include "std.h"
#define RECVPROT 9000

CRITICAL_SECTION g_cs;

int main()
{
	InitializeCriticalSection(&g_cs);         //초기화
	if (wbcommon_init() == 0)
	{
		printf("소켓라이브러리 초기화 에러\n");
		return -1;
	}
	wbrecvber_start(RECVPROT);
	wbsenderbr_start(RECVPROT);

	while (1)
	{
		EnterCriticalSection(&g_cs);    //임기영역시작

		char buf[BUFSIZE + 1];
		// 데이터 입력
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' 문자 제거
		//int len = strlen(buf);
		//if (buf[len - 1] == '\n')
		//	buf[len - 1] = '\0';

		if (strlen(buf) == 0)
			break;

		int retval = wbsenderbr_senddata(buf,strlen(buf));
		if (retval == 0)
			continue;

		printf("%d바이트를 보냈습니다.\n", retval);
		
		LeaveCriticalSection(&g_cs);         //임기영역 끝
		Sleep(1);
	}
	wbsenderbr_close();

	wbcommon_exit();

	InitializeCriticalSection(&g_cs);

	return 0;
}