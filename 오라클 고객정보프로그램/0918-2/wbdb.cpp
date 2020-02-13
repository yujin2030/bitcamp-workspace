//wbdb.cpp

#include "std.h"

#define DBNAME TEXT("wbdb")
#define ID	   TEXT("wb30")
#define PW		TEXT("1234")

SQLHSTMT hStmt;
SQLHENV hEnv;
SQLHDBC hDbc;


BOOL wbdb_DBConnect()
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

BOOL wbdb_DBDConnect()
{
	// 뒷정리
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return TRUE;
}

BOOL wbdb_CreateTeamTable()
{
	TCHAR str[1024] = TEXT("CREATE TABLE Team (GroupId number,GroupName varchar2(20),CONSTRAINT Group_id_pk primary key(GroupId));");

	return CommandSql(str);
}

BOOL wbdb_DropTeamTable()
{
	TCHAR str[1024] = TEXT("DROP TABLE Team;");

	return CommandSql(str);
}

BOOL wbdb_CreateMemberTable()
{
	TCHAR str[1024] = TEXT("CREATE TABLE member( \
		mem_ID   	 NUMBER,	\
		mem_NAME  	VARCHAR2(20 BYTE) NOT NULL,	\
		mem_gen		VARCHAR2(20 BYTE)			\
			check(mem_gen in('남성', '여성')),	\
		mem_phone 	 VARCHAR2(20 BYTE),			\
		mem_GID          NUMBER NOT NULL,		\
		mem_date	date,						\
		CONSTRAINT member_PK PRIMARY KEY(mem_ID)); ");

	CommandSql(str);

	TCHAR str1[1024] = TEXT("ALTER TABLE member \
		ADD CONSTRAINT member_FK FOREIGN KEY(mem_ID)	\
		REFERENCES member(mem_ID); ");

	return CommandSql(str1);
}

BOOL wbdb_DropMemberTable()
{
	TCHAR str[1024] = TEXT("DROP TABLE Member;");

	return CommandSql(str);
}

BOOL wbdb_CreateSequence()
{
	TCHAR str[1024] = TEXT("create sequence mem_ID_seq increment by 1 start with 1000; ");

	return CommandSql(str);
}

BOOL wbdb_DropSequence()
{
	TCHAR str[1024] = TEXT("drop sequence mem_ID_seq");

	return CommandSql(str);
}

BOOL wbdb_InsertTeam( TCHAR* name, TCHAR* phone, TCHAR* gender)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("insert into custmg values(custmg_seq.nextval, '%s','%s',sysdate,'%s');"),
	   name,phone,gender);
	if (CommandSql(str) == TRUE)
	{
		return CommandSql((LPWSTR)TEXT("commit"));
	}
	return FALSE;
}

BOOL wbdb_DeleteTeam(int id)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("delete custmg where id = %d;"), id);
	if (CommandSql(str) == TRUE)
	{
		return CommandSql((LPWSTR)TEXT("commit"));
	}
	return FALSE;
}

BOOL wbdb_UpdateTeam(int id, TCHAR* name, TCHAR* phone, TCHAR* gender)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("update custmg set name='%s',phone='%s',gender='%s' where id = %d"), 
		name,phone,gender,id);
	if (CommandSql(str) == TRUE)
	{
		return CommandSql((LPWSTR)TEXT("commit"));
	}
	return FALSE;
}

