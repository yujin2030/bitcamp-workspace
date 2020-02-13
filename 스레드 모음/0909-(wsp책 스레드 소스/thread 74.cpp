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
	//1.������ Ŭ���� �����
	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;   //�޽��� ó�� �Լ�
	wc.cbClsExtra = 0;   //����(�̸����)
	wc.cbWndExtra = 0;   //����(")
	wc.hInstance = hInst;   //�ڽ��� �ν��Ͻ� ���
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//�̸���ϵ�
	wc.hCursor = LoadCursor(0, IDC_ARROW);   //�̸���ϵ�
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//�̸���ϵ�
	wc.lpszMenuName = 0;
	wc.lpszClassName = TEXT("FIRST");//���Ű
	//2.������Ʈ�� ���
	RegisterClass(&wc);
	//3.������ â �����
	HWND hwnd = CreateWindowEx(0, //Ws_EX_TOPMOST
		TEXT("FIRST"),         //Ŭ���� ��
		TEXT("Hello"),         //ĸ�ǹ� ����
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,   //�ʱ���ġ
		0, 0,                        //�θ� ������ �ڵ�, �޴� �ڵ�
		hInst,                        //WinMain�� 1��° �Ķ����
		0);                           //��������
	 //4.������ �����ֱ�
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