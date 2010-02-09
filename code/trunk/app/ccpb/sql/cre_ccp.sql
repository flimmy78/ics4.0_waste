--1   Table: ccpshlcod   ( 大中专收费代码表 ) - ( 文件头 )
--原对公系统3.0里的表名sf_educodeofxz_tb
drop table ccpshlcod;
create table ccpshlcod
(
	ShlCod      char(10)    	not null,
--学校班级编码
  	ShlNam      char(60)    not null,
--校名
  	ShlGr	 	char(2)		not null,
--年级
	SubNam		char(60)	not null,
--专业名称
    	constraint PK_ZH_EDUCOD primary key( ShlCod )
);

--2   Table: ccptxnjnl   ( 大中专交易流水表 ) - ( 文件体 )
drop table ccptxnjnl;
create table ccptxnjnl
(
  BrNo          char(6)       not null,
--分行号
	LogNo		char(14)	not null,
--前置流水号
	TTxnCd      	char(10)    	default ' ',
--第三方交易码
	TxnCod      	char(6)     	default ' ',
--交易码
	TxnTyp      	char(1)     	default ' ',
--交易类型
	BusTyp      	char(6)     	default ' ',
--业务类型
	CrpCod      	char(10)    	default ' ',
--单位代码
    HTxnSb      	char(3)     	default ' ',
--交易子码
	ActDat      	char(8)     	default ' ',
--会计日期
	CcyCod		char(3)		default ' ',
--货币代码
	TxnAmt      	char(15)    	default ' ',
--交易金额
	Fee         	char(15)    	default ' ',
--交易手续费
	ActNo       	char(21)    	default ' ',
--客户账号
	CrdNo       	char(30)    	default ' ',
--客户卡号
	OrgNo       	char(6)     	default ' ',
--机构号
	NodNo       	char(6)     	default ' ',
--银行网点号
	TlrId       	char(7)     	default ' ',
--银行柜员号
	ChkTlr       	char(7)     	default ' ',
--复核柜员号
	CntrId      	char(10)    	default ' ',
--银行柜台号
	NodTrc      	char(20)    	default ' ',
--网点流水号
	TxnCnl      	char(3)     	default ' ',
--交易渠道
	ItgTyp      	char(1)     	default ' ',
--完整性类型
	FTxnTm      	char(14)    	default ' ',
--前置交易时间
	FRspCd      	char(6)     	default ' ',
--前置响应码
	HLogNo      	char(9)     	default ' ',
--主机流水号
	HRspCd      	char(6)     	default '999999',
--主机响应码
	HTxnSt      	char(1)     	default 'U',
--主机交易状态
   	TckNo           char(11)        default ' ',
--会计流水号
	HPrChk      	char(1)     	default '0',
--与主机日间对账标志
	HLsChk      	char(1)     	default '0',
--与主机日终对账标志
	TCusId      	char(30)    	default ' ',
--代理服务客户标识
	TCusNm      	char(80)    	default ' ',
--代理服务客户姓名
	TActDt      	char(8)     	default ' ',
--第三方账务日期
	TLogNo      	char(20)    	default ' ',
--第三方流水号
	TRspCd      	char(10)    	default ' ',
--第三方响应码
	TTxnSt      	char(1)     	default 'U',
--第三方交易状态
	ThdChk      	char(1) 	default '0',
--与第三方对账标志 0未对账 1对账成功 2金额不符 3我行有人行无  4 人行有我行无
	TxnSts		char(1)		default 'U',
--交易状态 S交易成功 F主机返回明确失败 T超时 U未知状态 X发送失败（未发到主机）
	TxnAtr		char(32)	default ' ',
--交易属性
	MstChk		char(1)		default '0',
--要求对账标志
	LChkTm		char(10)	default ' ',
--1970年距今的秒数
	HTxnCd		char(6)	    default ' ',
--主机交易码

--以下是本业务用到的字段
	VchSeq     	char(4)    default '0001',
--传票序号
 	CrgWay  	char(1)		not null ,
--收费方式(0-现金,1-转账,2-主机查询转账,3-划账)
    RcpNo       char(15)    default ' ',
--收据编号
 	CusNam    	char(60)	default ' ',
--缴款单位(人)
  	ShlNam      char(60)   	default ' ',
--校名
  	ShlGr	 	char(2)		default ' ',
--年级
	SubNam		char(60)	default ' ',
--专业名称
    constraint PK_ZH_TXNJNL primary key( LogNo )
);
create index ni1_ccptxnjnl on ccptxnjnl(ActDat);

--3   Table: ccpjnldtl   ( 行政收费收费流水明细表 ) - ( 文件头 )
drop table ccpjnldtl;
create table ccpjnldtl
(
	RecSts   	char(2)    	default '0',
--记录状态    0-未记账  1-记账成功，未发送  T-超时  C-抹账  3-已发送  4-第二天发送
	LogNo		char(14)	not null,
--前置流水号
   	TckNo       char(11)    default '0',
--会计流水号
	VchSeq     	char(4)     default '0001',
--传票序号
	ActDat     	char(8)    	default ' ',
--会计日期
	NodNo      	char(6)    	default ' ',
--银行网点号
	TlrId      	char(7)    	default ' ',
--银行柜员号
	CcyCod		char(3)		default 'CNY',
--货币代码
    RcpNo       char(15)    default ' ',
--收据编号
    RcpTyp      char(1)     default '5',
--收据类型
    CrgWay      char(1)     not null,
--收费方式(0-现金,1-转账)
	ShlCod     	char(7)    	not null,
--学校班级编码
  	ShlNam      char(60)    default ' ',
--校名
  	ShlGr	 	char(2)		default ' ',
--年级
	SubNam		char(60)	default ' ',
--专业名称
 	CusNam    	char(60)	default ' ',
--缴款单位(人)
	ActNo       char(21)    default ' ',
--客户账号
	TxnAt1     	char(12) 	default '0',
--学杂费
	TxnAt2     	char(12) 	default '0',
--住宿费
	TxnAt3      char(12) 	default '0',
--实习试验费
	TxnAt4      char(12) 	default '0',
--补考费
	TxnAt5      char(12) 	default '0',
--重修费
	TxnAt6      char(12) 	default '0',
--其他
	TxnAmt      char(15)    default ' ',
--合计

    constraint PK_ZH_TXNJNL primary key( LogNo)
);

--4   Table: ccptmptbl   ( 临时表 ) - ( 文件头 )
drop table ccptmptbl;
create table ccptmptbl
(
	VchSeq    	char(4)    	default ' ',
--传票序号
	VchSts    	char(1)    	default ' ',
--传票状态
	VchSig    	char(1)    	default ' ',
--借货方标志 D借；C贷
	ActNo     	char(21)   	default ' ',
--账号
	TxnAmt    	char(15)   	default ' ',
--金额
    CcyCod      char(3)     default 'CNY'
--货币代码
);
