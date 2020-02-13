//std.h
#define WIN32_LEAN_AND_MEAN   //windows.h과 winsock2.h 충돌 방지

#include <Windows.h>
//==============  공통 컨트롤 정보 획득 (page140)
#include <commctrl.h>					//함수 선언부 
#pragma comment(lib, "comctl32.lib")	//함수 구현부 
//======================================================
#include <stdio.h>

#include <tchar.h>
#include "resource.h"

#include "packet.h"
#include "wbclient.h"
#include "ui.h"
#include "handler.h"