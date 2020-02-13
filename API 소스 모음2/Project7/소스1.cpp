#include <windows.h>
#include <tchar.h>

//사용자 정의 메세지
#define WM_MYMESSAGE  WM_USER + 100
#define WM_MYMESSAGE1  WM_USER + 200

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM IParam)
{
	switch (msg)
	{
	case WM_MYMESSAGE:
		SetWindowText(hwnd, TEXT("첫번째 메세지"));
		return 0;
	case WM_MYMESSAGE1:
		SetWindowText(hwnd, TEXT("두번째 메세지"));
		return 0;
	case WM_LBUTTONDOWN:
		//비큐 메세지          -
		SendMessage(hwnd, WM_MYMESSAGE, 0, 0);
		return 0;
	case WM_RBUTTONDOWN:
		//큐 메세지         -이 메세지를 큐에다가 넣어버리는것
		PostMessage(hwnd, WM_MYMESSAGE1, 0, 0);
		PostMessage(hwnd, WM_CLOSE, 0, 0);		
		return 0;
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, IParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR IpCmdLine, int nShowCmd)
{
	//1. 윈도우 클래스 만들기
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = 0;
	//2. 등록(레지스트리에)
	RegisterClass(&wc);
	//3. 윈도우 창 만들기
	HWND hwnd = CreateWindowEx(0,
		TEXT("first"),
		TEXT("Hello"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		0, 0,
		hInst,
		0);
	//4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//5. 메시지
	/*
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
	*/

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)                   break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			HDC hdc = GetDC(hwnd);         //바탕화면을 위한 DC 얻기
			SetPixel(hdc, rand() % 500, rand() % 400,
				//RGB(255, 25y h 625, 0));
			      RGB(rand() % 256, rand() % 256, rand() % 256));
			ReleaseDC(hwnd, hdc);

		}


	}
}