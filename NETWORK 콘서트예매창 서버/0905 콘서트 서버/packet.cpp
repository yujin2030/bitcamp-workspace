//packet.cpp
#include <stdio.h>
#include <tchar.h>
#include "packet.h"

SELECT pack_insert(TCHAR *name)	//회원가입
{
	SELECT pack;

	pack.flage = ACK_INSERT_S;
	_tcscpy_s(pack.name, name);

	return pack;
}

INSERT pack_LOGINS(INSERT data)	//로그인 성공
{
	INSERT pack = data;

	pack.flage = ACK_LOGIN_S;		//로그인 성공시 로그인 성공 값을 보내준다.
									//크라이언트가 성공한 결과를 받았을 때 다음 위치로 넘어가도로간다.
	return pack;
}

INSERT pack_LOGINF(TCHAR* id)	//로그인 실패			이건 계속 확인하자 select는 이름만 받기때문데
{
	INSERT pack;									//INSERT로 모든 정보를 넣고 그중 아이디만 빼서

	pack.flage = ACK_LOGIN_F;						//받아온 데이터 아이디를 그대로 카피해서 패킷을 만들고
	_tcscpy_s(pack.id, id);
	//반환한다.
	return pack;
}

INSERT pack_SelectS(INSERT data) //회원가입
{
	INSERT pack = data;

	pack.flage = ACK_SELECT_S;

	return pack;
}

SELECT pack_SelectF(TCHAR* name) //회원가입
{
	SELECT pack;

	pack.flage = ACK_SELECT_F;
	_tcscpy_s(pack.name, name);

	return pack;
}

INSERT pack_UpdateS(INSERT data)	//수정
{
	INSERT pack = data;

	pack.flage = ACK_UPDATE_S;

	return pack;
}

SELECT pack_UpdateF(TCHAR* name)	//수정
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