#pragma once
#include <sql.h>
#include <sqlext.h>

BOOL wbdb_DBConnect();
BOOL wbdb_DBDConnect();
BOOL CommandSql(TCHAR *str);

BOOL wbdb_GetCusSelectAll(vector<CUSINFO> *cusinfolist);
BOOL wbdb_GetCusName(vector<CUSINFO> *cusnamelist, int cust_id);
BOOL wbdb_GetAccList(vector<ACCINFO> *acc_list, int cust_id);
BOOL wbdb_GetAccInfo(vector<ACCINFO> *accinfolist, int acc_id);

BOOL wbdb_GetIOSelectAll(vector<IOINFO>* IOINFOLIST, int acc_id);

BOOL wbdb_Deposit(int acc_id,int money);
BOOL wbdb_Withdrawl(int acc_id,int money);
BOOL wbdb_Refresh(int acc_id);