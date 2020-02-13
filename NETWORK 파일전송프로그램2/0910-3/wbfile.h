//wbfile.h

struct FILE_INFO
{
	char FileName[260]; // 전송할 파일 이름.
	int  size;			// 화일 크기
};

void wbfile_Run();

DWORD WINAPI RunThread(void *p);

DWORD WINAPI FileServer(void* p);
