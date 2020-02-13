//Skeleton 코드
#include <Windows.h>
#include <tchar.h>
#include "resource.h"

COLORREF g_color;

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM)
{
	g_color = RGB(255, 0, 0);

	return 0;
}

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	//====== 도형 출력 ===========================
	HBRUSH brush = CreateSolidBrush(g_color);
	HBRUSH oldb = (HBRUSH)SelectObject(hdc, brush);

	Rectangle(hdc, 10, 10, 100, 100);

	DeleteObject(SelectObject(hdc, oldb));
	//===============================================

	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT OnInitMenuPopup(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu = (HMENU)wParam;

	EnableMenuItem(hMenu, ID_40003,
		g_color == RGB(255, 0, 0) ? MF_GRAYED : MF_ENABLED);
	EnableMenuItem(hMenu, ID_40004,
		g_color == RGB(0, 255, 0) ? MF_GRAYED : MF_ENABLED);
	EnableMenuItem(hMenu, ID_40005,
		g_color == RGB(0, 0, 255) ? MF_GRAYED : MF_ENABLED);

	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case ID_40003: g_color = RGB(255, 0, 0); break;
	case ID_40004: g_color = RGB(0, 255, 0); break;
	case ID_40005: g_color = RGB(0, 0, 255); break;

	}

	InvalidateRect(hwnd, 0, FALSE);

	return 0;
}


LRESULT OnContextMenu(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu = GetMenu(hwnd);
	HMENU hSub = GetSubMenu(hMenu, 1);

	POINT pt = { LOWORD(lParam), HIWORD(lParam) };

	TrackPopupMenu(hSub, TPM_LEFTBUTTON, pt.x, pt.y,
		0, hwnd, 0);

	return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CONTEXTMENU:    return OnContextMenu(hwnd, wParam, lParam);
	case WM_COMMAND:		return OnCommand(hwnd, wParam, lParam);
	case WM_INITMENUPOPUP:  return OnInitMenuPopup(hwnd, wParam, lParam);
	case WM_CREATE:			return OnCreate(hwnd, wParam, lParam);
	case WM_PAINT:			return OnPaint(hwnd, wParam, lParam);
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = 0;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, //WS_EX_TOPMOST
		TEXT("first"), TEXT("Hello"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		0, 0,
		hInst, 0);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}