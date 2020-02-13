//handler.h

void logmessage(int flag, const char *msg);
void recvmessage(char *msg, int size);

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnIdCancel(HWND hDlg);
void OnConnect(HWND hDlg);
void OnDisConnect(HWND hDlg);
void OnInsert(HWND hDlg);
void OnSelect(HWND hDlg);
void OnUpdate(HWND hDlg);
void OnDelete(HWND hDlg);
