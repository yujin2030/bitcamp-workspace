//std.h
#define WIN32_LEAN_AND_MEAN   //windows.h�� winsock2.h �浹 ����

#include <Windows.h>
#include <commdlg.h>
#include <winsock2.h>	
#pragma comment(lib, "ws2_32.lib")
//==============  ���� ��Ʈ�� ���� ȹ�� (page140)
#include <commctrl.h>					//�Լ� ����� 
#pragma comment(lib, "comctl32.lib")	//�Լ� ������ 
//======================================================
#include <stdio.h>

#include <tchar.h>
#include "resource.h"

//#include "packet.h"
#include "wbfile.h"
#include "uifile.h"
#include "wbmsg.h"
#include "uimsg.h"
#include "handler.h"