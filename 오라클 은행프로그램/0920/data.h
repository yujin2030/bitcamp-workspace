#pragma once

typedef struct tagCUSINFO		//고객ID, 이름
{
	int id;
	TCHAR name[50];

}CUSINFO;

typedef struct tagACCINFO		//계좌ID, 계좌잔액, 거래횟수
{
	int acc_id;
	int acc_balance;
	TCHAR opendate[50];

}ACCINFO;

typedef struct tagIO	//입출금구조체
{
	int io_id;
	int ac_id;
	int deposit;
	int withdrawl;
	int curmoney;
	TCHAR actdate[20];
}IOINFO;