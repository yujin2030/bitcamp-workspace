//packet.h
#define PACK_INSERT      1      //회원가입
#define PACK_SELECT      2      //검색
#define PACK_UPDATE      3      //수정
#define PACK_LOGIN      4      //로그인

#define PACK_TIME      5      //날짜
#define PACK_TICKET      6      //티켓
#define PACK_CONNETED   7      //(민서)연결확인
#define PACK_LIST       8        //회차등록

//서버 => 클라이언트
#define ACK_INSERT_S   10   //이름   SELECT         회원가입 성공
#define ACK_INSERT_F   11    //이름   SELECT         회원가입 실패
#define ACK_SELECT_S   12   //전체정보 회신   INSERT   검색 성공
#define ACK_SELECT_F   13   //이름    SELECT         검색 실패
#define ACK_UPDATE_S   14    //전체정보 회신   INSERT   수정 성공
#define ACK_UPDATE_F   15    //이름   SELECT         수정 실패

#define ACK_CONNECTED_R   16    //좌석정보 회신         //(민서)연결결과 리턴
#define ACK_LOGIN_S   17    //전체정보 회신   INSERT      //로그인 성공
#define ACK_LOGIN_F   18    //이름   SELECT            //로그인 실패

#define ACK_TIME		19
#define ACK_LIST		20



typedef struct tagLOGIN
{
	int flage;
	TCHAR id[20];
	TCHAR pw[20];

}LOGIN;

typedef struct tagMEMBER
{
	int flage;
	TCHAR id[20];
	TCHAR pw[20];
	TCHAR name[20];
	TCHAR phone[20];
}MEMBER;

typedef struct tagTIME
{
	int flage;
	TCHAR date[20];
	TCHAR info[40];
}TIME;

typedef struct tagLIST
{
	int flage;
	TCHAR choice[20];
}LIST;


typedef struct tagLOGINS
{
	int flage;
}LOGINS;

typedef struct tagCONCERTMANAGER
{
	int flage;
	TCHAR date[20];
	TCHAR info[40];
	TCHAR choice[20];
}CONCERTMANAGER;

TIME pack_Time(TCHAR* date, TCHAR* info);
LIST pack_List(TCHAR* chioce);

//MEMBER _Info(MEMBER data);
MEMBER pack_LOGINS(MEMBER data);
MEMBER pack_LOGINF(TCHAR* id);
LOGINS pack_LoginS();