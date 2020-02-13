//ui.cpp

#include "std.h"

HWND g_hListTeamView, g_hCombo;


void ui_InitCombo(HWND hDlg)
{
	g_hCombo = GetDlgItem(hDlg, IDC_COMBO1);

	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("ID"));
	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("이름"));
	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("전화번호"));
	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("등록일자"));
	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("성별"));
}

void ui_GetTeamSelectInfo(HWND hDlg, int* id, TCHAR* name, TCHAR* phone, TCHAR* register_1, TCHAR* gender)
{
	*id = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
	GetDlgItemText(hDlg, IDC_EDIT2, name, 10);
	GetDlgItemText(hDlg, IDC_EDIT3, phone, 20);
	GetDlgItemText(hDlg, IDC_EDIT4, register_1, 20);
	GetDlgItemText(hDlg, IDC_EDIT5, gender, 2);
}

void ui_GetTeamUpdateInfo(HWND hDlg, int* id, TCHAR* name, TCHAR* phone, TCHAR* gender)
{
	*id = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
	GetDlgItemText(hDlg, IDC_EDIT2, name, 10);
	GetDlgItemText(hDlg, IDC_EDIT3, phone, 20);
	GetDlgItemText(hDlg, IDC_EDIT5, gender, 2);
}

void ui_GetTeamInsertInfo(HWND hDlg, int* id, TCHAR* name, TCHAR* phone, TCHAR* register_1, TCHAR* gender)
{
	*id = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
	GetDlgItemText(hDlg, IDC_EDIT2, name, 10);
	GetDlgItemText(hDlg, IDC_EDIT3, phone, 20);
	GetDlgItemText(hDlg, IDC_EDIT4, register_1, 20);
	GetDlgItemText(hDlg, IDC_EDIT5, gender, 2);

}

void ui_GetTeamDeleteInfo(HWND hDlg, int *id)
{
	*id = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
}

void ui_InitTeamListView(HWND hDlg)
{
	g_hListTeamView = GetDlgItem(hDlg, IDC_LIST1);
	LVCOLUMN COL;

	// 헤더를 추가한다.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("고객 ID");				// 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(g_hListTeamView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("이름");			// 두 번째 헤더
	COL.iSubItem = 1;
	SendMessage(g_hListTeamView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("전화번호");			// 두 번째 헤더
	COL.iSubItem = 2;
	SendMessage(g_hListTeamView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("등록일자");			// 두 번째 헤더
	COL.iSubItem = 3;
	SendMessage(g_hListTeamView, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("성별");			// 두 번째 헤더
	COL.iSubItem = 4;
	SendMessage(g_hListTeamView, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

}

void ui_TeamListPrint(vector<custmg> *datalist, int size)
{
	ListView_DeleteAllItems(g_hListTeamView);
	//ListView_DeleteItem(hList, idx);

	for (int i = 0; i < size; i++)
	{
		custmg info = (*datalist)[i];
		//========================================
		ListTeamPrint(info, i);
		//=========================================
	}
}

void ListTeamPrint(custmg info, int idx)
{
	LVITEM LI;

	// 텍스트와 이미지를 가진 아이템들을 등록한다.
	LI.mask = LVIF_TEXT;

	LI.iItem = idx;
	LI.iSubItem = 0;
	TCHAR buf[20];
	wsprintf(buf, TEXT("%d"), info.id);
	LI.pszText = buf;			// 첫 번째 아이템
	SendMessage(g_hListTeamView, LVM_INSERTITEM, 0, (LPARAM)&LI);
	
	LI.iSubItem = 1;
	LI.pszText = info.name;
	SendMessage(g_hListTeamView, LVM_SETITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 2;
	LI.pszText = info.phone;
	SendMessage(g_hListTeamView, LVM_SETITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 3;
	LI.pszText = info.register_1;
	SendMessage(g_hListTeamView, LVM_SETITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 4;
	LI.pszText = info.gender;
	SendMessage(g_hListTeamView, LVM_SETITEM, 0, (LPARAM)&LI);
}



/*
void ui_GetHandle(HWND hDlg)
{
	g_hListView = GetDlgItem(hDlg, IDC_LIST1);
}

void ui_SetListViewColumnHeader(HWND hDlg)
{
	LVCOLUMN COL;

	// 헤더를 추가한다.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 150;
	COL.pszText = TEXT("이름");				// 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = TEXT("PID");			// 두 번째 헤더
	COL.iSubItem = 1;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);
}



*/