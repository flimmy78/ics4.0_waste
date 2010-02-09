drop table PfaSubCfg;
drop table PfaOrgSts;
drop table PfaCusInf;
drop table PfaCodInf;
drop table PfaQuoBal;
drop table PfaVchBok;
drop table PfaTxnJnl;
drop table PfaClrRec;
drop table PfaClrJnl;
drop table PfaRptTbl;
drop table PfaCusAgr;
drop table PfaCrdInf;
drop table PfaCrdTxn;
drop table PfaCrdDtl;
drop table PfaCrdJnl;
--
--
--财政代码与分行号(控制表)
--
--
create table PfaSubCfg
(
  PfaSub      char(3)   not null,
--财政应用代码
  PfaNam      char(60)  not null,
--财政名称
  BrNo        char(6)   not null,
--分行号
  BrNm        char(60)  not null,
--分行名称
  OpnSts      char(1)   not null,
--开门状态 (0-已开门 1-已关门)
  BokFlg      char(1)   not null,
--记帐标志( 0-允许 1-不允许 )
  PreDat      char(8)   not null,
--上一会计日期
  CurDat      char(8)   not null,
--当前工作日期
  NxtDat      char(8)   not null,
--下一会计日期
  OprTm       char(14)  not null,
--操作时间
  AgtNod      char(6)   not null,
--代理网点
  ClrNod      char(6)   not null,
--清算网点号
  PmsSeq      char(5)   not null,
--大额往帐分户序号
  BepSeq      char(5)   not null,
--小额往帐分户序号
  RActSq      char(5)   not null,
--26201暂收户序号（清算付款）
  ClrAct      char(21)  not null,
--内部清算帐号
  ClrNam      char(60)  not null,
--内部清算户名
  ClrBTp      char(1)   not null,
--清算行别( 0-系统内 1-系统外 )
  ClrMod      char(1)   not null,
--清算方式( 0-轧差清算 1-收支独立 )
  PfaKnd      char(1)   not null,
--支付性质( 0-纸质 1-电子 )
  SOpnBk      char(12)  not null,
--清算行行号
  SOpnNm      char(60)  not null,
--清算行行名
  RcvAct      char(32)  not null,
--财政收款人账号
  RcvNam      char(60)  not null,
--财政收款人名称
  RbkNo       char(12)  not null,
--收款行行号
  RbkNm       char(60)  not null,
--收款行名称
  FldNm1      char(10)  default '',
--余额控制域名
  FldNm2      char(10)  default '',
--余额控制域名
  FldNm3      char(10)  default '',
--余额控制域名
  FldNm4      char(10)  default '',
--余额控制域名
  FldNm5      char(10)  default '',
--余额控制域名
  FldNm6      char(10)  default '',
--余额控制域名
  FldNm7      char(10)  default '',
--余额控制域名
  FldNm8      char(10)  default '',
--余额控制域名
  FldNm9      char(10)  default '',
--余额控制域名
  RtnSeq      char(2)   default '00',
--文件当日返回序号
  RtnFlg      char(1)   default '0',
--返回标志 (0-未回 1-已回)
  CONSTRAINT PK_PFASUBCFG PRIMARY KEY( PfaSub )
);
--
--
--机构状态表
--
--
create table PfaOrgSts
(
  BrNo        char(6)   not null,
--分行号
  PfaSub      char(3)   not null,  
--财政应用代码(001-中央财政 002-省级财政 003-市级财政 004-区级财政)
  OrgNod      char(6)   not null,
--机构号
  OrgNam      char(60)  not null,
--机构名称
  SgnFlg      char(1)   not null,
--签到状态 (0-已签到 1-签退)
  BokFlg      char(1)   not null,
--记帐标志( 0-允许 1-不允许 )
  OrgTyp      char(1)   default '',
--机构类型
  ActDat      char(8)   not null,
--签到日期
  CONSTRAINT PK_PFAORGSTS PRIMARY KEY( PfaSub,BrNo,OrgNod )
);
--
--
--预算单位信息表
--
--
create table PfaCusInf
(
  CusSts      char(1)   not null,
--账户状态( 0-有效 1-无效 )
  PfaSub      char(3)   not null,
--财政应用代码
  BCusId      char(18)  not null,
--基层预算单位编码
  BCusNm      char(60)  not null,
--预算单位名称
  TCusId      char(20)  default '',
--单位国标码(组织结构代码)
  ProId       char(18)  default '',
--上级预算单位编码
  ProNam      char(60)  default '',
--上级预算单位名称
  FCusId      char(18)  default '',
--一级预算单位编码
  FCusNm      char(60)  default '',
--一级预算单位名称
  ActNo       char(21)  default '',
--预算单位账号
  ActNam      char(60)  default '',
--预算单位账号名称
  CusLvl      char(1)   default '',
--单位级别
  OpnNod      char(6)   default '',
--开户部门号
  BrNo        char(6)   not null,
--分行号
  OpnBNm      char(60)  default '',
--开户银行名称
  Addr        char(60)  default '',
--预算单位地址
  Smr         char(60)  default '',
--备注（联系人、电话等）
  RegDat      char(8)   default '',
--登记日期
  AmtTyp      char(20)  default '',
--资金性质 (0001-预算内 0002-预算外 0003-自筹资金 0004-利息收入)
  ActTyp      char(1)   default '',
--账户性质
  TlrId       char(7)   not null,
--操作员
  CONSTRAINT PK_PFACUSINF PRIMARY KEY( PfaSub,BCusId )
);
--create index ni1_PfaCusInf on PfaCusInf( PfaSub,ActNo );
--
--
--基础信息代码表
--
--
create table PfaCodInf
(
  PfaSub      char(3)   not null,
--财政代码
  CodTyp      char(6)   not null,
--代码种类( SUBCOD-科目 ECONTP-经济分类 PRJCOD-项目代码 DPTCOD-业务处室 TPAYTP-支付类型 )
  Code        char(20)  not null,
--代码
  CodNam      char(60)  not null,
--代码名称
  CONSTRAINT PK_PFACODINF PRIMARY KEY( PfaSub, CodTyp, Code )
);

