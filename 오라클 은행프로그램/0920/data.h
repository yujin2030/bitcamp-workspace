#pragma once

typedef struct tagCUSINFO		//��ID, �̸�
{
	int id;
	TCHAR name[50];

}CUSINFO;

typedef struct tagACCINFO		//����ID, �����ܾ�, �ŷ�Ƚ��
{
	int acc_id;
	int acc_balance;
	TCHAR opendate[50];

}ACCINFO;

typedef struct tagIO	//����ݱ���ü
{
	int io_id;
	int ac_id;
	int deposit;
	int withdrawl;
	int curmoney;
	TCHAR actdate[20];
}IOINFO;