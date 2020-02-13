//handler.h

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnLButtonDown(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnIdCancel(HWND hDlg);
void OnClickButton(HWND hDlg);
void OnComboBoxSelChange(HWND hDlg, WPARAM wParam);

//Ãß°¡ 
void logmessage(int flag, const char *msg);
void recvmessage(char *msg, int size);