/*ԭ�Ӻ�������ֵ����*/
#define   MsgTypLen      1   /*����������*/
#define   RspCodLen      6   /*������*/
#define   RspMsgLen     56   /*������Ϣ*/

/*�����ѡ��ʵ�Ѽ����������*/
#define   TxnKndLen      6   /*��������ϸ�ִ���*/
#define   UsgCodLen      3   /*�ʽ���;����*/
#define   LclFlgLen      1   /*����ر�־*/
#define   BrNoLen        6   /*���к�*/
#define   CcyCodLen      3   /*����*/
#define   TxnAmtLen     15   /*���׽��*/
#define   FeeModLen      1   /*�������շ�ģʽ*/
#define   FeeRatLen      6   /*�����ѷ���*/
#define   FeeAmtLen     15   /*�����Ѷ��*/
#define   PstModLen      1   /*�ʵ���շ�ģʽ*/
#define   PstRatLen      6   /*�ʵ�ѷ���*/
#define   PstAmtLen     15   /*�ʵ�Ѷ��*/

/*��ȡ�ʻ����ͱ�������*/
#define   BgnLocLen      2   /*�����ĵ�������ʼλ��*/
#define   CenLenLen      2   /*�����ų���*/

/*�жϻ����ͷ���������*/
#define   UpdDirLen      1   /*���½衢����־*/
#define   TxnModLen      1   /*��������*/


/*�кŻ�ȡ��������*/
#define   CtlNodLen      6
#define   BusCodLen      6
#define   PBnkNoLen     12

/*�ж��ʻ����ԣ��Թ�����˽����������*/
#define   RcvActLen     35   /*�������ʺ�*/
#define   AccFlgLen      1   /*�������ʺ�����*/

/*�����ļ�������������*/
/*����*/
#define   FilPthLen    128   /*�ļ�·��*/
/*�����ļ�������*/
#define   FILMARK        "TXNTYP"   /*�ļ�����־*/
#define   RSPFILLEN      "00000337" /*���׻�Ӧ�ļ�����*/
#define   SYSID          "1006"     /*��ͨ����ϵͳ��*/
#define   DIRBNO         "301581000019"  /*��ͨ����ֱ�Ӳ������к�*/

#define   FNmLstLen     46   /*�ļ��б�������*/
#define   FNameLen     128   /*�ļ�������*/
#define   MsgIdLen       4   /*�������ͱ�ʶ��*/
#define   SysIdLen       4   /*ϵͳ��*/
#define   WorkDtLen      8   /*��������*/
#define   BchNoLen       8   /*����*/
#define   FSizeLen       8   /*�ļ�����*/
#define   MsgIdOffset    6
#define   TxnKndOffset   MsgIdOffset+MsgIdLen
#define   SysIdOffset    TxnKndOffset+TxnKndLen
#define   WorkDtOffset   SysIdOffset+SysIdLen
#define   BchNoOffset    WorkDtOffset+WorkDtLen
#define   FSizeOffset    BchNoOffset+BchNoLen

