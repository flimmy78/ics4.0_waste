--名称定义
--直接清算行  char(12) DBrCd
--查询通知种类标识 char(3) QryTyp
--地区号 char(4) AreaNo
--钞汇标识 char(1) BillFg
--贷方金额 CreAmt
--贷方笔数 CreCnt
--借方金额 DebAmt
--借方笔数 DebCnt
--原数据元 OrgId
--交易种类 TraKnd  char(4)
--指定交易种类 CTraKnd
--旧登陆标识 OSgnId
--新登陆标识 NSgnId
--密押  SecKey
--企业机构代码 CrpOrgCd
--交易是否即时回应  ImmFlg
drop table CbsBasInf;
drop table CbsBnkInf;
drop table CbsRunCtl;
drop table CbsFeeRat;
drop table CbsTxnJnl;
drop table CbsQryJnl;
drop table CbsCusAgr;
drop table CbsPubInf;
drop table CbsCenTot;
drop table CbsBchSum;
drop table CbsBchJnl;
drop table CbsBankCd;
drop table CbsBTxnCd;
drop table CbsCodeCd;
drop table CbsSyIdCd;
drop table CbsAreaCd;
drop table CbsBusAct;
drop table CbsClrRpt;
drop table CbsExchNo;
drop table CbsNetDtl;
drop table CbsNetFee;
drop table CbsFeeRpt;
--01应用基本信息表
create table CbsBasInf
(
  BusLog  char(12)  not null,
--信息序号十二位长
	ReqSeq  char(8)   not null
--查询报文编号
);

--02分行信息表
create table CbsBnkInf
(
	BrNo      char(6)   not null,
--交易分行
	CtlNod    char(6)   not null,
--通汇控制部门号
  BusNod    char(6)   not null,
--分行营业部
	CnlSub    char(6)   not null,
--分行渠道
	AccSq01   char(5)   default '',
--实时贷记5210帐户序号(往/来)
	AccSq02   char(5)   default '',
--帐务中心2622(手续费)帐户序号(往)
	AccSq03   char(5)   default '',
--帐务中心2622(邮电费)帐户序号(往)
	AccSq04   char(5)   default '',
--网点2621帐户序号(往帐退汇或来帐挂帐)
	AccSq05   char(5)   default '',
--定期借记往帐成功回应26201暂收
	AccSq06   char(5)   default '',
--在线支付5210帐户序号(往/来)
	AccSq07   char(5)   default '',
--批量定期贷记5210帐户序号(往/来)
	AccSq08   char(5)   default '',
--定期借记5210帐户序号(往/来)
	AccSq09   char(5)   default '',
--广州待清算往来
	AccSq10   char(5)   default '',
--批量定期贷记2621(往)
	AccSq11   char(5)   default '',
--机构代收来帐5210帐户序号
	AccSq12   char(5)   default '',
--网银联动26201
  AccIn01   char(21)  default '',
--汇兑来帐对私自动入帐5210内部帐号
  AccIn02   char(21)  default '',
--在线支付来帐对私自动入帐5210内部帐号
  AccIn03   char(21)  default '',
--未定
	FixAmt    char(15)  default '000000000000000',
--固定头寸
	FloAmt    char(15)  default '000000000000000',
--浮动头寸
	CurAmt    char(15)  default '000000000000000',
--当前头寸
	CityCd    char(4)   not null,
--城市代码
	constraint PK_CBSBASINF PRIMARY KEY(BrNo)
);

--03运行控制表
create table CbsRunCtl
(
	TxnKnd   char(6)   not null,
--交易种类细分
	TraTm    char(10)  not null,
--交易发起日期和时间
	SysSts   char(2)   not null,
--系统运行状态 （01：启动 02：关闭 03：日期切换,程序用）
  LogFlg   char(1)   not null,
--登陆状态 0-未登陆 1-已登陆
  CtlFlg   char(1)   not null,
--行内控制标识 0-不控制  1-禁止业务
	WorkDt   char(8)   not null,
--当前人行工作日期
	KndNam   char(30)  default '',
--交易种类名称
	Smr     varchar(300)  default '',
--摘要
	constraint PK_CBSRUNCTL PRIMARY KEY(TxnKnd)
);

