//uifile.cpp
#include "std.h"

//전송파일명
extern char filename[260];
HWND g_hList;

void uifile_GetControlHandle(HWND hDlg)
{
	g_hList = GetDlgItem(hDlg, IDC_LIST1);
}

void uifile_GetFileDir(HWND hDlg, TCHAR *msg)
{
	OPENFILENAME OFN;		//#include <commdlg.h>

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hDlg;
	OFN.lpstrFilter = TEXT("모든 파일(*.*)\0*.*\0텍스트 파일(*.txt)\0*.txt\0");
	OFN.lpstrFile = msg;	//<==============
	OFN.nMaxFile = MAX_PATH;
	GetOpenFileName(&OFN);

}

void uifile_SetFileDir(HWND hDlg, TCHAR *msg)
{
	SetDlgItemText(hDlg, IDC_EDIT1, msg);
}

void uifile_SetFileName(HWND hDlg, TCHAR *msg)
{
	char *ptr;
	ptr = strrstr(msg, "\\");
	SetDlgItemText(hDlg, IDC_EDIT2, ptr);

	strcpy(filename, ptr);
}

void uifile_PrintIP(TCHAR *ip)
{
	SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)ip);
}

char *strrstr(const char *haystack, const char *needle)
{
	int  haystack_len;
	int  needle_len;
	char *ptr;
	haystack_len = strlen(haystack);
	needle_len = strlen(needle);
	if (needle_len == 0) {
		return (char *)haystack;
	}
	if (needle_len > haystack_len) {
		return NULL;
	}
	ptr = (char *)haystack + haystack_len - needle_len;
	while (1) {
		if (strncmp(ptr, needle, needle_len) == 0) {
			ptr++;
			return ptr;
		}
		if (ptr == haystack) {
			break;
		}
		ptr--;
	}
	return NULL;
}