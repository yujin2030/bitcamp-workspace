//start.cpp
#include "std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:		return OnInitDialog(hDlg, wParam, lParam);
	case WM_COMMAND:		return OnCommand(hDlg, wParam, lParam);
	}
	return FALSE;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR lpCmdLine, int nShowCmd)
{
	AllocConsole(); // console â ����

	freopen("CONOUT$",   // console ��
		"wt",        // text write ����
		stdout);	  // stdout �� ����..


	UINT ret = DialogBox(hInst,
		MAKEINTRESOURCE(IDD_DIALOG1),
		0, DlgProc);

	return 0;
}

