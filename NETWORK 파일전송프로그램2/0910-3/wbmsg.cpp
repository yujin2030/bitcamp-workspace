//wbmsg.cpp

#include "std.h"

void uimsg_GetMessage(HWND hDlg, TCHAR*msg, int size)
{
	GetDlgItemText(hDlg, IDC_EDIT3, msg, size);
}

void uimsg_ClearEditMsg(HWND hDlg)
{
	SetDlgItemText(hDlg, IDC_EDIT3, TEXT(""));
}