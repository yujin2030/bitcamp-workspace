//packet.h
#define PACK_INSERT      1      //ȸ������
#define PACK_SELECT      2      //�˻�
#define PACK_UPDATE      3      //����
#define PACK_LOGIN      4      //�α���

#define PACK_TIME      5      //��¥
#define PACK_TICKET      6      //Ƽ��
#define PACK_CONNETED   7      //(�μ�)����Ȯ��
#define PACK_LIST       8        //ȸ�����

//���� => Ŭ���̾�Ʈ
#define ACK_INSERT_S   10   //�̸�   SELECT         ȸ������ ����
#define ACK_INSERT_F   11    //�̸�   SELECT         ȸ������ ����
#define ACK_SELECT_S   12   //��ü���� ȸ��   INSERT   �˻� ����
#define ACK_SELECT_F   13   //�̸�    SELECT         �˻� ����
#define ACK_UPDATE_S   14    //��ü���� ȸ��   INSERT   ���� ����
#define ACK_UPDATE_F   15    //�̸�   SELECT         ���� ����

#define ACK_CONNECTED_R   16    //�¼����� ȸ��         //(�μ�)������ ����
#define ACK_LOGIN_S   17    //��ü���� ȸ��   INSERT      //�α��� ����
#define ACK_LOGIN_F   18    //�̸�   SELECT            //�α��� ����

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