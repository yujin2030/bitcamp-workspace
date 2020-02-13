//packet.cpp
#include <stdio.h>
#include <tchar.h>
#include "packet.h"

SELECT pack_insert(TCHAR *name)	//ȸ������
{
	SELECT pack;

	pack.flage = ACK_INSERT_S;
	_tcscpy_s(pack.name, name);

	return pack;
}

INSERT pack_LOGINS(INSERT data)	//�α��� ����
{
	INSERT pack = data;

	pack.flage = ACK_LOGIN_S;		//�α��� ������ �α��� ���� ���� �����ش�.
									//ũ���̾�Ʈ�� ������ ����� �޾��� �� ���� ��ġ�� �Ѿ���ΰ���.
	return pack;
}

INSERT pack_LOGINF(TCHAR* id)	//�α��� ����			�̰� ��� Ȯ������ select�� �̸��� �ޱ⶧����
{
	INSERT pack;									//INSERT�� ��� ������ �ְ� ���� ���̵� ����

	pack.flage = ACK_LOGIN_F;						//�޾ƿ� ������ ���̵� �״�� ī���ؼ� ��Ŷ�� �����
	_tcscpy_s(pack.id, id);
	//��ȯ�Ѵ�.
	return pack;
}

INSERT pack_SelectS(INSERT data) //ȸ������
{
	INSERT pack = data;

	pack.flage = ACK_SELECT_S;

	return pack;
}

SELECT pack_SelectF(TCHAR* name) //ȸ������
{
	SELECT pack;

	pack.flage = ACK_SELECT_F;
	_tcscpy_s(pack.name, name);

	return pack;
}

INSERT pack_UpdateS(INSERT data)	//����
{
	INSERT pack = data;

	pack.flage = ACK_UPDATE_S;

	return pack;
}

SELECT pack_UpdateF(TCHAR* name)	//����
{
	SELECT pack;

	pack.flage = ACK_UPDATE_F;
	_tcscpy_s(pack.name, name);

	return pack;
}

TICKETING pack_Ticket(int Sit)
{
	TICKETING pack;

	//pack.flage = ACK_CONNECTED_R;
	pack.Sit = Sit;

	return pack;
}

CONNECTED_R pack_Connected_R(int &Sit)
{
	CONNECTED_R pack;

	pack.flage = ACK_CONNECTED_R;
	pack.Sit = Sit;

	return pack;
}

TIME pack_Time(TIME data)
{
	TIME pack = data;
	pack.flage = ACK_TIME;

	return pack;
}

LIST pack_List(LIST data)
{
	LIST pack = data;
	pack.flage = ACK_LIST;

	return pack;
}