drop table HawCrpInf;
drop table HawPrvInf;
drop table HawCrpTxn;
drop table HawPrvTxn;
--
--
--
--单位信息表
--
--
--
create table HawCrpInf
(
	TCrpCd   char(50)   not null,
--单位代码
	TCrpNm   char(60)   default '',
--单位名称
	TCrpAd   char(200)  default '',
--单位名称
	MailCd   char(10)   default '',
--邮政编码
  AreaCd   char(10)   default '',
--所在区
  TelNum   char(20)   default '',
--联系电话
  TelNam   char(20)   default '',
--联系人
  TFulNm   char(60)   default '',
--主管单位全称
  TCrpId   char(20)   default '',
--法人资格
  EConTp   char(20)   default '',
--经济类型
  TCrpTp   char(20)   default '',
--单位性质
  TCrpBL   char(20)   default '',
--隶属关系
  TFncBn   char(50)   default '',
--财政负担
  TCrpBn   char(50)   default '',
--单位负担
  PrYear   char(10)   default '',
--发放年限
  PayDat   char(50)   default '',
--发薪日
  DepNum   char(10)   default '',
--汇储人数
  DepAmt   char(50)   default '',
--月汇储总额
  PerNum   char(10)   default '',
--一次性发放人数
  PreAmt   char(50)   default '',
--一次性发放总额
	CrpFrm   char(10)   default '',
  constraint PK_HAWCRPINF PRIMARY KEY( TCrpCd )
);
--
--
--
--客户信息表
--
--
--
create table HawPrvInf
(
  IdNo     char(20)   not null,
--证件号码
  PrvNam   char(60)   default '',
--客户姓名
	MonCnt   char(5)    default '',
--补贴月数
  PMCntO   char(5)    default '',
--计发月数【一次性】
  PMAmtO   char(15)   default '',
--领发金额
  PMCnt    char(5)    default '',
--计发月数【逐月】
  BegTim   char(8)    default '',
--开始时间
  EndTim   char(8)    default '',
--结束日期
  MonAmt   char(15)   default '',
--月汇储额
  AmtStd   char(15)   default '',
--补贴标准
  PrvFrm   char(20)   default '',
--个人开户表号
  TRecNo   char(5)    default '',
--序号
	Duty     char(20)   default '',
--职务
	TCrpCd   char(50)   default '',
--单位代码
	TCrpNm   char(60)   default '',
--单位名称
  constraint PK_HAWPRVINF PRIMARY KEY( IdNo )
);
--
--
--
--单位业务流水表
--
--
--
create table HawCrpTxn
(
	TLogNo   char(19)   not null,
--交易流水号
	TCrpCd   char(50)   not null,
--单位代码
	CrpAct   char(30)   not null,
--单位账号
	TTxnTp   char(1)    not null,
--交易类型( 1-收入 2-支出 3-利息 )
	TxnAmt   char(15)   not null,
--交易金额
	TrAcDt   char(8)    not null,
--交易日期
	CrpBal   char(15)   not null,
--对公余额
	SndFlg   char(1)    default '0',
--记录发送状态( 0-未发送 1-已发送 )
	Sts      char(1)    default '0',
--记录状态( 0-有效 1-无效 )
  constraint PK_HAWCRPTXN PRIMARY KEY( TLogNo )
);
--
--
--
--个人业务流水表
--
--
--
create table HawPrvTxn
(
	TLogNo   char(19)   not null,
--交易流水号
  IdNo     char(20)   not null,
--证件号码
	PrvAct   char(30)   not null,
--个人账号
	TTxnTp   char(1)    not null,
--交易类型( 1-收入 2-支出 3-利息 )
	TxnAmt   char(15)   not null,
--交易金额
	TrAcDt   char(8)    not null,
--交易日期
	PrvBal   char(15)   not null,
--个人余额
	CrpAct   char(30)   not null,
--单位账号
	SndFlg   char(1)    default '0',
--记录发送状态( 0-未发送 1-已发送 )
	Sts      char(1)    default '0',
--记录状态( 0-有效 1-无效 )
  constraint PK_HAWPRVTXN PRIMARY KEY( TLogNo )
);
