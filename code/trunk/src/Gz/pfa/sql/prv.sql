drop table PfaQuoBok001;
drop table PfaVchDtl001;
drop table PfaCmdSum102;
drop table PfaQuoBok102;
drop table PfaVchDtl102;
--
--
--省财政下发额度登记表
--
--
create table PfaQuoBok001
(
  QuoSts   char(1)   not null,
--生效状态 (0-未复核 1-已复核 2-已打印授权到帐通知书)
  PfaSub   char(3)   not null,
--财政应用代码
  Year     char(4)   not null,
--年
  TSeqNo   char(20)  not null,
--计划编码
  BCusId   char(18)  not null,
--基层预算单位编码
  SubCod   char(20)  default '',
--预算科目编码（支出功能编码）
  SubNam   char(60)  default '',
--预算科目名称
  EConTp   char(20)  default '',
--经济分类
  PrjCod   char(20)  default '',
--项目编码
  DptCod   char(20)  default '',
--业务处室(指标来源)
  Mon      char(2)   not null,
--月
  TxnFlg   char(1)   default '',
--交易类型 (0-增加 1-减少)
  QuoAmt   char(15)  not null,
--额度金额
  QuoSmr   char(254) default '',
--备注
  RegDat   char(8)   not null,
--登记(下达)日期
  OTSeqNo  char(20)  default '',
--原计划编码
  QuoTim   char(14)  not null,
--下达时间
  ABnkNo   char(10)  default '',
--授权银行编码（代理银行编码）
  ActNo    char(21)  default '',
--银行账号
  AmtTyp   char(20)  default '',
--资金性质 (0001-预算内 0002-预算外 0003-自筹资金 0004-利息收入)
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
--索引
  QuoId    char(20)  default '',
--额度ID
  CONSTRAINT PK_PFAQUOBOK001 PRIMARY KEY( PfaSub,Year,TSeqNo )
);
--
--
--省财政支付凭证明细簿
--
--
create table PfaVchDtl001
(
  DtlSts   char(1)   default 'U',
--数据状态( U-初始 0-登记 1-确认 2-使用 3-撤销 4-退回 5-作废(柜员主动取消) )
  PfaSub   char(3)   not null,
--财政代码
  Year     char(4)   not null,
--财政年度
  VchDat   char(8)   not null,
--支付令日期
  AVchCd   char(30)  not null,
--支付令编号
  QuoId    char(20)  default '',
--额度ID
  PayNam   char(60)  default '',
--付款人全称
  PayAct   char(35)  default '',
--付款人帐号
  PayBNm   char(60)  default '',
--付款人开户银行
  PyeNam   char(60)  default '',
--收款人全称
  PyeAct   char(35)  default '',
--收款人账号
  PyeBNm   char(60)  default '',
--收款人开户银行
  OIFlag   char(1)   not null,
--交易方向 (O-支出 R-退回 I-主动收款) 
  DtlAmt   char(15)  not null,
--支付金额
  UseAmt   char(15)  default '0',
--实际使用金额
  BCusId   char(18)  not null,
--基层预算单位编码
  FCusId   char(18)  not null,
--一级预算单位编码
  DtlSmr   char(254) default '',
--用途
  SubCod   char(20)  default '',
--预算科目(功能分类)
  EConTp   char(20)  default '',
--经济分类编码
  PrjCod   char(20)  default '',
--预算项目编码
  DptCod   char(20)  default '',
--业务处室(指标来源)
  ChkFlg   char(1)   default '',
--银行确认标志( 0-未确认 1－已确认 )
  AmtTyp   char(20)  not null,
--资金性质 (0001-预算内 0002-预算外 0003-自筹资金 0004-利息收入)
  VchTyp   char(3)   default '',
--凭证种类
  VchNo    char(8)   default '',
--结算凭证编号
--UdwDat   char(8)   default '',
--签发日期
  TPayTp   char(20)  default '',
--支付类型
  StlMod   char(2)   default '',
--结算方式 ( 01-转帐 02-现金 03-信汇 04-电汇 05-汇票 06-本票  99-其他)
  TVchTp   char(1)   default '0',
--凭证种类( 0-普通 1-限额 2-调整 )
  OpAVCd   char(30)  default '',
--对照支付凭证号码(调整)
--行内要素
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
  DtlIdx   char(6)   default '',
--索引号
  CONSTRAINT PK_PFAVCHDTL001 PRIMARY KEY( PfaSub, Year, AVchCd )
);
create index ni1_PfaVchDtl001 on PfaVchDtl001( PfaSub, Year, AVchNo );
create index ni2_PfaVchDtl001 on PfaVchDtl001( PfaSub, PfaDat, ClrSts );
--
--
--越秀区财政指令批次表
--
--
create table PfaCmdSum102
(
  CmdSts   char(1)   not null,
--状态( U-未处理 S-审批通过 F-审批失败 )
  ACmdTp   char(1)   not null,
--指令类型(1-额度令 2-支付令 )
  Year     char(4)   not null,
--财政年度
  ACmdNo   char(8)   not null,
--批次号
  PfaLvl   char(2)   not null,
--财政级别( 00-广州市财政局 01-增城市财政局 02-白云区财政局 03-花都区财政局 04-从化市财政局 05-天河区财政局 06-荔湾区财政局 07-越秀区财政局 08-海珠区财政局 )
  OrnAmt   char(15)  not null,
--合计金额
  RegTim   char(14)  not null,
--下达日期
  OrnCnt   char(6)   not null,
--行数
  BilAth   char(10)  not null,
--制单人
  BankNo   char(12)  not null,
--总行交换行号
  BankCd   char(21)  not null,
--承办行行号
  BankNm   char(40)  not null,
--承办行名称
  MacKey   char(100) not null,
--校验位
  constraint PK_PFACMDSUM102 PRIMARY KEY( Year,ACmdNo )
);
--
--
--越秀区财政额度令明细表
--
--
create table PfaQuoBok102
(
  QuoSts   char(1)   not null,
--状态( 0-未处理 1-审批完成 )
  Year     char(4)   not null,
--财政年度
  ACmdNo   char(8)   not null,
--批次号
  TBusTp   char(4)   not null,
--业务类型( 0101-直接支付令下达 0102-直接支付支出变更 0103-直接支付令终止 0104-资金退库 )
--业务类型( 0105-授权额度下达 0106-授权额度回收 )
--业务类型( 0200-正常支付 0201-终止支付 0202-资金回退 0203-差错更正 )
  TVchNo   char(20)  not null,
--支付凭证编号
  TQuoNo   char(20)  not null,
--额度编号
  QuoId    char(20)  not null,
--对应预算指标编号
  ClrBNm   char(80)  not null,
--清算银行名称
  ClrANm   char(80)  not null,
--清算行户名
  ClrAct   char(40)  default '',
--清算行账号
  AgtBNm   char(80)  not null,
--单位代理行
  ActNm    char(80)  not null,
--单位代理行帐户名称
  ActNo    char(40)  not null,
--单位代理行账号
  BCusId   char(8)   not null,
--预算单位编码
  BCusNm   char(100) not null,
--预算单位名称
  FCusId   char(8)   not null,
--一级预算单位编码
  FCusNm   char(100) not null,
--一级预算单位名称
  AmtTyp   char(8)   not null,
--资金来源代码
  AmtNam   char(50)  not null,
--资金来源名称
  TypCod   char(2)   not null,
--功能科目类型编码
  TypNam   char(30)  not null,
--功能科目类型名称
  SubCod   char(20)  not null,
--功能分类科目编码
  SubNam   char(60)  not null,
--功能分类科目名称
  PrjCod   char(8)   default '',
--项目编码
  PrjNam   char(60)  default '',
--项目名称
  QuoAmt   char(16)  not null,
--金额
  TPayTp   char(3)   not null,
--支出类型编码( 001-统发工资 002-人员基本支出 003-专项支出 004-政府采购 005-基建支出 )
  TPayNm   char(30)  default '',
--支出类型名称
  DptCod   char(3)   not null,
--指标来源编码
  DptNam   char(30)  not null,
--指标来源名称
  EConTp   char(7)   default '',
--经济分类科目代码
  EConNm   char(60)  default '',
--经济分类科目名称
  QuoSmr   char(100) default '',
--备注
  BasFlg   char(1)   not null,
--是否允许拨回单位基本户( 0-允许，1-不允许 )
  BActNm   char(50)  default '',
--单位基本户名称
  BActNo   char(30)  default '',
--单位基本户帐号
  OpnBNm   char(30)  default '',
--单位开户行名称
  MacKey   char(100) not null,
--校验位
  RsFld1   char(30)  default '',
--预留字段1
  RsFld2   char(30)  default '',
--预留字段1
  Mon      char(2)   default '',
--月
  TxnFlg   char(1)   default '',
--交易类型 (0-增加 1-减少)
  ActDat   char(8)   default '',
--会计日期
  PfaSub   char(3)   not null,
--财政代码
  RegDat   char(8)   not null,
--读入日期
  UpdFlg   char(1)   default '0',
--更新余额表标志( 0-未更新 1-已更新 )
  ChkDat   char(8)   default '',
--审批日期
  ChkId    char(7)   default '',
--审批柜员
  RtnCod   char(3)   default '',
--处理结果( 000-表示成功 001-表示失败 002-表示注销 )
  RtnMsg   char(60)  default '',
--处理意见
  PrtCnt   char(2)   default '00',
--打印次数
  BrNo     char(6)   default '',
--分行号
  constraint PK_PFAQUOBOK102 PRIMARY KEY( Year, ACmdNo, TVchNo, TQuoNo )
);
--create index ni1_PfaQuoBok102 on PfaQuoBok102( Year,ACmdNo );
--
--
--越秀区财政支付令明细表
--
--
create table PfaVchDtl102
(
  DtlSts   char(1)   default 'U',
--数据状态( U-初始 0-登记 1-确认 2-使用 3-撤销 4-退回 5-作废(柜员主动取消) )
  PfaSub   char(3)   not null,
--财政代码
  Year     char(4)   not null,
--财政年度
  ACmdNo   char(8)   default '',
--批次号
  TLogNo   char(20)  default '',
--流水号
  TBusTp   char(4)   default '',
--业务类型
  DtlTim   char(14)  not null,
--支付日期
  TQuoNo   char(20)  default '',
--额度编号
  QuoId    char(20)  default '',
--对应预算指标编号
  TypCod   char(2)   default '',
--功能科目类型编码
  TypNam   char(40)  default '',
--功能科目类型名称
  AVchCd   char(20)  not null,
--支付凭证号
  PayNam   char(60)  not null,
--付款人全称
  PayAct   char(35)  not null,
--付款人帐号
  PayBNm   char(60)  not null,
--付款人开户银行
  PyeNam   char(60)  not null,
--付款人全称
  PyeAct   char(35)  not null,
--付款人帐号
  PyeBNm   char(60)  not null,
--付款人开户银行
  DtlAmt   char(15)  not null,
--开票金额
  UseAmt   char(15)  default '',
--实用金额
  StlMod   char(2)   default '',
--结算方式 ( 01-转帐 02-现金 03-信汇 04-电汇 05-汇票 06-本票 99-其他)
  TVchTp   char(1)   default '0',
--凭证种类( 0-普通 1-限额 2-调整 )
  FCusId   char(8)   default '',
--一级预算单位编码
  FCusNm   char(60)  default '',
--一级预算单位名称
  BCusId   char(8)   default '',
--预算单位编码
  BCusNm   char(60)  default '',
--预算单位名称
  SubCod   char(20)  default '',
--功能分类科目编码
  SubNam   char(80)  default '',
--功能分类科目名称
  Usage    char(40)  default '',
--用途
  DtlSmr   char(60)  default '',
--备注
  TPayTp   char(20)  default '',
--支出类型编码
  TPayNm   char(30)  default '',
--支出类型名称
  DptCod   char(3)   default '',
--指标来源编码
  DptNam   char(30)  default '',
--指标来源名称
  EConTp   char(6)   default '',
--经济分类科目代码
  EConNm   char(30)  default '',
--经济分类科目名称
  AmtTyp   char(8)   default '',
--资金来源代码
  AmtNam   char(30)  default '',
--资金来源名称
  PrjCod   char(8)   default '',
--项目编码
  PrjNam   char(50)  default '',
--项目名称
  StlNam   char(20)  default '',
--结算方式名称
  VchTyp   char(3)   default '',
--凭证种类
  VchNo    char(20)  default '',
--票据号码
  VchDat   char(8)   default '',
--票据日期
  MacKey   char(64)  default '',
--校验位
  RsFld1   char(100) default '',
--预留字段1
  RsFld2   char(100) default '',
--预留字段1
  OIFlag   char(1)   default '',
--交易方向 (O-支出 R-退回 I-主动收款) 
  AVchNo   char(8)   default '',
--授权凭证登记号（由行内系统生成）
  LogNo    char(14)  default '',
--记帐对应前置流水
  ActDat   char(8)   not null,
--会计日期
  RegId    char(7)   not null,
--登记柜员
  BokId    char(7)   default '',
--记帐柜员
  BokTck   char(11)  default '',
--记帐流水号
  ChkId    char(7)   default '',
--复核柜员
  NodNo    char(6)   default '',
--部门号（支付令确认部门）
  RegDat   char(8)   not null,
--登记日期
  AVchTm   char(14)  not null,
--凭证录入时间
  RefCod   char(2)   default '',
--退回代码
--PfaKnd   char(1)   not null,
--支付介质 (0-纸质 1-电子)
  ClrSts   char(1)   default '0',
--清算标志( 0-未清算 1-待清算 2-内部清算完成 3-财政清算确认 4-财政清算失败 )
  ClrBNo   char(10)  default '',
--清算批次
  ClrDat   char(8)   default '',
--内部清算日期
  PfaDat   char(8)   default '',
--财政清算日期
  DtlIdx   char(6)   default ''
--索引号
--  CONSTRAINT PK_PFAVCHDTL102 PRIMARY KEY( PfaSub, Year, TLogNo )
);
