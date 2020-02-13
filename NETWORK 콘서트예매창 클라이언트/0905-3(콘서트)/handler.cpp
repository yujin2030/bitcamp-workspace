//handler.cpp
#include "std.h"

#define IP "192.168.0.187"
#define PORT 7000

vector<MEMBER> g_memberlist;

int sock1;

typedef struct tagTTT
{
	int Sep=9;
	TCHAR info[40];
	TCHAR day[20];
}TTT;

static HWND g_hCombo2;
static HWND g_hCombo3;
static HWND g_hCombo4;
static HWND g_hCombo5;
static HWND g_hEdit3;

void logmessage(int flag, const char *msg)
{
	//if (flag == 1) //Ŭ���̾�Ʈ ����
	//	printf("[Ŭ���̾�Ʈ ����] %s\n", msg);
	//else if (flag == 2)
	//	printf("[���� ���� ���� ����] %s\n", msg);
}

void recvmessage(unsigned int sock, char *msg, int size)
{
	int i;
	int *flag = (int*)msg;
	if (*flag == PACK_INSERT)		//ȸ������ ����
	{
		//������ ���� ����ȯ�ؼ� ȹ��
		MEMBER *packet = (MEMBER*)msg;
		MEMBER data = *packet;

		g_memberlist.push_back(data);
		//[uilist]�ش� ������ ����Ʈ�� ����
		MEMBER pack = pack_LOGINS(data);
		//
		
		//[uipaint]�ϴ� ��Ʈ�� ������ ����
		//uipaint_InfoPrint(packet->color, packet->pt);
		wbclient_senddata(sock, (char *)&pack, sizeof(pack));
	}
	else if (*flag == PACK_LOGIN)
	{
		LOGIN *packet = (LOGIN*)msg;
		LOGIN data = *packet;

		int check = 0;
		for (i = 0; i < (int)g_memberlist.size(); i++)
		{
			MEMBER data = g_memberlist[i];
			if (strcmp(packet->id, data.id) == 0)   //for���� ���鼭 ��Ŷid�� ���� ����Ʈ id�� �´°� ������ ����.
			{
				if (strcmp(packet->pw, data.pw) == 0)   //�׸��� pw���� ������ check�� 1�� ������ break;
				{
					check = 1;
					break;
				}
			}
		}

		if (check == 0)
		{
			MEMBER pack = pack_LOGINF(packet->id);         //���� �𸣰ڴ�. insert�� ���� ��Ŷȭ �ϴ°ǵ�
			wbclient_senddata(sock, (char*)&pack, sizeof(pack));
		}
		else
		{
			LOGINS pack = pack_LoginS();
			wbclient_senddata(sock, (char*)&pack, sizeof(pack));
		}
	}

}

void OnInfo(HWND hDlg, WPARAM wParam)
{
	MEMBER member = { 0 };
	UINT ret = DialogBoxParam(GetModuleHandle(0),
		MAKEINTRESOURCE(IDD_DIALOG2),
		hDlg,
		InfoProc,
		(LPARAM)&member);
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();

	wbclient_init();
	sock1 = wbclient_start(IP, PORT);
	if (sock1 == 0)
		MessageBox(0, TEXT("���� ����"), TEXT("�˸�"), MB_OK);

	
	g_hCombo5 = GetDlgItem(hDlg, IDC_COMBO5);
	SendMessage(g_hCombo5, CB_ADDSTRING, 0, (LPARAM)TEXT("�ְ�â��"));

	g_hCombo4 = GetDlgItem(hDlg, IDC_COMBO4);
	for (int i = 1; i < 32; i++)           //�޺��ڽ� ���� ����
	{
		TCHAR temp[10];
		int Sep = 9;
		//wsprintf(Sep, TEXT("%d/"), i);

		wsprintf(temp, TEXT("%d��%d��"),Sep, i);
		SendMessage(g_hCombo4, CB_ADDSTRING, 0, (LPARAM)temp);
	}

	g_hCombo2 = GetDlgItem(hDlg, IDC_COMBO2);
	SendMessage(g_hCombo2, CB_ADDSTRING, 0, (LPARAM)TEXT("�ݿ��� 8��"));

	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON20:   OnNotifyButton1(hDlg, wParam);         break;
	case IDCANCEL:       OnCancel(hDlg);             break;
	case ID_Menu:        OnInfo(hDlg, wParam);                  break;
	case ID_40003:			EndDialog(hDlg, ID_40003); break;
	case IDC_BUTTON18:     OnNotifyButton2(hDlg);      break;
	}
	return TRUE;
}

void AddEditBox(HWND hDlg)
{
	TTT ttt;

	TCHAR str[256];

	GetDlgItemText(hDlg, IDC_COMBO4, ttt.day, sizeof(ttt.day));
	
	wsprintf(str, TEXT("%s"), ttt.day);

	//GetDlgItemInt(hDlg, IDC_EDIT3, 0, 0);
	SetDlgItemText(hDlg, IDC_EDIT3, str);

	 OnTime(hDlg);
}

void OnNotifyButton1(HWND hDlg, WPARAM wParam)
{
	AddEditBox(hDlg);
}

void OnTime(HWND hDlg)
{
	
	TCHAR info[20], day[20];

	ui_SetTimeData(hDlg, info, day);
	
	TIME pack = pack_Time(day, info);

	wbclient_senddata(sock1, (char*)&pack, sizeof(pack));

	
}

void OnCancel(HWND hDlg)
{
	wbclient_exit();
	EndDialog(hDlg, IDCANCEL);
}

void OnNotifyButton2(HWND hDlg)
{
	OnList(hDlg);
}

void OnList(HWND hDlg)
{
	TCHAR choice[20];

	ui_SetChoice(hDlg, choice);

	LIST pack = pack_List(choice);

	wbclient_senddata(sock1, (char*)&pack, sizeof(pack));
}