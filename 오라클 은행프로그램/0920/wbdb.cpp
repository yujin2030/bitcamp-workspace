//wbdb.cpp
#include "std.h"

#define DBNAME TEXT("wbdb")
#define ID	   TEXT("wb30")
#define PW		TEXT("1234")

SQLHSTMT hStmt;
SQLHENV hEnv;
SQLHDBC hDbc;

//static vector<CUSINFO> g_cusinfolist;

BOOL wbdb_DBConnect()		//데이터베이스 연결
{

	// 연결 설정을 위한 변수들
	SQLRETURN Ret;

	// 1, 환경 핸들을 할당하고 버전 속성을 설정한다.(p1741)
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
		return false;
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		return false;

	// 2. 연결 핸들을 할당하고 연결한다.
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
		return false;
	// 오라클 서버에 연결하기
	Ret = SQLConnect(hDbc, (SQLTCHAR *)DBNAME, SQL_NTS, (SQLTCHAR *)ID, SQL_NTS, (SQLTCHAR *)PW, SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
		return false;

	// 명령 핸들을 할당한다.
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS)
		return false;

	return true;
}

BOOL wbdb_DBDConnect()		//데이터베이스 연결해제
{
	// 뒷정리
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return TRUE;
}

BOOL CommandSql(TCHAR *str)		//데이터 베이스로 명령
{
	if (SQLExecDirect(hStmt, (SQLTCHAR *)str, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL wbdb_GetCusSelectAll(vector<CUSINFO>*cusinfolist)		//고객회원ID,이름 가져오기
{
	int cusinfo_id;
	SQLTCHAR cusinfo_name[50];
	SQLINTEGER lcusinfo_lid, lcusinfo_lname;

	SQLBindCol(hStmt, 1, SQL_C_ULONG, &cusinfo_id, 0, &lcusinfo_lid);
	SQLBindCol(hStmt, 2, SQL_C_WCHAR, cusinfo_name, sizeof(cusinfo_name), &lcusinfo_lname);
	


	TCHAR sql[256] = TEXT("select id,name from custmg");

	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		CUSINFO cuslist;

		cuslist.id = cusinfo_id;
		_tcscpy_s(cuslist.name, cusinfo_name);
	
		cusinfolist->push_back(cuslist);

	}

	return TRUE;
}

BOOL wbdb_GetCusName(vector<CUSINFO> *cusnamelist, int cust_id)		//고객이름 가져오기
{
	/*int cusinfo_id;*/
	SQLTCHAR cusinfo_name[50];
	SQLINTEGER /*lcusinfo_lid, */lcusinfo_lname;

	//SQLBindCol(hStmt, 1, SQL_C_ULONG, &cusinfo_id, 0, &lcusinfo_lid);
	SQLBindCol(hStmt, 2, SQL_C_WCHAR, cusinfo_name, sizeof(cusinfo_name), &lcusinfo_lname);

	/*TCHAR sql[256] = TEXT("select id,name from custmg where id = ");*/

	TCHAR sql[256];
	wsprintf(sql, TEXT("select id,name from custmg where id = %d"), cust_id);

	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		CUSINFO namelist;

	/*	namelist.id = cusinfo_id;*/
		_tcscpy_s(namelist.name, cusinfo_name);
		
		cusnamelist->push_back(namelist);

	}

	return TRUE;
}

BOOL wbdb_GetAccList(vector<ACCINFO> *acc_list, int cust_id)		//계좌번호 가져오기
{
	int accinfo_id, accinfo_bal, accinfo_usecount, accinfo_cusid;
	SQLTCHAR accinfo_date[50];
	SQLINTEGER laccinfo_id, laccinfo_bal, laccinfo_usecount, laccinfo_cusid, laccinfo_date;

	SQLBindCol(hStmt, 1, SQL_C_ULONG, &accinfo_id, 0, &laccinfo_id);
	SQLBindCol(hStmt, 2, SQL_C_ULONG, &accinfo_bal, 0, &laccinfo_bal);
	SQLBindCol(hStmt, 3, SQL_C_WCHAR, accinfo_date, sizeof(accinfo_date), &laccinfo_date);
	SQLBindCol(hStmt, 4, SQL_C_ULONG, &accinfo_usecount, 0, &laccinfo_usecount);
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &accinfo_cusid, 0, &laccinfo_cusid);


	TCHAR sql[256];
	wsprintf(sql, TEXT("select accountid from accountinfo where customerid = %d"), cust_id);		//명령에 따라 나는 오류는 무엇?

	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		ACCINFO acclist;

		acclist.acc_id = accinfo_id;
		//acclist.acc_balance = accinfo_bal;
		//_tcscpy_s(acclist.opendate, accinfo_date);

		acc_list->push_back(acclist);
	}

	return TRUE;
}

