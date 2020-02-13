//Skeleton 코드
#include <Windows.h>
#include <tchar.h>

//사용자 정의 메시지
#define WM_MYMESSAGE  WM_USER + 100
#define WM_MYMESSAGE1 WM_USER + 200

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MYMESSAGE:
		SetWindowText(hwnd, TEXT("첫번째 메시지"));
		return 0;
	case WM_MYMESSAGE1:
		SetWindowText(hwnd, TEXT("두번째 메시지"));
		return 0;
	case WM_LBUTTONDOWN:
		//비큐 메시지 
		SendMessage(hwnd, WM_MYMESSAGE, 0, 0);
		return 0;
	case WM_RBUTTONDOWN:
		//큐 메시지 
		PostMessage(hwnd, WM_MYMESSAGE1, 0, 0);
		PostMessage(hwnd, WM_CLOSE, 0, 0);
		return 0;
	case WM_CREATE:
		return 0;
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
	wc.lpszMenuName = 0;
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