BOOL CommandSql(TCHAR *str)
{
	if (SQLExecDirect(hStmt, (SQLTCHAR *)str, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL wbdb_GetTeamSelectAll(vector<custmg>*custmglist)
{
	int id;
	SQLTCHAR name[10], phone[20],register_1[20],gender[2] ;
	SQLINTEGER lid, lname,lphone,Iphone,Iregister_1,Igender;

	SQLBindCol(hStmt, 1, SQL_C_ULONG, &id, 0, &lid);
	SQLBindCol(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), &lname);
	SQLBindCol(hStmt, 3, SQL_C_WCHAR, phone, sizeof(phone), &Iphone);
	SQLBindCol(hStmt, 4, SQL_C_WCHAR, register_1, sizeof(register_1), &Iregister_1);
	SQLBindCol(hStmt, 5, SQL_C_WCHAR, gender, sizeof(gender), &Igender);

	TCHAR sql[256] = TEXT("select * from custmg");
	
	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		custmg data;
		data.id = id;
		_tcscpy(data.name, name);
		_tcscpy(data.phone, phone);
		_tcscpy(data.register_1, register_1);
		_tcscpy(data.gender, gender);
		
	    custmglist->push_back(data);
	}
}

BOOL wbdb_GetTeamSelectData(vector<custmg>*custmglist1,int id_1, TCHAR* name_1, TCHAR* phone_1,TCHAR* register_1_1, TCHAR* gender_1)
{
	int id;
	SQLTCHAR name[10], phone[20], register_1[20], gender[2];
	SQLINTEGER lid, lname, lphone, Iphone, Iregister_1, Igender;

	SQLBindCol(hStmt, 1, SQL_C_ULONG, &id, 0, &lid);
	SQLBindCol(hStmt, 2, SQL_C_WCHAR, name, sizeof(name), &lname);
	SQLBindCol(hStmt, 3, SQL_C_WCHAR, phone, sizeof(phone), &Iphone);
	SQLBindCol(hStmt, 4, SQL_C_WCHAR, register_1, sizeof(register_1), &Iregister_1);
	SQLBindCol(hStmt, 5, SQL_C_WCHAR, gender, sizeof(gender), &Igender);

	TCHAR str[256];
	if (id == NULL && lstrlen(name) == 0 && lstrlen(phone) == 0 && lstrlen(register_1) == 0 && lstrlen(gender) == 0)
	{
		wsprintf(str, TEXT("select * from custmg order by asc"));
	}
	
	else if (id != NULL)
	{
		wsprintf(str, TEXT("select * from custmg where id = %d;"),id_1);
	}

	else if (lstrlen(name) != NULL)
	{
		wsprintf(str, TEXT("select * from custmg where name = '%s';"), name_1);
	}

	else if (lstrlen(phone) != NULL)
	{
		wsprintf(str, TEXT("select * from custmg where phone = '%s';"), phone_1);
	}

	else if (lstrlen(register_1) != NULL)
	{
		wsprintf(str, TEXT("select * from custmg where register_1 = '%s';"), register_1_1);
	} 

	else if (lstrlen(gender) != NULL)
	{
		wsprintf(str, TEXT("select * from custmg where gender = '%s';"), gender_1);
	}

	if (SQLExecDirect(hStmt, (SQLTCHAR*)str, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		custmg data;
		data.id = id;
		_tcscpy(data.name, name);
		_tcscpy(data.phone, phone);
		_tcscpy(data.register_1, register_1);
		_tcscpy(data.gender, gender);

		custmglist1->push_back(data);
	}
}

//BOOL mydb_SelectData()
//{
//	SQLCHAR Name[256];
//
//	SQLINTEGER lName, lSnum, lPhone, lEmail;
//	int ssnum;
//
//	SQLCHAR Phone[256];
//	SQLCHAR Email[256];
//
//	SQLBindCol(hStmt, 1, SQL_C_CHAR, Name, sizeof(Name), &lName);
//	SQLBindCol(hStmt, 2, SQL_C_ULONG, &ssnum, 0, &lSnum);
//	SQLBindCol(hStmt, 3, SQL_C_CHAR, Phone, sizeof(Phone), &lPhone);
//	SQLBindCol(hStmt, 4, SQL_C_CHAR, Email, sizeof(Email), &lEmail);
//
//	char sql[256] = "select * from sb";
//
//	if (SQLExecDirect(hStmt, (SQLCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
//	{
//		return FALSE;
//	}
//
//	char name[21], num[21], phoneNumber[21], email[41];
//	int count = 0;
//	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
//	{
//		wsprintf(name, "%s", Name);
//		wsprintf(num, "%d", ssnum);
//		wsprintf(phoneNumber, "%s", Phone);
//		wsprintf(email, "%s", Email);
//
//		control_GetData(count++, name, num, phoneNumber, email);
//
//	}
//	return TRUE;
//}
//
//BOOL mydb_DeleteData()
//{
//	char sql[256];
//
//	wsprintf(sql, "delete sb");
//	if (SQLExecDirect(hStmt, (SQLCHAR *)sql, SQL_NTS) != SQL_SUCCESS)
//	{
//		return FALSE;
//	}
//	return TRUE;
//}