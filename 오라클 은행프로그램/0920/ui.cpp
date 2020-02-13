#include "std.h"

HWND g_hCombo1;
HWND g_hCombo2;
HWND g_hListIOview;
HWND g_hListAccView;

void ui_GetHandle(HWND hDlg)		//고객ID정보 콤보박스 핸들얻기
{
	g_hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
	g_hCombo2 = GetDlgItem(hDlg, IDC_COMBO2);
	g_hListAccView = GetDlgItem(hDlg, IDC_LIST2);
}

void ui_ComboCustSet(vector<CUSINFO> *cusinfolist, int size)		//고객ID정보 콤보박스에 전부 출력
{
	for (int i = 0; i < size; i++)
	{
		CUSINFO cust_info = (*cusinfolist)[i];
		TCHAR temp[20];
		wsprintf(temp, TEXT("%d"), (*cusinfolist)[i].id);
		SendMessage(g_hCombo1, CB_ADDSTRING, 0, (LPARAM)temp);
	}
}

void ui_GetCustId(HWND hDlg, int *cust_id)		//선택된 고객회원ID 콤보박스 셀값가져오기
{
	TCHAR combotext[20];
	int c_id;

	int nGetSel = SendMessage(g_hCombo1, CB_GETCURSEL, 0, 0);
	SendMessage(g_hCombo1, CB_GETLBTEXT, nGetSel, (LPARAM)combotext);
	c_id = _ttoi(combotext);	//문자열을 정수로 변환

	*cust_id = c_id;

	/**cust_id = GetDlgItemInt(hDlg, IDC_COMBO1, 0, 0);*/
}

void ui_SetNameIntoEdit(HWND hDlg,vector<CUSINFO> *cusnamelist, int size)		//고객이름 출력하기
{
	for (int i = 0; i < size; i++)
	{
		CUSINFO cust_name = (*cusnamelist)[i];

		TCHAR temp[50];
		wsprintf(temp, TEXT("%s"), (*cusnamelist)[i].name);
		SetDlgItemText(hDlg, IDC_EDIT2, temp);
	}
}


void ui_GetAccId(HWND hDlg, int *acc_id)		//선택된 계좌번호 리스트박스 셀값가져오기
{
	TCHAR listtext[20];
	int acid;

	int nGetSel = SendMessage(g_hListAccView, LB_GETCURSEL, 0, 0);
	SendMessage(g_hListAccView, LB_GETTEXT, nGetSel, (LPARAM)listtext);
	acid = _ttoi(listtext);	//문자열을 정수로 변환

	*acc_id = acid;

	/**cust_id = GetDlgItemInt(hDlg, IDC_COMBO1, 0, 0);*/
}


void ui_SetAccIntoList(HWND hDlg,vector<ACCINFO> *acclist, int size)	//리스트박스에 계좌번호 출력
{
	for (int i = 0; i < size; i++)
	{
		ACCINFO acc = (*acclist)[i];

		TCHAR temp[50];
		wsprintf(temp, TEXT("%d"), (*acclist)[i].acc_id);	//형이 달라도 액세스 위반; 조심
		SendMessage(g_hListAccView, LB_ADDSTRING, 0, (LPARAM)temp);
	}
}

void ui_SetAccInfoEdit(HWND hDlg, vector<ACCINFO> *acclist, int size)	//각 에디트에 계좌정보 출력
{
	for (int i = 0; i < size; i++)
	{
		ACCINFO acc = (*acclist)[i];

		TCHAR id[50];
		wsprintf(id, TEXT("%d"), (*acclist)[i].acc_id);	//형이 달라도 액세스 위반; 조심
		SetDlgItemText(hDlg, IDC_EDIT3, id);

		TCHAR bal[50];
		wsprintf(bal, TEXT("%d"), (*acclist)[i].acc_balance);	//형이 달라도 액세스 위반; 조심
		SetDlgItemText(hDlg, IDC_EDIT4, bal);

		TCHAR date[50];
		wsprintf(date, TEXT("%s"), (*acclist)[i].opendate);	//형이 달라도 액세스 위반; 조심
		SetDlgItemText(hDlg, IDC_EDIT5, date);
	}
}

void ui_Init_IO_ListView(HWND hDlg)		//리스트 초기화
{
	g_hListIOview = GetDlgItem(hDlg, IDC_LIST1);
	LVCOLUMN COL;

	// 헤더를 추가한다.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPWSTR)TEXT("입출금ID");				// 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("계좌번호");			// 두 번째 헤더
	COL.iSubItem = 1;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("입금금액");			// 세 번째 헤더
	COL.iSubItem = 2;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("출금금액");			// 네 번째 헤더
	COL.iSubItem = 3;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("현재금액");			// 다섯 번째 헤더
	COL.iSubItem = 4;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	COL.pszText = (LPWSTR)TEXT("거래일시");			// 여섯 번째 헤더
	COL.iSubItem = 5;
	SendMessage(g_hListIOview, LVM_INSERTCOLUMN, 5, (LPARAM)&COL);

}


void ui_IO_ListPrint(vector<IOINFO> *IOINFOLIST, int size)	//리스트출력함수호출하는 함수
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



void List_IO_print(IOINFO info, int idx)		//리스트 에 정보넣어서 출력
{
	LVITEM LI;

	// 텍스트와 이미지를 가진 아이템들을 등록한다.
	LI.mask = LVIF_TEXT;

	LI.iItem = idx;
	LI.iSubItem = 0;
	TCHAR buf[20];
	wsprintf(buf, TEXT("%d"), info.io_id);
	LI.pszText = buf;			// 첫 번째 아이템
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

void ui_InitIoCombo(HWND hDlg)			//입/출금 콤보박스 초기화
{
	SendMessage(g_hCombo2, CB_ADDSTRING, 0, (LPARAM)TEXT("입금"));
	SendMessage(g_hCombo2, CB_ADDSTRING, 0, (LPARAM)TEXT("출금"));
}

void ui_GetMoney(HWND hDlg, int *money)
{
	*money = GetDlgItemInt(hDlg, IDC_EDIT6, 0, 0);
}

void ui_Get_De_Wi(HWND hDlg, TCHAR *De_Wi)		//선택된 고객회원ID 콤보박스 셀값가져오기
{
	TCHAR combo2text[20];

	int nGetSel = SendMessage(g_hCombo1, CB_GETCURSEL, 0, 0);
	SendMessage(g_hCombo1, CB_GETLBTEXT, nGetSel, (LPARAM)combo2text);

	De_Wi = combo2text;

	/**cust_id = GetDlgItemInt(hDlg, IDC_COMBO1, 0, 0);*/
}

void ui_GetAccFromEdit(HWND hDlg, int *acc_id)	//게좌정보를 에디트로부터
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
