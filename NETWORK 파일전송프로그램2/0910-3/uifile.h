//uifile.h

void uifile_GetControlHandle(HWND hDlg);
void uifile_GetFileDir(HWND hDlg, TCHAR *msg);
void uifile_SetFileDir(HWND hDlg, TCHAR *msg);
void uifile_SetFileName(HWND hDlg, TCHAR *msg);

void uifile_PrintIP(TCHAR *ip);

char *strrstr(const char *haystack, const char *needle);