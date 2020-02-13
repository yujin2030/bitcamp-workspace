#include <windows.h>
#include <tchar.h>

//1.Ÿ�� ����
typedef struct tagSHAPE
{
	int type;        //1:R, 2:E
	int penwidth;    //1, 3, 5
	COLORREF color;  //R,G,B
	int  size;       //20,40,60
	POINT pt;        //����
}SHAPE;

//2. �ٽ� ���� ����
SHAPE g_shape;
POINT g_curpoint;

//3. ������ �ʱ�ȭ
LRESULT OnMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT pt = { LOWORD(lParam), HIWORD(lParam) };

	g_curpoint = pt;
	RECT rc = { 0,0,200,30 };
	InvalidateRect(hwnd, &rc, TRUE); //�����ǹ�ȿȭ(�ڵ鰪, ����, ����� ������ ����)

	return 0;
}

LRESULT OnButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT pt = { LOWORD(lParam), HIWORD(lParam) };

	g_shape.pt = pt;

	InvalidateRect(hwnd, 0, TRUE); //�����ǹ�ȿȭ(�ڵ鰪, ����, ����� ������ ����)

	return 0;
}

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM)
{
	g_shape.color = RGB(255, 0, 0);
	g_shape.penwidth = 1;
	g_shape.pt.x = 200;
	g_shape.pt.y = 200;
	g_shape.size = 20;
	g_shape.type = 1;

	g_curpoint.x = 0;
	g_curpoint.y = 0;
	return 0;
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM)
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	//====================�������=============================
	HPEN pen = CreatePen(PS_SOLID, g_shape.penwidth, RGB(0, 0, 0));
	HPEN old = (HPEN)SelectObject(hdc, pen);

	HBRUSH brush = CreateSolidBrush(g_shape.color);
	HBRUSH oldb = (HBRUSH)SelectObject(hdc, brush);

	if (g_shape.type == 1)
	{
		Rectangle(hdc, g_shape.pt.x, g_shape.pt.y,
			g_shape.pt.x + g_shape.size,
			g_shape.pt.y + g_shape.size);
	}
	else if (g_shape.type == 2)
	{
		Ellipse(hdc, g_shape.pt.x, g_shape.pt.y,
			g_shape.pt.x + g_shape.size,
			g_shape.pt.y + g_shape.size);
	}
	DeleteObject(SelectObject(hdc, old));
	DeleteObject(SelectObject(hdc, oldb));
	//=================================================================

	//=================��ǥ ��� ==================================
	TCHAR arr[20];
	wsprintf(arr, TEXT("%05d:%05d"),
		g_curpoint.x, g_curpoint.y);
	TextOut(hdc, 0, 0, arr, _tcslen(arr));
	//============================================================
	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT OnKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//1.����Ű ��, �ٿ��� �̿��ؼ� ũ�⺯��
	//2,R, E ���� ����
	switch (wParam)
	{
	case VK_UP:      g_shape.size += 10; break;
	case VK_DOWN:   g_shape.size -= 10; break;
	case 'R':      g_shape.type = 1;   break;
	case 'E':      g_shape.type = 2;   break;
	case VK_F1:      g_shape.color = RGB(255, 0, 0); break;
	case VK_F2:      g_shape.color = RGB(0, 255, 0); break;
	case VK_F3:      g_shape.color = RGB(0, 0, 255); break;
	}

	//1.���� ���� ��)����� + R
	/*if (wparam == 'r' && (getkeystate(vk_control) && 0xff00))
	{

	}*/

	InvalidateRect(hwnd, 0, TRUE);
	return 0;
}

LRESULT OnChar(HWND hwnd, WPARAM wParam, LPARAM lParam)
{


	InvalidateRect(hwnd, 0, TRUE);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM IParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:      return OnMouseMove(hwnd, wParam, IParam);
	case WM_CHAR:         return OnChar(hwnd, wParam, IParam);
	case WM_KEYDOWN:      return OnKeyDown(hwnd, wParam, IParam);
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