--
--
--额度余额表
--
--
create table PfaQuoBal
(
  BalSts      char(1)   not null,
--状态(0-正常 1-注销)
  BrNo        char(6)   not null,
--分行号
  PfaSub      char(3)   not null,
--财政应用代码
  Year        char(4)   not null,
--年度
  BCusId      char(18)  not null,
--基层预算单位编码
  TSeqNo      char(20)  default '',
--序号（计划编码）
  SubCod      char(20)  default '',
--预算科目
  PrjCod      char(20)  default '',
--预算项目
  EConTp      char(20)  default '',
--经济分类
  DptCod      char(20)  default '',
--业务处室(指标来源)
  AmtTyp      char(20)  default '',
--资金性质 (0001-预算内 0002-预算外 0003-自筹资金 0004-利息收入)
  QuoTot      char(15)  default '0',
--额度总额
  QuoBal      char(15)  default '0',
--额度余额
  FrzAmt      char(15)  default '0',
--冻结金额
  ClrAct      char(40)  default ''
);
create unique index ni1_PfaQuoBal on PfaQuoBal( PfaSub,Year,BCusId,TSeqNo,SubCod,PrjCod,EConTp,DptCod );
--
--
--支付凭证登记簿
--
--
create table PfaVchBok
(
  VchSts      char(1)    default '0',
--数据状态( U-初始 0-登记 1-确认 2-使用 3-撤销 4-退回 5-作废(柜员主动取消) )
  BrNo        char(6)    not null,
--分行号
  PfaSub      char(3)    not null,
--财政应用代码
  Year        char(4)    not null,
--财政年度
  AVchNo      char(8)    not null,
--授权凭证登记号（由行内系统生成）
  BusMod      char(1)    not null,
--业务类型 (0-授权支付 1-直接支付)
  OIFlag      char(1)    not null,
--交易方向 (O-支出 R-退回 I-主动收款)
  VchDat      char(8)    not null,
--支付令日期
  CrpVch      char(8)    not null,
--单位凭证号(？)
  PayAct      char(35)   not null,
--付款人帐号
  PayNam      char(60)   not null,
--付款人全称
  PayBNm      char(60)   default '',
--付款人开户银行
  PyeAct      char(35)   default '',
--收款人账号
  PyeNam      char(60)   default '',
--收款人全称
  PyeBNm      char(60)   default '',
--收款人开户银行
  BCusId      char(18)   not null,
--基层预算单位编码
  StlMod      char(2)    default '',
--结算方式 ( 01-转帐 02-现金 03-信汇 04-电汇 05-汇票 06-本票  99-其他)
  VchTyp      char(3)    default '',
--凭证种类
  VchNo       char(8)    default '',
--结算凭证编号
  UdwDat      char(8)    default '',
--签发日期
  Pin         char(16)   default '',
--支付密码
  TxnAmt      char(15)   not null,
--支付金额
  TPayTp      char(20)   default '',
--支付类型
  RefCod      char(2)    default '',
--退回代码
  VchSmr      char(60)   default '',
--用途
  PayCnl      char(1)    default '',
--支付渠道
  DtlNum      char(2)    not null,
--明细笔数
  TVchTp      char(1)    default '0',
--凭证种类( 0-普通 1-限额 2-调整 )
  ChkFlg      char(1)    default '',
--银行确认标志( 0-未确认 1－已确认 )
  AmtTyp      char(20)    not null,
--资金性质 (0001-预算内 0002-预算外 0003-自筹资金 0004-利息收入)
  AmtSrc      char(10)   default '',
--资金来源
  LogNo       char(14)   default '',
--记帐对应前置流水
  ActDat      char(8)    not null,
--会计日期
  RegId       char(7)    not null,
--登记柜员
  BokId       char(7)    default '',
--记帐柜员
  BokTck      char(11)   default '',
--记帐流水号
  ChkId       char(7)    default '',
--复核柜员
  NodNo       char(6)    default '',
--部门号（支付令确认部门）
  AVchTm      char(14)   not null,
--凭证录入时间
  PfaKnd      char(1)    not null,
--支付介质 (0-纸质 1-电子)
  ClrSts      char(1)    default '0',
--清算标志( 0-未清算 1-待清算 2-内部清算完成 3-财政清算确认 4-财政清算失败 ) 
  ClrBNo      char(10)   default '',
--清算批次
  ClrDat      char(8)    default '',
--内部清算日期
  PfaDat      char(8)    default '',
--财政清算日期
  RtnFlg      char(1)    not null,
--回应标志 (0-未回 1-已回)
  CONSTRAINT PK_PFAVCHBOK PRIMARY KEY( PfaSub, Year, AVchNo )
);
create unique index ni1_PfaVchBok on PfaVchBok( PfaSub,Year,BCusId,CrpVch );
create index ni2_PfaVchBok on PfaVchBok( PfaSub,Year,ClrBNo );
create index ni3_PfaVchBok on PfaVchBok( PfaSub, PfaDat, ClrSts );
--
--
--支付交易流水表
--
--
create table PfaTxnJnl
(
  LogNo      char(14)  not null,
--前置流水号
  TTxnCd     char(10)  not null,
--第三方交易码
  TxnCod     char(6)   not null,
--交易码
  TxnTyp     char(1)   not null,
--交易类型( N-正常交易 C-冲正交易 R-重发交易 )
  BusTyp     char(6)   not null,
--业务类型
  CrpCod     char(10)  Default '',
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
  CrdNo      char(30)  default '',
--客户卡号
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
  FRspCd     char(6)   not null,
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
--第三方交易状态(  S-成功 F-失败 R-被冲正 U-预记状态 )
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
  PfaSub     char(3)   not null,
--财政应用码
  BCusId     char(18)  not null,
--基层预算单位编码
  BusMod     char(1)   default '0',
--业务类型 (0-授权支付 1-直接支付)
  OIFlag     char(1)   not null,
--交易方向 (O-支出 R-退回 I-主动收款) 
  AVchCd     char(30)  default '',
--支付令编号
  TSeqNo     char(20)  default '',
--计划编码
  SubCod     char(20)  default '',
--预算科目
  PrjCod     char(20)  default '',
--预算项目
  EConTp     char(20)  default '',
--经济分类
  DptCod     char(20)  default '',
--业务处室(指标来源)
  AVchNo     char(8)   not null,
--授权凭证登记号码
  ActSts     char(1)   default '0',
--明细状态( 1-记帐 2-复核 3-抹帐 )
  PayAct     char(35)  default '',
--付款人帐号
  PayNam     char(60)  default '',
--付款单位全称
  PayAdr     char(60)  default '',
--付款单位地址
  PayBNm     char(60)  default '',
--付款单位开户银行
  PyeAct     char(35)  default '',
--收款单位帐号
  PyeNam     char(60)  default '',
--收款单位全称
  PyeAdr     char(60)  default '',
--收款单位地址
  PyeBNm     char(60)  default '',
--收款单位开户银行
  VchTyp     char(3)   default '',
--结算凭证种类
  VchNo      char(8)   default '',
--结算凭证编号
  UdwDat     char(8)   default '',
--签发日期
  Pin        char(16)  default '',
--支付密码
  Smr        char(60)  default '',
--用途
  EleBk      char(5)   default '',
--联行号
  CclAct     char(21)  default '',
--销帐帐号
  CclNo      char(12)  default '',
--销帐号
  CclSqn     char(4)   default '',
--销帐序号
  RBkNo      char(12)  default '',
--支付行号
  ChkId      char(7)   default '',
--凭证复核柜员号
  PChkId     char(7)   default '',
--支付复核柜员号
  PayCnl     char(2)   default '',
--支付渠道( 0-交换  1-支付  2-金融平台 )
  ClrSts     char(1)   default '0',
--清算标志( 0-未清算 1-待清算 2-内部清算完成 ) 
  ClrBNo     char(10)  default '',
--清算批次
  ClrDat     char(8)   default '',
--内部清算日期
--PfaDat     char(8)   default '',
--财政清算日期
  PrvDat     clob(3072) default '',
  CONSTRAINT PK_PFATXNJNL PRIMARY KEY( LogNo )
);
create index ni1_PfaTxnJnl on PfaTxnJnl( PfaSub, AVchNo );
create index ni2_PfaTxnJnl on PfaTxnJnl( ActDat, TckNo );
create index ni3_PfaTxnJnl on PfaTxnJnl( PfaSub, ClrSts, HTxnSt, ActSts, TxnAmt );
--
--
--清算记录表
--
--
create table PfaClrRec
(
  ClrSts      char(1)   not null,
--清算状态(0-初始状态 1-待清算 2-已清算 )
  BrNo        char(6)   not null,
--分行号
  PfaSub      char(3)   not null,
--财政应用代码
  ClrTyp      char(1)   not null,
--清算种类( 0-系统内清算 1-退款清算 2-人行清算 )
  ClrBNo      char(10)  not null,
--清算批次
  OIFlag      char(1)   not null,
--交易方向 (O-支出 R-退回 I-主动收款) 
  LogNo       char(14)  not null,
--流水号
  RknVno      char(20)  default '',
--人行清算凭证编号
  BCusId      char(18)  default '',
--基层预算单位编码
  BCusNm      char(60)  default '',
--基层预算单位名称
  ActNo       char(21)  default '',
--清算帐号
  ActNm       char(60)  default '',
--户名
  TxnAmt      char(15)  default '0',
--金额
  ClrDat      char(8)   default '',
--清算日期(会计日期）
  PfaDat      char(8)   default '',
--财政清算日期
  ClrTm       char(14)  default '0'
--清算时间
);
--create unique index ni1_PfaClrRec on PfaClrRec( PfaSub,ClrTyp,ClrBNo,OIFlag,BCusId,ActNo );
--
--
--清算流水表
--
--
create table PfaClrJnl
(
  LogNo      char(14)  not null,
--前置流水号
  TTxnCd     char(10)  not null,
--第三方交易码
  TxnCod     char(6)   not null,
--交易码
  TxnTyp     char(1)   not null,
--交易类型( N-正常交易 C-冲正交易 R-重发交易)
  BusTyp     char(6)   not null,
--业务类型
  CrpCod     char(10)  Default '',
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
  CrdNo      char(30)  default '',
--客户卡号
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
  FRspCd     char(6)   not null,
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
--第三方交易状态(  S-成功 F-失败 R-被冲正 U-预记状态 )
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
  ClrSts     char(1)   default '0',
--清算状态(0-初始状态 1-待清算 2-已清算)
  ClrBNo     char(10)  default '',
--清算批次
  ClrDat     char(8)   default '',
--内部清算日期
  PfaDat     char(8)   default '',
--财政清算日期
  OIFlag     char(1)   default '',
--交易方向 (O-支出 R-退回 I-主动收款) 
  CONSTRAINT PK_PFACLRJNL PRIMARY KEY( LogNo )
);
--
--
--财政回应文件临时表
--
--
create table PfaRptTbl
(
  PfaSub      char(3)    not null,
--财政应用代码
  BCusId      char(18)   not null,
--基层预算单位编码
  BCusNm      char(60)   default '',
--预算单位名称
  SubCod      char(20)   default '',
--预算科目(功能分类)
  SubNam      char(60)   default '',
--预算科目名称
  EConTp      char(20)   default '',
--经济分类编码
  EConNm      char(60)   default '',
--经济分类名称
  PrjCod      char(20)   default '',
--预算项目编码
  PrjNam      char(60)   default '',
--预算项目名称
  DptCod      char(20)   default '',
--处室代码
  DptNam      char(60)   default '',
--处室名称
  ActNo       char(35)   default '',
--帐号
  OIFlag      char(1)    default '',
--交易方向
  TxnAmt      char(15)   default '0',
--支出金额
  PmsBNo      char(12)   default ''
);
--
--
--财政代理业务协议表
--
--
create table PfaCusAgr
(
  AgrNo       char(60)   not null,
--借记协议编号
  PfaSub      char(3)    not null,
--财政代码
  BCusId      char(18)   not null,
--基层预算单位编码
  SubCod      char(20)   default '',
--预算科目
  EConTp      char(20)   default '',
--经济分类编码
  PrjCod      char(20)   default '',
--预算项目编码
  DptCod      char(20)   default '',
--处室代码
  ActNo       char(21)   not null,
--零余额帐户
  BrNo        char(6)    not null,
  CONSTRAINT PK_PFACLRJNL PRIMARY KEY( AgrNo )
);
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
  TLogNo      char(6)   not null,
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
  IdxNo        char(6)   default '',
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
  TLogNo      char(6)   default '',
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
  IdxNo        char(6)   default '',
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
  RtnFlg      char(1)    default '0',
--回应标志 (0-未回 1-已回)
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
