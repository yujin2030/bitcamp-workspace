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
			ResumeThread(hThread);            //스래드 재개
		else
			SuspendThread(hThread);            //스래드 중지

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

	//AllocConsole(); // console 창 생성

  //  freopen("CONOUT$",   // console 을
  //     "wt",        // text write 모드로
  //    stdout);     // stdout 과 연결..
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