//���̷��� �ڵ� - �޽��� �ڵ鷯 �Լ�
#include <windows.h>
#include <tchar.h>

//===========================�޽��� �ڵ鷯 �Լ�====================
//�޽��� �߻��� �޽��� ó�� �Լ� , �Լ��� �̸��� �Ϲ��� ���
//�̸� : OnXXXX

//p.81

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM IParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);
		Rectangle(hdc, 120, 10, 210, 100);
		ReleaseDC(hwnd, hdc);
	}
	return 0;

	case WM_RBUTTONDOWN:
	{
		RECT r = { 120,10,210,100 };
		InvalidateRect(hwnd, &r, TRUE);
	}
	return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc, 10, 10, 100, 100);
		EndPaint(hwnd, &ps);
	}
	return 0;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, IParam);
	}
}

//