--04业务费率表
create table CbsFeeRat
(
	Sts      char(1)   not null,
--状态( 0-有效 1-无效 )
	TxnKnd   char(6)   not null,
--业务种类( 参见PDF文件P85 )
	TxnNam   char(60)  not null,
--业务种类中文
	UsgCod   char(3)   not null,
--资金用途代码
	UsgNam   char(60)  not null,
--资金用途中文
	LclFlg   char(1)   not null,
--同城异地标志( 0-同城 1-异地 )
	BrNo     char(6)   not null,
--分行号
	CcyCod   char(3)   not null,
--币种
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
	PstMod   char(1)   not null,
--邮电收费模式
	PstRat   char(5)   not null,
--费率
	PstAmt   char(15)  not null,
--额度
	ValDt    char(8)   not null,
--生效日期
	constraint PK_CBSFEERAT PRIMARY KEY( TxnKnd, UsgCod, LclFlg, BrNo, CcyCod, MinAmt, MaxAmt )
);

create table CbsTxnJnl
(
	TraKnd  char(4)   not null,
--第三方交易种类
	SndBNo  char(12)  not null,
--发起行行号( 直接参与行行号 )
	SndDat  char(8)   not null,
--委托日期
	VchId   char(8)   not null,
--第三方凭证提交号( substr( LogNo, 7, 8 ) )
	OIFlag  char(1)   not null,
--往来账标志 0-往帐 1-来帐
	BilSts  char(1)   not null,
--报单状态
--往账状态：0预记录；1作废；A已记账; B已复核; C已确认; D等待回执; E发人行错误; F排队; G已清算（发送成功）; H往账抹账; L暂挂;   h往账抹账失败; b人行拒绝; 
--来账状态：P来账待处理（未记账）; R已抹账; M退汇已发; S批注已复核; T已批注待复核; U待批注入账; W已入对公帐并等待对私处理; X确认入帐;Z对公自动入账;Q对私挂帐;V对私自动入帐 F失败作废;
	TTxnSt  char(1)   default '0',
--第三方状态
	MsgId   char(4)   not null,
--报文类型标志
	TxnKnd  char(6)   not null,
--第三方交易种类细分类型
	TxnAmt  char(15)  not null,
--汇划金额
	TraTm   char(10)  not null,
--交易发起日期和时间
	ClrDat  char(8)   default '00000000',  
--清算日期
	ClrSce  char(4)   default '',  
--清算场次
	CcyCod  char(3)   not null,
--主机交易币种
	SvrCod  char(3)		default '',
--服务点输入方式码( 021-磁条读入且带PIN		022-磁条读入不带PIN		011-手工输入且带PIN		012-手工输入不带PIN )
	CenTm   char(14)  default '',
--中心交易受理时间和日期
	CenLog   char(16)  default '',
--中心交易受理号
	ThdTm   char(14)  default '',
--业务处理方处理日期和时间( 往帐时不需填写 )
	ThdLog  char(16)  default '',
--业务处理方流水号( 往帐时不需填写 )
	TRspCd  char(6)   default '',
--第三方返回码( 见PDF文件P84 )
	CshFlg  char(1)   default '',
--现金/转帐标志( 0-现金		1-转帐 )
	SmrCod  char(4)   default '',
--摘要代码( 见PDF文件P91 )
	UsgCod   char(3)  default '',
--资金用途( 见PDF文件P89 )
	RSdFlg  char(1)   not null,
--重发标识( 0-正常发送	1-重复发送 )
	AccFlg  char(1)   not null,
--对公/对私标识( 0-对公	1-对私 )
	TBusTp  char(5)   default '',
--业务种类( 见PDF文件P90 )
	CardFg  char(2)   default '',
--卡/折标志( 01-存折	02-卡 )
	AccKnd  char(1)   default '',
--帐户类型 ( 0-汇户		1-钞户 )
	FeeTyp  char(3)   default '',
--手续费方式
	PayFuc  char(3)   default '',
--支付工具
	AuthCd  char(6)   default '',
--授权码
	PayLvl  char(1)   default '',
--支付优先级
	SOpnBk	char(12)  default '',
--发起人开户行行号( 间接参与行支付行号 )
	SndNod  char(9)   default '',
--发起行网点号
	SndAct  char(35)  default '',	
--发起人帐号
	SndNm   char(60)  default '',
--发起人名称
	SndAdr  char(60)  default '',
--发起人地址
	RcvBNo  char(12)  default '',
--接收行行号( 直接参与行行号 )
	ROpnBk	char(12)  default '',
--接收人开户行行号( 间接参与行行号 )
	RcvNod  char(9)   default '',
--接收行网点号
	RcvAct  char(35)  default '',	
--接收人帐号
	RcvNm   char(60)  default '',
--接收人名称
	RcvAdr  char(60)  default '',
--接收人地址
	OrgId   char(32)  default '',
--退票原数据元标识
	Smr     varchar(300) default '',
--交易摘要
	SvrKnd  char(1)   default '',
--服务信息类型
	TBilNo  char(20)  default '',
--税票号码
	TaxNo   char(20)  default '',
--纳税人编码
	Taxer   char(60)  default '',
--纳税人名称
	TaxLvl  char(2)   default '',
--预算级次
	TSubCd  char(12)  default '',
--预算科目
	TOrgCd  char(11)  default '',
--征收机关代码
	TActDt  char(8)   default '',
--税票限缴日期
	SecKey  char(40)  default '',
--密押
	MatFlg  char(1)   default '0',
--匹配标识( 0-不匹配,对私来帐未发送	1-匹配,对私来帐已发送 )
--帐务要素
--帐务要素
	LogNo   char(14)  not null,
--前置流水号
	BrNo    char(6)   not null,
--交易分行
	NodNo   char(6)   default '',
--交易网点
	ActFlg  char(1)   default '',
--账户种类
	AVchTp  char(3)   default '',
--账户凭证种类
	VchCod  char(8)   default '',
--存折号码
	BokAct  char(21)  default '',
--记帐帐号
	BActSq  char(5)   default '',
--一本通账户序号
	RvsNo   char(12)  default '',
--销帐号
	VchTyp  char(3)   default '',
--凭证种类
	VchNo   char(8)   default '',
--凭证号码
	FeeFlg  char(1)   default '',
--扣收标志
	FeeAmt  char(15)  default '000000000000000',
--手续费
	PstAmt  char(15)  default '000000000000000',
--邮电费
	EtsFlg  char(1)   default '',
--入库标志
	PstTyp  char(1)   default '',
--批注类型( 1-确认入帐 2-批注 3-转他行)
	PstNod  char(6)   default '',
--批注挂帐部门
--流水要素
--流水要素
	BusTyp  char(5)   default '',
--业务类型
	ActDat  char(8)   default '',
--会计日期
	TTxnCd  char(6)   default '',
--前置交易码
	HTxnSt  char(1)   default '',
--主机交易状态
	HTxnCd  char(6)   default '',
--主机交易码
	HLogNo  char(9)   default '',
--主机流水号
	TckNo   char(11)  default '',
--会计流水号
	RspCod  char(6)   default '',
--前置返回码
	HRspCd  char(6)   default '',
--主机返回码
	PrtCnt  char(2)   default '00',
--打印次数
	RtnMsg  char(72)  default '',
--回应信息
	TlrId   char(7)   default '',
--记帐柜员
	ChkId   char(7)   default '',
--复核柜员
	Sup1Id  char(7)   default '',
--授权柜员
	RvsSmr	char(60)  default '',
--销帐摘要
	constraint PK_CBSTXNJNL PRIMARY KEY( TraKnd, SndBNo, SndDat, VchId, OIFlag )
);
CREATE UNIQUE INDEX ni1_CBSTXNJNL ON CBSTXNJNL( LogNo );
CREATE INDEX ni2_CBSTXNJNL ON CBSTXNJNL( ActDat, TlrId, TckNo );
CREATE INDEX ni3_CBSTXNJNL ON CBSTXNJNL( BrNo, NodNo );
--06查询查复流水表
create table CbsQryJnl
(
	TxnKnd  char(6)   not null,
--交易类型细分码
	SndDat  char(8)   not null,
--委托日期
	QryTyp  char(3)   not null,
--查询种类标识
--000银行帐户情况查询 001客户授权余额查询 002户名查询/核对查询
--003：同城确认查询/查复 004：同城支付申请/处理通知 005：同城退回申请/处理通知
--006：同城调账申请 999：通用查询
  OIFlag  char(1)   not null,
--往来查询标志 0-发起查询 1-接收查询  2-接收到不合法查询 3-接收不匹配查复
	MatFlg  char(1)   default '0',
--查复匹配标识 0-未查复	1-已查复 A录入待确认; C已确认; D-已删除; E-发送出错 
	BrNo    char(6)   not null,
--交易分行
	SndBNo  char(12)  not null,
--发起行行号( 直接参与行行号 )
	RcvBNo  char(12)  not null,
--接收行行号( 直接参与行行号 )
	MsgSeq  char(16)  not null,
--信息序号
	SvrCod  char(3)		default '',
--服务点输入方式码( 021-磁条读入且带PIN		022-磁条读入不带PIN		011-手工输入且带PIN		012-手工输入不带PIN )
	CenTm   char(14)  default '',
--中心交易受理时间和日期
	CenLog   char(16) default '',
--中心交易受理号
	ReqSeq  char(8)   default '00000000',
--查询报文编号
	RspSeq  char(8)   default '00000000',
--查复报文编号
	TRspCd  char(6)   default '',
--第三方返回码( 见PDF文件P84 )
	SOpnBk	char(12)  default '',
--发起人开户行行号( 间接参与行行号 )
	ROpnBk	char(12)  default '',
--接收人开户行行号( 间接参与行行号 )
	DeaNod  char(6)   default '',
--处理网点
	DeaTlr  char(7)   default '',
--处理柜员
	DeaDat  char(8)   default '',
--处理日期
	PriCls  char(1)   default '',
--优先级别 0：一般 1：紧急
	PTraKnd char(4)   default '',
--原交易类型
	PSndBNo char(12)  default '',
--原交易发起行行号
	PRcvBNo char(12)  default '',
--原交易接收行行号
	PSndDat char(8)   default '',
--原交易委托日期
	PClrDat char(8)   default '',
--原交易清算日期
	PTxnAmt char(15)  default '',
--原交易金额
	PCcyCod char(3)   default '',
--原交易币种
	PVchId  char(8)   default '',
--原凭证提交号
	PPayAct char(35)  default '',	
--原付款人帐号
	PPayNam char(60)  default '',
--原付款人名称
	PGatAct char(35)  default '',	
--原收款人帐号
	PGatNam char(60)  default '',
--原收款人名称
	ReqSmr  varchar(300) default '',
--查询备注
	RspSmr  varchar(300) default '',
--回复备注
	constraint PK_CBSQRYJNL PRIMARY KEY(TxnKnd,SndDat,SndBNo,MsgSeq,OIFlag)
);
CREATE INDEX ni1_CBSQRYJNL ON CBSQRYJNL(BrNo,QryTyp);


