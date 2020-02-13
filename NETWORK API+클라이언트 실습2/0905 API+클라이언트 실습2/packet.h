//packet.h

//��Ŷ ����(APP �������� ����)

//Ŭ���̾�Ʈ => ����
#define PACK_DRAW			1
#define PACK_MESSAGE		2

//���� => Ŭ���̾�Ʈ
#define ACK_DRAW			10   //�̸�   SELECT
#define ACK_MESSAGE			11	 //�̸�   SELECT


//��Ŷ ����ü 
typedef struct tagDRAW
{
	int flage;		//PACK���� �߰� 
	POINTS pt;
	COLORREF color;
}DRAW;

typedef struct tagMESSAGE
{
	int flage;		//PACK���� �߰� 
	TCHAR msg[100];
}MESSAGE;

DRAW packet_Draw(POINTS pt, COLORREF color);
MESSAGE packet_Message(TCHAR* msg);