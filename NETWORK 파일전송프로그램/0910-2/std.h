//std.h
#define _WINSOCK_DEPRECATED_NO_WARNINGS   
#define WIN32_LEAN_AND_MEAN   //windows.h�� winsock2.h �浹 ����

#include <Windows.h>
#include <commdlg.h>
#include <winsock2.h>
#include <vector>
using namespace std;
#pragma comment (lib,"ws2_32.lib")
//==============  ���� ��Ʈ�� ���� ȹ�� (page140)
#include <commctrl.h>					//�Լ� ����� 
#pragma comment(lib, "comctl32.lib")	//�Լ� ������ 
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