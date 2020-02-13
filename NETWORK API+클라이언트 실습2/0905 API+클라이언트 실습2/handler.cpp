//handler.cpp

#include "std.h"

#define IP "192.168.0.187"
#define PORT 7000
int sock1;

//flag 0 : 클라이언트 접속
void logmessage(int flag, const char *msg)
{
	//if (flag == 1) //클라이언트 접속
	//	printf("[클라이언트 접속] %s\n", msg);
	//else if (flag == 2)
	//	printf("[서버 연결 해제 해제] %s\n", msg);
}

void recvmessage(unsigned int sock, char *msg, int size)
{
	int *flag = (int*)msg;
	if (*flag == ACK_DRAW)
	{
		//데이터 강제 형변환해서 획득
		DRAW *packet = (DRAW*)msg;
		//[uipaint]해당 정보로 그림이 그려진다.
		uipaint_Draw(packet->color, packet->pt);
		//[uipaint]하단 컨트롤 정보가 변경
		uipaint_InfoPrint(packet->color, packet->pt);
	}
	else if (*flag == ACK_MESSAGE)
	{
		//데이터 강제 형변환해서 획득
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
		MessageBox(0, TEXT("연결 실패"), TEXT("알림"), MB_OK);

	return TRUE;
}

BOOL OnLButtonDown(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	POINTS pt = MAKEPOINTS(lParam);

	//그림그리기
	//uipaint_Drawing(hDlg, pt);

	//좌표 출력
	//uipaint_PrintPoint(hDlg, pt);

	//1. 정보를 획득
	COLORREF color = getColor(hDlg);

	//2. 패킷 생성
	DRAW pack = packet_Draw(pt, color);

	//3. 전송
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

	//2. 패킷 생성
	MESSAGE pack = packet_Message(msg);

	//3. 전송
	wbclient_senddata(sock1, (char*)&pack, sizeof(pack));
	//uimsg_DisplayText(hDlg, msg);
}

void OnComboBoxSelChange(HWND hDlg, WPARAM wParam)
{
	if (HIWORD(wParam) == CBN_SELCHANGE) //선택 변경될때마다...
	{
		uipaint_DrawColor(hDlg);
	}
}