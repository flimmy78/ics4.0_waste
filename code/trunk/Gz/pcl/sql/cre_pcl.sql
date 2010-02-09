drop table PclCusAgt;
drop table PclTxnDtl;
drop table PclAccJnl;
drop table PclTmpRpt;
drop table PclTrmAgt;
drop table PclDTxnDtl;
drop table PclITxnDtl;
drop table PclClrInf;
drop table PclDFeeJnl;
drop table PclFeeRat;
--
--
-- POS客户协议表
--
--
create table PclCusAgt
(
  Sts        char(1)      not null,
--状态
  PosTyp     char(1)      not null,
--POS种类( 0-银联  1-间联 )
  BusiNo     char(15)     not null,
--商户号
  CusNam     char(60)     not null,
--商户名
  SysFlg     char(1)      default '0',
--系统内外标志
  DeptNo     char(6)      not null,
--归属部门
  OpnBr      char(6)      not null,
--归属分行
  AgrBr      char(6)      not null,
--代理清算分行
  BankNo     char(12)     not null,
--分行支付行号
  BankNm     char(60)     not null,
--分行支付行名
  AccFlg     char(1)      not null,
--对公对私标志（0-对公 1-存折 2-卡）
  InAcNo     char(21)     not null,
--入帐（挂帐）帐号
  InAcNm     char(60)     not null,
--入帐（挂帐）户名
  InMode     char(1)      not null,
--入帐方式( 0-按交易总额 1-按清算总额 2-按单笔清算额 )
  FeeRat     char(6)      not null,
--手续费率
  TopAmt     char(15)     not null,
--最高额度
  ValDt      char(8)      not null,
--生效日期
  Smr        char(60)     default '',
--备注
  CONSTRAINT PK_PCLCUSAGT PRIMARY KEY( PosTyp,BusiNo )
);
--
--
-- POS客户交易明细表
--
--
create table PclTxnDtl
(
  Sts             char(1)    not null,
--状态( 0-初始 1-已清算 E-错误 A-不清算 B-正在记帐处理 9-?? )
  SeqNo           char(6)    not null,
--序号
  IssCode         char(8)    not null,
--发卡行代号
  RecvIns         char(8)    default '',
--接收方标识
  TranAcc         char(19)   not null,
--交易帐号
  AcqCode         char(8)    not null,
--收单行代号
  ForWins         char(8)    not null,
--转发机构
  AcqIns          char(8)    not null,
--代理方标识
  RefNo           char(12)   not null,
--系统参考号
  CtrDt           char(8)    not null,
--交易发生日
  CtrTime         char(8)    not null,
--交易时间
  CtrTrn          char(6)    not null,
--POS交易流水号
  TranAmt         char(12)   not null,
--交易金额
  MerStandComm    char(6)    not null,
--回扣率
  Mti             char(2)    not null,
--交易类型信息码
  ProcCode        char(6)    not null,
--处理码
  MerType         char(4)    not null,
--商户类型
  CtrPostDate     char(8)    not null,
--清算日（由银联四位扩展）
  TermId          char(8)    not null,
--POS机代号
  MerId           char(15)   not null,
--商户代号
  MerAccFromTbl   char(30)   not null,
--商户帐号
  TranCurr        char(3)    not null,
--交易币别
  ClearAmt        char(12)   not null,
--清算金额
  ManuAuthFlag    char(1)    default '',
--人工授权标志
  GnetAuthFlag    char(1)    default '',
--GNET代授权标志
  AuthCode        char(6)    not null,
--交易授权码
  TxCode          char(3)    not null,
--交易类型标识
  RepCode         char(2)    not null,
--交易响应码
  MerName         char(20)   not null,
--商户名
  OrigCtrTrn      char(6)    default '',
--原中心跟踪号
  OrigRefNo       char(12)   not null,
--调整系统参考号
  EndFlag         char(2)    not null,
--完成标记
  BankFee         char(12)   not null,
--银行应收服务费
  MerFee          char(12)   not null,
--商户应付服务费
  PrvFlg          char(1)    default '',
--个人帐户标识
--PosTyp          char(1)    not null,
--POS种类( 0-银联  1-间联 )
--TrmTyp          char(1)    not null,
--终端种类( 0-银联 1-间联 2-转帐 3-间联二级 4-银联二级 )
--ChkFlg          char(1)    default '0',
--转账POS对账标志( 0-未对 1-已对 )
  InAcNo          char(21)   not null,
--入帐（挂帐）帐号
  CdFlag          char(1)    not null,
--借贷标志
  DeptNo          char(6)    not null,
--归属部门号
  OpnBr           char(6)    not null,
--归属分行号
  AgrBr           char(6)    not null,
--代理清算分行
  BankNo          char(12)   not null,
--支付行号
  AccFlg          char(1)    not null,
--对公对私标志（0-对公 1-存折 2-卡）
  InMode          char(1)    not null,
--入帐方式
  DskNo           char(12)   default '',
--磁盘编号
  LogNo           char(14)   default '',
--前置流水号
  ActDat          char(8)    default '',
--会计日期
  HLogNo          char(9)    default '',
--主机流水号
  TlrId           char(7)    default '',
--银行柜员号
  TckNo           char(12)   default '',
--主机传票号
  HRspCd          char(6)    default '',
--主机响应码
  SPrtNum         char(2)    default '00',
--付款通知书打印次数
  RPrtNum         char(2)    default '00',
--收款通知书打印次数
  ErrMsg          char(60)   default ''
--处理信息
);
CREATE INDEX ni1_PCLTXNDTL ON PclTxnDtl( CtrPostDate, AgrBr, CdFlag, Sts );
CREATE INDEX ni2_PCLTXNDTL ON PclTxnDtl( CtrPostDate, OpnBr, CdFlag, Sts );
--
--
-- POS客户入帐明细表（大小通道使用）
--
--
create table PclAccJnl
(
  LogNo        char(14)     not null,
--前置流水号
  DskNo        char(12)     not null,
--磁盘编号
  BusTyp       char(5)      default 'PCL00',
--业务类型
  CrpCod       char(12)     default 'PCL999999999',
--单位代码
  ActDat       char(8)      not null,
--会计日期
  TTxnCd       char(6)      not null,
--前置交易码
  HTxnCd       char(6)      not null,
--主机交易码
  HLogNo       char(9)      default '',
--主机流水号
  HTxnSt       char(1)      default 'U',
--主机交易状态
  HRspCd       char(6)      default '',
--主机返回码
  IsTxn        char(1)      default 'N',
--是否发送主机标志，用于批量大小通道发送  Y发送N不发送
  TxnCnl       char(3)      default 'PCL',
--交易渠道
  CnlSub       char(10)     default '',
--子渠道
  TxnObj       char(8)      not null,
--大小通道目标服务
  UpdFlg       char(1)      default 'Y',
--更新标志
  UpdFld       char(20)     default 'HTxnCD|TCKNO|BUSTYP',
--更新字段名
  TlrId        char(7)      not null,
--银行柜员号
  TckNo        char(11)     default '',
--会计流水号
  CtrPostDate  char(8)      not null,
--银联清算日期（由银联四位扩展）
  PosTyp       char(1)      not null,
--POS种类( 0-银联  1-间联 )
  MerId        char(15)     not null,
--商户号
  SeqNo        char(6)      not null,
--序号
  ClrAct       char(21)     not null,
--清算账号
  BokAct       char(21)     not null,
--入帐帐号
  SndFlg       char(1)      default '0',
--发送标志( 0-对公 1-存折 2-卡 )
  InMode       char(1)      not null,
--入帐方式
  TranAmt      char(15)     not null,
--交易金额
  ClearAmt     char(15)     not null,
--清算金额
  MerFee       char(15)     not null,
--手续费金额
  DeptNo       char(6)      not null,
--归属部门
  OpnBr        char(6)      not null,
--交易分行
  CdFlag       char(1)      not null,
--清算款项
  CONSTRAINT PK_PCLACCJNL PRIMARY KEY( LogNo )
);
CREATE INDEX ni1_PCLACCJNL ON PclAccJnl( CtrPostDate, OpnBr, PosTyp, MerId, CdFlag );
--
--
-- POS客户入帐报表
--
--
create table PclTmpRpt
(
  MerId         char(15)     not null,
--商户号
  CtrPostDate   char(8)      not null,
--银联清算日（由银联四位扩展）
  TlrId         char(7)      default '',
--银行柜员号
  TckNo         char(11)     default '',
--主机传票号
  InAcNo        char(21)     not null,
--入帐帐号
  TranAmt       char(15)     default '0',
--交易金额
  ClearAmt      char(15)     default '0',
--清算金额
  BankFee       char(15)     default '0',
--银行应收手续费
  MerFee        char(15)     default '0',
--商户应付手续费
  InMode        char(1)      not null,
--入帐方式
  OpnBr         char(6)      not null,
--开户分行
  MerAccFromTbl char(30)     not null,
--商户帐号
  MerName       char(20)     not null
--商户户名
);
CREATE INDEX ni1_PCLTMPRPT ON PclTmpRpt( MerId );
--
--
-- POS转帐资料维护
--
--
create table PclTrmAgt
(
  PosTyp   char(1)   not null,
--POS种类( 0-银联  1-间联 )
  MerId    char(15)  not null,
--商户号
  TermId   char(8)   not null,
--POS机代号
  TrmTyp   char(1)   not null,
--终端种类( 0-银联 1-间联 2-转帐 3-间联二级 4-银联二级 )
  CusNam   char(60)  not null,
--转帐商户名
  InAcNo   char(21)  not null,
--清算帐号
  InAcNm   char(60)  not null,
--清算账户
  UniNo    char(4)   not null,
--电话号码类型  0001：移动；0002：联通；0003：小灵通；0004：固定电话
  MobTel   char(15)  not null,
--手机号码
  Addr     char(60)  default '',
--地址
  FeeMod   char(1)   not null,
--客户手续收费模式
  FeeRat   char(6)   not null,
--客户手续费率
  FeeAmt   char(15)  not null,
--客户手续额度
  TFeeMod  char(1)   not null,
--客户手续收费模式
  TFeeRat  char(6)   not null,
--客户手续费率
  TFeeAmt  char(15)  not null,
--客户手续额度
  DeptNo   char(6)   not null,
--归属部门
  OpnBr    char(6)   not null,
--开户分行
  Sts      char(1)   not null,
--状态( 0-开通 1-作废 )
  constraint PK_PCLTRMAGT PRIMARY KEY( PosTyp, MerId, TermId )
);
--
--
-- 转账POS成功交易明细(清算)表
--
--
create table PclDTxnDtl
(
  TxnSts        char(1)    default '0',
--状态
  RefNo         char(12)   not null,
--系统参考号（由银联对帐文件的交易时间＋POS机流水号构成）
  CtrPostDate   char(8)    not null,
--清算日（由银联四位扩展）
  CtrDt         char(8)    not null,
--交易发生日
  CtrTime       char(6)    not null,
--交易时间
  TranAcc       char(19)   not null,
--转出卡帐号
  DMti          char(4)    not null,
--交易类型信息码
  ProcCode      char(6)    not null,
--处理码
  CdFlag        char(1)    not null,
--借贷标志
  TranAmt       char(12)   not null,
--交易金额
  TxnAmt        char(15)   not null,
--清算金额
  FeeAmt        char(15)   not null,
--手续费金额
  BnkFee        char(15)   not null,
--银行手续费
  ThdFee        char(15)   not null,
--天信手续费
  OrigRefNo     char(12)   not null,
--调整系统参考号
  MerId         char(15)   not null,
--商户代号
  TermId        char(8)    not null,
--POS机代号
  CtrTrn        char(6)    not null,
--POS交易流水号
  RepCode       char(6)    not null,
--交易响应码
  BankId        char(6)    not null,
--银行代码
  TBusTp        char(4)    not null,
--业务代码
  LogNo         char(14)   default '',
--前置流水号
  ActDat        char(8)    default '',
--会计日期
  HTxnSt        char(1)    default 'U',
--主机交易状态
  HRspCd        char(6)    default '',
--主机返回码
  TlrId         char(7)    default '',
--银行柜员号
  ClrAct        char(21)   not null,
--行内清算账户
  ActNo         char(21)   not null,
--转入卡帐号
  ActNm         char(60)   not null,
--转入卡名称
  TckNo         char(11)   default '',
--会计流水号
  DeptNo        char(6)    not null,
--部门号
  OpnBr         char(6)    not null,
--开户分行
  ErrMsg        char(60)   default '',
--处理信息
  constraint PK_PCLDTXNDTL PRIMARY KEY( RefNo )
);
CREATE INDEX ni1_PCLDTXNDTL ON PclDTxnDtl( CtrPostDate, TxnSts );
--
--
-- 间联POS成功交易明细(清算)表
--
--
create table PclITxnDtl
(
  TxnSts        char(1)    default '0',
--状态
  CtrPostDate   char(8)    not null,
--清算日（由银联四位扩展）
  TranAmt       char(12)   not null,
--交易金额
  TxnAmt        char(15)   not null,
--清算金额
  FeeAmt        char(15)   not null,
--手续费金额
  PosTyp        char(1)    not null,
--终端种类
  MerId         char(15)   not null,
--商户代号
  TrmTyp        char(1)    not null,
--终端种类( 0-银联 1-间联 2-转帐 3-间联二级 4-银联二级 )
  TermId        char(8)    not null,
--POS机代号
  LogNo         char(14)   not null,
--前置流水号
  ActDat        char(8)    default '',
--会计日期
  HTxnSt        char(1)    default 'U',
--主机交易状态
  HRspCd        char(6)    default '',
--主机返回码
  ClrAct        char(21)   not null,
--行内清算账户
  ActNo         char(21)   not null,
--转入卡帐号
  ActNm         char(60)   not null,
--转入卡名称
  TckNo         char(11)   default '',
--会计流水号
  DeptNo        char(6)    not null,
--部门号
  OpnBr         char(6)    not null,
--开户分行
  ErrMsg        char(60)   default '',
--处理信息
  constraint PK_PCLITXNDTL PRIMARY KEY( LogNo )
);
CREATE INDEX ni1_PCLITXNDTL ON PclITxnDtl( CtrPostDate, TxnSts );
--
--
-- POS清算信息表
--
--
create table PclClrInf
(
  BrNo     char(6)   not null,
--清算分行
  ClrDat   char(8)   not null,
--清算日期
  PosTyp   char(1)   not null,
--POS种类( 0-银联  1-间联 )
  TrmTyp   char(1)   not null,
--终端种类( 0-银联 1-间联 2-转帐 3-间联二级 4-银联二级)
  SysSts   char(1)   not null,
--系统状态( 0-数据正在读入 1-数据读入成功 2-客户清算正在进行 3-客户清算完成 4-手续费清算正在进行 5-手续费清算完成 )
  DskNo    char(12)  default '',
--磁盘编号
  constraint PK_PCLCLRINF PRIMARY KEY( BrNo, ClrDat, PosTyp, TrmTyp )
);
--
--
-- 转帐POS手续费清算表
--
--
create table PclDFeeJnl
(
  LogNo    char(14)  not null,
--前置流水号
  ClrBr    char(6)   not null,
--清算分行
  ClrDat   char(8)   not null,
--清算日期
  ClrTyp   char(1)   not null,
--清算种类( 0-行内 1-天信)
  ActDat   char(8)   not null,
--会计日期
  HTxnSt   char(1)   default 'U',
--主机交易状态
  HRspCd   char(6)   default '',
--主机返回码
  TlrId    char(7)   not null,
--银行柜员号
  TckNo    char(11)  default '',
--会计流水号
  ClrAct   char(21)  not null,
--清算账号
  FeeAct   char(21)  not null,
--入帐帐号或手续费帐号
  TxnAmt   char(15)  not null,
--手续费金额
  constraint PK_PCLDFEEJNL PRIMARY KEY( LogNo )
);
--
--
-- 转帐POS手续费表
--
--
create table PclFeeRat
(
  Sts      char(1)   not null,
--状态( 0-有效 1-无效 )
  SysFlg   char(1)   not null,
--系统标志( 0-银联 1-转帐 )
  BrNo     char(6)   not null,
--分行号
  MinAmt   char(15)  not null,
--最低金额
  MaxAmt   char(15)  not null,
--最高金额
  FeeMod   char(1)   not null,
--手续收费模式
  FeeRat   char(5)   not null,
--费率
  FeeAmt   char(15)  not null,
--额度
  ValDt    char(8)   not null,
--生效日期
  constraint PK_CBSFEERAT PRIMARY KEY( SysFlg, BrNo, MinAmt, MaxAmt )
);
