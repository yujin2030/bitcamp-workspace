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
	UINT ret = DialogBox(hInst,
		MAKEINTRESOURCE(IDD_DIALOG1),
		0, DlgProc);
	
	HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
 
	return 0;
}