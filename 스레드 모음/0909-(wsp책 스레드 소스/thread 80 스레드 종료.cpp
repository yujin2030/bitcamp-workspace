//소스.cpp
#include <Windows.h>
#include <tchar.h>

static HWND hPrg;
static HANDLE hThread;

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM)
{
	hPrg = CreateWindow(PROGRESS_CLASS, TEXT(""),
		WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_SMOOTH,
		10, 10, 500, 30, hwnd, (HMENU)1, 0, 0);

	SendMessage(hPrg, PBM_SETRANGE32, 0, 1000);
	SendMessage(hPrg, PBM_SETPOS, 0, 0);

	return 0;
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM)
{
	CloseHandle(hThread);
	PostQuitMessage(0);
	return 0;
}

DWORD WINAPI foo(void* p)
{
	HWND hPrg = (HWND)p;
	for (int i = 0; i < 1000; i++)
	{
		SendMessage(hPrg, PBM_SETPOS, i, 0);       //프로그래스 전진
		for (int k = 0; k < 5000000; ++k);

	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_CREATE:                             return OnCreate(hwnd, wParam, lParam);
	case WM_DESTROY:                           return OnDestroy(hwnd, wParam, lParam);
	case WM_LBUTTONDOWN:
	   {     		
		      DWORD tid;

	           hThread = CreateThread(0, 0,
		       foo, (void*)hPrg,  //스레드로 실행할 함수,인자
				   0,        //CREATE_SUSPENDED
		       &tid);
	    }
	   return 0;

	case WM_RBUTTONDOWN:
	   {
		DWORD code;

		GetExitCodeThread(hThread, &code);    //종료조사
		     if (code == STILL_ACTIVE)
		     {
		    	TerminateThread(hThread, 100);     //강제종료
		    	CloseHandle(hThread);
		     }
			

	   }
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
