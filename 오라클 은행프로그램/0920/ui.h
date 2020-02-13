#pragma once


void ui_GetHandle(HWND hDlg);

void ui_ComboCustSet(vector<CUSINFO> *cuslist, int size);
void ui_GetCustId(HWND hDlg, int *cust_id);
void ui_SetNameIntoEdit(HWND hDlg,vector<CUSINFO> *cusnamelist, int size);
void ui_GetAccId(HWND hDlg, int *acc_id);
void ui_SetAccIntoList(HWND hDlg, vector<ACCINFO> *acclist, int size);
void ui_SetAccInfoEdit(HWND hDlg, vector<ACCINFO> *acclist, int size);

void ui_Init_IO_ListView(HWND hDlg);


void ui_IO_ListPrint(vector<IOINFO> *IOINFOLIST, int size);
void List_IO_print(IOINFO info, int idx);
void ui_InitIoCombo(HWND hDlg);
void ui_GetMoney(HWND hDlg, int *money);
void ui_Get_De_Wi(HWND hDlg, TCHAR *De_Wi);
void ui_GetAccFromEdit(HWND hDlg, int *acc_id);
void ui_Reset(HWND hDlg);
