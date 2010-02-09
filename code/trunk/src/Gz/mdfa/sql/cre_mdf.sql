drop table MDFFILLST;
drop table MDFYHYSHZ;
drop table MDFYHYSMX;
drop table MDFTXNJNL;
drop table MDFCUSINF;
--
--01接收发送文件清单
--
create table MDFFILLST
(
  FilSts   char(1)    not null,
--处理结果( F-失败  S-成功 )
  LstFNm   char(40)   not null,
--列表文件名
  DatFNm   char(40)   not null,
--数据文件名
  OIFlag   char(1)    not null
--接收发送标志( 0-发出 1-接收 )
);
--
--02应收汇总表
--
create table MDFYHYSHZ
(
  DatFNm   char(40)   not null,
--数据文件名
  YSHZZT   char(1)    not null,
--应收批次状态
  YSPC     char(11)   not null,
--应收批次
  DSJBR    char(10)   default '',
--地税经办人
  PCFSSJ   char(19)   not null,
--发送时间
  MXBS     char(9)    not null,
--明细笔数
  MXZJE    char(15)   not null,
--明细总金额
  CJBS     char(9)    default '',
--冲减笔数
  CJZJE    char(15)   default '',
--冲减金额
  JFYH     char(2)    default '',
--缴费银行( 01-工商银行 02-建设银行 03-农业银行 92-广州市商业银行 52-光大银行 53-交通银行 )
  YHJBR    char(10)   default '',
--银行经办人
  JSSJ     char(19)   default '',
--银行接收时间
  JSMXBS   char(9)    default '',
--银行接收明细笔数
  JSMXZJE  char(15)   default '',
--银行接收明细总金额
  JSCJBS   char(9)    default '',
--银行接收冲减笔数
  JSCJZJE  char(15)   default '',
--银行接收冲减总金额
  DZBZ     char(1)    default '2',
--对账标志( 0-对账成功 1-对账失败 2-未对账 )
  PCBZ     char(30)   default '',
--备注
  DskNo    char(12)   default '',
--磁盘编号
  BokDat   char(8)    default '',
  constraint PK_MDFYHYSHZ PRIMARY KEY( YSPC )
);
CREATE INDEX ni1_MDFYHYSHZ ON MDFYHYSHZ( DskNo );
--
--03应收明细表
--
create table MDFYHYSMX
(
  YSMXZT   char(1)    not null,
--明细状态( U-初始 S-成功 F-失败 A-不处理 B-处理中 C-名字核对通过 R-冲正 )
  YSPC     char(11)   not null,
--地税发送给银行应收批次
  YSLSH    char(18)   not null,
--地税发送给银行应收流水
  SBPC     char(9)    not null,
--社保发送原始应收批次
  SBLSH    char(18)   not null,
--社保发送原始应收流水号
  DYSBLSH  char(18)   not null,
--对应社保流水号( 当核定方式为"正常"、"补收"、"差额调整"且金额>0时，写入自身的流水号；当核定方式为"差额调整"且金额<0时，写入对应被冲减数据的流水号 )
  TBSDM    char(1)    not null,
--投保属地码( A-东山 B-越秀 C-荔湾 D-白云 E-海珠 F-芳村 G-黄埔 H-市属 K-开发 N-南沙 P-番禺 Q-花都 S-从化 T-天河 Z-增城  )
  SBBM     char(20)   not null,
--社保编码
  SSQ      char(6)    not null,
--所属区( 440102-东山区 440103-荔湾区 440104-越秀区 440105-海珠区 440107-芳村区 440111-白云区 440112-黄埔区 440113-开发区 440114-保税区 440116-天河区 440117-南沙区 440181-番禺区 440182-花都区 440183-增城市 440184-从化市 )
  HDFS     char(1)    not null,
--核定方式( 0-正常 1-补收 3-差额调整 4-部分还款且金额为正 5-部分还款冲减且金额为负 注：部份还款记录与部分还款冲减记录成对出现 )
  TZNY     char(6)    not null,
--台帐年月
  SSRQ     char(6)    not null,
--费款所属期
  XZDM     char(2)    not null,
--险种代码( 11-基本养老保险 12-农转居养老保险 13-被征地农民养老保险 21-失业保险 31-基本医疗保险 32-公务员医疗补助 33-住院保险 34-补充医疗保险 35-重大疾病医疗补助 36-居民医疗保险 37-家属医疗 41-工伤保险 51-生育保险 15-居民养老保险 )
  ZMDM     char(2)    not null,
--款项(子目代码)( 1-个人 2-单位 3-社保利息 4-社保滞纳  )
  JE       char(15)   not null,
--金额
  JFZT     char(1)    not null,
--缴费主体( 1-个人 2-单位 )
  JFLX     char(2)    not null,
--缴费类型( 0-定期缴 1-过渡性缴 2-预缴 3-趸缴 4-代扣 5-缴费历史修定 6-异地转入 7-合并缴费历史 8-补收72号文补建个人帐户金额 9-早期国企人员一次性缴费 10-转入缴统筹 )
  JFFS     char(1)    default '',
--缴费方式
  JFYH     char(2)    not null,
--缴费银行( 01-工商银行 02-建设银行 03-农业银行 92-广州市商业银行 52-光大银行 53-交通银行 )
  YHHH     char(10)   default '',
--缴费开户银行行号
  KHYH     char(40)   default '',
--缴费开户银行名称
  YHZH     char(40)   default '',
--缴费银行帐号
  YHHM     char(40)   default '',
--缴费人银行户名
  LSH      char(14)   default '',
--流水号
  TZTZ     char(6)    default '',
--调整台帐年月
  FSSJ     char(19)   default '',
--发送时间
  SJZT     char(4)    default '',
--数据状态
  SJLY     char(1)    default '',
--来据来源
  BZ       char(30)   default '',
--备注
  KDM       char(2)    not null,
--银行根据库代码进行款项入库
-- 77-市局工行库代码 55-市局建行库代码 88-市局农行库代码 91-市局商行库代码 11-市局光大库代码 41-市局交行库代码
-- 81-番禺工行库代码 60-番禺建行库代码 01-番禺农行库代码 27-番禺商行库代码 12-番禺光大库代码 42-番禺交行库代码
-- 79-花都工行库代码 56-花都建行库代码 02-花都农行库代码 28-花都商行库代码 13-花都光大库代码 43-花都交行库代码
-- 78-增城工行库代码 57-增城建行库代码 04-增城农行库代码 29-增城商行库代码 14-增城光大库代码 44-增城交行库代码
-- 80-从化工行库代码 59-从化建行库代码 03-从化农行库代码 30-从化商行库代码 15-从化光大库代码 45-从化交行库代码
  CdFLag   char(1)   not null,
--借贷标志( D-借 C-贷 )
  DskNo    char(12)  default '',
--磁盘编号
  LogNo    char(14)  default '',
--前置流水号
  RegDat   char(8)   not null,
--接收日期
  BokDat   char(8)   default '',
--会计日期
	BokAmt   char(15)  default '',
--实扣金额
	TckNo    char(11)  default '',
--会计流水号
  DZPC     char(11)  default '',
--对账批次
  JYSJ     char(19)  default '',
--银行交易时间
  ZSFS     char(2)   default '',
--征收方式( 02-前台征收 03-后台批扣 )
	RtnFlg   char(1)   default '0',
--返盘状态( 0-未回应 1-已回应 )
	YHDZLSH  char(30)  default '',
--银行对账流水号
	YHFSSJ   char(19)  default '',
--银行对账发送时间
  constraint PK_MDFYHYSMX PRIMARY KEY( YSLSH )
);
--CREATE INDEX ni1_MDFYHYSMX ON MDFYHYSMX( LogNo );
CREATE UNIQUE INDEX ni1_MDFYHYSMX ON MDFYHYSMX( SBLSH,KDM );
CREATE INDEX ni2_MDFYHYSMX ON MDFYHYSMX( YSPC,YSMXZT,CDFLAG );
CREATE INDEX ni3_MDFYHYSMX ON MDFYHYSMX( TBSDM, SBBM, XZDM, TZNY, CDFLAG );
--
--
--扣款流水表
--
--
create table MdfTxnJnl
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
  OIFlag   char(1)   not null,
