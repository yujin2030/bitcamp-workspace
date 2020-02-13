//handler.cpp
#include "std.h"

#define IP		"192.168.0.52"
#define PORT	7000

int sock1;

//flag 0 : 클라이언트 접속
void logmessage(int flag, const char *msg)
{
	if (flag == 1) //클라이언트 접속
		printf("[클라이언트 접속] %s\n", msg);
	else if (flag == 2)
		printf("[서버 연결 해제 해제] %s\n", msg);
}

void recvmessage(char *msg, int size)
{
	int *flag = (int*)msg;
	if (*flag == ACK_INSERT_S)
	{
		SELECT *packet = (SELECT*)msg;
		MessageBox(0, TEXT("회원가입성공"), packet->name, MB_OK);
	}
	else if (*flag == ACK_INSERT_F)
	{
		SELECT *packet = (SELECT*)msg;
		MessageBox(0, TEXT("회원가입실패"), packet->name, MB_OK);
	}
	else if (*flag == ACK_SELECT_S)
	{
		INSERT *packet = (INSERT*)msg;
		ui_SetInfoData(packet);
	}
	else if (*flag == ACK_SELECT_F)
	{
		SELECT *packet = (SELECT*)msg;
		MessageBox(0, TEXT("로그인실패"), packet->name, MB_OK);
	}
}


BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();

	ui_GetControlHandle(hDlg);

	ui_InitListView(hDlg);

	ui_SetAddress(hDlg, IP, PORT);

	ui_SetButtonEnable(TRUE, FALSE, FALSE, FALSE, FALSE, FALSE);

	wbclient_init();

	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL:		OnIdCancel(hDlg);		break;
	case IDC_BUTTON1:	OnConnect(hDlg);		break;
	case IDC_BUTTON2:   OnDisConnect(hDlg);		break;
	case IDC_BUTTON3:	OnInsert(hDlg);			break;
	case IDC_BUTTON4:	OnSelect(hDlg);			break;
	case IDC_BUTTON5:	OnUpdate(hDlg);			break;
	case IDC_BUTTON6:	OnDelete(hDlg);			break;
	}
	return TRUE;
}

void OnIdCancel(HWND hDlg)
{
	EndDialog(hDlg, IDCANCEL);

	wbclient_exit();
}

void OnConnect(HWND hDlg)
{
	TCHAR ip[40];
	int port;

	ui_GetAddress(hDlg, ip, &port);

	//서버 접속 요청
	sock1 = wbclient_start(ip, port);
	if (sock1 == 0)
		MessageBox(0, TEXT("연결 실패"), TEXT("알림"), MB_OK);
	else
		ui_SetButtonEnable(FALSE, TRUE, TRUE, TRUE, TRUE, TRUE);
}

void OnDisConnect(HWND hDlg)
{
	wbclient_sockclose(sock1);

	//서버 접속 해제 요청 
	ui_SetButtonEnable(TRUE, FALSE, FALSE, FALSE, FALSE, FALSE);
}

void OnInsert(HWND hDlg)
{
	TCHAR id[20], pw[20], name[20], phone[20];
	int age;

	//전달 정보 획득
	ui_GetInsertData(hDlg, id, pw, name, phone, &age);

	//패킷 정의
	INSERT pack = pack_Insert(id, pw, name, phone, age);

	//전송
	wbclient_senddata(sock1, (char*)&pack, sizeof(pack));

}

void OnSelect(HWND hDlg)
{
	TCHAR name[20];

	ui_GetName(hDlg, name);

	//패킷 정의
	SELECT pack = pack_Select(name);

	//전송
	wbclient_senddata(sock1, (char*)&pack, sizeof(pack));
}

void OnUpdate(HWND hDlg)
{
	TCHAR name[20], phone[20];
	int age;

	ui_GetUpdate(hDlg, name, phone, &age);

	//패킷 정의
	UPDATE pack = pack_Update(name, phone, age);

	//전송
	wbclient_senddata(sock1, (char*)&pack, sizeof(pack));
}

void OnDelete(HWND hDlg)
{
	TCHAR name[20];

	ui_GetName(hDlg, name);

	//패킷 정의
	SELECT pack = pack_Delete(name);

	//전송
	wbclient_senddata(sock1, (char*)&pack, sizeof(pack));
}