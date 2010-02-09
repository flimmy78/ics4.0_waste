drop table PftBnkInf;
drop table PftChkTot;
drop table PftCusAgt;
drop table PftTxnJnl;
drop table PftTxnSum;
drop table PftVchReg;
drop table PftSec202Sum;
drop table PftSec202Dtl;
drop table PftBxt201;
drop table PftEft003;
--
--
--
--分行信息表
--
--
--
create table PftBnkInf
(
  BnkCls   char(1)   not null,
--银行类型 0-直接参与行  1-业务分行
  BrNo     char(6)   not null,
--交易分行
  BnkCod   char(12)  not null,
--分行支付行号
  CtlNod   char(6)   not null,
--通汇控制部门号
  ClrDat   char(8)   not null,
--当前清算日期
  SysSts   char(1)   not null,
--系统运行状态 0-系统关闭  1-系统运行
  Act01    char(21)  default '',
--22203扣款专户
  Act02    char(21)  default '',
--13801退库专户
  UserPs   char(8)   default '',
  constraint PK_PFTBNKINF PRIMARY KEY(BnkCls,BrNo)
);
--
--
--
--核对统计表
--
--
--
create table PftChkTot
(
  BnkCod   char(12)   not null,
--银行代码
  ClrDat   char(8)    not null,
--资金对数日期
  ClrSce   char(1)    not null,
--资金对数场次
  TTxnTp   char(2)    not null,
--交易类型
  ChkFlg   char(1)    default '0',
--对帐标识 0未对帐 1对帐成功
  TotNum   char(6)    not null,
--总笔数
  TotAmt   char(15)   not null,
--总金额
  BnkNum   char(6)    default '',
--银行总笔数
  BnkAmt   char(15)   default '',
--银行总金额
  CONSTRAINT PK_PFTCHKTOT PRIMARY KEY( BnkCOd,ClrDat,ClrSce,TTxnTp)
);
--
--
--
--缴税协议表
--
--
create table PftCusAgt
(
  Sts      char(1)   not null,
--状态( 0-有效 1-无效 )
  TCrpTp   char(1)   not null,
--征收机关类别( 1-国税 2-地税 3-海关 4-财政)
  AgtInf   char(35)  not null,
--协议确认码
  ActTyp   char(1)   not null,
--账户性质( 0-普通对公 1-一本通 2-普通存折 4-太平洋卡 A-中央财政对公 B-广东省财政对公 )
  ActNo    char(21)  not null,
--纳税人缴款帐号
  ActNam   char(60)  default '',
--客户名称
  VchTyp   char(3)   default '',
--凭证种类
  VchCod   char(8)   default '00000000',
--凭证号码
  ActSqn   char(5)   default '',
--一本通账户序号
  PfaSub   char(3)   default '',
--财政代码
  BCusId   char(18)  default '',
--基层预算单位编码
  SubCod   char(30)  default '',
--预算科目
  EConTp   char(20)  default '',
--经济分类编码
  PrjCod   char(20)  default '',
--预算项目编码
  DptCod   char(20)   default '',
--处室代码
  CusTel   char(60)   default ' ',
--纳税人联系电话
  OpnNod   char(6)   not null,
--开户网点
  OpnBr    char(6)   not null,
--开户分行
  CONSTRAINT PK_PFTCUSAGT PRIMARY KEY( TCrpTp,AgtInf,ActNo )
);
--
--
--缴税流水表
--
--
create table PftTxnJnl
(
  LogNo    char(14)  not null,
--前置流水号
  TTxnCd   char(6)   not null,
--接口交易码
  TxnCod   char(6)   not null,
--前置交易码
  HTxnCd   char(6)   not null,
--主机交易码
  TxnTyp   char(1)   not null,
--交易类型( N-正常交易 C-冲正交易 R-重发交易)
  BilSts   char(1)   default 'U',
--交易状态( S-成功 F-失败 R-被抹帐 C-被冲正 U-预记状态 T-主机超时 W-第三方超时 V-主机成功 )
  OIFlag   char(1)   not null,
--往来账标志( 0-往帐 1-来帐 )
  BusTyp   char(6)   not null,
--业务类型
  CrpCod   char(12)  default '',
--单位代码
  ActDat   char(8)   not null,
--会计日期
  CcyCod   char(3)   default 'CNY',
--货币代码
  TxnAmt   char(15)  not null,
--交易金额
  ActNo    char(21)  default '',
--客户帐号
  ActNam   char(60)  default '',
--客户名称
  ActTyp   char(2)   not null,
--账户性质( 0-普通对公 1-一本通 2-普通存折 4-太平洋卡 A-中央财政对公 B-广东省财政对公 )
  VchTyp   char(3)   default '',
--凭证种类
  VchCod   char(8)   default '00000000',
--凭证号码
  ActSqn   char(5)   default '',
--一本通账户序号
  PfaSub   char(3)   default '',
--财政代码
  BCusId   char(18)  default '',
--基层预算单位编码
  SubCod   char(20)  default '',
--预算科目
  EConTp   char(20)  default '',
--经济分类编码
  PrjCod   char(20)  default '',
--预算项目编码
  DptCod   char(20)  default '',
--处室代码
  NodNo    char(6)   default '',
--银行网点号
  BrNo     char(6)   not null,
--交易分行
  TlrId    char(7)   not null,
--银行柜员号
  TxnCnl   char(3)   default '',
--交易渠道
  FTxnTm   char(14)  default '',
--前置交易时间
  HLogNo   char(9)   default '',
--主机流水号
  TckNo    char(11)  default '',
--会计流水号
  PLogNo   char(14)  default '',
--中央财政流水号
  HTxnSt   char(1)   default 'U',
--主机交易状态( S-成功 F-失败 R-被抹帐 C-被冲正 U-预记状态 E-差错 T-超时)
  HRspCd   char(6)   default '',
--主机响应码
  RspCod   char(6)   default '',
--前置返回码
  RtnCod   char(4)   default '',
--返回码
  ClrDat   char(8)   default '',
--清算对数日期
  ClrSce   char(1)   default '',
--清算对数对数场次
  BTxnID   char(16)  default '',
--银行交易识别号
  ThdChk   char(1)   default '0',
--与第三方对帐标志( 0-未对帐 1-已对帐 )
  MsgFmt   char(6)   default '',
--信息格式码
  TCrpCd   char(11)  not null,
--征收机关代码
  TActDt   char(8)   default '',
--征收机关提交日期
  TLogNo   char(16)  not null,
--征收机机关流水号
  RcvBNo   char(12)  not null,
--经收处银行行号
  FskCod   char(11)  not null,
--收款国库代码
  TTxnTp   char(2)   not null,
--第三方交易类型
  OTActDt  char(8)   default '',
--对照征收机关提交日期(冲正使用)
  OTLogNo  char(16)  default '',
--对照征收机关流水号(冲正使用)
  AgtInf   char(35)  default '',
--签约附加信息
  SndAct   char(35)  default '',
--发起人帐号
  SndNm    char(60)  default '',
--发起人名称
  RcvAct   char(35)  default '',
--接收人帐号
  RcvNm    char(60)  default '',
--接收人名称
  TPayTp   char(1)   default '',
--申报方式代码( OIFlag='0'时 e-现金 f-转帐 g-POS )
  SavFld   char(2)   default '',
--保留域
  AppFlg   char(1)   default '0',
--扩展要素标志
  CONSTRAINT PK_PFTTXNJNL PRIMARY KEY( LogNo )
);
create unique index ni1_PftTxnJnl on PftTxnJnl( TCrpCd, TActDt, TLogNo );
create index ni2_PftTxnJnl on PftTxnJnl( TCrpCd, OTActDt, OTLogNo );
create index ni3_PftTxnJnl on PftTxnJnl( MsgFmt, ClrDat, ClrSce, BTxnID );
--
--
--
--缴税凭证汇总表
--
--
create table PftSec202Sum
(
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
  FilSeq   char(10)  not null,
--文件序号
  OIFlag   char(1)   default '',
--往来账标志( 0-往帐 1-来帐 )
  RcvBNo   char(12)  default '',
--经收处银行行号
  RcvBNm   char(60)  default '',
--经收处银行名称
  ActDat   char(8)   default '',
--银行提交日期
  BTxnID   char(16)  default '',
--银行交易识别号
  TTxnTp   char(2)   default '',
--第三方交易类型
  AgtInf   char(35)  default '',
--签约附加信息
  ActTyp   char(2)   default '',
--账户性质( 0-普通对公 1-一本通 2-普通存折 4-太平洋卡 A-中央财政对公 B-广东省财政对公 )
	SndAct   char(35)  default '',
--发起人账号
  RcvAct   char(35)  default '',
--缴款帐号
  ActNo    char(21)  default '',
--记帐账号
  ActNam   char(60)  default '',
--付款人名称
  TxnAmt   char(15)  not null,
--金额
  PrtFlg   char(1)   default '',
--打印完税要素标志( 0-不打 2-由商业银行打印银行回单时一并打印完税要素 )
  TaxNo    char(20)  default '',
--纳税人识别号
  TaxNam   char(100) default '',
--纳税人名称
  CrpKnd   char(40)  default '',
--企业注册类型
  TCrpNm   char(60)  default '',
--征收机关名称
  TLogNo   char(16)  not null,
--征收机机关流水号(电子税票号)
  FskNam   char(60)  default '',
--收款单位(国库)名称
  Smr      char(200) default '',
--备注
  DtlNum   char(3)   not null,
--明细数目
  DtlMac   char(64)  default '',
--密押
  PrtCnt   char(2)   default '00',
--打印次数
  OpnNod   char(6)   default '',
--网点号
  OpnBr    char(6)   default '',
--分行号
  CONSTRAINT PK_PFTSEC202SUM PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq )
);
--
--
--缴税凭证明细表
--
--
create table PftSec202Dtl
(
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
  FilSeq   char(10)  not null,
--文件序号
  DtlSeq   char(3)   not null,
--明细顺序号
  TaxTyp   char(40)  default '',
--税种名称
  PrjNam   char(60)  default '',
--品目名称
  LvlNam   char(40)  default '',
--预算级次名称
  TaxDt    char(17)  default '',
--税款所属日期
  DtlAmt   char(15)  default '',
--明细金额
  TSubCd   char(12)  default '',
--预算科目代码
  TVchNo   char(20)  default '',
--电子税票号(凭证号)
  CONSTRAINT PK_PFTSEC202DTL PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq,DtlSeq )
);
--
--
--预算外应入帐明细表
--
--
create table PftBxt201
(
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
  FilSeq   char(10)  not null,
--文件序号
  TCrpCd   char(11)  not null,
--征收机关代码
  TActDt   char(8)   not null,
--征收机关提交日期
  TLogNo   char(16)  not null,
--征收机机关流水号
  RcvBNo   char(12)  not null,
--经收处银行行号
  DirBNo   char(12)  not null,
--经收处银行清算行号
  TTxnTp   char(2)   not null,
--第三方交易类型
  TxnAct   char(35)  not null,
--缴款帐号
  TaxNam   char(100) default '',
--纳税人名称
  TaxNo    char(20)  default '',
--纳税人识别号
  CrpKnd   char(40)  default '',
--企业注册类型
  DtlSeq   char(3)   not null,
--明细顺序号
  TSubCd   char(12)  default '',
--预算科目
  TSubNm   char(60)  default '',
--预算科目名称
  AgtBNo   char(12)  not null,
--代理财政专户银行行号
  TActNo   char(35)  not null,
--代理财政专户账户
  DtlAmt   char(15)  not null,
--明细金额
  TaxTyp   char(40)  default '',
--税种名称
  PrjNam   char(60)  default '',
--品目名称
  TaxDt    char(17)  default '',
--税款所属日期
  DtlMac   char(64)  not null,
--密押
  CONSTRAINT PK_PFTBXT201 PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq )
);
--
--
--资金清算信息表
--
--
create table PftEft003
(
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
  FilSeq   char(10)  not null,
--文件序号
  PyrCod   char(12)  default '',
--付款方代码
  PyrNam   char(60)  default '',
--付款方名称
  PyrBNo   char(12)  not null,
--付款方清算支付行号
  PyrBNm   char(60)  default '',
--付款方清算支付行名
  PyrAct   char(35)  default '',
--收款方清算支付行名
  PyeCod   char(12)  default '',
--收款方代码
  PyeNam   char(60)  default '',
--收款方名称
  PyeBNo   char(12)  not null,
--收款方清算支付行号
  PyeBNm   char(60)  default '',
--收款方清算支付行名
  PyeAct   char(35)  not null,
--付款账户
  TTxnTp   char(2)   not null,
--第三方交易类型
  TRcvTp   char(1)   not null,
--经收类型
  TRTpNm   char(60)  default '',
--经收类型名称
  TaxKnd   char(12)  default '',
--税费种类
  TaxNam   char(60)  default '',
--税费种类名称
  TxnAmt   char(15)  not null,
--交易金额
  TCrpCd   char(11)  default '',
--征收机关代码
  TCrpNm   char(60)  default '',
--征收机关名称
  DtlMac   char(64)  not null,
--密押
  CONSTRAINT PK_PFTEFT003 PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq )
);
