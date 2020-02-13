//uipaint.cpp
#include "std.h"

HWND g_hCombo, g_hColor;
HWND g_hDlg;

void uipaint_GetHandle(HWND hDlg)
{
	g_hDlg = hDlg;
	g_hCombo = GetDlgItem(hDlg, IDC_COMBO1);
	g_hColor = GetDlgItem(hDlg, IDC_STATIC1);
}

void uipaint_InitCombo(HWND hDlg)
{
	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("»¡°­"));
	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("³ì»ö"));
	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("ÆÄ¶û"));
}

void uipaint_Drawing(HWND hDlg, POINTS pt)
{
	HDC hdc = GetDC(hDlg);

	HBRUSH brush = CreateSolidBrush(getColor(hDlg));
	HBRUSH oldb = (HBRUSH)SelectObject(hdc, brush);

	Rectangle(hdc, pt.x, pt.y, pt.x + 25, pt.y + 25);

	DeleteObject(SelectObject(hdc, oldb));
	ReleaseDC(hDlg, hdc);
}

void uipaint_PrintPoint(HWND hDlg, POINTS pt)
{
	SetDlgItemInt(hDlg, IDC_EDIT5, pt.x, 0);
	SetDlgItemInt(hDlg, IDC_EDIT6, pt.y, 0);
}

void uipaint_DrawColor(HWND hDlg)
{
	COLORREF color = getColor(hDlg);
	HDC hdc = GetDC(g_hColor);
	RECT rc;
	GetClientRect(g_hColor, &rc);
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(hdc, &rc, brush);
	ReleaseDC(g_hColor, hdc);
}

COLORREF getColor(HWND hDlg)
{
	COLORREF color;
	int sel = SendMessage(g_hCombo, CB_GETCURSEL, 0, 0);
	if (sel == 0)
		color = RGB(255, 0, 0);
	else if (sel == 1)
		color = RGB(0, 255, 0);
	else if (sel == 2)
		color = RGB(0, 0, 255);
	else
		color = RGB(255, 255, 255);

	return color;
}

void uipaint_Draw(COLORREF color, POINTS pt)
{
	HDC hdc = GetDC(g_hDlg);

	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oldb = (HBRUSH)SelectObject(hdc, brush);

	Rectangle(hdc, pt.x, pt.y, pt.x + 25, pt.y + 25);

	DeleteObject(SelectObject(hdc, oldb));
	ReleaseDC(g_hDlg, hdc);
}

void uipaint_InfoPrint(COLORREF color, POINTS pt)
{
	SetDlgItemInt(g_hDlg, IDC_EDIT5, pt.x, 0);
	SetDlgItemInt(g_hDlg, IDC_EDIT6, pt.y, 0);

	if (color == RGB(255, 0, 0))
		SendMessage(g_hCombo, CB_SETCURSEL, 0, 0);
	else if (color == RGB(0, 255, 0))
		SendMessage(g_hCombo, CB_SETCURSEL, 1, 0);
	else if (color == RGB(0, 0, 255))
		SendMessage(g_hCombo, CB_SETCURSEL, 2, 0);
	else
		SendMessage(g_hCombo, CB_SETCURSEL, 0, 0);

	HDC hdc = GetDC(g_hColor);
	RECT rc;
	GetClientRect(g_hColor, &rc);
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(hdc, &rc, brush);
	ReleaseDC(g_hColor, hdc);
}