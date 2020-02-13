//Infoproc.cpp

#include "std.h"


BOOL OnInitDialog2(HWND hDlg,WPARAM wParam, LPARAM lParam)
{
	ui_GetControlHandle(hDlg);
	ui_InitListView(hDlg);      //자식창 출력

	return TRUE;
}

BOOL OnCommand2(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL:       EndDialog(hDlg, IDCANCEL);             break;
	case IDOK:       EndDialog(hDlg, IDOK);             break;

	}
	return TRUE;

	return FALSE;
}

BOOL CALLBACK InfoProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg)
	{
	case WM_INITDIALOG:		return OnInitDialog2(hDlg, wParam, lParam);
	case WM_COMMAND:		return OnCommand2(hDlg, wParam, lParam);
	}
	return FALSE;
}