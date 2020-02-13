//���̷��� �ڵ� - �޽��� �ڵ鷯 �Լ�
#include <windows.h>
#include <tchar.h>
#include <vector>
using namespace std;

vector<POINT> g_pointlist;

//===========================�޽��� �ڵ鷯 �Լ�====================
//�޽��� �߻��� �޽��� ó�� �Լ� , �Լ��� �̸��� �Ϲ��� ���
//�̸� : OnXXXX

//p.81
LRESULT OnButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT pt = { LOWORD(lParam), HIWORD(lParam) };

	g_pointlist.push_back(pt);

	InvalidateRect(hwnd, 0, FALSE);

	//===========================Ÿ��Ʋ�ٿ� ���� ������ ���===================
	TCHAR temp[20];
	wsprintf(temp, TEXT("���尳�� : %d"), g_pointlist.size());
	SetWindowText(hwnd, temp);

	return 0;
}

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN old = (HPEN)SelectObject(hdc, pen);

	for (int i = 0; i < (int)g_pointlist.size(); i++)
	{
		POINT pt = g_pointlist[i];
		Rectangle(hdc, pt.x, pt.y, pt.x + 100, pt.y + 100);
	
	}
	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM)
{
	return 0;
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM)
{
	PostQuitMessage(0);
	return 0;
}
//=================================================================

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM IParam)
{
	switch (msg)
	{
	case WM_PAINT:         return OnPaint(hwnd, wParam, IParam);
	case WM_LBUTTONDOWN:   return OnButtonDown(hwnd, wParam, IParam);
	case WM_CREATE:         return OnCreate(hwnd, wParam, IParam);
	case WM_DESTROY:      return OnDestroy(hwnd, wParam, IParam);
	}
	return DefWindowProc(hwnd, msg, wParam, IParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR IpCmdLine, int nShowCmd)
{
	//1. ������ Ŭ���� �����
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
	//2. ���(������Ʈ����)
	RegisterClass(&wc);
	//3. ������ â �����
	HWND hwnd = CreateWindowEx(0,
		TEXT("first"),
		TEXT("Hello"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		0, 0,
		hInst,
		0);
	//4. ������ �����ֱ�
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//5. �޽���
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;

}