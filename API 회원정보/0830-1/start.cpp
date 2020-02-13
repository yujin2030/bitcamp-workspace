//start.cpp
//대화상자 기반(page150)
#include "std.h"

vector<MEMBER> g_memberlist;

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
	UINT ret = DialogBox(hInst,
		MAKEINTRESOURCE(IDD_DIALOG1),
		0, DlgProc);

	return 0;
}

