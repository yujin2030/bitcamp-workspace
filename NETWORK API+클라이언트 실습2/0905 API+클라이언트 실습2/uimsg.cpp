//uimsg.cpp
#include "std.h"

#define UI_NAME  TEXT("000")

HWND g_hEditView;

void uimsg_GetHandle(HWND hDlg)
{
	g_hEditView = GetDlgItem(hDlg, IDC_EDIT2);
}

void uimsg_SetName(HWND hDlg)
{
	SetDlgItemText(hDlg, IDC_EDIT1, UI_NAME);
}

BOOL uimsg_GetMessage(HWND hDlg, TCHAR *msg)
{
	TCHAR name[20], temp[60];
	GetDlgItemText(hDlg, IDC_EDIT1, name, sizeof(TCHAR) * 20);
	GetDlgItemText(hDlg, IDC_EDIT3, temp, sizeof(TCHAR) * 100);

	if (_tcslen(name) == 0)
	{
		MessageBox(hDlg, TEXT("이름을 입력하세요"), TEXT("알림"), MB_OK);
		return FALSE;
	}

	if (_tcslen(msg) == 0)
	{
		return FALSE;
	}

	SYSTEMTIME sm;
	GetLocalTime(&sm);
	wsprintf(msg, (LPWSTR)TEXT("[%s]%s(%02d:%02d:%02d)"),
		name, temp, sm.wHour, sm.wMinute, sm.wSecond);

	return TRUE;
}

void uimsg_DisplayText(HWND hDlg, TCHAR* msg)
{
	DisplayText(g_hEditView, (LPWSTR)TEXT("%s\r\n"), msg);
}

// 에디트 컨트롤에 문자열 출력
void DisplayText(HWND hEdit, TCHAR *fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);

	TCHAR cbuf[512 + 256];
	vswprintf_s(cbuf, fmt, arg);

	int nLength = GetWindowTextLength(hEdit);
	SendMessage(hEdit, EM_SETSEL, nLength, nLength);
	SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)cbuf);

	va_end(arg);
}



void uimsg_Print(TCHAR *msg)
{
	DisplayText(g_hEditView, (LPWSTR)TEXT("%s\r\n"), msg);
}