//packet.cpp
#include "std.h"

INSERT pack_Insert(TCHAR*id, TCHAR*pw, TCHAR*name, TCHAR*phone, int age)
{
	INSERT pack;

	pack.flage = PACK_INSERT;
	_tcscpy_s(pack.id, id);
	_tcscpy_s(pack.pw, pw);
	_tcscpy_s(pack.name, name);
	pack.age = age;
	_tcscpy_s(pack.phone, phone);

	return pack;
}

SELECT pack_Select(TCHAR*name)
{
	SELECT pack;

	pack.flage = PACK_SELECT;
	_tcscpy_s(pack.name, name);

	return pack;
}

UPDATE pack_Update(TCHAR*name, TCHAR*phone, int age)
{
	UPDATE pack;

	pack.flage = PACK_UPDATE;
	_tcscpy_s(pack.name, name);
	pack.age = age;
	_tcscpy_s(pack.phone, phone);

	return pack;
}

SELECT pack_Delete(TCHAR*name)
{
	SELECT pack;

	pack.flage = PACK_DELETE;
	_tcscpy_s(pack.name, name);

	return pack;
}