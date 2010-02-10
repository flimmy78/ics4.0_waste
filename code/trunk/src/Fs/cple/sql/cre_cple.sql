drop table cplactreg446;
create table cplactreg446              
--对私转对公客户帐户签约表
(
	CAgtNO    char(10) NOT NULL,					 
	--协议编号（来源于savcrpagr） 
	PayAct		char(21) Not NULL,		       
	--签约扣款对私帐号
	RcvAct		char(21) Not NULL,		       
	--签约入账对公帐号
	InMode 		char(1)	 Not NULL,		       
	--入账方式(0-根据卡流水逐笔入账 1-留存最低金额后一笔入账)
	KepAmt		char(15) Not NULL, 	         
	--留存金额 
	SgnOrg 		char(6)  default ' ',        
	--签约网点
  SgnTlr 		char(7)  default ' ', 	     
  --签约柜员
  SgnDat		char(8)  default ' '        
  --签约日期
);
CREATE unique INDEX N1_cplactreg446 ON cplactreg446(CAgtNo);

drop table cpltxnjnl446;
create table cpltxnjnl446           
--记账交易流水，送大小通道(26201-CD户)
(
	LogNo				CHAR(14)		NOT NULL,	              
	--前置流水号
	DskNo				CHAR(12)		NOT NUll,	              
	--磁盘编号
	BusTyp			CHAR(5)			NOT NUll,	              
	--业务类型
	CrpCod			CHAR(12)		NOT NUll,               
	--单位代码
	ActDat			CHAR(8)			NOT NULL,              
	--会计日期
	TTxnCd			CHAR(6)			NOT NULL,               
	--前置交易码
	HTxnCd			CHAR(6)			DEFAULT '',             
	--主机交易码
	HTxnSb			CHAR(3)			DEFAULT '',	            
	--主机交易子码
	HLogNo			CHAR(9)			DEFAULT '',	            
	--主机流水号
	HRspCd			CHAR(6)			DEFAULT '',	            
	--主机响应码
	HTxnSt			CHAR(1)			DEFAULT 'U' NOT NULL,	  
	--主机交易状态
	IsTxn				CHAR(1)			DEFAULT 'N' NOT NULL,	  
	--是否发送主机标志，用于批量大小通道发送  Y发送N不发送
	TxnCnl			CHAR(3)			NOT NULL,				        
	--交易渠道
	CnlSub			CHAR(10)		DEFAULT '',             
	--子渠道
	TxnObj			CHAR(8)			NOT NULL,		            
	--大小通道目标服务
	TlrId				CHAR(7)			NOT NULL,			          
	--银行柜员号
	NodNo				CHAR(6)			DEFAULT '',		          
	--银行网点号
	TckNo				CHAR(12)		DEFAULT '',		          
	--主机传票号
	UpdFlg			CHAR(1)			DEFAULT '',             
	--更新标志
	UpdFld			CHAR(200)		DEFAULT '',	            
	--更新字段集合
  TrmNo			  CHAR(7)			DEFAULT '',             
  --终端号

  DAcSqn      CHAR(5)     NOT NULL,              
  --借记帐户顺序号(26201)  
  CclNo       CHAR(12)    DEFAULT '',             
  --销账号 
  CcyCod      CHAR(3)     NOT NULL,               
  --币种            
  TxnAmt      CHAR(15)    NOT NULL,               
  --金额            
  AccMod      CHAR(1)     NOT NULL,               
  --入帐方式 0-转CD户 1－转内部户
  TActNo      CHAR(21)    NOT NULL,               
  --入帐帐号      
  TActNm      CHAR(60)    NOT NULL,               
  --入帐户名      
  NamChk      CHAR(1)     NOT NULL,               
  --户名检查标志 0-检查户名 1－不检查
  CAcSqn      CHAR(5)     NOT NULL,  
  --入帐账号序号       
  Smr         CHAR(60)    DEFAULT '',             
  --摘要   
  --以下字段为对私卡号的会计流水(仅借方流水）
  XActNo		  char(21)    default '',										
  --对私帐户会计交易流水交易帐号
  XTckNo      char(12)    default '',										
  --对私帐户会计交易流水号 
	XVchSeq     char(4) 		default '',               		
	--对私帐户会计交易传票序号
	XLogNo      CHAR(14)		default '',	              		
	--对私帐户前置流水号
  XOppAct     char(32)  	default ' ',						
  --对私帐户会计交易流水对方账号
	XOppNam     char(60)  	default ' ',						
	--对私帐户会计交易流水对方户名    
	XNodNo      char(6)   	default '',										
	--对私帐户会计交易流水交易机构
	XTxTim      char(6)	  	default '',	  								
	--对私帐户会计交易流水交易时间
	xSmr				CHAR(60)		DEFAULT ''             
	--摘要   
); 
create index ni1_cpltxnjnl446  on cpltxnjnl446(DskNo); 
  
  
  
  
  
  
  
  