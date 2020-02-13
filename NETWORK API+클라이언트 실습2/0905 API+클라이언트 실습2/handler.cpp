//handler.cpp

#include "std.h"

#define IP "192.168.0.187"
#define PORT 7000
int sock1;

//flag 0 : Ŭ���̾�Ʈ ����
void logmessage(int flag, const char *msg)
{
	//if (flag == 1) //Ŭ���̾�Ʈ ����
	//	printf("[Ŭ���̾�Ʈ ����] %s\n", msg);
	//else if (flag == 2)
	//	printf("[���� ���� ���� ����] %s\n", msg);
}

void recvmessage(unsigned int sock, char *msg, int size)
{
	int *flag = (int*)msg;
	if (*flag == ACK_DRAW)
	{
		//������ ���� ����ȯ�ؼ� ȹ��
		DRAW *packet = (DRAW*)msg;
		//[uipaint]�ش� ������ �׸��� �׷�����.
		uipaint_Draw(packet->color, packet->pt);
		//[uipaint]�ϴ� ��Ʈ�� ������ ����
		uipaint_InfoPrint(packet->color, packet->pt);
	}
	else if (*flag == ACK_MESSAGE)
	{
		//������ ���� ����ȯ�ؼ� ȹ��
		MESSAGE *packet = (MESSAGE*)msg;

		uimsg_Print(packet->msg);
	}

}


BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	uimsg_GetHandle(hDlg);
	uipaint_GetHandle(hDlg);
	uipaint_InitCombo(hDlg);

	uimsg_SetName(hDlg);

	wbclient_init();
	sock1 = wbclient_start(IP, PORT);
	if (sock1 == 0)
		MessageBox(0, TEXT("���� ����"), TEXT("�˸�"), MB_OK);

	return TRUE;
}

BOOL OnLButtonDown(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	POINTS pt = MAKEPOINTS(lParam);

	//�׸��׸���
	//uipaint_Drawing(hDlg, pt);

	//��ǥ ���
	//uipaint_PrintPoint(hDlg, pt);

	//1. ������ ȹ��
	COLORREF color = getColor(hDlg);

	//2. ��Ŷ ����
	DRAW pack = packet_Draw(pt, color);

	//3. ����
	wbclient_senddata(sock1, (char*)&pack, sizeof(pack));

	return TRUE;
}


BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL:			OnIdCancel(hDlg);		break;
	case IDC_BUTTON1:		OnClickButton(hDlg);    break;
	case IDC_COMBO1:		OnComboBoxSelChange(hDlg, wParam); break;
	}
	return TRUE;
}

void OnIdCancel(HWND hDlg)
{
	EndDialog(hDlg, IDCANCEL);

	wbclient_sockclose(sock1);
	wbclient_exit();
}

void OnClickButton(HWND hDlg)
{
	TCHAR msg[100];
	if (uimsg_GetMessage(hDlg, msg) == FALSE)
		return;

	//2. ��Ŷ ����
	MESSAGE pack = packet_Message(msg);

	//3. ����
	wbclient_senddata(sock1, (char*)&pack, sizeof(pack));
	//uimsg_DisplayText(hDlg, msg);
}

void OnComboBoxSelChange(HWND hDlg, WPARAM wParam)
{
	if (HIWORD(wParam) == CBN_SELCHANGE) //���� ����ɶ�����...
	{
		uipaint_DrawColor(hDlg);
	}
}