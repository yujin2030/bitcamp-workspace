//std.h
#define WIN32_LEAN_AND_MEAN   //windows.h�� winsock2.h �浹 ����

#include <Windows.h>
//==============  ���� ��Ʈ�� ���� ȹ�� (page140)
#include <commctrl.h>					//�Լ� ����� 
#pragma comment(lib, "comctl32.lib")	//�Լ� ������ 
//======================================================
#include <stdio.h>

#include <tchar.h>
#include "resource.h"

#include "packet.h"
#include "wbclient.h"
#include "ui.h"
#include "handler.h"