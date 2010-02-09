drop table PntTxnBok;




create table PntTxnBok
(
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
	PayDat   char(14)    default '',
--缴费日期
	Smr      char(60)   default '',
--备注
	PrvDat   clob(2048) default '',   
--个性数据( PrjNum、PrjRec、RmkNum、RmkRec )
	BilSts   char(1)    default 'U',
--状态( U-初始 B-记帐成功(确认) S-转发成功 X-系统错误(未发送) F-发送失败 T-发送超时 R-抹账 C-冲正未确认 D-已冲正)
	LogNo    char(14)   default '',
--前置流水号
	ActDat   char(8)    not null,
--会计日期
	TckNo    char(11)   default '',
--会计流水
  RActNo   char(21)   default '',
--收款账号
	ChkDat   char(8)    default '',
--对账日期
	ChkBch   char(2)    default '',
--对账批次
	CONSTRAINT PK_PNTTXNBOK PRIMARY KEY( TBilTp,TBilNo )
);