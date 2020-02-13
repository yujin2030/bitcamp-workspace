//wbfile.h

struct FILE_INFO
{
	char FileName[260];
	int size;
};

DWORD WINAPI FileServer(void *p);
DWORD WINAPI RunThread(void *p);
void wbfile_Run();