#define   F8583SizeOffset 84
/*����Ӧ�ñ���ͷ*/
#define   ClrDatLen      8   /*��������*/
#define   ClrSceLen      1   /*���㳡��*/
#define   SSysIdLen      4   /*����ϵͳ��*/
#define   SndBNoLen     12   /*���𷽴���*/
#define   RSysIdLen      4   /*���շ�ϵͳ��*/
#define   RcvBNoLen     12   /*���շ�����*/
#define   TraKndLen      4   /*��������*/
#define   FilNamLen     60   /*�ļ���*/
#define   RefFilLen     60   /*�����ļ���*/
#define   BchSqnLen      8   /*���������*/
#define   RefSqnLen      8   /*�ο����������*/
#define   CusSqnLen      8   /*�ͻ����������*/
#define   TotNumLen     10   /*�����ܱ���*/
#define   TotAmtLen     16   /*�����ܽ��*/
#define   RefNumLen     10   /*�ܾ�֧���ܱ���*/
#define   RefAmtLen     16   /*�ܾ�֧���ܽ��*/
#define   RtnCodLen      8   /*������*/
#define   ReServLen     16   /*Ԥ��λ*/
#define   BchStsLen      1   /*�ļ�����״̬*/
/*������¼Ӧ�ñ���ͷ*/
#define   MsgSqnLen     16   /*��Ϣ���*/
/*������¼������*/
#define   SndTmLen      10   /*���׷������ں�ʱ��*/
#define   ClrBNoLen     12   /*ֱ��������*/
#define   SndDatLen      8   /*ί������*/
/*����ͷ�Ѷ���
#define   ClrDatLen      8   *��������*
*/
#define   QryTypLen      3   /*��ѯ֪ͨ����*/
#define   AreaNoLen      4   /*������*/
#define   SvrCodLen      4   /*��������뷽ʽ��*/
#define   CenIdLen      18   /*���Ŀͻ���*/
#define   CusIdLen      18   /*��ҵ�ͻ���*/
#define   CenTmLen      14   /*������������ʱ��*/
#define   CenLogLen     16   /*���������*/ 
#define   ThdTmLen      14   /*ҵ������������ʱ��*/
#define   ThdLogLen     16   /*ҵ��������ˮ��*/
#define   CshFlgLen      1   /*�ֽ�ת�ʱ�־*/
#define   SmrCodLen      4   /*ժҪ����*/
#define   RSdFlgLen      1   /*�ط���ʶ*/
#define   AccFlgLen      1   /*�Թ���˽��ʶ*/
#define   TBusTpLen      5   /*ҵ������*/
#define   CardFgLen      2   /*���۱�ʶ*/
#define   BillFgLen      1   /*�����㻧��ʶ*/
#define   FeeTypLen      3   /*�շѷ�ʽ*/
#define   PayFucLen      3   /*֧������*/
#define   AuthCdLen      6   /*��Ȩ��*/
#define   PayLvlLen      1   /*֧�����ȼ�*/
#define   OrgIdLen      32   /*ԭ����Ԫ*/
#define   SndBNoLen     12   /*�������к�*/
#define   SOpnBkLen     12   /*�����˿������к�*/
#define   SndNodLen      9   /*�����������*/
#define   SndActLen     35   /*�������˺�*/
#define   SndNmLen      60   /*����������*/
#define   VchIdLen       8   /*ƾ֤�ύ��*/
#define   RcvBNoLen     12   /*�������к�*/
#define   ROpnBkLen     12   /*�����˿������к�*/
#define   RcvNodLen      9   /*�����������*/
#define   RcvActLen     35   /*�������˺�*/
#define   RcvNmLen      60   /*����������*/
#define   AgrNoLen      60   /*Э���*/
#define   SysStsLen      2   /*ϵͳ����״̬*/
#define   CreAmtLen     15   /*�������*/
#define   CreCntLen     10   /*��������*/
#define   DebAmtLen     15   /*�跽���*/ 
#define   DebCntLen     10   /*�跽����*/ 
#define   CTraKndLen     4   /*��������*/
#define   OSgnIdLen     20   /*�ɵ�½��ʶ*/
#define   NSgnIdLen     20   /*�µ�½��ʶ*/
#define   SmrLen       300   /*����ժҪ*/
#define   SecKeyLen     40   /*��Ѻ*/
#define   TCrpCdLen     12   /*��ҵ��������*/
#define   SvrKndLen      1   /*������Ϣ����*/
#define   TBilNoLen     30   /*˰Ʊ����*/
#define   TaxNoLen      20   /*��˰�˱���*/
#define   TaxerLen      60   /*��˰������*/
#define   TaxLvlLen      2   /*Ԥ�㼶��*/
#define   TSubCdLen     12   /*Ԥ���Ŀ*/
#define   TOrgCdLen     11   /*���ջ��ش���*/
#define   TActDtLen      8   /*˰Ʊ�޽�����*/
#define   SvrMsgLen    300   /*������Ϣ����*/
#define   SndNm2Len     80   /*���ӷ���������*/
#define   SndAdrLen     60   /*�����˵�ַ*/
#define   RcvNm2Len     80   /*���ӽ���������*/
#define   RcvAdrLen     60   /*�����˵�ַ*/
#define   TraTmLen      10   /*����ʱ��*/
/*
**��Сͨ����������
*/
#define   DskNoLen      12   /*���̺�*/
#define   BchStsLen      1   /*������¼״̬*/
#define   OIFlagLen      1   /*������־*/
#define   BilStsLen      1   /*���ʼ�¼״̬*/
#define   AccKndLen      1   /*�ʻ�����*/
#define   NodNoLen       6   /*���ʻ�ۿ��ڲ�������������*/
#define   AccSeqLen      5   /*�ڲ��ʻ����*/
#define   LogNoLen      14   /*ǰ����ˮ��*/
#define   BusTypLen      5   /*ҵ������*/
#define   RgCFlgLen      1   /*������ִ*/
#define   RgDFlgLen      1   /*�跽��ִ*/
#define   TTxnCdLen      6   /*ǰ�ý�����*/
#define   HTxnCdLen      6   /*����������*/
#define   HTxnSbLen      3   /*������������*/
#define   HLogNoLen      9   /*������ˮ��*/
#define   HTxnStLen      1   /*��������״̬*/
#define   ActDatLen      8   /*�������*/
#define   IsTxnLen       1
#define   HRspCdLen      6   /*����������*/
#define   TxnCnlLen      3   /*��������*/
#define   CnlSubLen      6   /*����ҵ������*/
#define   TxnObjLen      8   /*�����������*/
#define   TlrIdLen       7   /*���ʹ�Ա��*/
#define   TckNoLen      11   /*��Ա����ˮ��*/
#define   ActNoLen      21   /*�ʺ�*/
#define   CdFlagLen      1   /*�����־*/
#define   OrnCntLen      8   /*����*/
#define   UpdFlgLen      1   /*�Ƿ���±�־*/
#define   UpdFldLen    200   /*������*/

