//packet.cpp
#include "std.h"

DRAW packet_Draw(POINTS pt, COLORREF color)
{
	DRAW pack;
	pack.flage = PACK_DRAW;
	pack.pt = pt;
	pack.color = color;

	return pack;
}

MESSAGE packet_Message(TCHAR* msg)
{
	MESSAGE pack;
	pack.flage = PACK_MESSAGE;
	_tcscpy_s(pack.msg, msg);

	return pack;
}