BOOL wbdb_GetAccInfo(vector<ACCINFO> *accinfolist, int acc_id)		//계좌번호를 토대로 계좌정보 가져오기
{
	int accinfo_id, accinfo_bal, accinfo_usecount, accinfo_cusid;
	SQLTCHAR accinfo_date[50];
	SQLINTEGER laccinfo_id, laccinfo_bal, laccinfo_usecount, laccinfo_cusid, laccinfo_date;

	SQLBindCol(hStmt, 1, SQL_C_ULONG, &accinfo_id, 0, &laccinfo_id);
	SQLBindCol(hStmt, 2, SQL_C_ULONG, &accinfo_bal, 0, &laccinfo_bal);
	SQLBindCol(hStmt, 3, SQL_C_WCHAR, accinfo_date, sizeof(accinfo_date), &laccinfo_date);
	SQLBindCol(hStmt, 4, SQL_C_ULONG, &accinfo_usecount, 0, &laccinfo_usecount);
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &accinfo_cusid, 0, &laccinfo_cusid);


	TCHAR sql[256];
	wsprintf(sql, TEXT("select accountid,accountbank,accountdate from accountinfo where accountid = %d"), acc_id);		//명령에 따라 나는 오류는 무엇?

	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		ACCINFO acclist;

		acclist.acc_id = accinfo_id;
		acclist.acc_balance = accinfo_bal;
		_tcscpy_s(acclist.opendate, accinfo_date);

		accinfolist->push_back(acclist);
	}

	return TRUE;
}


BOOL wbdb_GetIOSelectAll(vector<IOINFO>* IOINFOLIST,int acc_id)			//계좌번호 받아와 입출금정보 출력
{
	int ioinfo_id;
	int	ioinfo_ac_id;
	int ioinfo_deposit;
	int ioinfo_withdrawl;
	int ioinfo_curbal;
	SQLTCHAR ioinfo_actdate[50];

	SQLINTEGER lioinfo_id, lioinfo_ac_id, lioinfo_deposit, lioinfo_withdrawl, lioinfo_curbal, lioinfo_actdate;

	SQLBindCol(hStmt, 1, SQL_C_ULONG, &ioinfo_id, 0, &lioinfo_id);
	SQLBindCol(hStmt, 2, SQL_C_ULONG, &ioinfo_ac_id ,0, &lioinfo_ac_id);
	SQLBindCol(hStmt, 3, SQL_C_ULONG, &ioinfo_deposit,0, &lioinfo_deposit);
	SQLBindCol(hStmt, 4, SQL_C_ULONG, &ioinfo_withdrawl, 0, &lioinfo_withdrawl);
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &ioinfo_curbal, 0, &lioinfo_curbal);
	SQLBindCol(hStmt, 6, SQL_C_WCHAR, ioinfo_actdate, sizeof(ioinfo_actdate), &lioinfo_actdate);


	TCHAR sql[256];
	wsprintf(sql,TEXT("select * from accountio where ac_id = %d order by ioid asc"),acc_id);

	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		IOINFO iolist;
		iolist.io_id = ioinfo_id;
		iolist.ac_id = ioinfo_ac_id;
		iolist.deposit = ioinfo_deposit;
		iolist.withdrawl = ioinfo_withdrawl;
		iolist.curmoney = ioinfo_curbal;
		_tcscpy_s(iolist.actdate, ioinfo_actdate);
		IOINFOLIST->push_back(iolist);

	}
	return TRUE;
}

BOOL wbdb_Deposit(int acc_id,int money)		//입금 기능
{
	TCHAR str[1024];
	wsprintf(str, TEXT("insert into accountio(ioid,ac_id,inmoney,curmoney,actdate) values(accountio_seq.nextval,%d,%d,%d + (select accountbank from accountinfo where accountid = %d),sysdate);"), acc_id,money,money,acc_id,acc_id);

	if (CommandSql(str) == TRUE)
	{
		return CommandSql((TCHAR*)TEXT("commit"));
	}
	return FALSE;
}


BOOL wbdb_Withdrawl(int acc_id,int money)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("insert into accountio(ioid,ac_id,inmoney,curmoney,actdate) values(accountio_seq.nextval,%d,%d,%d - (select accountbank from accountinfo where accountid = %d),sysdate);"), acc_id, money, money, acc_id);
	if (CommandSql(str) == TRUE)
	{
		return CommandSql((TCHAR*)TEXT("commit"));
	}
	return FALSE;

	TCHAR str1[1024];
	wsprintf(str1, TEXT("update accountinfo set accountbank = (select max(ioid) from accountio) where accountid = %d;"), acc_id);
	if (CommandSql(str) == TRUE)
	{
		return CommandSql((TCHAR*)TEXT("commit"));
	}
	return FALSE;
}

BOOL wbdb_Refresh(int acc_id)		//잔액 갱신
{
	TCHAR str1[1024];
	wsprintf(str1, TEXT("update accountinfo set accountbank = (select curmoney from accountio where ioid = (select max(ioid) from accountio)) where accountid = 10240;"), acc_id);
	if (CommandSql(str1) == TRUE)
	{
		return CommandSql((TCHAR*)TEXT("commit"));
	}
	return FALSE;
}