--往来账标志( 0-往帐 1-来帐 )
  BusTyp   char(6)   default '',
--业务类型
  CrpCod   char(12)  default '',
--单位代码
  ActDat   char(8)   not null,
--会计日期
  CcyCod   char(3)   default 'CNY',
--货币代码
  TxnAmt   char(15)  not null,
--交易金额
  ActTyp   char(1)   default '',
--账户种类( 0-现金 1-一本通 2-普通存折 4-太平洋卡 A-普通对公 B-中央财政 C-广东财政 )
  AVchTp   char(3)   default '',
--账户凭证种类
  VchCod   char(8)   default '',
--存折号码
  ActNo    char(21)  default '',
--记帐帐号
  BActSq   char(5)   default '',
--一本通账户序号
  RvsNo    char(12)  default '',
--销帐号
  VchTyp   char(3)   default '',
--凭证种类
  VchNo    char(8)   default '',
--凭证号码
  NodNo    char(6)   default '',
--银行网点号
  BrNo     char(6)   not null,
--交易分行
  TlrId    char(7)   not null,
--银行柜员号
  FTxnTm   char(14)  default '',
--前置交易时间
  HLogNo   char(9)   default '',
--主机流水号
  TckNo    char(11)  default '',
--会计流水号
  TTxnSt   char(1)   default 'U',
