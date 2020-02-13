//wbdb.h

#include <sql.h>
#include <sqlext.h>

BOOL wbdb_DBConnect();
BOOL wbdb_DBDConnect();

BOOL wbdb_CreateTeamTable();
BOOL wbdb_DropTeamTable();
BOOL wbdb_CreateMemberTable();
BOOL wbdb_DropMemberTable();
BOOL wbdb_CreateSequence();
BOOL wbdb_DropSequence();

BOOL wbdb_InsertTeam(TCHAR* name, TCHAR* phone, TCHAR* gender);
BOOL wbdb_DeleteTeam(int id);
BOOL wbdb_UpdateTeam(int id, TCHAR* name, TCHAR* phone, TCHAR* gender);
BOOL wbdb_GetTeamSelectData(vector<custmg>*custmglist1, int id, TCHAR* name, TCHAR* phone, TCHAR* register_1, TCHAR* gender);

BOOL wbdb_GetTeamSelectAll(vector<custmg>*custmglist);

BOOL CommandSql(TCHAR *str);




//
////BOOL mydb_InsertData(Student *pData);
//
//BOOL mydb_SelectData();
//
//BOOL mydb_DeleteData();