//std.h
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")

#define WIN32_LEAN_AND_MEAN     //Windows.h 와 winsock2.h 충돌방지

//==============  공통 컨트롤 정보 획득 (page140)
#include <commctrl.h>					//함수 선언부 
#pragma comment(lib, "comctl32.lib")	//함수 구현부 
//======================================================

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
using namespace std;
#include "resource.h"

#include "ui.h"
#include "handler.h"
#include "packet.h"
#include "Infoproc.h"
#include "wbclient.h"