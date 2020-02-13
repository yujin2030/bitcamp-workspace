//handler.cpp

#include "std.h"

extern vector<MEMBER> g_memberlist;

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();

	ui_GetControlHandle(hDlg);

	ui_InitListView(hDlg);

	return TRUE;
}

void OnIdCancel(HWND hDlg)
{
	EndDialog(hDlg, IDCANCEL);
}

void OnExit(HWND hDlg)
{
	EndDialog(hDlg, IDOK);
}

void OnInsert(HWND hDlg)
{
	MEMBER mem;
	BOOL b = ui_Insert(hDlg, &mem);
	if (b == FALSE)
	{
		MessageBox(NULL, TEXT("저장 취소"), TEXT("알림"), MB_OK);
		return;
	}

	//저장의 흐름
	g_memberlist.push_back(mem);

	ui_PrintAll(hDlg);
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL: OnIdCancel(hDlg);		break;
		//File >> Exit
	case ID_FILE_EXIT: OnExit(hDlg);		break;
		//Project >> Insert
	case ID_PROJECT_INSERT: OnInsert(hDlg); break;
	}
	return TRUE;
}