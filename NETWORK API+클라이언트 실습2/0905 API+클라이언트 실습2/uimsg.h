//uimsg.h
//

void uimsg_Print(TCHAR *msg);

void uimsg_GetHandle(HWND hDlg);

void uimsg_SetName(HWND hDlg);

BOOL uimsg_GetMessage(HWND hDlg, TCHAR *msg);

void uimsg_DisplayText(HWND hDlg, TCHAR* msg);

void DisplayText(HWND hEdit, TCHAR *fmt, ...);