--08协议信息表
create table CbsCusAgr
(
	AgrAct   char(21)   not null,
--协议帐号
	EntCod   char(6)    not null,
--公共事业单位代码
	EntAct   char(35)   not null,
--公共事业单位帐号
  AccFlg   char(1)    not null,
--帐户性质( 0-对公 1-存折 2-卡 )
	Smr      char(60)   default '',
--备注
	BrNo     char(6)    not null,
--分行号
	BltNod   char(6)    not null,
--建立部门
	BltTlr   char(7)    not null,
--建立柜员
  BltDat   char(8)    not null,
--生效日期
	UpdTlr   char(7)    default '',
--修改柜员
	UpdNod   char(6)    default '',
--修改部门
	UpdDat   char(8)    default '',
--修改日期
	constraint PK_CBSCUSAGR PRIMARY KEY( AgrAct, EntCod, EntAct )
);

--09定期借记公共事业资料表
create table CbsPubInf
(
	BrNo     char(6)   not null,
--归属分行
	EntCod   char(6)   not null,
--公共事业单位代码
	EntAct   char(35)  not null,
--公共事业单位帐号
	EntNam   char(60)  not null,
--公共事业单位名称
	OpnBNo   char(12)  not null,
--开户行行号
	AgrKnd   char(1)   not null,
--协议类型（0－强制签约 1－非强制签约）
	Smr      char(60)  default '',
--备注
	constraint PK_CBSPUBINF PRIMARY KEY( BrNo, EntCod )
);

