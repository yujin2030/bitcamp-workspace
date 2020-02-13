//ui.cpp
#include "std.h"

HWND g_hList;		//IDC_LIST1
extern vector<MEMBER> g_memberlist;

void ui_GetControlHandle(HWND hDlg)
{
	g_hList = GetDlgItem(hDlg, IDC_LIST1);
}

void ui_InitListView(HWND hDlg)
{
	LVCOLUMN COL = { 0 };

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("�̸�");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 120;
	COL.pszText = (LPWSTR)TEXT("��ȭ��ȣ");				// 
	COL.iSubItem = 1;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 80;
	COL.pszText = (LPWSTR)TEXT("����");				// 
	COL.iSubItem = 2;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("����");				// 
	COL.iSubItem = 3;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);
}

BOOL ui_Insert(HWND hDlg, MEMBER *pmem)//page146
{
	MEMBER member = { 0 };

	UINT ret = DialogBoxParam(GetModuleHandle(0),
		MAKEINTRESOURCE(IDD_DIALOG2), hDlg,
		InsertProc, (LPARAM)&member);

	if (ret == IDOK)
	{
		*pmem = member;
		return TRUE;
	}
	else					return FALSE;
}

void ui_PrintAll(HWND hDlg)
{
	int size = g_memberlist.size();
	SetDlgItemInt(hDlg, IDC_EDIT1, size, 0);
	//=================================================
	ListView_DeleteAllItems(g_hList); //������ ��� ����

	for (int i = 0; i < (int)g_memberlist.size(); i++)
	{
		MEMBER mem = g_memberlist[i];
		// �ؽ�Ʈ�� �̹����� ���� �����۵��� ����Ѵ�.

		LVITEM LI;

		LI.mask = LVIF_TEXT;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = (LPWSTR)mem.name;			// ù ��° ������
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