//skeleton code
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>

DWORD WINAPI foo(void* p)
{
	HWND hPrg = (HWND)p;
	for (int i = 0; i < 1000; ++i)
	{
		SendMessage(hPrg, PBM_SETPOS, i, 0);
		for (int k = 0; k < 5000000; ++k);
	}
	return 0;
}

LRESULT OnCreate(HWND hwnd, WPARAM wPama, LPARAM)
{
	return 0;
}

//LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM)
//{
//   
//}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hPrg;
	static HANDLE hThread;

	switch (msg) {
	case WM_CREATE:      hPrg = CreateWindow(PROGRESS_CLASS, TEXT(""),
		WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_SMOOTH,
		10, 10, 500, 30, hwnd, (HMENU)1, 0, 0);
		SendMessage(hPrg, PBM_SETRANGE32, 0, 1000);
		SendMessage(hPrg, PBM_SETPOS, 0, 0);
	
		return 0;

	case WM_LBUTTONDOWN:
	{	
		DWORD tid;

		hThread = CreateThread(0, 0,
			foo, (void*)hPrg, CREATE_SUSPENDED,
			&tid);
	}

	   return 0;

	case WM_RBUTTONDOWN:
	{
		static BOOL bRun = FALSE;

		bRun = !bRun;
		if (bRun)
			ResumeThread(hThread);            //������ �簳
		else
			SuspendThread(hThread);            //������ ����

	}
	   return 0;

	case WM_DESTROY:

		CloseHandle(hThread);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{

	//AllocConsole(); // console â ����

  //  freopen("CONOUT$",   // console ��
  //     "wt",        // text write ����
  //    stdout);     // stdout �� ����..
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