--10对帐合计信息表
create table CbsCenTot
(
	CTraKnd  char(4)     not null,
--第三方交易类型
	TraTm    char(10)    not null,
--交易发起日期和时间
	DBrCd    char(12)    not null,
--直接清算行
	ClrDat   char(8)     not null,
--清算日期
  AreaNo   char(4)     not null,
--开通区域
	CcyCod   char(3)     not null,
--币种
  ChkFlg   char(1)     default '0',
--0未对帐 1对帐成功
	CreAmt   char(15)    not null,
--人行贷方金额
	CreCnt   char(10)    not null,
--人行贷方笔数
	DebAmt   char(15)    not null,
--人行借方金额
	DebCnt   char(10)    not null,
--人行借方笔数
	CreAmt2  char(15)    default '',
--银行贷方金额
	CreCnt2  char(10)    default '',
--银行人行贷方笔数
	DebAmt2  char(15)    default '',
--银行人行借方金额
	DebCnt2  char(10)    default '',
--银行人行借方笔数
	constraint PK_CBSCENTOT PRIMARY KEY( CTraKnd,DBrCd,ClrDat,AreaNo,CcyCod)
);

--11批量业务汇总表
create table CbsBchSum
(
	BchSts  char(1)     not null,
--状态
--定期借记( 来帐: U-初始 B-处理中 C-已回应 D-已清算 )
--定期贷记( 往帐: U-初始 B-处理中 C-已转发 D-已清算 R-已回应 M-清算中 )
	ClrDat  char(8)     not null,
--清算日期
	ClrSce  char(1)     not null,
--清算场次
	SSysId  char(4)     not null,
--发起方系统号
	SndBNo  char(12)    not null,
--发起方代码
	RSysId  char(4)     not null,
--接收方系统号
	RcvBNo  char(12)    not null,
--接收方代码
	TraKnd  char(4)     not null,
--交易种类
	OIFlag  char(1)     not null,
--往来标志( 0-往, 1-来 )
	FilNam  char(60)    not null,
--文件名
	RefFil  char(60)    default '',
--参照文件名
	BchSqn  char(8)     not null,
--批量包序号
	RefSqn  char(8)     default '',
--参照批量包序号
	CusSqn  char(8)     default '',
--客户批量包序号
	TotNum  char(10)    not null,
--交易总笔数
	TotAmt  char(16)    not null,
--交易总金额
	RefNum  char(10)    default '0',
--拒绝支付总笔数
	RefAmt  char(16)    default '0',
--拒绝支付总金额
	RtnCod  char(8)     default '',
--返回码
	ReServ  char(16)    default '',
--预留域
	AckFil1 char(60)    default '',
--往帐：定期借记 ACK回应(2210)、定期贷记收妥回应2212
--来帐：定期借记收妥回应(2242)、定期贷记收妥回应2222
	ClrFil  char(60)    default '',
--往帐：定期借记业务回应2212、定期贷记清算通知2210
--来帐：定期借记业务回应2212
	AckFil2 char(60)    default '',
--往帐：定期借记业务回应2222、定期贷记网点提交的文件名
--来帐：定期借记业务回应2220
	DskNo   char(12)    default '',
--磁盘编号
	ActDat  char(8)     default '',
--会计日期
	NodNo   char(6)     default '',
--交易网点
	BrNo    char(6)     default '',
--分行号
	constraint PK_CBSBCHSUM PRIMARY KEY( FilNam )
);
create INDEX ni1_CBSBCHSUM ON CBSBCHSUM( FilNam, OIFlag, BchSts  );


