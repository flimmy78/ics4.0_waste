drop table PfaCrdInf;
drop table PfaCrdTxn;
drop table PfaCrdDtl;
drop table PfaCrdJnl;
--
--
--公务员卡资料
--
--
create table PfaCrdInf
(
	PfaSub      char(3)   not null,
--财政代码
	CardNo      char(19)  not null,
--卡号
	CollDt      char(8)   default '',
--收集日期
	LmtAmt      char(15)  default '',
--额度
	CrdSts      char(4)   default '',
--卡片状态
	IdType      char(4)   default '',
--证件种类
	IdNo        char(60)  default '',
--证件号码
	CardNm      char(30)  default '',
--姓名
	GendCd      char(2)   default '',
--性别
	BthPlc      char(100) default '',
--籍贯
	CrpNam      char(60)  default '',
--单位名称
	DptNam      char(30)  default '',
--任职部门
	DutyCd      char(2)   default '',
--职务
	MobTel      char(20)  default '',
--手机号码
	Email       char(30)  default '',
--电子邮件
	CrpTel      char(20)  default '',
--单位电话
	Addr        char(100) default '',
--账单地址
	HisBr       char(12)  default '',
--原零售系统分行号
	EffDat      char(8)   default '',
--发卡日期
	IvdDat      char(8)   default '',
--有效期
	SellId      char(12)  default '',
--营销代码
	BCusId      char(18)  default '',
--基层预算单位编码
	BrNo        char(6)   not null,
--分行号
	ActDat      char(8)   not null,
--更新日期
	constraint PK_PFACRDINF PRIMARY KEY( PfaSub,CardNo )
);
--
--
--公务员卡消费明细
--
--
create table PfaCrdTxn
(
	CardNo      char(19)  not null,
--卡号
	CollDt      char(8)   default '',
--收集日期
	HisBr       char(12)  default '',
--原零售系统分行号
	TxnDat      char(8)   not null,
--交易日期
	TxnTim      char(8)   default '',
--交易时间
	IbsDat      char(8)   default '',
--核心入账日期
	TxnSmr      char(60)  default '',
--交易说明
	MerId       char(15)  default '',
--商户号
	TermId      char(9)   default '',
--终端号
	MerNam      char(60)  default '',
--商户名称
	TLogNo			char(6)   not null,
--交易流水号
	DtlAmt      char(15)  default '',
--交易金额
	CcyCod      char(3)   default '',
--币种
	ThdCod      char(4)   default '',
--交易码
	AuthCd      char(6)   default '',
--授权码
	SltOrg      char(12)  default '',
--受理机构号
	PtgOrg      char(12)  default '',
--转发机构号
	RefNum      char(30)  default '',
--检索参考号
	SltDat      char(8)   default '',
--清算日期
	CardNm      char(30)  default '',
--持卡人姓名
	HActDt      char(8)   default '',
--历史库查询日期(该笔明细获取日期)
	IdxNo  	    char(6)   default '',
--索引号
	PfaSub      char(3)   not null,
--财政应用代码
	Year        char(4)   default '',
--年度
	BCusId      char(18)  default '',
--基层预算单位编码
	SndFlg      char(1)   default '0',
--报销状态( 0-未发送 1-已发送 )
	constraint PK_PFACRDTXN PRIMARY KEY( PfaSub,CardNo,TxnDat,TLogNo )
);
create index ni1_PfaCrdTxn on PfaCrdTxn( PfaSub, HActDt, IdxNo );
--
--
--公务员卡还款明细
--
--
create table PfaCrdDtl
(
	DtlSts      char(1)   not null,
--报销状态( U-初始 B-报销 S-成功 F-失败)
	PfaSub      char(3)   not null,
--财政应用代码
	Year        char(4)   not null,
--年度
	AVchCd      char(30)  not null,
--支付令编号
	PfaIdx      char(16)  not null,
--公务卡消费明细编码
	CardNo      char(19)  not null,
--卡号
	CardNm      char(30)  not null,
--持卡人姓名
	TxnDat      char(8)   not null,
--交易日期
	TxnTim      char(8)   default '',
--交易时间
	MerId       char(15)  default '',
--商户号
	TermId      char(8)   default '',
--终端号
	MerNam      char(60)  default '',
--商户名称
	TLogNo			char(6)   default '',
--交易流水号
	DtlAmt      char(15)  default '',
--交易金额
	CcyCod      char(3)   default '',
--币种
	ThdCod      char(4)   default '',
--交易码
	AuthCd      char(6)   default '',
--授权码
	HActDt      char(8)   default '',
--历史库查询日期(该笔明细获取日期)
	IdxNo  	    char(6)   default '',
--索引号
	BrNo        char(6)   default '',
--分行号
	BCusId      char(18)  default '',
--基层预算单位编码
	BokAmt      char(15)  default '',
--报销金额
	TActDt      char(8)   default '',
--财政确认日期
	BokDat      char(8)   default '',
--报销日期
	LogNo       char(14)  default '',
--前置流水号
  RtnFlg      char(1)   default '0',
--返回标志 (0-未回 1-已回)
	constraint PK_PFACRDDTL PRIMARY KEY( PfaSub, Year, AVchCd, PfaIdx )
);
--
--
--公务员卡还款流水表
--
--
create table PfaCrdJnl
(
	TxnSts      char(1)   default 'U',
--状态( U-初始 S-报销成功 F-报销失败 T-主机超时 C-撤销 )
	TxnTyp      char(1)   default 'N',
--交易类型( N-正常交易 C-冲正交易 R-重发交易)
	LogNo       char(14)  not null,
--前置流水号
	BrNo        char(6)   not null,
--分行号
	ActDat      char(8)   not null,
--会计日期
	HTxnSt      char(1)   default 'U',
--主机交易状态
	HRspCd      char(6)   default '',
--主机返回码
	HLogNo      char(9)   default '',
--主机流水号
	TlrId       char(7)   default '',
--银行柜员号
	TckNo       char(11)  default '',
--会计流水号
	CardNo      char(19)  default '',
--客户帐号
	CardNm      char(30)  not null,
--持卡人姓名
	CcyCod      char(3)   default '',
--货币代码
	TotAmt      char(15)  not null,
--消费总额
	TxnAmt      char(15)  not null,
--交易金额
	PfaSub      char(3)   not null,
--财政应用代码
	Year        char(4)   not null,
--年度
	BCusId      char(18)  not null,
--基层预算单位编码
	AVchCd      char(30)  not null,
--支付令编号
	constraint PK_PFACRDJNL PRIMARY KEY( LogNo )
);
create index ni1_PfaCrdJnl on PfaCrdJnl( PfaSub,Year,AVchCd );