--第三方交易状态( S-成功 F-失败 R-被抹帐 C-被冲正 U-预记状态 T-超时 V-主机成功 )
  TxnSts   char(1)   default 'U',
--交易状态( S-成功 F-失败 R-被抹帐 C-被冲正 U-预记状态 T-超时  )
  HTxnSt   char(1)   default 'U',
--主机交易状态( S-成功 F-失败 R-被抹帐 C-被冲正 U-预记状态 E-差错 T-超时)
  HRspCd   char(6)   default '',
--主机响应码
  DskNo    char(12)  default '',
--磁盘编号
  TxnObj   char(8)   default '',
--大小通道目标服务
  TxnCnl   char(3)   default 'MDF',
--交易渠道
  IsTxn    char(1)   default '',
--是否上送主机
  UpdFlg   char(1)   default 'Y',
--更新标志
  UpdFld   char(20)  default '',
--更新字段名
------以下是业务数据------
------以下是业务数据------
------以下是业务数据------
--YSLSH    char(18)  not null,
--地税发送给银行应收流水
  CdFLag   char(1)   not null,
--借贷标志( D-借 C-贷 )
  TBSDM    char(1)   not null,
--投保属地码( A-东山 B-越秀 C-荔湾 D-白云 E-海珠 F-芳村 G-黄埔 H-市属 K-开发 N-南沙 P-番禺 Q-花都 S-从化 T-天河 Z-增城  )
  SBBM     char(20)  not null,
--社保编码
  TZNY     char(6)   not null,
--台帐年月
  XZDM     char(2)   default '',
--险种代码( 11-基本养老保险 12-农转居养老保险 13-被征地农民养老保险 21-失业保险 31-基本医疗保险 32-公务员医疗补助 33-住院保险 34-补充医疗保险 35-重大疾病医疗补助 36-居民医疗保险 37-家属医疗 41-工伤保险 51-生育保险 15-居民养老保险 )
  CONSTRAINT PK_MDFTXNJNL PRIMARY KEY( LogNo )
);
--
--
--客户资料表
--
--
create table MdfCusInf
(
	RegDat   char(8)   not null,
--入库日期
  TBSDM    char(1)   not null,
--投保属地码( A-东山 B-越秀 C-荔湾 D-白云 E-海珠 F-芳村 G-黄埔 H-市属 K-开发 N-南沙 P-番禺 Q-花都 S-从化 T-天河 Z-增城  )
  SBBM     char(20)  not null,
--社保编码
  JFZT     char(1)   not null,
--缴费主体( 1-个人 2-单位 )
  SSQ      char(6)   not null,
--所属区( 440102-东山区 440103-荔湾区 440104-越秀区 440105-海珠区 440107-芳村区 440111-白云区 440112-黄埔区 440113-开发区 440114-保税区 440116-天河区 440117-南沙区 440181-番禺区 440182-花都区 440183-增城市 440184-从化市 )
  DWMC     char(60)  default '',
--缴费人名称(单位和个人)
  GRSF     char(3)   default '',
--个人身份（缴费人类别 70-学龄前儿童 71-中小学生 72-大中专学生 73-其他未成年人 74-非从业人员 75-老年人 76-托幼学生）
  CBDWBM   char(8)   default '',
--所在参保单位编码
  CBDWMC   char(100) default '',
--所在参保单位名称
  ZJLX     char(3)   default '',
--证件类型( 1-身份证 2-护照 3-军官证 4-学籍证 5-其他 )
  ZJHM     char(25)  default '',
--证件号码
  XJHM     char(40)  default '',
--学籍号码
  JFYH     char(2)   default '',
--签约缴费银行( 01-工商银行 02-建设银行 03-农业银行 92-广州市商业银行 52-光大银行 53-交通银行 )
  YHHH     char(10)  default '',
--缴费开户银行行号
  KHYH     char(40)  default '',
--缴费开户银行名称
  YHZH     char(40)  default '',
--缴费银行帐号
  YHHM     char(40)  default '',
--缴费人银行户名
  YB       char(6)   default '',
--邮编
  DWDZ     char(100) default '',
--联系地址
  LXR      char(10)  default '',
--联系人
  LXDH     char(15)  default '',
--联系电话
--LRSJ     char(19)  default '',
--录入时间
--XGSJ     char(19)  default ''
--修改时间
  CONSTRAINT PK_MDFCUSINF PRIMARY KEY( TBSDM,SBBM )
);
CREATE INDEX ni1_MDFCUSINF ON MDFCUSINF( ZJHM );
