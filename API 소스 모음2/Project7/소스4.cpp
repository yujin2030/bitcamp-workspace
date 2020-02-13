//스켈레톤 코드 - 메시지 핸들러 함수
#include <windows.h>
#include <tchar.h>

//=================================================================

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM IParam)
{
	switch (msg){
		{ case WM_PAINT:

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			HBRUSH brush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
			HBRUSH old = (HBRUSH)SelectObject(hdc, brush);
			Rectangle(hdc, 10, 10, 100, 100);
			DeleteObject(SelectObject(hdc, old));
			EndPaint(hwnd, &ps);
			return 0; }
	
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
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;

}