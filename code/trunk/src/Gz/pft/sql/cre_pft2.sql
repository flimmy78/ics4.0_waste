drop table PftCrpInf;
drop table PftFilInf;
drop table PftSec203Sum;
drop table PftSec203Dtl;
--
--
--
--征收机关信息表
--
--
--
create table PftCrpInf
(
  Sts      char(1)   not null,
--状态( 0-有效 1-无效 )
  TCrpTp   char(1)   not null,
--征收机关类别( 1-国税 2-地税 3-海关 4-财政)
  TCrpCd   char(11)  not null,
--征收机关代码
  TCrpNm   char(60)  not null,
--征收机关名称
  FskCod   char(11)  not null,
--对应国库代码
  FskNam   char(60)  not null,
--对应国库名称
  AgtBNo   char(8)   default '',
--代理行行号
  AgtBNm   char(60)  default '',
--代理行名称
  Rmk      char(60)  default '',
--备注
  constraint PK_PFTCRPINF PRIMARY KEY( TCrpTp,TCrpCd )
);
--
--
--
--广州退库信息表
--
--
--
create table PftFilInf
(
  FilSts   char(1)   not null,
--文件处理状态( 0-数据正在读入 1-数据读入成功 2-清算正在进行 3-清算完成 4-退库退回正在处理 5-退库退回完成 )
  PftFil   char(60)  not null,
--文件名
  ClrDat   char(8)   not null,
--清算日期
  ActDat   char(8)   not null,
--会计日期
  MsgFmt   char(6)   default '',
--信息类型
  RcvBNo   char(11)  default '',
--直接参与行行号
  BatNo    char(4)   default '',
--批次号
  TotNum   char(6)   default '',
--总笔数
  TotAmt   char(15)  default '',
--总金额
  RetCod   char(4)   default '',
--批返回码
  ErrNum   char(6)   default '',
--错误笔数
  constraint PK_PFTFILINF primary key( PftFil )  
);
--
--
--退库凭证汇总表
--
--
create table PftSec203Sum
(
  PftFil   char(60)  not null,
--文件名
  MsgFmt   char(6)   not null,
--信息格式码
  ClrDat   char(8)   not null,
--ETS资金对数日期
  SndCod   char(12)  not null,
--文件发送方代码
  RcvCod   char(12)  not null,
--文件接收方代码
  ClrSce   char(4)   not null,
--ETS资金对数场次
  OIFlag   char(1)   default '',
--往来账标志( 0-往帐 1-来帐 )
  TCrpCd   char(11)  not null,
--征收机关代码
  TActDt   char(8)   not null,
--征收机关提交日期
  TLogNo   char(16)  not null,
--征收机机关流水号
  RcvBNo   char(12)  not null,
--经收处银行行号
  FskCod   char(11)  not null,
--收款国库代码
  TTxnTp   char(2)   not null,
--第三方交易类型
  Smr      char(8)   default '',
--备注
  TVchNo   char(20)  default '',
--电子税票号(凭证号)
  RcvAct   char(35)  default '',
--接收人帐号
  SndAct   char(35)  default '',
--发起人帐号
  TxnAmt   char(15)  not null,
--金额
  TPayTp   char(1)   default '',
--申报方式代码( OIFlag='0'时 e-现金 f-转帐 g-POS )
  PrtFlg   char(1)   not null,
--打印完税要素标志( 0-不打 2-由商业银行打印银行回单时一并打印完税要素 )
  TaxNam   char(100) default '',
--纳税人名称
  TaxNo    char(20)  default '',
--纳税人识别号
  CrpKnd   char(4)   default '',
--企业注册类型
  DtlNum   char(3)   not null,
--明细数目
  DtlMac   char(64)  default '',
--密押
  BilSts   char(1)   default 'U',
--处理结果
  ActDat   char(8)   not null,
--银行提交日期
  LogNo    char(14)  default '',
--前置流水号
  HRspCd   char(6)   default '',
--主机返回码
  TckNo    char(11)  default '',
--会计流水号
  RtnCod   char(8)   default '',
--处理结果
  ActTyp   char(2)   default '',
--账户性质( 0-普通对公 1-一本通 2-普通存折 4-太平洋卡 A-中央财政对公 B-广东省财政对公 )
  ActNo    char(21)  default '',
--缴款帐号
  ActNam   char(60)  default '',
--付款人名称
  PrtCnt   char(2)   default '00',
--打印次数
  OpnNod   char(6)   default '',
--网点号
  OpnBr    char(6)   default '',
--分行号
  CONSTRAINT PK_PFTSEC203SUM PRIMARY KEY( PftFil,TCrpCd,TActDt,TLogNo )
);
create index ni1_PftSec03Sum on PftSec203Sum( ClrDat );
--
--
--退库凭证明细表
--
--
create table PftSec203Dtl
(
  PftFil   char(60)  not null,
--文件名
  TCrpCd   char(11)  not null,
--征收机关代码
  TActDt   char(8)   not null,
--征收机关提交日期
  TLogNo   char(16)  not null,
--征收机机关流水号
  DtlSeq   char(3)   not null,
--明细顺序号
  DtlAmt   char(15)  default '',
--明细金额
  LvlNam   char(40)  default '',
--预算级次名称
  TSubCd   char(12)  default '',
--预算科目代码
  TaxTyp   char(40)  default '',
--税种名称
  TRtnCd   char(10)  default '',
--退库原因代码
  Rmk1     char(7)   default '',
--保留域一
  Rmk2     char(16)  default '',
--保留域二
  CONSTRAINT PK_PFTSEC203DTL PRIMARY KEY( PftFil,TCrpCd,TActDt,TLogNo,DtlSeq )
);
