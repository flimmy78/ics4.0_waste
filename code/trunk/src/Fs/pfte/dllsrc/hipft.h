/*ԭ�Ӻ�������ֵ����*/
#define   MsgTypLen      1   /*����������*/
#define   RspCodLen      6   /*������*/
#define   RspMsgLen     56   /*������Ϣ*/
/*������*/
#define   RPTPTH         "dat/term/send"
#define   PrtBufLen    180   /*��ӡ����*/
#define   AmtBufLen     20   /*��д���*/
#define   BufLen        80   /*��ʱ����*/
/*�������*/
#define   NodNoLen       6   /*���ź�*/
#define   BrNoLen        6   /*���к�*/
#define   MsgFmtLen      6   /*��Ϣ��ʽ��*/
#define   ClrDatLen      8   /*��������*/
#define   SndCodLen     12   /*���ͷ�����*/
#define   RcvCodLen     12   /*���շ�����*/
#define   ClrSceLen      4   /*���㳡��*/
#define   ActTypLen      1   /*�ʺ�����*/
#define   ActNoLen      21   /*�����ʺ�*/
#define   FilNamLen     32   /*�����ļ���*/
#define   PrtDatLen      8   /*��ӡ����*/
#define   RptFilLen    256   /*�����ļ�����·��*/
/*�α����*/
#define   FilSeqLen     10   /*�ļ����*/
#define   RcvBNoLen     11   /*���մ������к�*/
#define   RcvBNmLen     60   /*���մ���������*/
#define   ActDatLen      8   /*�����ύ����*/
#define   SndActLen     35   /*�տ��ʺ�*/
#define   RcvActLen     35   /*�ɿ��ʺ�*/
#define   ActNamLen     60   /*����������*/
#define   TxnAmtLen     15   /*���׽��*/
#define   TaxNoLen      20   /*��˰��ʶ���*/
#define   TaxNamLen    100   /*��˰������*/
#define   TCrpNmLen     60   /*���ջ�������*/
#define   TLogNoLen     16   /*���ջ�����ˮ��*/
#define   FskNamLen     60   /*�տλ(����)����*/
#define   DtlNumLen      3   /*��ϸ��Ŀ*/
#define   DtlSeqLen      3   /*��ϸ˳���*/
#define   TaxTypLen     40   /*˰������*/
#define   PrjNamLen     60   /*ƷĿ����*/
#define   LvlNamLen     40   /*Ԥ�㼶������*/
#define   TaxDtLen      17   /*˰����������*/
#define   DtlAmtLen     15   /*��ϸ���*/
#define   TSubCdLen     12   /*Ԥ���Ŀ����*/
#define   TVchNoLen     24   /*����˰Ʊ��(ƾ֤��)*/
#define   PrtCntLen      2   /*��ӡ����*/
#define   SmrLen       200   /*��ע*/
/*��˰��ӡ���ݺ�����*/
#define   PrtDatLoc     16 	 /*�����*/
#define	 	TVchNoLoc	    72   /*����˰Ʊ��*/ 
#define   TaxNoLoc      18   /*��˰�˱���*/
#define   TaxNamLoc     18   /*��˰��ȫ��*/
#define   RcvActLoc     18   /*�������ʺ�*/
#define   TCrpNmLoc     68   /*���ջ�������*/
#define   RcvBNmLoc     68   /*���մ���������*/
#define   FskNamLoc     68   /*�տ����(����)����*/

#define   CapAmtLoc     42   /*��д���*/
#define   TxnAmtLoc     84 	 /*���׽��Сд*/

#define		ItmNamLoc			44	 /*��������*/ 
#define		TActDtLoc			74	 /*�ɿ�����*/
#define   PrtCntLoc     95   /*��ӡ����*/

#define   MaxRow        10   /*�����ϸ��¼��*/
#define   TaxTypLoc     12   /*˰��*/
#define 	LvlNamLoc		  36   /*Ԥ���Ŀ��Ԥ�㼶��*/
#define   TaxDtLoc      62   /*����ʱ��*/
#define   DtlAmtLoc     84   /*��ϸ���*/

/*�˿��ӡ���ݺ�����*/
#define   PrtDatLoc_Rt  12 	 /*�����*/
#define   TaxNoLoc_Rt   12   /*��˰�˱���*/
#define   TaxNamLoc_Rt  12   /*��˰��ȫ��*/
#define   RcvActLoc_Rt  12   /*�������ʺ�*/
#define	 	TLogNoLoc_Rt	62   /*����˰Ʊ��*/ 
#define   TCrpNmLoc_Rt  62   /*���ջ�������*/
#define   RcvBNmLoc_Rt  62   /*���մ���������*/
#define   FskNamLoc_Rt  62   /*�տ����(����)����*/

#define		TSubCdLoc_Rt	12	 /*Ԥ���Ŀ*/
#define   LvlNamLoc_Rt	23	 /*Ԥ�㼶�Σ��˿⣩*/
#define		TRtnCdLoc_Rt	37	 /*�˿�ԭ��*/
#define   DtlAmtLoc_Rt  68   /*��ϸ���*/

#define   CapAmtLoc_Rt  12   /*��д���*/
#define   TxnAmtLoc_Rt  68 	 /*���׽��Сд*/

#define		ItmNamLoc_Rt	12	 /*��������*/ 
#define		TActDtLoc_Rt	40	 /*�ɿ�����*/
#define   PrtCntLoc_Rt  62   /*��ӡ����*/

#define 	NodNoLoc_Rt	  12	 /*��ӡ����*/
#define 	TlrIdLoc_Rt	  40	 /*��ӡ��Ա*/

/*��ɽ ETS*/
#define   PftFilLen     60   /*�ļ���*/
#define   ErrNumLen      6   /*�������*/
#define   ErrAmtLen     15   /*������*/
#define   LogNoLen      14   /*ǰ����ˮ��*/
#define   TCrpCdLen     11   /*���ջ��ش���*/
#define   TCrpTpLen      1   /*���ջ�������*/
#define   TActDtLen      8   /*���ջ�������*/
#define   FskCodLen     11   /*�������*/
#define   TTxnTpLen      2   /*��������*/
#define   RtnCodLen      8   /*��������*/
#define   TPayTpLen      1   /*�ɿʽ����*/
#define   PrtFlgLen      1   /*��ӡ��˰��־*/
#define   CrpKndLen      4   /*��ҵע������*/
#define   TRtnCdLen     10   /*�˿�ԭ�����*/
#define		TRtnNmLen			30	 /*�˿�ԭ��*/
#define	  TRtnTpLen      1   /*��˰����*/
#define   Rmk1Len        7   /*������һ*/
#define   Rmk2Len       16   /*�������*/
