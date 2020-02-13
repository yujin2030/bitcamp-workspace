//packet.cpp
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include "packet.h"

DRAW pack_draw(COLORREF color, POINTS data)
{
	DRAW pack;
	
	pack.flage = ACK_DRAW;
	pack.color = color;
	pack.pt = data;
	
	return pack;
}

MESSAGE pack_message(TCHAR *msg)
{
	MESSAGE pack;

	pack.flage = ACK_MESSAGE;
	_tcscpy_s(pack.msg, msg);

	return pack;
}