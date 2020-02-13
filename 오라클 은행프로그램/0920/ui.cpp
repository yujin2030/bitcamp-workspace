#include "std.h"

HWND g_hCombo1;
HWND g_hCombo2;
HWND g_hListIOview;
HWND g_hListAccView;

void ui_GetHandle(HWND hDlg)		//��ID���� �޺��ڽ� �ڵ���
{
	g_hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
	g_hCombo2 = GetDlgItem(hDlg, IDC_COMBO2);
	g_hListAccView = GetDlgItem(hDlg, IDC_LIST2);
}

void ui_ComboCustSet(vector<CUSINFO> *cusinfolist, int size)		//��ID���� �޺��ڽ��� ���� ���
{
	for (int i = 0; i < size; i++)
	{
		CUSINFO cust_info = (*cusinfolist)[i];
		TCHAR temp[20];
		wsprintf(temp, TEXT("%d"), (*cusinfolist)[i].id);
		SendMessage(g_hCombo1, CB_ADDSTRING, 0, (LPARAM)temp);
	}
}

void ui_GetCustId(HWND hDlg, int *cust_id)		//���õ� ��ȸ��ID �޺��ڽ� ������������
{
	TCHAR combotext[20];
	int c_id;

	int nGetSel = SendMessage(g_hCombo1, CB_GETCURSEL, 0, 0);
	SendMessage(g_hCombo1, CB_GETLBTEXT, nGetSel, (LPARAM)combotext);
	c_id = _ttoi(combotext);	//���ڿ��� ������ ��ȯ

	*cust_id = c_id;

	/**cust_id = GetDlgItemInt(hDlg, IDC_COMBO1, 0, 0);*/
}

void ui_SetNameIntoEdit(HWND hDlg,vector<CUSINFO> *cusnamelist, int size)		//���̸� ����ϱ�
{
	for (int i = 0; i < size; i++)
	{
		CUSINFO cust_name = (*cusnamelist)[i];

		TCHAR temp[50];
		wsprintf(temp, TEXT("%s"), (*cusnamelist)[i].name);
		SetDlgItemText(hDlg, IDC_EDIT2, temp);
	}
}


void ui_GetAccId(HWND hDlg, int *acc_id)		//���õ� ���¹�ȣ ����Ʈ�ڽ� ������������
{
	TCHAR listtext[20];
	int acid;

	int nGetSel = SendMessage(g_hListAccView, LB_GETCURSEL, 0, 0);
	SendMessage(g_hListAccView, LB_GETTEXT, nGetSel, (LPARAM)listtext);
	acid = _ttoi(listtext);	//���ڿ��� ������ ��ȯ

	*acc_id = acid;

	/**cust_id = GetDlgItemInt(hDlg, IDC_COMBO1, 0, 0);*/
}


void ui_SetAccIntoList(HWND hDlg,vector<ACCINFO> *acclist, int size)	//����Ʈ�ڽ��� ���¹�ȣ ���
{
	for (int i = 0; i < size; i++)
	{
		ACCINFO acc = (*acclist)[i];

		TCHAR temp[50];
		wsprintf(temp, TEXT("%d"), (*acclist)[i].acc_id);	//���� �޶� �׼��� ����; ����
		SendMessage(g_hListAccView, LB_ADDSTRING, 0, (LPARAM)temp);
	}
}

void ui_SetAccInfoEdit(HWND hDlg, vector<ACCINFO> *acclist, int size)	//�� ����Ʈ�� �������� ���
{
	for (int i = 0; i < size; i++)
	{
		ACCINFO acc = (*acclist)[i];

		TCHAR id[50];
		wsprintf(id, TEXT("%d"), (*acclist)[i].acc_id);	//���� �޶� �׼��� ����; ����
		SetDlgItemText(hDlg, IDC_EDIT3, id);

		TCHAR bal[50];
		wsprintf(bal, TEXT("%d"), (*acclist)[i].acc_balance);	//���� �޶� �׼��� ����; ����
		SetDlgItemText(hDlg, IDC_EDIT4, bal);

		TCHAR date[50];
		wsprintf(date, TEXT("%s"), (*acclist)[i].opendate);	//���� �޶� �׼��� ����; ����
		SetDlgItemText(hDlg, IDC_EDIT5, date);
	}
}

