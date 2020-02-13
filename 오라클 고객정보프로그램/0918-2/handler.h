//handler.h

BOOL  OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL  OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnDBConnect(HWND hDlg);
void OnDBDConnect(HWND hDlg);
//DDL=========================================================
void OnCreateTeamTable(HWND hDlg);
void OnDropTeamTable(HWND hDlg);
void OnCreateMemberTable(HWND hDlg);
void OnDropMemberTable(HWND hDlg);
void OnCreateSequence(HWND hDlg);
void OnDropSequence(HWND hDlg);
//==========================================================
void OnShowList(HWND hDlg);
void OnInsertTeam(HWND hDlg);
void OnDeleteTeam(HWND hDlg);
void OnUpdateTeam(HWND hDlg);
void OnSelectTeam(HWND hDlg);

void OnCancel(HWND hDlg);


//void OnPrint(HWND hDlg);
//
//void GetProcessList(HWND hDlg);