#define   TxnSubLen      3   /*��������*/
#define   CnlTypLen      1   /*���׷�ʽ*/
#define   VchCodLen      8   /*ƾ֤����*/
#define   PrtFlgLen      1   /*��ӡ���۱�־*/
#define   CcyTypLen      1   /*�����־*/
#define   PayModLen      1   /*֧����ʽ*/
#define   VchChkLen      1   /*���ۼල��־*/
#define   VchTypLen      3   /*����ƾ֤����*/
#define   TrkModLen      1   /*��ű�־*/
#define   MaskLen        4   /*ժҪ��*/
#define   FeeCodLen      4   /*���ʴ���*/

#define   AgrKndLen      1   /*Э������*/
#define   ActFlgLen      1   /*��������*/
#define   AreaCdLen      3   /*������*/
/*
**���ڣ����������������ļ�
*/
#define   RecLen         449
#define   RecDatLen      447
#define   RcvBNoOffset   0
#define   ROpnBkOffset   RcvBNoOffset+RcvBNoLen
#define   RcvActOffset   ROpnBkOffset+ROpnBkLen
#define   RcvNmOffset    RcvActOffset+RcvActLen
#define   TxnAmtOffset   RcvNmOffset+RcvNmLen 
#define   TBusTpOffset   TxnAmtOffset+TxnAmtLen
#define   UsgCodOffset   TBusTpOffset+TBusTpLen
#define   SmrCodOffset   UsgCodOffset+UsgCodLen
#define   SmrOffset      SmrCodOffset+SmrCodLen
#define   AgrNoOffset    SmrOffset+SmrLen
/*
**���д���
*/
#define   BOCSGN         "301"
/*
**��Ϣ�ļ�����
*/
#define   BankNoLen      12
#define   SwftNoLen      12
#define   CityCdLen      4
#define   BlAreaLen      4
#define   DirBNoLen      12
#define   BnkTypLen      3
#define   BankNmLen      60
#define   SimBNmLen      20
#define   SecBNoLen      12
#define   AdrLen         60
#define   PosCodLen      6
#define   TelNoLen       20
#define   FaxNoLen       20
#define   EMailLen       30
#define   CommanLen      16
#define   DirFlgLen      1
#define   CnpsFgLen      1
#define   EffDatLen      8
#define   IvdDatLen      8
#define   ReMarkLen      60

#define   CodTypLen      6
#define   CodeLen        18
#define   CodSmrLen      40

#define   SysNamLen      20
#define   IdTypeLen      1

#define   CityNmLen      40
#define   UpgCodLen      4
#define   CityFgLen      1

#define   OrgCodLen      12
#define   OrgNamLen      60
#define   OrgActLen      32
#define   OrgANmLen      60

#define   SucFlgLen      1   /*���ʳɹ���־*/
#define   ResultLen      40  /*���ʽ��*/

#define   WebChvLen      8   /*������ˮ��*/
#define   RecNoLen       14  /*ϵͳ��ˮ��*/
#define   DrActLen       21  /*�跽�˺�*/
#define   DrNamLen       60  /*�跽����*/ 
#define   CrActLen       32  /*�����˺�*/
#define   CrNamLen       60  /*��������*/
#define   TxnAmtLen      15  /*���׽��*/
#define   RmkLen         60  /*ժҪ*/
#define   RvsNoLen       12  /*���ʺ�*/
#define   MsgLen         60  /*����*/
#define   OppExcLen      10  /*������*/

#define   ErrMsgLen      60  /*��ʾ��Ϣ*/

#define   TxnMonLen      6   /*�����·�*/
#define   TxnNumLen      6   /*��ϸ����*/
#define   FeeFlgLen      1   /*���ձ�־*/
