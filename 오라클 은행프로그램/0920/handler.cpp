#include "std.h"

//extern vector<CUSINFO> g_cusinfolist;

BOOL  OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)		//다이아로그 초기화 함수
{
	ui_Init_IO_ListView(hDlg);
	InitCommonControls();
	ui_GetHandle(hDlg);
	ui_InitIoCombo(hDlg);


	/*ui_InitCombo(hDlg);*/

	return TRUE;
}


BOOL  OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)		//각 콘트롤별 명령함수
{
	switch (LOWORD(wParam))
	{
		//DB접속
	case IDC_BUTTON1:   OnDBConnect(hDlg);						return 0;
		//DB접속해제
	case IDC_BUTTON2:	OnDBDConnect(hDlg);						return 0;
	case IDC_COMBO1:	On_Cust_ComboBoxSelChange(hDlg,wParam);	return 0;
	case IDC_LIST2:		On_Acc_ListBoxSelChange(hDlg, wParam);	return 0;
	case IDC_BUTTON3:	On_Depo_With(hDlg);						return 0;
	//case IDC_BUTTON3:	OnAccPrintAll(hDlg, wParam);			return 0;
	//case IDC_BUTTON4:	OnAccPrint(hDlg, wParam);			return 0;
	//case IDC_BUTTON5:	OnAccInsert(hDlg);					return 0;
	//case IDC_BUTTON6:	OnAccDeleteAll(hDlg);					return 0;
	//case IDC_BUTTON7:	OnAccDelete(hDlg);					return 0;
	//	//case IDC_COMBO1:	OnComboBoxSelChange(hDlg, wParam);	return 0;

	case IDCANCEL:		OnClose(hDlg);						return 0;
	}

	return TRUE;
}


void OnDBConnect(HWND hDlg)		//데이터베이스 연결 함수
{
	if (wbdb_DBConnect() == TRUE)
		MessageBox(NULL, TEXT("DB접속 성공"), TEXT("알림"), MB_OK);
	else
		MessageBox(NULL, TEXT("DB접속 실패"), TEXT("알림"), MB_OK);

	vector<CUSINFO> cusinfolist;
	wbdb_GetCusSelectAll(&cusinfolist);
	ui_ComboCustSet(&cusinfolist, cusinfolist.size());

}

void OnDBDConnect(HWND hDlg)	//데이터베이스 연결해제 함수
{
	if (wbdb_DBDConnect() == TRUE)
	{
		MessageBox(NULL, TEXT("DB접속해제 성공"), TEXT("알림"), MB_OK);
		ui_Reset(hDlg);
	}

	else
		MessageBox(NULL, TEXT("DB접속해제 실패"), TEXT("알림"), MB_OK);


}

void OnClose(HWND hDlg)		//다이알로그 끝내기
{
	EndDialog(hDlg, IDCANCEL);
}




void On_Cust_ComboBoxSelChange(HWND hDlg, WPARAM wParam)	//고객ID 셀 바뀔때마다 고객이름 에디트 이름 갱신
{
	//int cust_id;
	//ui_GetCustId(hDlg, &cust_id);

	if (HIWORD(wParam) == CBN_SELENDOK) 
	{
	int cust_id;
	ui_GetCustId(hDlg, &cust_id);

	vector<CUSINFO> cusnamelist;			
	wbdb_GetCusName(&cusnamelist, cust_id);
	ui_SetNameIntoEdit(hDlg, &cusnamelist, cusnamelist.size());

	vector<ACCINFO> acclist;				//계좌번호 출력
	wbdb_GetAccList(&acclist, cust_id);
	ui_SetAccIntoList(hDlg, &acclist, acclist.size());
	}
}


void On_Acc_ListBoxSelChange(HWND hDlg, WPARAM wParam)		//리스트박스의 계좌번호 바뀔때마다 계좌정보갱신
{
	if (HIWORD(wParam) == LBN_DBLCLK)
	{
		int acc_id;
		ui_GetAccId(hDlg, &acc_id);

		vector<ACCINFO> acclist;				//계좌 정보 출력
		wbdb_GetAccInfo(&acclist, acc_id);
		ui_SetAccInfoEdit(hDlg, &acclist, acclist.size());

		vector<IOINFO> iolist;				//입출금정보 출력
		wbdb_GetIOSelectAll(&iolist, acc_id);
		ui_IO_ListPrint(&iolist, iolist.size());

	}
}

void On_Depo_With(HWND hDlg)
{
	int acc_id;
	int money;
	TCHAR De_Wi[20];

	TCHAR De[20];
	wsprintf(De, TEXT("입금"));
;
	TCHAR Wi[20];
	wsprintf(Wi, TEXT("출금"));

	ui_GetAccFromEdit(hDlg, &acc_id);
	ui_Get_De_Wi(hDlg, De_Wi);
	ui_GetMoney(hDlg, &money);

	if (_tcscmp(De_Wi, De) == TRUE)
	{
		wbdb_Deposit(acc_id,money);
	}

	else if (_tcscmp(De_Wi, Wi) == TRUE)
	{
		wbdb_Withdrawl(acc_id,money);
	}

}