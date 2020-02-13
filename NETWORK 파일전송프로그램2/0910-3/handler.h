//handler.h

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnIdCancel(HWND hDlg);
void OnFileSelect(HWND hDlg);
void OnFileSend(HWND hDlg);
void OnSendMsg(HWND hDlg);
void OnPrintClear(HWND hDlg);




//void logmessage(int flag, const char *msg);
//void recvmessage(char *msg, int size);