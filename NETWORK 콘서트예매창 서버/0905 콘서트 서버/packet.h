#pragma once

//클라이언트 => 서버
#define PACK_INSERT		1		//회원가입
#define PACK_SELECT		2		//검색
#define PACK_UPDATE		3		//수정
#define PACK_LOGIN		4		//로그인

#define PACK_TIME		5		//날짜
#define PACK_TICKET		6		//티켓
#define PACK_CONNETED	7		//(민서)연결확인
#define PACK_LIST	8

//서버 => 클라이언트
#define ACK_INSERT_S	10   //이름   SELECT			회원가입 성공
#define ACK_INSERT_F	11	 //이름   SELECT			회원가입 실패
#define ACK_SELECT_S	12   //전체정보 회신	INSERT	검색 성공
#define ACK_SELECT_F	13   //이름    SELECT			검색 실패
#define ACK_UPDATE_S	14	 //전체정보 회신	INSERT	수정 성공
#define ACK_UPDATE_F	15	 //이름   SELECT			수정 실패

#define ACK_CONNECTED_R	16	 //좌석정보 회신			//(민서)연결결과 리턴
#define ACK_LOGIN_S	17	 //전체정보 회신	INSERT		//로그인 성공
#define ACK_LOGIN_F	18	 //이름   SELECT				//로그인 실패

#define ACK_TIME	19	 //전체정보 회신	INSERT		//로그인 성공
#define ACK_LIST	20	 //이름   SELECT				//로그인 실패
//#define ACK_UPDATE_F	17	 //이름   SELECT

//패킷 구조체 
typedef struct tagLOGIN		//로그인 아이디 비번값
{
	int flage;	//PACK정의 추가 
	TCHAR id[20];
	TCHAR pw[20];
}LOGIN;

typedef struct tagINSERT	//회원가입 회원정보 값을 받아서 리스트에 등록할 구조체
{
	int flage;
	TCHAR id[20];
	TCHAR pw[20];
	TCHAR name[20];
	TCHAR phone[20];
}INSERT;

typedef struct tagSELECT	//이름을 받아 리스트에서 비교해볼 구조체
{
	int flage;
	TCHAR name[20];
}SELECT;


typedef struct tagUPDATE	//이름을 받고 리스트에서 비교 후 맞는 이름이 있으면 전화번호를 다시 넣어 수정한다.
{
	int flage;
	TCHAR name[20];
	TCHAR phone[20];
}UPDATE;

typedef struct tagTIME	//시간값을 받는다.
{
	int flage;
	TCHAR date[20];
	TCHAR info[40];
}TIME;

typedef struct tagTICKETING	//좌석 번호를 받아 그 배열에 값을 동일하게 저장한다.
{
	int flage;
	int Sit;
}TICKETING;

typedef struct tagCONNECTED_R	//다시 저장된 좌석 전부를 보내주는 구조체
{
	int flage;
	int Sit;
}CONNECTED_R;

typedef struct tagCONCERTMANAGER	//다시 저장된 좌석 전부를 보내주는 구조체
{
	int flage;
	TCHAR date[20];
	TCHAR info[40];
	TCHAR choice[20];
}CONCERTMANAGER;

typedef struct tagLIST
{
	int flage;
	TCHAR choice[20];
}LIST;

SELECT pack_insert(TCHAR *name);		//이름					회원 가입
SELECT pack_SelectF(TCHAR* name);		//이름					검색 성공
INSERT pack_SelectS(INSERT data);		//전체정보				검색 실패

INSERT pack_UpdateS(INSERT data);		//전체정보				수정 성공
SELECT pack_UpdateF(TCHAR* name);		//이름					수정 실패

INSERT pack_LOGINS(INSERT data);		//전체정보				로그인 성공
INSERT pack_LOGINF(TCHAR* id);			//??실패시 아이디확인	로그인 실패

TICKETING pack_Ticket(int Sit);			//좌석					좌석정보
CONNECTED_R pack_Connected_R(int &Sit);	//좌석					좌석정보

TIME pack_Time(TIME data);		//이름					검색 성공

LIST pack_List(LIST data);