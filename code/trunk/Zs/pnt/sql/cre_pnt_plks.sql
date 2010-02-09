drop table pntfilctl;
drop table pntbatrec;
drop table pntextbat;
drop table pntfilinf;
--批量文件控制表
create table pntfilctl
(
   FileNo      char(10) not null,
-- 文件号
   FileNam    char(50) not null,
-- 文件名
   DskNo      char(12) not null,
-- 批次号   
   BankCd     char(30) not null,
-- 银行编码
   TCrpCd     char(30) not null,
-- 执收单位编码
   TxnDat     char(8)  not null,
-- 日期
   ActDat     char(8)  not null,
-- 会计日期
   TotNum     char(10) not null,
-- 总笔数
   TotAmt     char(16) not null,
-- 总金额
   RcvTim     char(14) not null default '',
-- 接收文件时间   
   SndTim     char(14) not null default '',
-- 回盘文件时间
   TlrId      char(7)  not null default '',
-- 操作柜员
   DskSts     char(1)  not null default '',
-- 批次状态(1为未扣费,2为已扣费,3已打印)
   Primary key(DskNo)
);

--批量文件明细表
create table pntbatrec
(
   FSeqNo     char(15)    not null default ' ',
--前置记录序号
   LogNo     char(14)    not null default ' ',
--流水号
   FileNo    char(10)     not null,
--文件号
   DskNo     char(12)    not null,
--批次号
   SeqNo     char(07)    not null,
--顺序号
   BusTyp    char(6)     not null default ' ',
--业务类型
   CrpCod   char(10)     not null default ' ', 
--单位代码
   ActDat   char(8)      not null,
--会计日期
   BSmr     char(04)     not null default ' ',
--业务摘要码
   VchCod    char(03)    not null default ' ',
--凭证代码*
   ActTyp    char(01)    not null default ' ',
--账号类型 2账号 4卡号
   ActSqn      char(5)   default ' ' not null,
--账号顺序号
   ActNo     char(21)    not null default ' ',
--新账号
   ActNam    char(60)    not null default ' ',
--户名
   CAgtNo   char(10)    not null default ' ',
--单位编号
   TxnCod   char(06)    not null default ' ',
--交易码
   CcyCod   char(3)     not null default 'CNY',
--货币代码
   TxnDat   char(08)    not null default ' ',
--交易日期
   TxnDir   char(01)    not null default ' ',
--借贷标志
   FulChk  char(01) not null default ' ',
--不足额扣款标志	‘0’正常扣款 ‘1’余额不足时最大额扣款
   CrgFlg   char(01) not null default ' ',
--收费标志
   CrgCod   char(04) not null default ' ',
--收费代码
   CActNo   char(21) not null default ' ',
--单位账号
   RecSts   char(01) not null default ' ',
--状态	SPACE-未处理 E-处理错误(应有出错代码) F-处理成功 N-代发类交易转下批处理  R-代发类交易转发其它户 P-部分扣款成功 X-协议检查错
   Fee         char(15)    default ' ' not null,
--手续费金额
   HTxnCd       char(6)    default ' ',
--主机交易码
   HLogNo       char(9)    default ' ' not null,
--主机流水号
   HRspCd       char(6)    default ' ',
--主机响应码
   HTxnSt       char(1)    default 'U' not null,   
--U:预记状态(缺省值) S：成功 F:失败 C:被冲正 U:预记状态  X:发送失败  T:发送超时  D:交易被撤销  E:其他错误
   HPrChk      char(1)     default '0' not null,
--0:未对账(缺省值) 1:已对账 2:对账不符
   HLsChk      char(1)     default '0' not null,
--0:未对账(缺省值) 1:已对账 2:对账不符
   IsTxn     char(1)    default 'Y' not null,
--Y:要发送  N:不发送
   TxnCnl       char(3) default ' ' not null,
--交易渠道
   TxnObj       char(8) default ' ' not null,
--目标服务器
   TlrId        char(7) default ' ' not null,
--记账柜员号
   TTxnCd       char(6)     default ' ' not null,
--前置交易码
   BrNo         char(6)     default ' ' not null,
--入账分行号
   NodNo       char(6)     default ' ' not null,
--入账网点号
   TxnMod      char(1)     default ' ' not null,
--交易方式
   PayMod      char(1)     default ' ' not null,
--支付方式
   FunCod   char(2 ) not null default ' ',
--业务类型
	TVchId   char(50)   not null,
--缴款通知书编码
	TBilTp   char(8)    not null,
--票据类型编码
  TBilNo   char(20)   not null default ' ',
--票据号码
	PayNam   char(60)   default '',
--缴费人(单位)名称
	TxnAmt   char(15)   not null,
--应收总金额
  PrjNum   char(1)    not null,
--收费项目数
  TCusID    char(30) not null default ' ',
--第三方客户标识,凭单号
  TCusNm    char(60) not null default ' ',
--第三方客户名称
   RsFld1   char(30) not null default ' ',
--备注
   CTBLNm      char(30)   not null  default ' ',
--扩展子表名
   ExtKey      bigint ,
--扩展子表键值
    primary key(DskNo,SeqNo)
);

create table pntextbat
(
   ExtKey      bigint ,
--扩展子表键值
  AA     char(30),
  BB     char(30),
  CC     char(30),
  DD     char(30),
  EE     char(30),
  FF     char(30),
  GG     char(30),  
  HH     char(30),
  II     char(30),
  JJ     char(30),
  KK     char(30),
  LL     char(30),
  MM     char(30),
  NN     char(30),  
  OO     char(30),
  PP     char(30),
  QQ     char(30),
  RR     char(30),
  SS     char(30),
  TT     char(30),
  UU     char(30),  
  VV     char(30),
  WW     char(30),
  XX     char(30),
  YY     char(30),
  ZZ     char(30),
  A1     char(30),
  B1     char(30),  
  C1     char(30),
  D1     char(30),    
  E1     char(30),
  F1     char(30),
  G1     char(30),  
  H1     char(30),
  I1     char(30)
);

--文件信息表
create table pntfilInf
(
   FileNo      char(10) not null,
-- 文件号
   FileNam    char(50) not null,
-- 文件名  
   BankCd     char(30) not null,
-- 银行编码
   TCrpCd     char(30) not null,
-- 执收单位编码
   TxnDat     char(8)  not null,
-- 日期
   ActDat     char(8)  not null,
-- 会计日期
   TotNum     char(10) not null,
-- 总笔数
   TotAmt     char(16) not null,
-- 总金额
   RcvTim     char(14) not null default '',
-- 接收文件时间   
   SndTim     char(14) not null default '',
-- 回盘文件时间
   TlrId      char(7)  not null default '',
-- 操作柜员
   DskSts     char(1)  not null default '',
-- 批次状态(1为未扣费,2为已扣费,3已打印)
   Primary key(FileNo,FileNam)
);