//std.h
#define _WINSOCK_DEPRECATED_NO_WARNINGS   
#define WIN32_LEAN_AND_MEAN   //windows.h과 winsock2.h 충돌 방지

#include <Windows.h>
#include <commdlg.h>
#include <winsock2.h>
#include <vector>
using namespace std;
#pragma comment (lib,"ws2_32.lib")
//==============  공통 컨트롤 정보 획득 (page140)
#include <commctrl.h>					//함수 선언부 
#pragma comment(lib, "comctl32.lib")	//함수 구현부 
//======================================================
#include <stdio.h>

#include <tchar.h>
#include "resource.h"

#include "wbmessage.h"
#include "wbfile.h"
#include "wbmessage.h"
#include "uifile.h"
#include "uimessage.h"
#include "handler.h"