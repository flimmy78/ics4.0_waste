#define   FmpSrcLen   22   /*����ǰ����*/
#define   FmpValLen   32   /*���ܺ�����*/
#define   MaxLen       8   /*�������*/

#define   MaxMsgLen 8192   /*������ݳ���*/
#define   HexDatLen    4   /*ʮ���������ݳ���*/
#define   DecDatLen    8   /*ʮ�������ݳ���*/
#define   StatusLen    2   /*ʮ��״̬�򳤶ȣ�һλ����λ��*/

#define   TComCdLen    6   /*�����볤��*/
#define   PrvFrmLen   20   /*���˱�ų���*/
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

/*���ݴ�ѧ��IC����������*/
#define    MesgLenLen  6   /*���ĳ���*/
#define    TTxnCdLen   6   /*������������*/
#define    MchIDLen    6   /*�����̱��*/
#define    TTxnTmLen   14  /*����������ʱ��*/
#define    RetCodLen   4   /*������������*/
#define    TLogNoLen   20  /*ϵͳ�ο���*/
#define    BodyMacLen  32  /*�������ݵ�Mac��*/
/*#define    HeadLen          BusinessIdLen+ReqCodeLen+RetCodeLen+TransLineLen+BodyLenLen+BodyMacLen  ��ͷ����*/
#define    HeadLen          88
#define    DesKey           "12345678"
