#pragma once

//Ŭ���̾�Ʈ => ����
#define PACK_INSERT		1		//ȸ������
#define PACK_SELECT		2		//�˻�
#define PACK_UPDATE		3		//����
#define PACK_LOGIN		4		//�α���

#define PACK_TIME		5		//��¥
#define PACK_TICKET		6		//Ƽ��
#define PACK_CONNETED	7		//(�μ�)����Ȯ��
#define PACK_LIST	8

//���� => Ŭ���̾�Ʈ
#define ACK_INSERT_S	10   //�̸�   SELECT			ȸ������ ����
#define ACK_INSERT_F	11	 //�̸�   SELECT			ȸ������ ����
#define ACK_SELECT_S	12   //��ü���� ȸ��	INSERT	�˻� ����
#define ACK_SELECT_F	13   //�̸�    SELECT			�˻� ����
#define ACK_UPDATE_S	14	 //��ü���� ȸ��	INSERT	���� ����
#define ACK_UPDATE_F	15	 //�̸�   SELECT			���� ����

#define ACK_CONNECTED_R	16	 //�¼����� ȸ��			//(�μ�)������ ����
#define ACK_LOGIN_S	17	 //��ü���� ȸ��	INSERT		//�α��� ����
#define ACK_LOGIN_F	18	 //�̸�   SELECT				//�α��� ����

#define ACK_TIME	19	 //��ü���� ȸ��	INSERT		//�α��� ����
#define ACK_LIST	20	 //�̸�   SELECT				//�α��� ����
//#define ACK_UPDATE_F	17	 //�̸�   SELECT

//��Ŷ ����ü 
typedef struct tagLOGIN		//�α��� ���̵� �����
{
	int flage;	//PACK���� �߰� 
	TCHAR id[20];
	TCHAR pw[20];
}LOGIN;

typedef struct tagINSERT	//ȸ������ ȸ������ ���� �޾Ƽ� ����Ʈ�� ����� ����ü
{
	int flage;
	TCHAR id[20];
	TCHAR pw[20];
	TCHAR name[20];
	TCHAR phone[20];
}INSERT;

typedef struct tagSELECT	//�̸��� �޾� ����Ʈ���� ���غ� ����ü
{
	int flage;
	TCHAR name[20];
}SELECT;


typedef struct tagUPDATE	//�̸��� �ް� ����Ʈ���� �� �� �´� �̸��� ������ ��ȭ��ȣ�� �ٽ� �־� �����Ѵ�.
{
	int flage;
	TCHAR name[20];
	TCHAR phone[20];
}UPDATE;

typedef struct tagTIME	//�ð����� �޴´�.
{
	int flage;
	TCHAR date[20];
	TCHAR info[40];
}TIME;

typedef struct tagTICKETING	//�¼� ��ȣ�� �޾� �� �迭�� ���� �����ϰ� �����Ѵ�.
{
	int flage;
	int Sit;
}TICKETING;

typedef struct tagCONNECTED_R	//�ٽ� ����� �¼� ���θ� �����ִ� ����ü
{
	int flage;
	int Sit;
}CONNECTED_R;

typedef struct tagCONCERTMANAGER	//�ٽ� ����� �¼� ���θ� �����ִ� ����ü
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

SELECT pack_insert(TCHAR *name);		//�̸�					ȸ�� ����
SELECT pack_SelectF(TCHAR* name);		//�̸�					�˻� ����
INSERT pack_SelectS(INSERT data);		//��ü����				�˻� ����

INSERT pack_UpdateS(INSERT data);		//��ü����				���� ����
SELECT pack_UpdateF(TCHAR* name);		//�̸�					���� ����

INSERT pack_LOGINS(INSERT data);		//��ü����				�α��� ����
INSERT pack_LOGINF(TCHAR* id);			//??���н� ���̵�Ȯ��	�α��� ����

TICKETING pack_Ticket(int Sit);			//�¼�					�¼�����
CONNECTED_R pack_Connected_R(int &Sit);	//�¼�					�¼�����

TIME pack_Time(TIME data);		//�̸�					�˻� ����

LIST pack_List(LIST data);