void ui_Init_IO_ListView(HWND hDlg)		//����Ʈ �ʱ�ȭ
{
	g_hListIOview = GetDlgItem(hDlg, IDC_LIST1);
	LVCOLUMN COL;

	// ����� �߰��Ѵ�.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("�����ID");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("���¹�ȣ");			// �� ��° ���
	COL.iSubItem = 1;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("�Աݱݾ�");			// �� ��° ���
	COL.iSubItem = 2;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("��ݱݾ�");			// �� ��° ���
	COL.iSubItem = 3;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("����ݾ�");			// �ټ� ��° ���
	COL.iSubItem = 4;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("�ŷ��Ͻ�");			// ���� ��° ���
	COL.iSubItem = 5;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 5, (LPARAM)&COL);

}


void ui_IO_ListPrint(vector<IOINFO> *IOINFOLIST, int size)	//����Ʈ����Լ�ȣ���ϴ� �Լ�
{
	ListView_DeleteAllItems(g_hListIOview);
	//ListView_DeleteItem(hList, idx);

	for (int i = 0; i < size; i++)
	{
		IOINFO info = (*IOINFOLIST)[i];
		//========================================
		List_IO_print(info, i);
		//=========================================
	}
}



void List_IO_print(IOINFO info, int idx)		//����Ʈ �� �����־ ���
{
	LVITEM LI;

	// �ؽ�Ʈ�� �̹����� ���� �����۵��� ����Ѵ�.
	LI.mask = LVIF_TEXT;

	LI.iItem = idx;
	LI.iSubItem = 0;
	TCHAR buf[20];
	wsprintf(buf, TEXT("%d"), info.io_id);
	LI.pszText = buf;			// ù ��° ������
	SendMessage(g_hListIOview, LVM_INSERTITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 1;
	wsprintf(buf, TEXT("%d"), info.ac_id);
	LI.pszText = buf;
	SendMessage(g_hListIOview, LVM_SETITEM, 1, (LPARAM)&LI);

	LI.iSubItem = 2;
	wsprintf(buf, TEXT("%d"), info.deposit);
	LI.pszText = buf;
	SendMessage(g_hListIOview, LVM_SETITEM, 2, (LPARAM)&LI);

	LI.iSubItem = 3;
	wsprintf(buf, TEXT("%d"), info.withdrawl);
	LI.pszText = buf;
	SendMessage(g_hListIOview, LVM_SETITEM, 3, (LPARAM)&LI);

	LI.iSubItem = 4;
	wsprintf(buf, TEXT("%d"), info.curmoney);
	LI.pszText = buf;
	SendMessage(g_hListIOview, LVM_SETITEM, 4, (LPARAM)&LI);

	LI.iSubItem = 5;
	LI.pszText = info.actdate;
	SendMessage(g_hListIOview, LVM_SETITEM, 2, (LPARAM)&LI);
}

void ui_InitIoCombo(HWND hDlg)			//��/��� �޺��ڽ� �ʱ�ȭ
{
	SendMessage(g_hCombo2, CB_ADDSTRING, 0, (LPARAM)TEXT("�Ա�"));
	SendMessage(g_hCombo2, CB_ADDSTRING, 0, (LPARAM)TEXT("���"));
}

void ui_GetMoney(HWND hDlg, int *money)
{
	*money = GetDlgItemInt(hDlg, IDC_EDIT6, 0, 0);
}

void ui_Get_De_Wi(HWND hDlg, TCHAR *De_Wi)		//���õ� ��ȸ��ID �޺��ڽ� ������������
{
	TCHAR combo2text[20];

	int nGetSel = SendMessage(g_hCombo1, CB_GETCURSEL, 0, 0);
	SendMessage(g_hCombo1, CB_GETLBTEXT, nGetSel, (LPARAM)combo2text);

	De_Wi = combo2text;

	/**cust_id = GetDlgItemInt(hDlg, IDC_COMBO1, 0, 0);*/
}

void ui_GetAccFromEdit(HWND hDlg, int *acc_id)	//���������� ����Ʈ�κ���
{
	*acc_id = GetDlgItemInt(hDlg, IDC_EDIT3, 0, 0);
}

void ui_Reset(HWND hDlg)
{
	SendMessage(g_hCombo1, CB_RESETCONTENT, 0, 0);
	SendMessage(g_hListAccView, LB_RESETCONTENT, 0, 0);
	SendMessage(g_hCombo2, CB_RESETCONTENT, 0, 0);
	SetDlgItemText(hDlg, IDC_EDIT2, 0);
	SetDlgItemText(hDlg, IDC_EDIT3, 0);
	SetDlgItemText(hDlg, IDC_EDIT4, 0);
	SetDlgItemText(hDlg, IDC_EDIT5, 0);
	SetDlgItemText(hDlg, IDC_EDIT6, 0);
	ListView_DeleteAllItems(g_hListIOview);
}