--12批量业务流水表
create table CbsBchJnl
(
	FilNam  char(60)  not null,
--文件名
	MsgSqn  char(16)  not null,
--信息序号
	TraKnd  char(4)   not null,
--第三方交易种类
	SndBNo  char(12)  not null,
--发起行行号( 直接参与行行号 )
	SndDat  char(8)   not null,
--委托日期
	VchId   char(8)   not null,
--第三方凭证提交号( substr( LogNo, 7, 8 ) )
	OIFlag  char(1)   not null,
--往来账标志 0-往帐 1-来帐
	BilSts  char(1)   not null,
--报单状态
--来帐：U-初始, Z-已扣帐成功 E-扣帐失败 S批注已复核 T已批注待复核 X确认入帐
--往帐：0-初始, A-已补录, B-待记帐 C-已转发 G-发送成功
	MsgId   char(4)   not null,
--报文类型标志
	TxnKnd  char(6)   not null,
--第三方交易种类细分类型
	TxnAmt  char(15)  not null,
--交易金额
	TraTm   char(10)  not null,
--交易发起日期和时间
	ClrDat  char(8)   default '',
--清算日期
	CcyCod  char(3)   not null,
--主机交易币种
	SvrCod  char(3)		default '',
--服务点输入方式码( 021-磁条读入且带PIN		022-磁条读入不带PIN		011-手工输入且带PIN		012-手工输入不带PIN )
	CenTm   char(14)  default '',
--中心交易受理时间和日期
	CenLog  char(16)  default '',
--中心交易受理号
	ThdTm   char(14)  default '',
--业务处理方处理日期和时间( 往帐时不需填写 )
	ThdLog  char(16)  default '',
--业务处理方流水号( strcat( '00', LogNo ) )
	RtnCod  char(8)   default '',
--返回码
	CshFlg  char(1)   default '',
--现金/转帐标志( 0-现金		1-转帐 )
	SmrCod  char(4)   default '',
--摘要代码( 见PDF文件P91 )
	UsgCod  char(3)   default '',
--资金用途( 见PDF文件P89 )
	RSdFlg  char(1)   not null,
--重发标识( 0-正常发送	1-重复发送 )
	AccFlg  char(1)   not null,
--对公/对私标识( 0-对公	1-对私  )
	TBusTp  char(5)   default '',
--业务种类( 见PDF文件P90 )
	CardFg  char(2)   default '00',
--卡/折标志( 00-其他  01-存折	02-卡 )
	AccKnd  char(1)   default '0',
--帐户类型 ( 0-汇户		1-钞户 )
	FeeTyp  char(3)   default '',
--手续费方式
	PayFuc  char(3)   default '',
--支付工具
	AuthCd  char(6)   default '',
--授权码
	PayLvl  char(1)   default '0',
--支付优先级
	SOpnBk	char(12)  default '',
--发起人开户行行号( 间接参与行支付行号 )
	SndNod  char(9)   default '',
--发起行网点号
	SndAct  char(35)  default '',	
--发起人帐号
	SndNm   char(60)  default '',
--发起人名称
	SndAdr  char(60)  default '',
--发起人地址
	RcvBNo  char(12)  default '',
--接收行行号( 直接参与行行号 )
	ROpnBk	char(12)  default '',
--接收人开户行行号( 间接参与行行号 )
	RcvNod  char(9)   default '',
--接收行网点号
	RcvAct  char(35)  default '',	
--接收人帐号
	RcvNm   char(60)  default '',
--接收人名称
	RcvAdr  char(60)  default '',
--接收人地址
	AgrNo   char(60)  default '',
--多方协议号
	Smr     varchar(300) default '',
--交易摘要
	OrgId   char(32)  default '',
--退票原数据元标识
	SvrKnd  char(1)   default '',
--服务信息类型
	EtsFlg  char(1)   default '',
--入库标志
	TBilNo  char(30)  default '',
--税票号码
	TaxNo   char(20)  default '',
--纳税人编码
	Taxer   char(60)  default '',
--纳税人名称
	TaxLvl  char(2)   default '',
--预算级次
	TSubCd  char(12)  default '',
--预算科目
	TOrgCd  char(11)  default '',
--征收机关代码
	TActDt  char(8)   default '',
--税票限缴日期
	SecKey  char(40)  default ' ',
--密押
	BrNo    char(6)   not null,
--交易分行
	NodNo   char(6)   not null,
--交易网点
	LogNo   char(14)  default '',
--前置流水号
	ActFlg  char(1)   not null,
--账户种类
	AVchTp  char(3)   default '',
--账户凭证种类
	VchCod  char(8)   default '',
--存折号码
	BokAct  char(21)  default '',
--记帐帐号
	BActSq  char(5)   default '',
--一本通账户序号
	RvsNo   char(12)  default '',
--销帐号
	VchTyp  char(3)   default '',
--凭证种类
	VchNo   char(8)   default '',
--凭证号码
	FeeFlg  char(1)   default '',
--扣收标志
	FeeAmt  char(15)  default '000000000000000',
--手续费
	PstAmt  char(15)  default '000000000000000',
--邮电费
	PstTyp  char(1)   default '',
--批注类型( 1-确认入帐 2-批注 3-转他行)
	PstNod  char(6)   default '',
--批注挂帐部门
--流水要素
--流水要素
	DskNo   char(12)  default '',
--磁盘编号
	ActDat  char(8)   default '',
--会计日期
	TTxnCd  char(6)   default '',
--前置交易码
	HTxnCd  char(6)   default '',
--主机交易码
	HTxnSt  char(1)   default 'U',
--主机交易状态
	HRspCd  char(6)   default '',
--主机返回码
	HLogNo  char(9)   default '',
--主机流水号
	IsTxn   char(1)   default 'N',
--是否发送主机标志，用于批量大小通道发送  Y发送N不发送
	TxnObj  char(8)   default '',
--大小通道目标服务
	TlrId   char(7)   default '',
--银行柜员号
	ChkId   char(7)   default '',
--复核柜员
	Sup1Id  char(7)   default '',
--授权柜员
	TckNo   char(11)  default '',
--会计流水号
	constraint PK_CBSBCHJNL PRIMARY KEY( TraKnd, SndBNo, SndDat, VchId, OIFlag )
);
create index ni1_CBSBCHJNL ON CBSBCHJNL( FilNam, OIFlag, BilSts  );


