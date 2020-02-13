//ui.h

void ui_InitCombo(HWND hDlg);
void ui_GetTeamInsertInfo(HWND hDlg, int *id, TCHAR* name, TCHAR* phone, TCHAR* register_1, TCHAR* gender);
void ui_GetTeamDeleteInfo(HWND hDlg, int *id);
void ui_GetTeamUpdateInfo(HWND hDlg, int* id, TCHAR* name, TCHAR* phone,TCHAR* gender);
void ui_GetTeamSelectInfo(HWND hDlg, int* id, TCHAR* name, TCHAR* phone, TCHAR* register_1, TCHAR* gender);

void ui_InitTeamListView(HWND hDlg);
void ui_TeamListPrint(vector<custmg> *datalist, int size);
void ListTeamPrint(custmg info, int idx);


//void ui_GetHandle(HWND hDlg);
//void ui_SetListViewColumnHeader(HWND hDlg);
//void ui_processListPrint(vector<PROINFO> *datalist, int size);
//void ListPrint(PROINFO info, int idx);