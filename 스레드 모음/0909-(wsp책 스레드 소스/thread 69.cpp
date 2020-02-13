#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int Blue = 0;
	switch (msg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, 10, NULL);
		break;
	case WM_TIMER:
		Blue += 5;
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hwnd, &ps);
		HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, Blue));
		HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbrush);

		Rectangle(hdc, 100, 100, 400, 400);

		DeleteObject(SelectObject(hdc, hOld));

		EndPaint(hwnd, &ps);
	}
	return 0;

	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);
		POINTS pt = MAKEPOINTS(lParam);
		Rectangle(hdc, pt.x, pt.y, pt.x + 50, pt.y + 50);
		ReleaseDC(hwnd, hdc);
	}
	return 0;
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	//윈도우 클래스 생성
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = 0;

	//레지스트리 등록
	RegisterClass(&wc);

	//윈도우 창 생성
	HWND hwnd = CreateWindowEx(0,
		TEXT("first"),
		TEXT("Hello"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 0, 0, hInst, 0);

	//윈도우 화면 출력
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//메세지
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}