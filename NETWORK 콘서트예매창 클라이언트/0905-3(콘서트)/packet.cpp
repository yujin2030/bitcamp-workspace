//packet.cpp

#include "std.h"

MEMBER pack_LOGINS(MEMBER data)
{
	MEMBER pack = data;

	pack.flage = ACK_LOGIN_S;

	return pack;
}

MEMBER pack_LOGINF(TCHAR* id)
{
	MEMBER pack;

	pack.flage = ACK_LOGIN_F;
	_tcscpy_s(pack.id, id);

	return pack;
}

TIME pack_Time(TCHAR* date, TCHAR* info)
{
	TIME pack;

	pack.flage = PACK_TIME;
	_tcscpy_s(pack.date, date);
	_tcscpy_s(pack.info, info);
	return pack;
}

LIST pack_List(TCHAR* choice)
{
	LIST pack;

	pack.flage = PACK_LIST;
	_tcscpy_s(pack.choice, choice);
	return pack;
}

MEMBER ui_LoginS(MEMBER data)
{
	MEMBER pack;

	pack.flage = ACK_LOGIN_S;
	return pack;
}

MEMBER ui_LoginF(MEMBER data)
{
	MEMBER pack;

	pack.flage = ACK_LOGIN_F;
		return pack;
}

LOGINS pack_LoginS()
{
	LOGINS pack;
	pack.flage = ACK_LOGIN_S;
	return pack;
}