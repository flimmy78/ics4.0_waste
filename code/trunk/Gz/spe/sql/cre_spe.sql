drop table SpeCusInf;
drop table SpeNodInf;
drop table SpeTxnInf;
drop table SpeTxnDtl;
--
--
-- 客户类别数据表
--
--
create table SpeCusInf
(
	cunb      char(13) not null,
-- 客户号
	acnm      char(30) not null,	
--户名
--idtp      char(2)  not null,	
--证件种类 
	idno      char(20) not null, 
-- 证件号 
	cutp	    char(16) not null,
--客户类别 
	snum      int      default 0
--查询次数
);
CREATE INDEX ni1_SPECUSINF ON SpeCusInf( cunb );
--
--
-- 网点管理员数据表
--
--
create table SpeNodInf
(
	NodNo     char(6)  not null,
--网点号
	NodNam    char(60) not null,	
--网点名
	MagNam    char(10) not null, 
--管理员名称
	MagLvl    char(1)  not null,
--管理员级别
	UniNo     char(4)  not null,
--手机类型
	MobTel    char(15) not null,
--手机号码
	Sts       char(1)  not null,
	constraint PK_SPENODINF PRIMARY KEY(NodNo,MobTel)
);
--
--
-- 网点业务量数据表
--
--
create table SpeTxnInf
(
	BrNo     char(6)   not null,
--分行号
	NodNo    char(6)   not null,
--网点号
	ActDat   char(8)   not null,
--会计日期
	TlrId    char(7)   not null,
--柜员号
	FTxnTm   char(14)  not null,
--前置交易时间
	ActNo    char(21)  default '',
--查询帐号
	Cunb     char(13)  default ''
--客户号
);
--
--
-- 交易明细数据表
--
--
create table SpeTxnDtl
(
	TckNo   char(11)   default '',
--会计流水号
	CardNo  char(19)   default '',
--卡号
	ActNo   char(21)   default '',
--账号
	BokDat  char(8)    default '',
--记账日期
	TxnSmr  char(60)   default '',
--摘要
	CdFlag  char( 1)   default '',
--借贷标志
	BokAmt  char(15)   not null,
--记账金额
	Bal     char(15)   not null,
--余额
	BTxnCd  char(6)    default '',
--交易码
	BSubCd  char(3)    default '',
--交易子码
  Year    char(4)    default '',
--年
  PgNum   char(6)    default '',
--页号
  PgSeq   char(2)    default '',
--页内笔序号
  OppAct  char(32)   default '',
--对方帐号
  OppNam  char(60)   default '',
--对方户名
	TxnNod  char( 6)   default '',
--交易网点
	CcyCod  char( 3)   default '',
--货币
	TxnLog  char(18)   default '',
--交易日志号
	TxnAdr  char(60)   default '',
--交易地点
	TxnDat  char( 8)   default '',
--交易日期
	TxnTim  char( 6)   default '',
--交易时间
	AuthCd  char( 6)   default ''
--授权号
);
