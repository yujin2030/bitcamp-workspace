//std.h
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")

#define WIN32_LEAN_AND_MEAN     //Windows.h �� winsock2.h �浹����

//==============  ���� ��Ʈ�� ���� ȹ�� (page140)
#include <commctrl.h>					//�Լ� ����� 
#pragma comment(lib, "comctl32.lib")	//�Լ� ������ 
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