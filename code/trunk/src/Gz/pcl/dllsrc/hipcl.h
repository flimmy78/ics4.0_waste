#define   CdFlagLen             1
#define   AccFlgLen             1
#define   BankNoLen            12
#define   PrtNumLen             2
#define   ErrMsgLen            60
#define   FeeRatLen             6
#define   TopAmtLen            15
#define   StsLen                1
#define   ActSqLen              5
/*
**	��Сͨ���������ݱ�
*/
#define   LogNoLen             14
#define   DskNoLen             12
#define   BusTypLen             5
#define   CrpCodLen            12
#define   ActDatLen             8
#define   TTxnCdLen             6
#define   HTxnCdLen             6
#define   HTxnSbLen             3
#define   HLogNoLen             9
#define   HRspCdLen             6
#define   HTxnStLen             1
#define   IsTxnLen              1
#define   TxnCnlLen             3
#define   CnlSubLen            10
#define   TxnObjLen             8
#define   TlrIdLen              7
#define   TckNoLen             11
#define   UpdFlgLen             1
#define   UpdFldLen           200
#define   BrNoLen               6
#define   SndFlgLen             1   /* ��˽�ʻ���ʶ */
#define   ActNoLen             21   /* ���ʿ��Ż��ۺ� */
#define   TxnAmtLen            15   /* ���׽�� */
/*
**	�α����
*/
#define   RepFlgLen             1   /* ��־ */
#define   OrnCntLen             8   /* �����ܱ��� */
#define   InAcNoLen            21		/* �����ʻ� */
#define   DeptNoLen             6   /* ���ź� */
#define   AccFlgLen             1   /* �ʻ����� */
#define   InModeLen             1   /* ���ʷ�ʽ */
#define   PosTypLen             1   /* �̻����� */
/*
**	POS�ļ����ݽṹ
*/
#define   MsgLen              279   /* ������ϸ���� */
#define   SeqNoLen              6   /* ��� */
#define   IssCodeLen            8   /* �����д��� */
#define   RecvInsLen            8   /* ���շ���ʶ */
#define   TranAccLen           19   /* �����ʺ� */
#define   AcqCodeLen            8   /* �յ��д��� */
#define   ForwInsLen            8   /* ת������ */
#define   AcqInsLen             8   /* ������ʶ */
#define   RefNoLen             12   /* ϵͳ�ο��� */
#define   CtrDtLen              8   /* ���׷����� */
#define   CtrTimeLen            8   /* ����ʱ�� */
#define   CtrTrnLen             6   /* POS������ˮ�� */
#define   TranAmtLen           12   /* ���׽�� */
#define   MerStandCommLen       4   /* �ؿ��� */
#define   MtiLen                2   /* ����������Ϣ�� */
#define   ProcCodeLen           6   /* ������ */
#define   MerTypeLen            4   /* �̻����� */
#define   CtrPostDateLen        4   /* ������ */
#define   TermIdLen             8   /* POS������ */
#define   MerIdLen             15   /* �̻����� */
#define   MerAccFromTblLen     30   /* �̻��ʺ� */
#define   TranCurrLen           3   /* ���ױұ� */
#define   ClearAmtLen          12   /* ������ */
#define   ManuAuthFlagLen       1   /* �˹���Ȩ��־ */
#define   GnetAuthFlagLen       1   /* GNET����Ȩ��־ */
#define   AuthCodeLen           6   /* ������Ȩ�� */
#define   TxCodeLen             3   /* �������ͱ�ʶ */
#define   RepCodeLen            2   /* ������Ӧ�� */
#define   MerNameLen           20   /* �̻��� */
#define   OrigCtrTrnLen         6   /* ԭ���ĸ��ٺ� */
#define   OrigRefNoLen         12   /* ����ϵͳ�ο��� */
#define   EndFlagLen            2   /* ��ɱ�� */
#define   BankFeeLen           12   /* ����Ӧ�շ���� */
#define   MerFeeLen            12   /* �̻�Ӧ������� */
#define   OCtrDtLen            10   /* ԭ��������ʱ�� */
#define   PrvFlgLen             1   /* �����˻���־ */


#define   SeqNoOffset           0
#define   IssCodeOffset         SeqNoOffset+SeqNoLen
#define   RecvInsOffset         IssCodeOffset+IssCodeLen
#define   TranAccOffset         RecvInsOffset+RecvInsLen
#define   AcqCodeOffset         TranAccOffset+TranAccLen
#define   ForwInsOffset         AcqCodeOffset+AcqCodeLen
#define   AcqInsOffset          ForwInsOffset+ForwInsLen
#define   RefNoOffset           AcqInsOffset+AcqInsLen
#define   CtrDtOffset           RefNoOffset+RefNoLen
#define   CtrTimeOffset         CtrDtOffset+CtrDtLen
#define   CtrTrnOffset          CtrTimeOffset+CtrTimeLen
#define   TranAmtOffset         CtrTrnOffset+CtrTrnLen
#define   MerStandCommOffset    TranAmtOffset+TranAmtLen
#define   MtiOffset             MerStandCommOffset+MerStandCommLen
#define   ProcCodeOffset        MtiOffset+MtiLen
#define   MerTypeOffset         ProcCodeOffset+ProcCodeLen
#define   CtrPostDateOffset     MerTypeOffset+MerTypeLen
#define   TermIdOffset          CtrPostDateOffset+CtrPostDateLen
#define   MerIdOffset           TermIdOffset+TermIdLen
#define   MerAccFromTblOffset   MerIdOffset+MerIdLen
#define   TranCurrOffset        MerAccFromTblOffset+MerAccFromTblLen
#define   ClearAmtOffset        TranCurrOffset+TranCurrLen
#define   ManuAuthFlagOffset    ClearAmtOffset+ClearAmtLen
#define   GnetAuthFlagOffset    ManuAuthFlagOffset+ManuAuthFlagLen
#define   AuthCodeOffset        GnetAuthFlagOffset+GnetAuthFlagLen
#define   TxCodeOffset          AuthCodeOffset+AuthCodeLen
#define   RepCodeOffset         TxCodeOffset+TxCodeLen
#define   MerNameOffset         RepCodeOffset+RepCodeLen
#define   OrigCtrTrnOffset      MerNameOffset+MerNameLen
#define   OrigRefNoOffset       OrigCtrTrnOffset+OrigCtrTrnLen
#define   EndFlagOffset         OrigRefNoOffset+OrigRefNoLen
#define   BankFeeOffset         EndFlagOffset+EndFlagLen
#define   MerFeeOffset          BankFeeOffset+BankFeeLen
#define   PrvFlgOffset          MerFeeOffset+MerFeeLen
/*
**	ת��POS
*/
#define   UniNoLen    4
#define   MobTelLen   15
#define   BankIdLen   6
#define   TBusTpLen   4
#define   ActNmLen    60
#define   DMtiLen     4
#define   FlagLen     1
#define   SysFlgLen   1
/*
**	����POS
*/
#define   TrmTypLen   1
#define   TotNumLen   6
#define   TotAmtLen   15
#define   TotFeeLen   15
#define   TTxnTmLen   19
#define   TTxnSmLen   4
#define   MaxBufLen   15
#define   DateLen     6
#define   SerialLen   8
