//skeleton code
#include <Windows.h>
#include <tchar.h>


DWORD WINAPI ThreadFunc1(LPVOID temp)
{
	HDC hdc;
	BYTE Blue = 0;
	HBRUSH hBrush, hOldBrush;

	HWND h = (HWND)temp;

	hdc = GetDC(h);
	while (1)
	{
		Blue++;
		Sleep(1);
		hBrush = CreateSolidBrush(RGB(0, 0, Blue));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 100, 100, 300, 400);
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
	}
	ReleaseDC(h, hdc);
}


LRESULT OnCreate(HWND hwnd, WPARAM wPama, LPARAM)
{
	return 0;
}
LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM)
{
	PostQuitMessage(0);
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hThread;
	static DWORD ThreadID;
	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		hThread = CreateThread(NULL, 0, ThreadFunc1, hwnd, 0, &ThreadID);
		CloseHandle(hThread);
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);
		Ellipse(hdc, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam) + 20, HIWORD(lParam) + 20);
		ReleaseDC(hwnd, hdc);

		return 0;
	}
	case WM_CREATE:            return OnCreate(hwnd, wParam, lParam);
	case WM_DESTROY:         return OnDestroy(hwnd, wParam, lParam);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	//1.윈도우 클래스 만들기
	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;   //메시지 처리 함수
	wc.cbClsExtra = 0;   //예약(미리등록)
	wc.cbWndExtra = 0;   //예약(")
	wc.hInstance = hInst;   //자신의 인스턴스 등록
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//미리등록된
	wc.hCursor = LoadCursor(0, IDC_ARROW);   //미리등록된
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//미리등록된
	wc.lpszMenuName = 0;
	wc.lpszClassName = TEXT("FIRST");//등록키
	//2.레지스트리 등록
	RegisterClass(&wc);
	//3.윈도우 창 만들기
	HWND hwnd = CreateWindowEx(0, //Ws_EX_TOPMOST
		TEXT("FIRST"),         //클래스 명
		TEXT("Hello"),         //캡션바 내용
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,   //초기위치
		0, 0,                        //부모 윈도우 핸들, 메뉴 핸들
		hInst,                        //WinMain의 1번째 파라미터
		0);                           //생성인자
	 //4.윈도우 보여주기
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