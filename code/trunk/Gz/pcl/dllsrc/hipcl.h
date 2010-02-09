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
**	大小通道上送数据表
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
#define   SndFlgLen             1   /* 对私帐户标识 */
#define   ActNoLen             21   /* 入帐卡号或折号 */
#define   TxnAmtLen            15   /* 交易金额 */
/*
**	游标参数
*/
#define   RepFlgLen             1   /* 标志 */
#define   OrnCntLen             8   /* 入帐总笔数 */
#define   InAcNoLen            21		/* 入帐帐户 */
#define   DeptNoLen             6   /* 部门号 */
#define   AccFlgLen             1   /* 帐户性质 */
#define   InModeLen             1   /* 入帐方式 */
#define   PosTypLen             1   /* 商户类型 */
/*
**	POS文件数据结构
*/
#define   MsgLen              279   /* 单条明细长度 */
#define   SeqNoLen              6   /* 序号 */
#define   IssCodeLen            8   /* 发卡行代号 */
#define   RecvInsLen            8   /* 接收方标识 */
#define   TranAccLen           19   /* 交易帐号 */
#define   AcqCodeLen            8   /* 收单行代号 */
#define   ForwInsLen            8   /* 转发机构 */
#define   AcqInsLen             8   /* 代理方标识 */
#define   RefNoLen             12   /* 系统参考号 */
#define   CtrDtLen              8   /* 交易发生日 */
#define   CtrTimeLen            8   /* 交易时间 */
#define   CtrTrnLen             6   /* POS交易流水号 */
#define   TranAmtLen           12   /* 交易金额 */
#define   MerStandCommLen       4   /* 回扣率 */
#define   MtiLen                2   /* 交易类型信息码 */
#define   ProcCodeLen           6   /* 处理码 */
#define   MerTypeLen            4   /* 商户类型 */
#define   CtrPostDateLen        4   /* 清算日 */
#define   TermIdLen             8   /* POS机代号 */
#define   MerIdLen             15   /* 商户代号 */
#define   MerAccFromTblLen     30   /* 商户帐号 */
#define   TranCurrLen           3   /* 交易币别 */
#define   ClearAmtLen          12   /* 清算金额 */
#define   ManuAuthFlagLen       1   /* 人工授权标志 */
#define   GnetAuthFlagLen       1   /* GNET代授权标志 */
#define   AuthCodeLen           6   /* 交易授权码 */
#define   TxCodeLen             3   /* 交易类型标识 */
#define   RepCodeLen            2   /* 交易响应码 */
#define   MerNameLen           20   /* 商户名 */
#define   OrigCtrTrnLen         6   /* 原中心跟踪号 */
#define   OrigRefNoLen         12   /* 调整系统参考号 */
#define   EndFlagLen            2   /* 完成标记 */
#define   BankFeeLen           12   /* 银行应收服务费 */
#define   MerFeeLen            12   /* 商户应付服务费 */
#define   OCtrDtLen            10   /* 原交易日期时间 */
#define   PrvFlgLen             1   /* 个人账户标志 */


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
**	转帐POS
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
**	间联POS
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
