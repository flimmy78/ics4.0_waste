#define   FmpSrcLen   22   /*����ǰ����*/
#define   FmpValLen   32   /*���ܺ�����*/
#define   MaxLen       8   /*�������*/

#define   MaxMsgLen 8192   /*������ݳ���*/
#define   HexDatLen    4   /*ʮ���������ݳ���*/
#define   DecDatLen    8   /*ʮ�������ݳ���*/
#define   StatusLen    2   /*ʮ��״̬�򳤶ȣ�һλ����λ��*/

#define   TComCdLen    6   /*�����볤��*/
#define   PrvFrmLen   20   /*���˱��ų���*/
#define   TCrpCdLen   50   /*��֯�������볤��*/
#define   RecNumLen    5   /*ѭ����������*/
#define   QryDatLen   12   /*��ѯ����*/

#define   TotLenOffSet   0
#define   ComIdOffSet    TotLenOffSet+HexDatLen
#define   SeqIdOffSet    ComIdOffSet+HexDatLen
#define   StatusOffSet   SeqIdOffSet+HexDatLen

#define   TotLenLen    4   /*�����ܳ���*/
#define   ComIdLen     4   /*��Ӧ����*/
#define   SeqIdLen     4   /*��Ϣ��ˮ��*/

/*�㶫�̲ݶ���*/
#define    MsgLenLen   4  /*��Ϣ����*/
#define    MsgHedLen   3  /*��Ϣͷ*/
#define    TranCodLen  4  /*������*/
#define    DepCodLen   4  /*��˾����*/
#define    EndLen      3  /*������־*/ 
#define    HeadLen     15 /*��Ϣ����+��Ϣͷ+������+��˾����*/
#define    DesKey      "12345678" /*��ʼ��Կ*/