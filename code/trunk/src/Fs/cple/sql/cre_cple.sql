drop table cplactreg446;
create table cplactreg446              
--��˽ת�Թ��ͻ��ʻ�ǩԼ��
(
	CAgtNO    char(10) NOT NULL,					 
	--Э���ţ���Դ��savcrpagr�� 
	PayAct		char(21) Not NULL,		       
	--ǩԼ�ۿ��˽�ʺ�
	RcvAct		char(21) Not NULL,		       
	--ǩԼ���˶Թ��ʺ�
	InMode 		char(1)	 Not NULL,		       
	--���˷�ʽ(0-���ݿ���ˮ������� 1-������ͽ���һ������)
	KepAmt		char(15) Not NULL, 	         
	--������ 
	SgnOrg 		char(6)  default ' ',        
	--ǩԼ����
  SgnTlr 		char(7)  default ' ', 	     
  --ǩԼ��Ա
  SgnDat		char(8)  default ' '        
  --ǩԼ����
);
CREATE unique INDEX N1_cplactreg446 ON cplactreg446(CAgtNo);

drop table cpltxnjnl446;
create table cpltxnjnl446           
--���˽�����ˮ���ʹ�Сͨ��(26201-CD��)
(
	LogNo				CHAR(14)		NOT NULL,	              
	--ǰ����ˮ��
	DskNo				CHAR(12)		NOT NUll,	              
	--���̱��
	BusTyp			CHAR(5)			NOT NUll,	              
	--ҵ������
	CrpCod			CHAR(12)		NOT NUll,               
	--��λ����
	ActDat			CHAR(8)			NOT NULL,              
	--�������
	TTxnCd			CHAR(6)			NOT NULL,               
	--ǰ�ý�����
	HTxnCd			CHAR(6)			DEFAULT '',             
	--����������
	HTxnSb			CHAR(3)			DEFAULT '',	            
	--������������
	HLogNo			CHAR(9)			DEFAULT '',	            
	--������ˮ��
	HRspCd			CHAR(6)			DEFAULT '',	            
	--������Ӧ��
	HTxnSt			CHAR(1)			DEFAULT 'U' NOT NULL,	  
	--��������״̬
	IsTxn				CHAR(1)			DEFAULT 'N' NOT NULL,	  
	--�Ƿ���������־������������Сͨ������  Y����N������
	TxnCnl			CHAR(3)			NOT NULL,				        
	--��������
	CnlSub			CHAR(10)		DEFAULT '',             
	--������
	TxnObj			CHAR(8)			NOT NULL,		            
	--��Сͨ��Ŀ�����
	TlrId				CHAR(7)			NOT NULL,			          
	--���й�Ա��
	NodNo				CHAR(6)			DEFAULT '',		          
	--���������
	TckNo				CHAR(12)		DEFAULT '',		          
	--������Ʊ��
	UpdFlg			CHAR(1)			DEFAULT '',             
	--���±�־
	UpdFld			CHAR(200)		DEFAULT '',	            
	--�����ֶμ���
  TrmNo			  CHAR(7)			DEFAULT '',             
  --�ն˺�

  DAcSqn      CHAR(5)     NOT NULL,              
  --����ʻ�˳���(26201)  
  CclNo       CHAR(12)    DEFAULT '',             
  --���˺� 
  CcyCod      CHAR(3)     NOT NULL,               
  --����            
  TxnAmt      CHAR(15)    NOT NULL,               
  --���            
  AccMod      CHAR(1)     NOT NULL,               
  --���ʷ�ʽ 0-תCD�� 1��ת�ڲ���
  TActNo      CHAR(21)    NOT NULL,               
  --�����ʺ�      
  TActNm      CHAR(60)    NOT NULL,               
  --���ʻ���      
  NamChk      CHAR(1)     NOT NULL,               
  --��������־ 0-��黧�� 1�������
  CAcSqn      CHAR(5)     NOT NULL,  
  --�����˺����       
  Smr         CHAR(60)    DEFAULT '',             
  --ժҪ   
  --�����ֶ�Ϊ��˽���ŵĻ����ˮ(���跽��ˮ��
  XActNo		  char(21)    default '',										
  --��˽�ʻ���ƽ�����ˮ�����ʺ�
  XTckNo      char(12)    default '',										
  --��˽�ʻ���ƽ�����ˮ�� 
	XVchSeq     char(4) 		default '',               		
	--��˽�ʻ���ƽ��״�Ʊ���
	XLogNo      CHAR(14)		default '',	              		
	--��˽�ʻ�ǰ����ˮ��
  XOppAct     char(32)  	default ' ',						
  --��˽�ʻ���ƽ�����ˮ�Է��˺�
	XOppNam     char(60)  	default ' ',						
	--��˽�ʻ���ƽ�����ˮ�Է�����    
	XNodNo      char(6)   	default '',										
	--��˽�ʻ���ƽ�����ˮ���׻���
	XTxTim      char(6)	  	default '',	  								
	--��˽�ʻ���ƽ�����ˮ����ʱ��
	xSmr				CHAR(60)		DEFAULT ''             
	--ժҪ   
); 
create index ni1_cpltxnjnl446  on cpltxnjnl446(DskNo); 
  
  
  
  
  
  
  
  