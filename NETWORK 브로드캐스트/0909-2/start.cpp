//start.cpp

#include "std.h"
#define RECVPROT 9000

CRITICAL_SECTION g_cs;

int main()
{
	InitializeCriticalSection(&g_cs);         //�ʱ�ȭ
	if (wbcommon_init() == 0)
	{
		printf("���϶��̺귯�� �ʱ�ȭ ����\n");
		return -1;
	}
	wbrecvber_start(RECVPROT);
	wbsenderbr_start(RECVPROT);

	while (1)
	{
		EnterCriticalSection(&g_cs);    //�ӱ⿵������

		char buf[BUFSIZE + 1];
		// ������ �Է�
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' ���� ����
		//int len = strlen(buf);
		//if (buf[len - 1] == '\n')
		//	buf[len - 1] = '\0';

		if (strlen(buf) == 0)
			break;

		int retval = wbsenderbr_senddata(buf,strlen(buf));
		if (retval == 0)
			continue;

		printf("%d����Ʈ�� ���½��ϴ�.\n", retval);
		
		LeaveCriticalSection(&g_cs);         //�ӱ⿵�� ��
		Sleep(1);
	}
	wbsenderbr_close();

	wbcommon_exit();

	InitializeCriticalSection(&g_cs);

	return 0;
}