//uipaint.h

void uipaint_GetHandle(HWND hDlg);
void uipaint_InitCombo(HWND hDlg);
void uipaint_Drawing(HWND hDlg, POINTS pt);
void uipaint_PrintPoint(HWND hDlg, POINTS pt);
void uipaint_DrawColor(HWND hDlg);

COLORREF getColor(HWND hDlg);

//���� -> Ŭ���̾�Ʈ 
void uipaint_Draw(COLORREF color, POINTS pt);
void uipaint_InfoPrint(COLORREF color, POINTS pt);