--13行名行号表
create table CbsBankCd
(
	BankNo   char(12)  not null,
--行号
	SwftNo   char(12)  default '',
--Switch行号
	SysId    char(4)   default '',
--系统号
	CityCd   char(4)   default '',
--地区代码
	BlArea   char(4)   not null,
--所在区域
	DirBNo   char(12)  not null,
--直接清算行行号
	BnkTyp   char(3)   not null,
--行别代码
	BankNm   char(60)  not null,
--银行名称
	SimBNm   char(20)  not null,
--银行简称
	SecBNo   char(12)  default '',
--二级核算行行号
	Adr      char(60)  default '',
--银行地址
	PosCod   char(6)   default '',
--邮编
	TelNo    char(20)  default '',
--联系电话
	FaxNo    char(20)  default '',
--传真
	EMail    char(30)  default '',
--电邮地址
	Comman   char(16)  default '',
--联系人
	DirFlg   char(1)   not null,
--直接清算行标志( 0-非清算行 1-清算行 )
	CnpsFg   char(1)   not null,
--支付行号标志( 0-非支付 1-支付 )
	EffDat   char(8)   not null,
--生效日期
	IvdDat   char(8)   default '',
--停用日期
	ReMark   char(60)  default '',
--备注
	constraint PK_CBSBANKCD PRIMARY KEY( BankNo )
);

