#pragma once


BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);


void OnDBConnect(HWND hDlg);

void OnDBDConnect(HWND hDlg);

void OnClose(HWND hDlg);


//void On_Cust_ComboBoxAction(HWND hDlg, WPARAM wParam);
void On_Cust_ComboBoxSelChange(HWND hDlg, WPARAM wParam);
void On_Acc_ListBoxSelChange(HWND hDlg, WPARAM wParam);
void On_Depo_With(HWND hDlg);