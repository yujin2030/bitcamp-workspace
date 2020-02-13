//ui.h

void ui_GetControlHandle(HWND hDlg);
void ui_InitListView(HWND hDlg);
void ui_SetAddress(HWND hDlg, TCHAR* ip, int port);

void ui_GetAddress(HWND hDlg, TCHAR* ip, int *port);
void ui_GetInsertData(HWND hDlg, TCHAR* id, TCHAR* pw, TCHAR* name, TCHAR* phone, int *age);
void ui_GetName(HWND hDlg, TCHAR* name); //Select, Delete
void ui_GetUpdate(HWND hDlg, TCHAR*name, TCHAR* phone, int* age);

void ui_SetButtonEnable(BOOL b1, BOOL b2, BOOL b3, BOOL b4, BOOL b5, BOOL b6);

void ui_SetInfoData(INSERT *data);