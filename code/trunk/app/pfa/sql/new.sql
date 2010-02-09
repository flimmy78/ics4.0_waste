drop table PfaQuoBok001;
drop table PfaVchDtl001;
drop table PfaTotChk001;
drop table PfaDtlChk001;
--
--
--广东省财政额度登记表
--
--
create table PfaQuoBok001
(
  TActDt   char(8)   default '',
--交易日期
  TPkgNo   char(16)  default '',
--包流水号
	QuoKey   char(16)  not null,
--主键(与交易流水号等值)
	AQuoCd   char(60)  not null,
--凭证编号
	QuoId    char(16)  not null,
--额度ID
  QuoSmr   char(100) default '',
--备注
  SubCod   char(30)  default '',
--预算科目编码（支出功能编码）
  DptCod   char(30)  default '',
--业务处室(指标来源)
  BCusId   char(30)  not null,
--基层预算单位编码
  EConTp   char(30)  default '',
--经济分类
	BilDat   char(8)   default '',
--制定日期
  Mon      char(2)   not null,
--月
  PrjCod   char(20)  default '',
--项目编码
  Year     char(4)   not null,
--年
  AmtKnd   char(20)  default '',
--资金性质 (0001-预算内 0002-预算外 0003-自筹资金 0004-利息收入)
  QuoAmt   char(15)  not null,
--额度金额
---
---行内要素
---
  QuoSts   char(1)   not null,
--生效状态 (0-未复核 1-已复核 2-已打印授权到帐通知书)
  PfaSub   char(3)   not null,
--财政应用代码
  TxnFlg   char(1)   default '',
--交易类型 (0-增加 1-减少)
  RegDat   char(8)   not null,
--登记(下达)日期
  QuoTim   char(14)  not null,
--下达时间
  ABnkNo   char(10)  default '',
--授权银行编码（代理银行编码）
  ActNo    char(21)  default '',
--银行账号
  RtnFlg   char(1)   not null,
--返回标志 (0-未回 1-已回)
  PrtCnt   char(2)   default '00',
--打印次数
  RegId    char(7)   default '',
--录入人
  ChkId    char(7)   default '',
--确认人
  NodNo    char(6)   default '',
--确认部门
  BrNo     char(6)   not null,
--确认分行号
  ActDat   char(8)   default '',
--确认会计日期
  UpdFlg   char(1)   default '0',
--更新标志( 0-未更新余额表 1-已更新余额表 )
  BokIdx   char(6)   default '',
  CONSTRAINT PK_PFAQUOBOK001 PRIMARY KEY( PfaSub,Year,QuoKey )
);
--
--
--广东省财政支付凭证明细簿
--
--
create table PfaVchDtl001
(
  TActDt   char(8)   default '',
--交易日期
  TPkgNo   char(16)  default '',
--包流水号
	DtlKey   char(16)  not null,
--主键(与交易流水号等值)
  AVchCd   char(30)  not null,
--支付令编号
  MdAVCd   char(30)  default '',
--调帐凭证编码
  SubCod   char(30)  default '',
--预算科目(功能分类)
  DtlAmt   char(15)  default '',
--支付金额
	TBusTp   char(30)  default '',
--业务种类
  DptCod   char(30)  default '',
--业务处室(指标来源)
  BCusId   char(30)  default '',
--基层预算单位编码
  EConTp   char(30)  default '',
--经济分类编码
  AmtKnd   char(30)  default '',
--资金性质 (0001-预算内 0002-预算外 0003-自筹资金 0004-利息收入)
  PyeAct   char(35)  default '',
--收款人账号
  PyeNam   char(60)  default '',
--收款人全称
  PyeBNm   char(60)  default '',
--收款人开户银行
  VchDat   char(8)   not null,
--支付令日期
  PayAct   char(35)  default '',
--付款人帐号
  PayNam   char(60)  default '',
--付款人全称
  PayBNm   char(60)  default '',
--付款人开户银行
  PayBId   char(30)  default '',
--付款单位编码
  PrjCod   char(30)  default '',
--预算项目编码
  DtlSmr   char(100) default '',
--用途
  VchNo    char(8)   default '',
--结算凭证编号
	QuoId    char(16)  not null,
--额度ID
---
---行内要素
---
  DtlSts   char(1)   default 'U',
--数据状态( R-接收中 U-初始 0-登记 1-确认 2-使用 3-撤销 4-退回 5-作废(柜员主动取消) )
  PfaSub   char(3)   not null,
--财政代码
  Year     char(4)   not null,
--财政年度
  OIFlag   char(1)   not null,
--交易方向 (O-支出 R-退回 I-主动收款) 
  UseAmt   char(15)  default '0',
--实际使用金额
  RegDat   char(8)   not null,
--登记日期
  DtlTim   char(14)  not null,
--凭证录入时间
  RefCod   char(2)   default '',
--退回代码
  PfaKnd   char(1)   not null,
--支付介质 (0-纸质 1-电子)
  ActDat   char(8)   default '',
--会计日期
  PrtNum   char(2)   default '00',
--打印次数
  AVchNo   char(8)   default '',
--授权凭证登记号（由行内系统生成）
  ClrSts   char(1)   default '0',
--清算标志( 0-未清算 1-待清算 2-内部清算完成 3-财政清算确认 4-财政清算失败 ) 
  ClrBNo   char(10)  default '',
--清算批次
  ClrDat   char(8)   default '',
--内部清算日期
  PfaDat   char(8)   default '',
--财政清算日期
  RtnFlg   char(1)   default '0',
--回应标志 (0-未回 1-已回)
  CONSTRAINT PK_PFAVCHDTL001 PRIMARY KEY( PfaSub, Year, DtlKey )
);
create index ni1_PfaVchDtl001 on PfaVchDtl001( PfaSub, Year, AVchNo );
create index ni2_PfaVchDtl001 on PfaVchDtl001( PfaSub, PfaDat, ClrSts );
create unique index ni3_PfaVchDtl001 on PfaVchDtl001( PfaSub, Year, AVchCd );
--
--
--广东省财政支付总帐对帐结果
--
--
create table PfaTotChk001
(
  TActDt   char(8)   default '',
--交易日期
  TPkgNo   char(16)  default '',
--包流水号
  TotKey   char(16)  not null,
--主键
	SubCod   char(30)  default '',
--科目
	ChkFlg	 char(1)   default '',
--对帐标识【0-支出金额和累计支出金额都无差异；1-支出金额有差异；2-累计支出金额有差异；
--          3-代理银行缺失这条记录；4-支付局行缺失这条记录】
  BnkCAmt  char(15)  defautl '',
--当旬（月）银行支出金额
  BnkTAmt  char(15)  default '',
--银行累计支出金额
  PfaCAmt  char(15)  default '',
--当旬（月）支付局支出金额
  PfaTAmt  char(15)  default '',
--支付局累计支出金额
  DptCod   char(30)  default '',
--处室编码
	DffCAmt  char(15)  default '',
--当旬（月）支出金额差额
	DffTAmt  char(15)  default '',
--累计支出金额差额
  BCusId   char(30)  default '',
--单位编码
  MonFlg   char(10)  default '',
--月（旬）【前两位代表月(01-12)，后两位代表旬(00：月；01：上旬；02：中旬；03：下旬)】
  PayMod   char(30)  default '',
--支付方式
  PrjCod   char(30)  default '',
--项目编码
  RtnKey   char(30)  default '',
--返回主键
  Year     char(4)   default '',
--年度
  AmtKnd   char(30)  default '',
--资金性质
  PfaSub   char(3)   not null,
--财政编码
  CONSTRAINT PK_PFATOTCHK001 PRIMARY KEY( PfaSub, Year, TotKey )
);
--
--
--广东省财政支付明细对帐结果
--
--
create table PfaDtlChk001
(
  TActDt   char(8)   default '',
--交易日期
  TPkgNo   char(16)  default '',
--包流水号
  DtlKey   char(16)  not null,
--主键
	SubCod   char(30)  default '',
--科目
	ChkFlg	 char(1)   default '',
--对帐标识【0-支出金额和累计支出金额都无差异；1-支出金额有差异；2-累计支出金额有差异；
--          3-代理银行缺失这条记录；4-支付局行缺失这条记录】
  BnkAmt   char(15)  defautl '',
--银行支出金额
  PfaAmt   char(15)  default '',
--支付局支出金额
  DptCod   char(30)  default '',
--处室编码
	DffAmt   char(15)  default '',
--支出金额差额
  BCusId   char(30)  default '',
--单位编码
  PayMod   char(30)  default '',
--支付方式
  PrjCod   char(30)  default '',
--项目编码
  RtnKey   char(30)  default '',
--返回主键
  PfaDat   char(8)   default '',
--支付日期
  AmtKnd   char(30)  default '',
--资金性质
  PfaSub   char(3)   not null,
--财政编码
  CONSTRAINT PK_PFADTLCHK001 PRIMARY KEY( PfaSub, Year, DtlKey )
);
