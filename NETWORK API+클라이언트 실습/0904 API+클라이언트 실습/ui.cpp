//ui.cpp
#include "std.h"

HWND g_hList;		//IDC_LIST1
HWND g_button1, g_button2, g_button3, g_button4, g_button5, g_button6;
HWND g_hDlg;

void ui_GetControlHandle(HWND hDlg)
{
	g_hDlg = hDlg;

	g_hList = GetDlgItem(hDlg, IDC_LIST1);
	g_button1 = GetDlgItem(hDlg, IDC_BUTTON1);
	g_button2 = GetDlgItem(hDlg, IDC_BUTTON2);
	g_button3 = GetDlgItem(hDlg, IDC_BUTTON3);
	g_button4 = GetDlgItem(hDlg, IDC_BUTTON4);
	g_button5 = GetDlgItem(hDlg, IDC_BUTTON5);
	g_button6 = GetDlgItem(hDlg, IDC_BUTTON6);
}

void ui_InitListView(HWND hDlg)
{
	LVCOLUMN COL = { 0 };

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("ID");				// 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("PW");				// 
	COL.iSubItem = 1;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("이름");				// 
	COL.iSubItem = 2;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("나이");				// 
	COL.iSubItem = 3;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("전화번호");				// 
	COL.iSubItem = 4;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	// 위 4 개의 확장 스타일 모두 지정
	ListView_SetExtendedListViewStyle(
		g_hList,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP);
}

void ui_SetAddress(HWND hDlg, TCHAR* ip, int port)
{
	SetDlgItemText(hDlg, IDC_IPADDRESS1, ip);
	SetDlgItemInt(hDlg, IDC_EDIT1, port, 0);
}

void ui_GetAddress(HWND hDlg, TCHAR* ip, int *port)
{
	GetDlgItemText(hDlg, IDC_IPADDRESS1, ip, sizeof(TCHAR) * 40);
	*port = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
}

void ui_GetInsertData(HWND hDlg, TCHAR* id, TCHAR* pw, TCHAR* name, TCHAR* phone, int *age)
{
	GetDlgItemText(hDlg, IDC_EDIT2, id, sizeof(TCHAR) * 20);
	GetDlgItemText(hDlg, IDC_EDIT3, pw, sizeof(TCHAR) * 20);
	GetDlgItemText(hDlg, IDC_EDIT4, name, sizeof(TCHAR) * 20);
	GetDlgItemText(hDlg, IDC_EDIT6, phone, sizeof(TCHAR) * 20);
	*age = GetDlgItemInt(hDlg, IDC_EDIT5, 0, 0);
}

void ui_GetName(HWND hDlg, TCHAR* name)
{
	GetDlgItemText(hDlg, IDC_EDIT4, name, sizeof(TCHAR) * 20);
}

void ui_GetUpdate(HWND hDlg, TCHAR*name, TCHAR* phone, int* age)
{
	GetDlgItemText(hDlg, IDC_EDIT4, name, sizeof(TCHAR) * 20);
	GetDlgItemText(hDlg, IDC_EDIT6, phone, sizeof(TCHAR) * 20);
	*age = GetDlgItemInt(hDlg, IDC_EDIT5, 0, 0);
}

void ui_SetButtonEnable(BOOL b1, BOOL b2, BOOL b3, BOOL b4, BOOL b5, BOOL b6)
{
	EnableWindow(g_button1, b1);
	EnableWindow(g_button2, b2);
	EnableWindow(g_button3, b3);
	EnableWindow(g_button4, b4);
	EnableWindow(g_button5, b5);
	EnableWindow(g_button6, b6);
}

void ui_SetInfoData(INSERT *data)
{
	SetDlgItemText(g_hDlg, IDC_EDIT2, data->id);
	SetDlgItemText(g_hDlg, IDC_EDIT3, data->pw);
	SetDlgItemText(g_hDlg, IDC_EDIT4, data->name);
	SetDlgItemText(g_hDlg, IDC_EDIT6, data->phone);
	SetDlgItemInt(g_hDlg, IDC_EDIT5, data->age, 0);
}

/*
void ui_PrintAll(HWND hDlg)
{
	int size = g_memberlist.size();
	SetDlgItemInt(hDlg, IDC_EDIT1, size, 0);
	//=================================================
	ListView_DeleteAllItems(g_hList); //아이템 모두 삭제

	for (int i = 0; i < (int)g_memberlist.size(); i++)
	{
		MEMBER mem = g_memberlist[i];
		// 텍스트와 이미지를 가진 아이템들을 등록한다.

		LVITEM LI;

		LI.mask = LVIF_TEXT;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = (LPWSTR)mem.name;			// 첫 번째 아이템
		SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 1;
		LI.pszText = (LPWSTR)mem.phone;
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 2;
		TCHAR temp[20];
		wsprintf(temp, TEXT("%c"), mem.gender);
		LI.pszText = temp;
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 3;
		wsprintf(temp, TEXT("%d"), mem.age);
		LI.pszText = temp;
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);
	}
}
*/