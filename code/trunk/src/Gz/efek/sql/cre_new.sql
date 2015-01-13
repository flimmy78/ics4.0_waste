drop table EFEKRUNCTL;
drop table EFEKCUSAGT;
drop table EFEKBCHREC;
drop table EFEKTXNDTL;
drop table EFEKTXNJNL;
-- ============================================================
--   系统运行状态控制表
-- ============================================================
create table EFEKRUNCTL(
  DWBM   char(8)   not null,      --单位编码
  JYLSH  char(24)  not null,      --交易流水号
  JYRQ   char(8)   not null,      --交易日期
  JYSJ   char(6)   default '',    --交易时间
--  GDDW   char(8)   default '',    --供电单位
  YWBSH  char(6)   default '',    --业务标识号
  CZRY   char(20)  default '',    --操作人员
  ZT     char(1)   default '',    --状态( K开工  Q签退 )
  BZ     char(128) default '',    --备注
  BRNO   char(6)   default '',    --归属分行
  InAcNo char(40)  default '',    --日间记账账号
  ClrAct char(40)  default '',     --电网清算账号
  CONSTRAINT PK_EFEKRUNCTL PRIMARY KEY( DWBM )
);
-- ============================================================
--    银电客户签约表
-- ============================================================
create table EFEKCUSAGT(
  ChkFlg   char(1)   default 'U',--核对标志( U-未核对，S-核对成功 F-核对失败 )
  OIFLAG   char(1)   not null,   --交易方向
  DWBM     char(8)   not null,   --单位编码
	JFH	     char(20)	 not null,   --缴费号
  JSHMC	   char(64)  default '', --结算账户名称
  QYYHDM   char(4)	 default '', --签约银行代码
  QYYHZH   char(40)  default '', --签约银行账户
  QYYHZHMC char(128) default '', --签约银行账户名称
  ZHLX     char(2)   default '', --0对公账户 1对私储蓄 2对私信用卡 3对私借记卡 4外币
  ZJLX	   char(2)   default '', --证件类型
  ZJHM     char(32)	 default '', --证件号码
  LXDH     char(20)  default '', --联系电话
  SJHM     char(20)  default '', --手机号码
  EMAIL    char(64)  default '', --电邮
  FQFJYLSH char(24)  default '', --发起方交易流水号
  FQFJYRQ  char(8)   default '', --发起方交易日期
  FQFJYSJ  char(6)   default '', --发起方交易时间
  JSFJYLSH char(24)  default '', --接收方交易流水号
  JSFJYRQ  char(8)   default '', --接收方交易日期
  JSFJYSJ  char(6)   default '', --接收方交易时间
  QDBZ     char(1)   default '', --签约标志 0新增 1修改 2注销
  QYZT     char(1)   default '', --签约状态 1本行已签 2本行已变更待确定 3他行已签
  NodNo    char(11)  default '', --网点号
  BrNo     char(11)  default '', --分行号
  ActFlg   char(1)   not null,   --银行内部账户类型(  0-对公 1-存折 2-一本通 3-借记卡 A-中央财政 B-地方财政 )
  PfaSub   char(3)   default '', --财政代码
  BCusId   char(18)  default '', --预算单位编码
  PayCod   char(30)  default '', --中央财政支付密码
  CONSTRAINT PK_EFEKCUSAGT PRIMARY KEY( DWBM,JFH )
);
-- ============================================================
--    银电客户签约表历史表,记录客户协议变更的各个操作
-- ============================================================
create table EFEKCUSHIS(
  ChkFlg   char(1)   default 'U',--核对标志( U-未核对，S-核对成功 F-核对失败 )
  OIFLAG   char(1)   not null,   --交易方向
  DWBM     char(8)   not null,   --单位编码
	JFH	     char(20)	 not null,   --缴费号
  JSHMC	   char(64)  default '', --结算账户名称
  QYYHDM   char(4)	 default '', --签约银行代码
  QYYHZH   char(40)  default '', --签约银行账户
  QYYHZHMC char(128) default '', --签约银行账户名称
  ZHLX     char(2)   default '', --0对公账户 1对私储蓄 2对私信用卡 3对私借记卡 4外币
  ZJLX	   char(2)   default '', --证件类型
  ZJHM     char(32)	 default '', --证件号码
  LXDH     char(20)  default '', --联系电话
  SJHM     char(20)  default '', --手机号码
  EMAIL    char(64)  default '', --电邮
  FQFJYLSH char(24)  default '', --发起方交易流水号
  FQFJYRQ  char(8)   default '', --发起方交易日期
  FQFJYSJ  char(6)   default '', --发起方交易时间
  JSFJYLSH char(24)  default '', --接收方交易流水号
  JSFJYRQ  char(8)   default '', --接收方交易日期
  JSFJYSJ  char(6)   default '', --接收方交易时间
  QDBZ     char(1)   default '', --签约标志 0新增 1修改 2注销
  QYZT     char(1)   default '', --签约状态 1本行已签 2本行已变更待确定 3他行已签
  NodNo    char(11)  default '', --网点号
  BrNo     char(11)  default '', --分行号
  ActFlg   char(1)   not null,   --银行内部账户类型(  0-对公 1-存折 2-一本通 3-借记卡 A-中央财政 B-地方财政 )
  PfaSub   char(3)   default '', --财政代码
  BCusId   char(18)  default '', --预算单位编码
  PayCod   char(30)  default '' --中央财政支付密码
);
-- ============================================================
--    银电批扣记录表
-- ============================================================
create table EFEKBCHREC(
  RecSts  char(1)   default 'u',--批量记录状态( u-接收后 U-接收完成 b-账务处理中 B-账务处理完成 c冲正中 C冲正完成 s回应发送 S回应完成 )
  OIFlag  char(1)   not null, --发起标志( O-银行发起 I-电力发起 )
--数据包内容
  FQFJYLSH	  char(24)  not null,   --交易流水号
  FQFJYRQ	  char(8 )  default '', --交易日期
  FQFJYSJ	  char(6 )  default '', --交易时间
  DWBM	  char(8 )  default '', --单位编码
  SFFS	  char(3 )  default '', --收费方式
  FYLX	  char(3 )  default '', --费用类型
  KHBZ	  char(1 )  default '', --跨行标志
  FQFWJMC	  char(36)  not null,   --文件名称
  FQFWJLX	  char(2 )  default '', --文件类型
  FQFWJMD5	  char(32)  default '', --文件MD5
  ZBS	    char(11)  default '', --总笔数
  ZJE	    char(16)  default '', --总金额
--文件头第一行内容
  PLDSXXBS char(27) default '', --批量代收信息标识
  YHDM	  char(4 )  default '', --银行代码
  SYHRQ	  char(8 )  default '', --送银行日期
  HBFH	  char(5 )  default '', --货币符号
  DGBZ	  char(2 )  default '', --对公标志
  SM	    char(128) default '', --说明
--回应文件第一行内容
  JSFJYLSH char(24)  default '', --银行流水号
  JSFYHJYRQ  char(8 )  default '', --交易日期
  JSFYHJYSJ	char(6 )  default '', --交易时间
  JSFWJMC	char(36)  default '', --文件名称
  JSFWJLX	char(2 )  default '', --文件类型
  JSFWJMD5	char(32)  default '', --文件MD5
  CGBS    char(11)  default '', --成功笔数
  CGJE    char(16)  default '', --成功金额
  SBBS    char(11)  default '', --失败笔数
  SBJE    char(16)  default '', --失败金额
  SFY     char(20)  default '', --收费员
  ActDat  char(8)   default '', --银行会计日期
  DskNo   char(12)  default '', --批量磁盘号
  NodNo   char(6)   default '', --网点号
  BrNo    char(6)   default '', --分行号
  CONSTRAINT PK_EFEKBCHREC PRIMARY KEY( OIFLAG, FQFJYLSH )
);
create unique index ni1_EFEKBCHREC ON EFEKBCHREC( OIFlag, FQFWJMC );
create index ni2_EFEKBCHREC ON EFEKBCHREC( DskNo );
-- ============================================================
--    银电交易明细表
-- ============================================================
create table EFEKTXNDTL(
  DtlSts char(1)    default 'U', --明细状态( U-初始 B-账务处理 S-成功 F-失败 C-冲销)
  BatFlg char(1)    not null, --批量标志( B-批量 S-单笔 )
  TxnSrc char(3)    default '',  --交易来源( TRM-柜面 )
  WJMC	 char(36)   default '',  --文件名称
  OIFlag char(1)    not null, --发起标志( O-银行发起 I-电力发起 )
  FQFJYLSH char(24)   not null, --交易流水号  
  XH       char(10)   not null default '0000000001',
  FQFJYRQ	 char(8 )   default '', --交易日期
  FQFJYSJ	 char(6 )   default '', --交易时间
  SFFS	 char(3 )   default '', --收费方式
  FYLX	 char(3 )   default '', --费用类型
  DWBM   char(20)   default '', --单位代码
  JFH    char(20)   default '', --缴费号
  JSHMC  char(64)   default '', --结算户名称
  KKYHDM char(4 )   default '', --扣款银行代码
  KKZH   char(32)   default '', --扣款账户
  KKZHMC char(128)  default '', --扣款账户名称
  BFJFBZ char(1 )   default '', --部分缴费标志
  ZWLSH  char(16)   default '', --账务流水号
  DFNY   char(6 )   default '', --电费年月
  HBFH	 char(5 )   default 'RMB', --货币符号
  YKJE   char(16)   default '', --应扣金额
  BJ     char(16)   default '', --本金
  WYJ    char(16)   default '', --违约金
  FKFS   char(1 )   default '', --付款方式( 0-现金 1-非现金 )
  YFFBZ  char(1 )   default '', --预付费标志
  YFFJE  char(16)   default '', --预付费金额
  SKJE   char(16)   default '', --实扣金额
  XJYDGJXX char(128) default '', --协议号等(需校验的关键信息)
  TSBZ   char(1)    default '', --托收标志
  KKRQ   char(8 )   default '', --扣款日期
  KKSJ   char(6 )   default '', --扣款时间
  CXYY   char(128)  default '', --冲销原因
  PJLY   char(1)    default '', --票据来源(	0-银行自有 1-电力提供 )
  PJLX   char(2)    default '', --票据类型( 1-普通发票 2-收据 )
  FPDM   char(32)   default '', --发票代码
  PJHM   char(16)   default '', --票据号码
--银行内部要素
  LogNo  char(14)   default '', --前置流水号
  DskNo  char(12)   default '', --批量磁盘号
  ActDat char(8)    default '', --会计日期
  IsTxn  char(1)    default 'N',--是否发送主机标志，用于批量大小通道发送  Y发送N不发送
  TxnObj char(8)    default '',--大小通道目标服务
  UpdFlg char(1)    default 'N',--更新标志
  UpdFld char(20)   default 'HTXNCD|BUSTYP|',--更新字段名
  TTxnCd char(6)    default '', --前置交易码
  TTxnSt char(1)    default '', --第三方状态
  HTxnCd char(6)    default '', --主机交易码
  HTxnSt char(1)    default 'U',--主机状态
  HLogNo char(9)    default '', --主机流水号
  HRspCd char(6)    default '', --主机返回码
  TRspCd char(6)    default '', --电网返回码
  TlrId  char(7)    default '', --柜员号
  TrmNo  char(7)    default '', --终端号
  TckNo  char(11)   default '', --会计流水号
  RspCod char(6)    default '', --银行处理结果码
  InAcNo char(40)   default '', --日间记账账号
  NodNo  char(11)   default '', --网点号
  BrNo   char(11)   default '', --分行号
  JSFJYLSH char(24)  default '', --银行流水号
  JSFJYRQ char(8 )   default '', --交易日期
  JSFJYSJ char(6 )   default '', --交易时间
  YHSFLSH char(27)   default '', --银行流水号
  DAZRQ  char(8 )   default '', --达账日期
  DAZSJ  char(6 )   default '', --达账时间
  DZPCLSH char(27)  default '', --对账批次流水号
  CONSTRAINT PK_EFEKTXNDTL PRIMARY KEY( OIFLAG, FQFJYLSH, XH )
); 
create index ni1_EFEKTXNDTL ON EFEKTXNDTL( LogNo );
create index ni2_EFEKTXNDTL ON EFEKTXNDTL( FQFWJMC );
-- ============================================================
--    银电交易流水表
-- ============================================================
create table EFEKTXNJNL(
  LogNo      char(14)  not null,
--前置流水号
  TTxnCd     char(10)  not null,
--第三方交易码
  TxnCod     char(6)   not null,
--交易码
  TxnTyp     char(1)   default 'N',
--交易类型( N-正常交易 C-冲正交易 R-重发交易 )
  BusTyp     char(6)   default '',
--业务类型
  CrpCod     char(12)  default '',
--单位代码
  ActDat     char(8)   not null,
--会计日期
  CcyCod     char(3)   default '',
--货币代码
  TxnAmt     char(15)  not null,
--交易金额
  ActNo      char(21)  default '',
--客户帐号
  ActNam     char(60)  default '',
--客户名称
  NodNo      char(6)   default '',
--银行网点号
  TlrId      char(7)   not null,
--银行柜员号
  NodTrc     char(20)  default '',
--网点流水号
  TxnCnl     char(3)   default '',
--交易渠道
  FTxnTm     char(14)  default '',
--前置交易时间
  FRspCd     char(6)   default '',
--前置响应码
  HLogNo     char(9)   default '',
--主机流水号
  TckNo      char(11)  default '',
--会计流水号
  HRspCd     char(6)   default '',
--主机响应码
  HTxnSt     char(1)   default 'U',
--主机交易状态( S-成功 F-失败 R-被冲正 U-预记状态 E-差错 )
  TTxnSt     char(1)   default 'U',
--第三方交易状态(  S-成功 F-失败 R-被冲正 U-预记状态 )
  TxnSts     char(1)   default 'U',
--交易状态( S-成功 F-失败 R-被冲正 U-预记状态 )
  BrNo       char(6)   not null,
--分行号
  VchTyp     char(3)   default '',
--结算凭证种类
  VchNo      char(30)  default '',
--结算凭证编号
  UdwDat     char(8)   default '',
--签发日期
  VchCod     char(8)   default '',
--凭证号码
  Pin        char(16)  default '',
--支付密码
  Smr        char(60)  default '',
--用途
  CclAct     char(21)  default '',
--销帐帐号
  CclNo      char(12)  default '',
--销帐号
  CclSqn     char(4)   default '',
--销帐序号
  PrvDat     clob(3072) default '',
  CONSTRAINT PK_EFEKTXNJNL PRIMARY KEY( LogNo )
);
