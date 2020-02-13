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
	AllocConsole(); // console 창 생성

	freopen("CONOUT$",   // console 을
		"wt",        // text write 모드로
		stdout);	  // stdout 과 연결..


	UINT ret = DialogBox(hInst,
		MAKEINTRESOURCE(IDD_DIALOG1),
		0, DlgProc);

	return 0;
}