--14银行业务开通信息
create table CbsBTxnCd
(
	BankNo   char(12)  not null,
--行号
	TxnKnd   char(6)   not null,
--开通的交易种类细分
	CcyCod   char(3)   not null,
--币种
	EffDat   char(8)   not null,
--生效日期
	IvdDat   char(8)   default '',
--停用日期
	constraint PK_CBSBTXNCD PRIMARY KEY( BankNo, TxnKnd, CcyCod )
);

--15系统代码信息
create table CbsCodeCd
(
	CodTyp   char(6)   not null,
--代码类型
	Code     char(18)  not null,
--代码
	CodSmr   char(40)  not null,
--代码描述
	EffDat   char(8)   not null,
--生效日期
	IvdDat   char(8)   default '',
--停用日期
	constraint PK_CBSCODECD PRIMARY KEY( CodTyp, Code )
);

--16系统号信息
create table CbsSyIdCd
(
	SysId    char(4)   not null,
--代码类型
	SysNam   char(60)  not null,
--代码名称
	BlArea   char(4)   not null,
--代码描述
	IdType   char(1)   not null,
--成员类型( 1-银行 2-机构 3-中心 )
	EffDat   char(8)   not null,
--生效日期
	IvdDat   char(8)   default '',
--停用日期
	constraint PK_CBSSYIDCD PRIMARY KEY( SYSID )
);

--17地区代码信息
create table CbsAreaCd
(
	CityCd   char(4)   not null,
--地区代码
	CityNm   char(40)  not null,
--代码
	UpgCod   char(4)   not null,
--代码描述
	CityFg   char(1)   not null,
--成员类型( 1-国家 2-省、特别行政区 3-市 4-乡、镇银行 )
	constraint PK_CBSAREACD PRIMARY KEY( CityCd )
);

--18业务帐号使用表
create table CbsBusAct
(
	BrNo     char(6)   not null,
--分行号
	NodNo    char(6)   not null,
--网点号
	TxnKnd   char(6)   not null,
--业务类型
	InAcNo   char(21)  not null,
--内部帐号
	constraint PK_CBSBUSACT PRIMARY KEY( BrNo, NodNo, TxnKnd )
);

