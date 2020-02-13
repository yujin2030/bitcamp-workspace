//handler.cpp
#include "std.h"

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();

	uifile_GetControlHandle(hDlg);

	wbserver_init();

	wbserver_start(7000);

	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL:		OnIdCancel(hDlg);		break;
	case IDC_BUTTON1:   OnFileSelect(hDlg);  break;
	case IDC_BUTTON2:   OnFileSend(hDlg); break;
	case IDC_BUTTON3:   OnPrintClear(hDlg); break;
	//case IDC_BUTTON4: OnSendMsg(hDlg); break;
	}
	return TRUE;
}

void OnIdCancel(HWND hDlg)
{
	EndDialog(hDlg, IDCANCEL);

	wbserver_exit();
}

void OnFileSelect(HWND hDlg)
{
	TCHAR filedir[MAX_PATH] = "";
	uifile_GetFileDir(hDlg, filedir);
	uifile_SetFileDir(hDlg, filedir);
	uifile_SetFileName(hDlg, filedir);

}

void OnFileSend(HWND hDlg)
{
	wbfile_Run();
}

void OnSendMsg(HWND hDlg)
{
	//1. 문자열 획득
	TCHAR msg[512];
	uimsg_GetMessage(hDlg, msg, sizeof(msg));

	//2. 전송
	sendAlldata(0, msg, _tcslen(msg));

	//3. 에디트초기화
	uimsg_ClearEditmsg(hDlg);
}