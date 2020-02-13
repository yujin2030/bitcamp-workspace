//wbfile.cpp
#define _WINSOCK_DEPRECATED_NO_WARNINGS   
#include "std.h"

char filename[260]; // ������ ����

void wbfile_Run()
{
	CloseHandle(CreateThread(0, 0, RunThread, 0, 0, 0));
}

//���� �����ϰ� ���� ���� ���
DWORD WINAPI RunThread(void *p)
{
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		printf("Can't Initialize Socket !\n");
		return -1;
	}
	//--------------------------------------------
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		printf("Can't Bind\n");
		closesocket(s);
		return -1;
	}

	if (listen(s, 10) == -1)
	{
		printf("Can't Listen\n");
		closesocket(s);
		return -1;
	}

	while (1)
	{
		SOCKADDR_IN c_addr;
		int size = sizeof(c_addr);

		SOCKET c_s = accept(s, (SOCKADDR*)&c_addr, &size);

		//printf("Client ���� : %s\n", inet_ntoa(c_addr.sin_addr));
		uifile_PrintIP(inet_ntoa(c_addr.sin_addr));

		CloseHandle(CreateThread(0, 0, FileServer, (void*)c_s, 0, 0));
	}
	//--------------------------------------------
	closesocket(s);
	WSACleanup();
	return 1;
}

// ������ Client���� ������ �����Ѵ�.
DWORD WINAPI FileServer(void* p)
{
	SOCKET s = (SOCKET)p;

	// ������ ����Open
	HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Can't Open File\n");
		closesocket(s);
		return 0;
	}
	// ũ�⸦ ���ϰ� ȭ���� ������ �����Ѵ�.
	DWORD size1;
	DWORD size2 = GetFileSize(hFile, &size1);

	FILE_INFO fi;
	strcpy(fi.FileName, filename);
	fi.size = size2;

	send(s, (char*)&fi, sizeof(fi), 0);
	//-------------------------------------------------
	// ȭ�� ����
	int total = size2; // ������ ��ü ũ��
	int current = 0;   // ������ ũ��
	int nRead = 0;
	char buf[4096];    // 4k ����.

	while (total > current)
	{
		DWORD len;
		nRead = ReadFile(hFile, buf, 4096, &len, 0);

		if (len <= 0) break;

		int nSend = send(s, buf, len, 0);
		if (nSend <= 0) break;

		current += nSend;
	}
	if (total != current)	printf("���ۿ���\n");
	else					printf("���ۿϷ� \n");

	closesocket(s);
	CloseHandle(hFile);
	return 0;
}


