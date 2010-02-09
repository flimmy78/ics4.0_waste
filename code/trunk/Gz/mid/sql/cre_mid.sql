drop table MidTxnJnl;
--
--
--统一支付平台流水表
--
--
create table MidTxnJnl
(
	LogNo      char(14)  not null,
--前置流水号
	TTxnCd     char(10)  not null,
--第三方交易码
	TxnCod     char(6)   not null,
--交易码
	TxnTyp     char(1)   not null,
--交易类型( N-正常交易 C-冲正交易 R-重发交易)
	BusTyp     char(6)   default '',
--业务类型
	CrpCod     char(10)  default '',
--单位代码
	ActDat     char(8)   not null,
--会计日期
	CcyCod     char(3)   default '',
--货币代码
	TxnAmt     char(15)  not null,
--交易金额
	Fee        char(15)  default '0',
--手续费金额
	ActNo      char(21)  default '',
--客户帐号
	ActNam     char(60)  default '',
--客户名称
	OrgNo      char(6)   default '',
--机构号
	NodNo      char(6)   default '',
--银行网点号                                                
	TlrId      char(7)   not null,
--银行柜员号                                                
	CntrId     char(10)  default '',
--银行柜台号
	NodTrc     char(20)  default '',
--网点流水号
	TxnCnl     char(3)   default '',
--交易渠道
	ItgTyp     char(1)   not null,
--完整性类型( 0-非冲正 1-手动冲正 2-系统冲正 6-重发 )
	FTxnTm     char(14)  not null,
--前置交易时间
	FRspCd     char(6)   default '',
--前置响应码
	HLogNo     char(9)   default '',
--主机流水号
	TckNo      char(11)  default '',
--会计流水号
	HRspCd     char(6)   default '',
--主机响应码
	HTxnSt     char(1)   default 'U',
--主机交易状态( S-成功 F-失败 R-被冲正 U-预记状态 E-差错 )
	HPrChk     char(1)   default '0',
--与主机日间对帐标志( 0-未对帐 1-已对帐 2-对帐不符 )
	HLsChk     char(1)   default '0',
--与主机日终对帐标志( 0-未对帐 1-已对帐 2-对帐不符 )
	TCusId     char(30)  default '0',
--代理服务客户标识
	TCusNm     char(60)  default '',
--代理服务客户姓名
	TActDt     char(8)   default '',
--第三方帐务日期(授权凭证登记日期)
	TLogNo     char(20)  default '',
--第三方流水号
	TRspCd     char(10)  default '',
--第三方响应码
	TTxnSt     char(1)   default 'U',
--第三方交易状态(  S-成功 F-失败 R-被冲正 U-预记状态 T-超时 )
	ThdChk     char(1)   default '0',
--与第三方对帐标志( 0-未对帐 1-已对帐 )
	TxnSts     char(1)   default 'U',
--交易状态( S-成功 F-失败 R-被冲正 U-预记状态 )
	TxnAtr     char(32)  default '',
--交易属性
	MstChk     char(1)   default '',
--要求对帐标志( 0-不需对帐 1-必须对帐 )
	LChkTm     char(10)  default '',
--上次对帐时间
	BrNo       char(6)   not null,
--分行号
	BokFlg     char(1)   not null,
--记帐标志( 0－记帐、1－不记帐 )
	BchFlg     char(1)   not null,
--报文种类( 0－大额、1－小额、2-联行、9－金融平台 )
	RpdFlg     char(1)   not null,
--报文优先级( 1-普通、2-紧急、3-特急 )
	PMBTyp     char(2)   not null,
--业务种类( 10—现金汇款 11—普通汇兑 30—外汇清算 40—资金调拨 50—国库汇款 51—国库同城交换净额清算 61—人行跨区域票据交换轧差净额 99—其他 )
	AccFlg     char(1)   not null,
--记帐帐号种类( 0－对公 2－存折 4-卡 )
	CclNo      char(12)  default '',
--销帐号
	SndAct     char(32)  default '',
--发起人帐号
	SndNam     char(60)  default '',
--发起人户名
	SndAdr     char(60)  default '',
--发起人地址
	SndBNo     char(12)  default '',
--发起行行号
	RcvAct     char(32)  default '',
--接收人帐号
	RcvNam     char(60)  default '',
--接收人户名
	RcvAdr     char(60)  default '',
--接收人地址
	RcvBNo     char(12)  default '',
--接收人行号
	Smr        char(60)  default '',
--摘要
	VchTyp     char(3)   default '',
--凭证类型
	VchNo      char(8)   default '',
--凭证号码
	BilDat     char(8)   default '',
--签发日期
	PayPsw     char(16)  default '',
--支付密码
	FeeTyp     char(1)   default '',
--收费方式( 1－普汇 2-特急 3－优惠  5－手工输入 )
	PstAmt     char(15)  default '0',
--电子汇划费
	FeeAmt     char(15)  default '0',
--手续费
	CONSTRAINT PK_MIDTXNJNL PRIMARY KEY( LogNo )
);
