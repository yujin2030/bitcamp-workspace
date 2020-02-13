//handler.cpp

#include "std.h"

BOOL  OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	ui_InitTeamListView(hDlg);

	ui_InitCombo(hDlg);

	return TRUE;
}

BOOL  OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	//DB접속
	case IDC_BUTTON1:   OnDBConnect(hDlg);      return 0;
	//DB접속해제
	case IDC_BUTTON2:	OnDBDConnect(hDlg);		return 0;

	case IDC_BUTTON3:	OnShowList(hDlg);		return 0;

	case IDC_BUTTON4:   OnInsertTeam(hDlg);      return 0;

	case IDC_BUTTON5:   OnDeleteTeam(hDlg);      return 0;

	case IDC_BUTTON6:   OnUpdateTeam(hDlg);      return 0;

	case IDC_BUTTON7:   OnSelectTeam(hDlg);      return 0;
	//DDL문===================================================
	//Tean 테이블 생성
	//case IDC_BUTTON3:	OnCreateTeamTable(hDlg);	break;
	////Tean 테이블 삭제
	//case IDC_BUTTON4:	OnDropTeamTable(hDlg);		break;
	////Member 테이블 생성
	//case IDC_BUTTON5:	OnCreateMemberTable(hDlg);	break;
	////Member 테이블 삭제
	//case IDC_BUTTON6:	OnDropMemberTable(hDlg);	break;
	////시퀀스 생성
	//case IDC_BUTTON7:	OnCreateSequence(hDlg);		break;
	////시퀀스 삭제
	//case IDC_BUTTON8:	OnDropSequence(hDlg);		break;
	////========================================================
	////Team등록
	//case IDC_BUTTON9:	OnInsertTeam(hDlg);		return 0;
	case IDCANCEL:		OnCancel(hDlg);			return 0;
	}
	return TRUE;
}

void OnDBConnect(HWND hDlg)
{
	if (wbdb_DBConnect() == TRUE)
		MessageBox(NULL, TEXT("DB접속 성공"), TEXT("알림"), MB_OK);
	else
		MessageBox(NULL, TEXT("DB접속 실패"), TEXT("알림"), MB_OK);

}

void OnDBDConnect(HWND hDlg)
{
	if (wbdb_DBDConnect() == TRUE)
		MessageBox(NULL, TEXT("DB접속해제 성공"), TEXT("알림"), MB_OK);
	else
		MessageBox(NULL, TEXT("DB접속해제 실패"), TEXT("알림"), MB_OK);
}

//DDL=========================================================
void OnCreateTeamTable(HWND hDlg)
{
	if (wbdb_CreateTeamTable() == TRUE)
		MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	else
		MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
}

void OnDropTeamTable(HWND hDlg)
{
	if (wbdb_DropTeamTable() == TRUE)
		MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	else
		MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
}

void OnCreateMemberTable(HWND hDlg)
{
	if (wbdb_CreateMemberTable() == TRUE)
		MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	else
		MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
}

void OnDropMemberTable(HWND hDlg)
{
	if (wbdb_DropMemberTable() == TRUE)
		MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	else
		MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
}

void OnCreateSequence(HWND hDlg)
{
	if (wbdb_CreateSequence() == TRUE)
		MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	else
		MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
}

void OnDropSequence(HWND hDlg)
{
	if (wbdb_DropSequence() == TRUE)
		MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	else
		MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
}
//==========================================================

void OnShowList(HWND hDlg)
{
	vector<custmg> custmglist;
	wbdb_GetTeamSelectAll(&custmglist);
	ui_TeamListPrint(&custmglist, custmglist.size());
}

void OnInsertTeam(HWND hDlg)
{
	int   id;
	TCHAR name[10];
	TCHAR phone[20];
	TCHAR register_1[20];
	TCHAR gender[2];

	ui_GetTeamInsertInfo(hDlg, &id, name, phone,register_1,gender);
	if (wbdb_InsertTeam(name, phone,gender) == TRUE)
	{
		vector<custmg> custmglist;
		wbdb_GetTeamSelectAll(&custmglist);
		ui_TeamListPrint(&custmglist, custmglist.size());
	}
	else
		MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
}

void OnDeleteTeam(HWND hDlg)
{
	int   id;

	ui_GetTeamDeleteInfo(hDlg, &id);
	if (wbdb_DeleteTeam(id) == TRUE)
	{
		vector<custmg> custmglist;
		wbdb_GetTeamSelectAll(&custmglist);
		ui_TeamListPrint(&custmglist, custmglist.size());
	}
	else
		MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);

}

void OnUpdateTeam(HWND hDlg)
{
	int   id;
	TCHAR name[10];
	TCHAR phone[20];
	TCHAR gender[2];

	ui_GetTeamUpdateInfo(hDlg, &id, name, phone, gender);
	if (wbdb_UpdateTeam(id, name, phone, gender) == TRUE)
	{
		vector<custmg> custmglist;
		wbdb_GetTeamSelectAll(&custmglist);
		ui_TeamListPrint(&custmglist, custmglist.size());
	}
	else
		MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
	//OnShowList(hDlg);
}

void OnSelectTeam(HWND hDlg)
{
	int   id;
	TCHAR name[10];
	TCHAR phone[20];
	TCHAR register_1[20];
	TCHAR gender[2];

	ui_GetTeamSelectInfo(hDlg, &id, name, phone, register_1, gender);

    vector<custmg> custmglist1;

	wbdb_GetTeamSelectData(&custmglist1,id, name, phone, register_1, gender);
	ui_TeamListPrint(&custmglist1, custmglist1.size());

}

void OnCancel(HWND hDlg)
{
	EndDialog(hDlg, IDCANCEL);

}

/*
void OnPrint(HWND hDlg)
{
	GetProcessList(hDlg);
}

void GetProcessList(HWND hDlg)
{
	//프로세스 리스트 출력
	vector<PROINFO> datalist;
	int size;
	pro_getProcessList(&datalist, &size);
	coll_proListSave(&datalist, size);
	ui_processListPrint(&datalist, size);
}
*/