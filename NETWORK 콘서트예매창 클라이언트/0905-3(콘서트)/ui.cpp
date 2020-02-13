#include "std.h"
HWND g_hList;

extern vector<MEMBER> g_memberlist;

void ui_SetChoice(HWND hDlg, TCHAR* choice)
{
	GetDlgItemText(hDlg, IDC_COMBO2, choice, sizeof(TCHAR) * 20);
}

void ui_SetTimeData(HWND hDlg, TCHAR* info, TCHAR* day)
{
	GetDlgItemText(hDlg, IDC_COMBO4, day, sizeof(TCHAR) * 20);
	GetDlgItemText(hDlg, IDC_COMBO5, info, sizeof(TCHAR) * 40);
}



void ui_InitListView(HWND hDlg)     //�ڽ�â ���
{
	LVCOLUMN COL = { 0 };

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 100;
	COL.pszText = (LPSTR)TEXT("ID");         //ù ��° ���
	COL.iSubItem = 0;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 0, (LPARAM)& COL);

	COL.cx = 120;
	COL.pszText = (LPSTR)TEXT("PW");         //�� ��° ���
	COL.iSubItem = 1;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 1, (LPARAM)& COL);

	COL.cx = 80;
	COL.pszText = (LPSTR)TEXT("�̸�");         //�� ��° ���
	COL.iSubItem = 2;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 2, (LPARAM)& COL);

	COL.cx = 100;
	COL.pszText = (LPSTR)TEXT("��ȭ��ȣ");         //4 ��° ���
	COL.iSubItem = 3;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 3, (LPARAM)& COL);


}

void ui_GetControlHandle(HWND hDlg)
{
	g_hList = GetDlgItem(hDlg, IDC_LIST1);
}

void ui_PrintAll(HWND hDlg)      //�ڽĲ� �޾ƿͼ� �θ�â�� ���
{
	int size = g_memberlist.size();
	//=======================================
	ListView_DeleteAllItems(g_hList);  //�������� �ʱ�ȭ
	for (int i = 0; i < (int)g_memberlist.size(); i++)
	{
		MEMBER mem = g_memberlist[i];
		//�ؽ�Ʈ�� �̹�� ���� �����۵��� ����Ѵ�
		LVITEM LI;

		LI.mask = LVIF_TEXT;
		LI.iItem = i;

		LI.iSubItem = 0;
		LI.pszText = mem.id;
		SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 1;
		LI.pszText = mem.pw;
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 2;
		LI.pszText = mem.name;
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 3;
		LI.pszText = mem.phone;
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);
	}
}