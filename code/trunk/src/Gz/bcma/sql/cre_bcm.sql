drop table BcmActReg441;
drop table BcmTxnJnl441;
--
--
-- BCM集团客户帐号登记表
--
--
create table BcmActReg441
(
	Sts     char(1)      not null,
--状态( 0-有效	1-无效 )
	MActNo  char(21)     not null,
--集团主帐号
	SActNo  char(21)     not null,
--集团子帐号
	SActNm  char(60)     not null,
--集团子帐号户名
	MaxAmt  char(15)     not null,
--最大金额
	Rmk     char(60)     default '',
--相关信息
	ValDat  char(8)      not null,
--生效日期
	BltTlr  char(7)      not null,
--建立柜员
	BltNod  char(6)      not null,
--建立部门
	UpdTlr  char(7)      default '',
--修改柜员
	UpdNod  char(6)      default '',
--修改部门
	UpdDat  char(8)      default '',
--修改日期
	constraint PK_BCMACTREG441 PRIMARY KEY( MActNo, SActNo )
);
--
--
-- BCM集团交易流水表
--
--
create table BcmTxnJnl441
(
	TxnSts  char(1)   not null,
--状态
	LogNo   char(14)  not null,
--前置流水号
	MActNo  char(21)  not null,
--集团主帐号
	MActNm  char(60)  not null,
--集团主帐号户名
	SActNo  char(21)  not null,
--集团子帐号
	SActNm  char(60)  not null,
--集团子帐号户名
	TxnAmt  char(15)  not null,
--划款金额
	Smr     char(60)  default '',
--划款原因
	PrtCnt  char(2)   default '00',
--打印次数
	TlrId   char(7)   not null,
--记帐柜员
	Sup1Id  char(7)   default '',
--复核(授权柜员)
	Sup2Id  char(7)   default '',
--复核(授权柜员)
	NodNo   char(6)   not null,
--交易网点
	BusTyp  char(5)   not null,
--业务类型
	TTxnCd  char(6)   not null,
--前置交易码
	HTxnCd  char(6)   not null,
--主机交易码
	ActDat  char(8)   default '',
--会计日期
	HLogNo  char(9)   default '',
--主机流水号
	TckNo   char(11)  default '',
--会计流水号
	HTxnSt  char(1)   default '',
--主机交易状态
	HRspCd  char(6)   default '',
--主机返回码
	constraint PK_BCMTXNJNL441 PRIMARY KEY( LogNo )
);
