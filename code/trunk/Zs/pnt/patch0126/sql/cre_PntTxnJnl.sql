drop table PntTxnJnl;

create table PntTxnJnl
(
	LogNo    char(14)   not null,
--前置流水号
	TTxnCd   char(6)    not null,
--接口交易码
	TxnCod   char(6)    not null,
--前置交易码
	HTxnCd   char(6)    not null,
--主机交易码
	TxnTyp   char(1)    not null,
--交易类型( N-正常交易 C-冲正交易 R-重发交易)
	OIFlag   char(1)    not null,
--往来账标志( 0-往帐 1-来帐 )
	BusTyp   char(6)    not null,
--业务类型
	CrpCod   char(12)   default '',
--单位代码
	ActDat   char(8)    not null,
--会计日期
	CcyCod   char(3)    default 'CNY',
--货币代码
	TxnAmt   char(15)   not null,
--交易金额
	ActTyp   char(1)    not null,
--账户种类( 0-现金 1-一本通 2-普通存折 4-太平洋卡 A-普通对公 B-中央财政 C-广东财政 )
	AVchTp   char(3)    default '',
--账户凭证种类
	VchCod   char(8)    default '',
--存折号码
	ActNo    char(21)   default '',
--记帐帐号
	BActSq   char(5)    default '',
--一本通账户序号
	RvsNo    char(12)   default '',
--销帐号
	VchTyp   char(3)    default '',
--凭证种类
	VchNo    char(8)    default '',
--凭证号码
	NodNo    char(6)     default '',
--银行网点号
	BrNo     char(6)     not null,
--交易分行
	TlrId    char(7)     not null,
--银行柜员号
	FTxnTm   char(14)    default '',
--前置交易时间
	HLogNo   char(9)     default '',
--主机流水号
	TckNo    char(11)    default '',
--会计流水号
	TTxnSt   char(1)    default 'U',
--第三方交易状态( S-成功 F-失败 R-被抹帐 C-被冲正 U-预记状态 T-超时 V-主机成功 )
	TxnSts   char(1)    default 'U',
--交易状态( S-成功 F-失败 R-被抹帐 C-被冲正 U-预记状态 T-超时  )
	HTxnSt   char(1)     default 'U',
--主机交易状态( S-成功 F-失败 R-被抹帐 C-被冲正 U-预记状态 E-差错 T-超时)
	HRspCd   char(6)     default '',
--主机响应码
------以下是业务数据------
------以下是业务数据------
------以下是业务数据------
	CmdCod   char(3)    not null,
--命令字( 第三方功能码 )
	BankCd   char(30)   not null,
--银行编码
	TCrpCd   char(30)   not null,
--执收单位编码
	TVchTp   char(2)    default '',
--缴款通知书类别
	TVchId   char(50)   not null,
--缴款通知书编码
	PayNam   char(60)   default '',
--缴费人(单位)名称
	TVchDt   char(8)    default '',
--缴款通知书日期
	TBilTp   char(8)    not null,
--票据类型编码
	TBilNo   char(20)   not null,
--票据号码
	BilAmt   char(15)   not null,
--应收总金额
	FulCrc   char(5)    default '',
--全书校验码
	PenAmt   char(15)   not null,
--应收总滞纳金
	PayDat   char(8)    default '',
--缴费日期
  PActNo   char(50)   default '',
--汇缴账户
	Smr      char(60)   default '',
--备注
	PrvDat   clob(2048) default '',   
--个性数据( PrjNum、PrjRec、RmkNum、RmkRec )
	BilSts   char(1)    default 'U',
--状态( U-初始 B-记帐成功 S-转发成功 X-系统错误(未发送) F-发送失败 T-发送超时 R-抹账)
	ChkDat   char(8)    default '',
--对账日期
	ChkBch   char(2)    default '',
--对账批次
	CONSTRAINT PK_PNTTXNJNL PRIMARY KEY( LogNo )
);