--19清算报表临时表
create table CbsClrRpt
(
  BchFlg  char(1)  not null,
--单笔批量标志( 0-单笔业务  1-批量业务 )
	BrNo    char(6)  not null,
--分行号
	TxnKnd  char(6)  not null,
--业务类型细分
	InNum   char(10) default '0',
--汇入笔数
	InAmt   char(15) default '000000000000000',
--汇入金额
	OutNum   char(10) default '0',
--汇出笔数
	OutAmt   char(15) default '000000000000000',
--汇出金额
	constraint PK_CBSCLRRPT PRIMARY KEY( BrNo,TxnKnd )
);
--20交换号对照表
create table CbsExchNo
(
	BrNo    char(6)  not null,
--分行号
	ExchNo  char(10) not null,
--交换行号
	BankNo  char(12) not null,
--支付行号
	constraint PK_CBSEXCHNO PRIMARY KEY( BrNo, ExchNo )
);
--21网银流水表
create table CbsNetDtl
(
	DtlSts  char(1)  default 'U',
--明细状态( U-初始 S-记帐成功 G-转发成功 F-转发失败 T-记帐超时 E-记帐失败)
	LogNo   char(14) not null,
--前置流水号
	ActDat  char(8)  not null,
--会计日期
	TlrId   char(7)  not null,
--银行柜员号
	TckNo   char(11) default '',
--会计流水号
	TTxnCd  char(6)  default '',
--前置交易码	
	HTxnCd  char(6)  default '',
--主机交易码	
	HTxnSt  char(1)  default 'U',
--主机交易状态
	HLogNo  char(9)  default '',
--主机流水号
	HRspCd  char(6)  default '',
--主机返回码
	BrNo    char(6)  not null,
--分行号
	NodNo   char(6)  not null,
--网点号
	WebChv  char(8)  not null,
--网银流水号
	RecNo   char(14) not null,
--系统流水号
	DrAct   char(21) not null,
--借方账号
	DrNam   char(60) not null,
--借方户名
	CrAct   char(32) not null,
--贷方账号
	CrNam   char(60) not null,
--借方户名
	TxnAmt  char(15) not null,
--交易金额
	Rmk     char(60) default '',
--摘要
	RvsNo   char(12) not null,
--销账编号
	DonDat  char(8)  not null,
--网银挂帐会计日期
	DonJnl  char(11) not null,
--网银挂帐流水
	Msg     char(60) default '',
--附言
	OppExc  char(10) not null,
--对方交换号
	SndBNo  char(12) default '',
--发起行号
	RcvBNo  char(12) default '',
--接收行号
	FeeAmt  char(15) default '0',
--手续费
	PstAmt  char(15) default '0',
--邮电费
	FeeFlg  char(1)  default '0',
--费用扣收标志( 0-未扣收 1-已扣收 )
	constraint PK_CBSNETDTL PRIMARY KEY( LogNo )
);
create unique index ni1_CBSNETDTL ON CBSNETDTL( RecNo );
create index ni2_CBSNETDTL ON CBSNETDTL( BrNo,ActDat,DtlSts,FeeFlg );
--22网银手续费表
create table CbsNetFee
(
	FeeSts  char(1)  default 'U',
--明细状态( U-初始 S-记帐成功 T-记帐超时 E-记帐失败)
	LogNo   char(14) not null,
--前置流水号
	DskNo   char(12) not null,
--磁盘编号
	ActDat  char(8)  not null,
--会计日期
	TlrId   char(7)  not null,
--银行柜员号
	TckNo   char(11) default '',
--会计流水号
	TTxnCd  char(6)  default '',
--前置交易码	
	HTxnCd  char(6)  default '',
--主机交易码	
	HTxnSt  char(1)  default 'U',
--主机交易状态
	HLogNo  char(9)  default '',
--主机流水号
	HRspCd  char(6)  default '',
--主机返回码
	IsTxn   char(1)  default 'N',
--是否发送主机标志，用于批量大小通道发送  Y发送N不发送
	TxnCnl  char(3)  default 'CBS' not null,
--交易渠道
	CnlSub  char(10) default '',
--子渠道
	TxnObj  char(8)  not null,
--大小通道目标服务
	UpdFlg  char(1)  default 'Y',
--更新标志
	UpdFld  char(20) default '',
--更新字段名
	BrNo    char(6)  not null,
--分行号
	NodNo   char(6)  not null,
--网点号
	TxnMon  char(6)  not null,
--交易月份
	DrAct   char(21) not null,
--借方账号
	DrNam   char(60) not null,
--借方户名
	TxnNum  char(6)  not null,
--交易笔数
	CcyCod  char(3)  default 'CNY',
--币种
	FeeAmt  char(15) default '0',
--手续费
	PstAmt  char(15) default '0',
--邮电费
	PrtNum  char(2)  default '0',
	constraint PK_CBSNETDTL PRIMARY KEY( LogNo )
);
--23人行手续费用表
create table CbsFeeRpt
(
	Mon     char(6)   not null,
--收费月份
	SndBNo  char(12)  not null,
--发起行行号
	TxnKnd  char(6)   not null,
--业务种类细分
  PkgNum  char(6)   default '',
--交易包数
	TxnNum  char(6)   default '0',
--交易笔数
	TxnCcy  char(3)   default '',
--交易币种
	TxnAmt  char(15)  default '0',
--交易总金额
	FeeCcy  char(3)   default '',
--收费币种
	FeeAmt  char(15)  default '0'
--收费总金额
--	constraint PK_CBSFEERPT PRIMARY KEY( Mon,SndBNo,TxnKnd )
);
create index ni1_CBSFEERPT ON CBSFEERPT( Mon,SndBNo,TxnKnd );
