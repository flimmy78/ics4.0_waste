--���ƶ���
--ֱ��������  char(12) DBrCd
--��ѯ֪ͨ�����ʶ char(3) QryTyp
--������ char(4) AreaNo
--�����ʶ char(1) BillFg
--������� CreAmt
--�������� CreCnt
--�跽��� DebAmt
--�跽���� DebCnt
--ԭ����Ԫ OrgId
--�������� TraKnd  char(4)
--ָ���������� CTraKnd
--�ɵ�½��ʶ OSgnId
--�µ�½��ʶ NSgnId
--��Ѻ  SecKey
--��ҵ�������� CrpOrgCd
--�����Ƿ�ʱ��Ӧ  ImmFlg
drop table CbsBasInf;
drop table CbsBnkInf;
drop table CbsRunCtl;
drop table CbsFeeRat;
drop table CbsTxnJnl;
drop table CbsQryJnl;
drop table CbsCusAgr;
drop table CbsPubInf;
drop table CbsCenTot;
drop table CbsBchSum;
drop table CbsBchJnl;
drop table CbsBankCd;
drop table CbsBTxnCd;
drop table CbsCodeCd;
drop table CbsSyIdCd;
drop table CbsAreaCd;
drop table CbsBusAct;
drop table CbsClrRpt;
drop table CbsExchNo;
drop table CbsNetDtl;
drop table CbsNetFee;
drop table CbsFeeRpt;
--01Ӧ�û�����Ϣ��
create table CbsBasInf
(
  BusLog  char(12)  not null,
--��Ϣ���ʮ��λ��
	ReqSeq  char(8)   not null
--��ѯ���ı��
);

--02������Ϣ��
create table CbsBnkInf
(
	BrNo      char(6)   not null,
--���׷���
	CtlNod    char(6)   not null,
--ͨ����Ʋ��ź�
  BusNod    char(6)   not null,
--����Ӫҵ��
	CnlSub    char(6)   not null,
--��������
	AccSq01   char(5)   default '',
--ʵʱ����5210�ʻ����(��/��)
	AccSq02   char(5)   default '',
--��������2622(������)�ʻ����(��)
	AccSq03   char(5)   default '',
--��������2622(�ʵ��)�ʻ����(��)
	AccSq04   char(5)   default '',
--����2621�ʻ����(�����˻�����ʹ���)
	AccSq05   char(5)   default '',
--���ڽ�����ʳɹ���Ӧ26201����
	AccSq06   char(5)   default '',
--����֧��5210�ʻ����(��/��)
	AccSq07   char(5)   default '',
--�������ڴ���5210�ʻ����(��/��)
	AccSq08   char(5)   default '',
--���ڽ��5210�ʻ����(��/��)
	AccSq09   char(5)   default '',
--���ݴ���������
	AccSq10   char(5)   default '',
--�������ڴ���2621(��)
	AccSq11   char(5)   default '',
--������������5210�ʻ����
	AccSq12   char(5)   default '',
--��������26201
  AccIn01   char(21)  default '',
--������ʶ�˽�Զ�����5210�ڲ��ʺ�
  AccIn02   char(21)  default '',
--����֧�����ʶ�˽�Զ�����5210�ڲ��ʺ�
  AccIn03   char(21)  default '',
--δ��
	FixAmt    char(15)  default '000000000000000',
--�̶�ͷ��
	FloAmt    char(15)  default '000000000000000',
--����ͷ��
	CurAmt    char(15)  default '000000000000000',
--��ǰͷ��
	CityCd    char(4)   not null,
--���д���
	constraint PK_CBSBASINF PRIMARY KEY(BrNo)
);

--03���п��Ʊ�
create table CbsRunCtl
(
	TxnKnd   char(6)   not null,
--��������ϸ��
	TraTm    char(10)  not null,
--���׷������ں�ʱ��
	SysSts   char(2)   not null,
--ϵͳ����״̬ ��01������ 02���ر� 03�������л�,�����ã�
  LogFlg   char(1)   not null,
--��½״̬ 0-δ��½ 1-�ѵ�½
  CtlFlg   char(1)   not null,
--���ڿ��Ʊ�ʶ 0-������  1-��ֹҵ��
	WorkDt   char(8)   not null,
--��ǰ���й�������
	KndNam   char(30)  default '',
--������������
	Smr     varchar(300)  default '',
--ժҪ
	constraint PK_CBSRUNCTL PRIMARY KEY(TxnKnd)
);

--04ҵ����ʱ�
create table CbsFeeRat
(
	Sts      char(1)   not null,
--״̬( 0-��Ч 1-��Ч )
	TxnKnd   char(6)   not null,
--ҵ������( �μ�PDF�ļ�P85 )
	TxnNam   char(60)  not null,
--ҵ����������
	UsgCod   char(3)   not null,
--�ʽ���;����
	UsgNam   char(60)  not null,
--�ʽ���;����
	LclFlg   char(1)   not null,
--ͬ����ر�־( 0-ͬ�� 1-��� )
	BrNo     char(6)   not null,
--���к�
	CcyCod   char(3)   not null,
--����
	MinAmt   char(15)  not null,
--��ͽ��
	MaxAmt   char(15)  not null,
--��߽��
	FeeMod   char(1)   not null,
--�����շ�ģʽ
	FeeRat   char(5)   not null,
--����
	FeeAmt   char(15)  not null,
--���
	PstMod   char(1)   not null,
--�ʵ��շ�ģʽ
	PstRat   char(5)   not null,
--����
	PstAmt   char(15)  not null,
--���
	ValDt    char(8)   not null,
--��Ч����
	constraint PK_CBSFEERAT PRIMARY KEY( TxnKnd, UsgCod, LclFlg, BrNo, CcyCod, MinAmt, MaxAmt )
);

create table CbsTxnJnl
(
	TraKnd  char(4)   not null,
--��������������
	SndBNo  char(12)  not null,
--�������к�( ֱ�Ӳ������к� )
	SndDat  char(8)   not null,
--ί������
	VchId   char(8)   not null,
--������ƾ֤�ύ��( substr( LogNo, 7, 8 ) )
	OIFlag  char(1)   not null,
--�����˱�־ 0-���� 1-����
	BilSts  char(1)   not null,
--����״̬
--����״̬��0Ԥ��¼��1���ϣ�A�Ѽ���; B�Ѹ���; C��ȷ��; D�ȴ���ִ; E�����д���; F�Ŷ�; G�����㣨���ͳɹ���; H����Ĩ��; L�ݹ�;   h����Ĩ��ʧ��; b���оܾ�; 
--����״̬��P���˴�����δ���ˣ�; R��Ĩ��; M�˻��ѷ�; S��ע�Ѹ���; T����ע������; U����ע����; W����Թ��ʲ��ȴ���˽����; Xȷ������;Z�Թ��Զ�����;Q��˽����;V��˽�Զ����� Fʧ������;
	TTxnSt  char(1)   default '0',
--������״̬
	MsgId   char(4)   not null,
--�������ͱ�־
	TxnKnd  char(6)   not null,
--��������������ϸ������
	TxnAmt  char(15)  not null,
--�㻮���
	TraTm   char(10)  not null,
--���׷������ں�ʱ��
	ClrDat  char(8)   default '00000000',  
--��������
	ClrSce  char(4)   default '',  
--���㳡��
	CcyCod  char(3)   not null,
--�������ױ���
	SvrCod  char(3)		default '',
--��������뷽ʽ��( 021-���������Ҵ�PIN		022-�������벻��PIN		011-�ֹ������Ҵ�PIN		012-�ֹ����벻��PIN )
	CenTm   char(14)  default '',
--���Ľ�������ʱ�������
	CenLog   char(16)  default '',
--���Ľ��������
	ThdTm   char(14)  default '',
--ҵ�����������ں�ʱ��( ����ʱ������д )
	ThdLog  char(16)  default '',
--ҵ������ˮ��( ����ʱ������д )
	TRspCd  char(6)   default '',
--������������( ��PDF�ļ�P84 )
	CshFlg  char(1)   default '',
--�ֽ�/ת�ʱ�־( 0-�ֽ�		1-ת�� )
	SmrCod  char(4)   default '',
--ժҪ����( ��PDF�ļ�P91 )
	UsgCod   char(3)  default '',
--�ʽ���;( ��PDF�ļ�P89 )
	RSdFlg  char(1)   not null,
--�ط���ʶ( 0-��������	1-�ظ����� )
	AccFlg  char(1)   not null,
--�Թ�/��˽��ʶ( 0-�Թ�	1-��˽ )
	TBusTp  char(5)   default '',
--ҵ������( ��PDF�ļ�P90 )
	CardFg  char(2)   default '',
--��/�۱�־( 01-����	02-�� )
	AccKnd  char(1)   default '',
--�ʻ����� ( 0-�㻧		1-���� )
	FeeTyp  char(3)   default '',
--�����ѷ�ʽ
	PayFuc  char(3)   default '',
--֧������
	AuthCd  char(6)   default '',
--��Ȩ��
	PayLvl  char(1)   default '',
--֧�����ȼ�
	SOpnBk	char(12)  default '',
--�����˿������к�( ��Ӳ�����֧���к� )
	SndNod  char(9)   default '',
--�����������
	SndAct  char(35)  default '',	
--�������ʺ�
	SndNm   char(60)  default '',
--����������
	SndAdr  char(60)  default '',
--�����˵�ַ
	RcvBNo  char(12)  default '',
--�������к�( ֱ�Ӳ������к� )
	ROpnBk	char(12)  default '',
--�����˿������к�( ��Ӳ������к� )
	RcvNod  char(9)   default '',
--�����������
	RcvAct  char(35)  default '',	
--�������ʺ�
	RcvNm   char(60)  default '',
--����������
	RcvAdr  char(60)  default '',
--�����˵�ַ
	OrgId   char(32)  default '',
--��Ʊԭ����Ԫ��ʶ
	Smr     varchar(300) default '',
--����ժҪ
	SvrKnd  char(1)   default '',
--������Ϣ����
	TBilNo  char(20)  default '',
--˰Ʊ����
	TaxNo   char(20)  default '',
--��˰�˱���
	Taxer   char(60)  default '',
--��˰������
	TaxLvl  char(2)   default '',
--Ԥ�㼶��
	TSubCd  char(12)  default '',
--Ԥ���Ŀ
	TOrgCd  char(11)  default '',
--���ջ��ش���
	TActDt  char(8)   default '',
--˰Ʊ�޽�����
	SecKey  char(40)  default '',
--��Ѻ
	MatFlg  char(1)   default '0',
--ƥ���ʶ( 0-��ƥ��,��˽����δ����	1-ƥ��,��˽�����ѷ��� )
--����Ҫ��
--����Ҫ��
	LogNo   char(14)  not null,
--ǰ����ˮ��
	BrNo    char(6)   not null,
--���׷���
	NodNo   char(6)   default '',
--��������
	ActFlg  char(1)   default '',
--�˻�����
	AVchTp  char(3)   default '',
--�˻�ƾ֤����
	VchCod  char(8)   default '',
--���ۺ���
	BokAct  char(21)  default '',
--�����ʺ�
	BActSq  char(5)   default '',
--һ��ͨ�˻����
	RvsNo   char(12)  default '',
--���ʺ�
	VchTyp  char(3)   default '',
--ƾ֤����
	VchNo   char(8)   default '',
--ƾ֤����
	FeeFlg  char(1)   default '',
--���ձ�־
	FeeAmt  char(15)  default '000000000000000',
--������
	PstAmt  char(15)  default '000000000000000',
--�ʵ��
	EtsFlg  char(1)   default '',
--����־
	PstTyp  char(1)   default '',
--��ע����( 1-ȷ������ 2-��ע 3-ת����)
	PstNod  char(6)   default '',
--��ע���ʲ���
--��ˮҪ��
--��ˮҪ��
	BusTyp  char(5)   default '',
--ҵ������
	ActDat  char(8)   default '',
--�������
	TTxnCd  char(6)   default '',
--ǰ�ý�����
	HTxnSt  char(1)   default '',
--��������״̬
	HTxnCd  char(6)   default '',
--����������
	HLogNo  char(9)   default '',
--������ˮ��
	TckNo   char(11)  default '',
--�����ˮ��
	RspCod  char(6)   default '',
--ǰ�÷�����
	HRspCd  char(6)   default '',
--����������
	PrtCnt  char(2)   default '00',
--��ӡ����
	RtnMsg  char(72)  default '',
--��Ӧ��Ϣ
	TlrId   char(7)   default '',
--���ʹ�Ա
	ChkId   char(7)   default '',
--���˹�Ա
	Sup1Id  char(7)   default '',
--��Ȩ��Ա
	RvsSmr	char(60)  default '',
--����ժҪ
	constraint PK_CBSTXNJNL PRIMARY KEY( TraKnd, SndBNo, SndDat, VchId, OIFlag )
);
CREATE UNIQUE INDEX ni1_CBSTXNJNL ON CBSTXNJNL( LogNo );
CREATE INDEX ni2_CBSTXNJNL ON CBSTXNJNL( ActDat, TlrId, TckNo );
CREATE INDEX ni3_CBSTXNJNL ON CBSTXNJNL( BrNo, NodNo );
--06��ѯ�鸴��ˮ��
create table CbsQryJnl
(
	TxnKnd  char(6)   not null,
--��������ϸ����
	SndDat  char(8)   not null,
--ί������
	QryTyp  char(3)   not null,
--��ѯ�����ʶ
--000�����ʻ������ѯ 001�ͻ���Ȩ����ѯ 002������ѯ/�˶Բ�ѯ
--003��ͬ��ȷ�ϲ�ѯ/�鸴 004��ͬ��֧������/����֪ͨ 005��ͬ���˻�����/����֪ͨ
--006��ͬ�ǵ������� 999��ͨ�ò�ѯ
  OIFlag  char(1)   not null,
--������ѯ��־ 0-�����ѯ 1-���ղ�ѯ  2-���յ����Ϸ���ѯ 3-���ղ�ƥ��鸴
	MatFlg  char(1)   default '0',
--�鸴ƥ���ʶ 0-δ�鸴	1-�Ѳ鸴 A¼���ȷ��; C��ȷ��; D-��ɾ��; E-���ͳ��� 
	BrNo    char(6)   not null,
--���׷���
	SndBNo  char(12)  not null,
--�������к�( ֱ�Ӳ������к� )
	RcvBNo  char(12)  not null,
--�������к�( ֱ�Ӳ������к� )
	MsgSeq  char(16)  not null,
--��Ϣ���
	SvrCod  char(3)		default '',
--��������뷽ʽ��( 021-���������Ҵ�PIN		022-�������벻��PIN		011-�ֹ������Ҵ�PIN		012-�ֹ����벻��PIN )
	CenTm   char(14)  default '',
--���Ľ�������ʱ�������
	CenLog   char(16) default '',
--���Ľ��������
	ReqSeq  char(8)   default '00000000',
--��ѯ���ı��
	RspSeq  char(8)   default '00000000',
--�鸴���ı��
	TRspCd  char(6)   default '',
--������������( ��PDF�ļ�P84 )
	SOpnBk	char(12)  default '',
--�����˿������к�( ��Ӳ������к� )
	ROpnBk	char(12)  default '',
--�����˿������к�( ��Ӳ������к� )
	DeaNod  char(6)   default '',
--��������
	DeaTlr  char(7)   default '',
--�����Ա
	DeaDat  char(8)   default '',
--��������
	PriCls  char(1)   default '',
--���ȼ��� 0��һ�� 1������
	PTraKnd char(4)   default '',
--ԭ��������
	PSndBNo char(12)  default '',
--ԭ���׷������к�
	PRcvBNo char(12)  default '',
--ԭ���׽������к�
	PSndDat char(8)   default '',
--ԭ����ί������
	PClrDat char(8)   default '',
--ԭ������������
	PTxnAmt char(15)  default '',
--ԭ���׽��
	PCcyCod char(3)   default '',
--ԭ���ױ���
	PVchId  char(8)   default '',
--ԭƾ֤�ύ��
	PPayAct char(35)  default '',	
--ԭ�������ʺ�
	PPayNam char(60)  default '',
--ԭ����������
	PGatAct char(35)  default '',	
--ԭ�տ����ʺ�
	PGatNam char(60)  default '',
--ԭ�տ�������
	ReqSmr  varchar(300) default '',
--��ѯ��ע
	RspSmr  varchar(300) default '',
--�ظ���ע
	constraint PK_CBSQRYJNL PRIMARY KEY(TxnKnd,SndDat,SndBNo,MsgSeq,OIFlag)
);
CREATE INDEX ni1_CBSQRYJNL ON CBSQRYJNL(BrNo,QryTyp);


--08Э����Ϣ��
create table CbsCusAgr
(
	AgrAct   char(21)   not null,
--Э���ʺ�
	EntCod   char(6)    not null,
--������ҵ��λ����
	EntAct   char(35)   not null,
--������ҵ��λ�ʺ�
  AccFlg   char(1)    not null,
--�ʻ�����( 0-�Թ� 1-���� 2-�� )
	Smr      char(60)   default '',
--��ע
	BrNo     char(6)    not null,
--���к�
	BltNod   char(6)    not null,
--��������
	BltTlr   char(7)    not null,
--������Ա
  BltDat   char(8)    not null,
--��Ч����
	UpdTlr   char(7)    default '',
--�޸Ĺ�Ա
	UpdNod   char(6)    default '',
--�޸Ĳ���
	UpdDat   char(8)    default '',
--�޸�����
	constraint PK_CBSCUSAGR PRIMARY KEY( AgrAct, EntCod, EntAct )
);

--09���ڽ�ǹ�����ҵ���ϱ�
create table CbsPubInf
(
	BrNo     char(6)   not null,
--��������
	EntCod   char(6)   not null,
--������ҵ��λ����
	EntAct   char(35)  not null,
--������ҵ��λ�ʺ�
	EntNam   char(60)  not null,
--������ҵ��λ����
	OpnBNo   char(12)  not null,
--�������к�
	AgrKnd   char(1)   not null,
--Э�����ͣ�0��ǿ��ǩԼ 1����ǿ��ǩԼ��
	Smr      char(60)  default '',
--��ע
	constraint PK_CBSPUBINF PRIMARY KEY( BrNo, EntCod )
);

--10���ʺϼ���Ϣ��
create table CbsCenTot
(
	CTraKnd  char(4)     not null,
--��������������
	TraTm    char(10)    not null,
--���׷������ں�ʱ��
	DBrCd    char(12)    not null,
--ֱ��������
	ClrDat   char(8)     not null,
--��������
  AreaNo   char(4)     not null,
--��ͨ����
	CcyCod   char(3)     not null,
--����
  ChkFlg   char(1)     default '0',
--0δ���� 1���ʳɹ�
	CreAmt   char(15)    not null,
--���д������
	CreCnt   char(10)    not null,
--���д�������
	DebAmt   char(15)    not null,
--���н跽���
	DebCnt   char(10)    not null,
--���н跽����
	CreAmt2  char(15)    default '',
--���д������
	CreCnt2  char(10)    default '',
--�������д�������
	DebAmt2  char(15)    default '',
--�������н跽���
	DebCnt2  char(10)    default '',
--�������н跽����
	constraint PK_CBSCENTOT PRIMARY KEY( CTraKnd,DBrCd,ClrDat,AreaNo,CcyCod)
);

--11����ҵ����ܱ�
create table CbsBchSum
(
	BchSts  char(1)     not null,
--״̬
--���ڽ��( ����: U-��ʼ B-������ C-�ѻ�Ӧ D-������ )
--���ڴ���( ����: U-��ʼ B-������ C-��ת�� D-������ R-�ѻ�Ӧ M-������ )
	ClrDat  char(8)     not null,
--��������
	ClrSce  char(1)     not null,
--���㳡��
	SSysId  char(4)     not null,
--����ϵͳ��
	SndBNo  char(12)    not null,
--���𷽴���
	RSysId  char(4)     not null,
--���շ�ϵͳ��
	RcvBNo  char(12)    not null,
--���շ�����
	TraKnd  char(4)     not null,
--��������
	OIFlag  char(1)     not null,
--������־( 0-��, 1-�� )
	FilNam  char(60)    not null,
--�ļ���
	RefFil  char(60)    default '',
--�����ļ���
	BchSqn  char(8)     not null,
--���������
	RefSqn  char(8)     default '',
--�������������
	CusSqn  char(8)     default '',
--�ͻ����������
	TotNum  char(10)    not null,
--�����ܱ���
	TotAmt  char(16)    not null,
--�����ܽ��
	RefNum  char(10)    default '0',
--�ܾ�֧���ܱ���
	RefAmt  char(16)    default '0',
--�ܾ�֧���ܽ��
	RtnCod  char(8)     default '',
--������
	ReServ  char(16)    default '',
--Ԥ����
	AckFil1 char(60)    default '',
--���ʣ����ڽ�� ACK��Ӧ(2210)�����ڴ������׻�Ӧ2212
--���ʣ����ڽ�����׻�Ӧ(2242)�����ڴ������׻�Ӧ2222
	ClrFil  char(60)    default '',
--���ʣ����ڽ��ҵ���Ӧ2212�����ڴ�������֪ͨ2210
--���ʣ����ڽ��ҵ���Ӧ2212
	AckFil2 char(60)    default '',
--���ʣ����ڽ��ҵ���Ӧ2222�����ڴ��������ύ���ļ���
--���ʣ����ڽ��ҵ���Ӧ2220
	DskNo   char(12)    default '',
--���̱��
	ActDat  char(8)     default '',
--�������
	NodNo   char(6)     default '',
--��������
	BrNo    char(6)     default '',
--���к�
	constraint PK_CBSBCHSUM PRIMARY KEY( FilNam )
);
create INDEX ni1_CBSBCHSUM ON CBSBCHSUM( FilNam, OIFlag, BchSts  );


--12����ҵ����ˮ��
create table CbsBchJnl
(
	FilNam  char(60)  not null,
--�ļ���
	MsgSqn  char(16)  not null,
--��Ϣ���
	TraKnd  char(4)   not null,
--��������������
	SndBNo  char(12)  not null,
--�������к�( ֱ�Ӳ������к� )
	SndDat  char(8)   not null,
--ί������
	VchId   char(8)   not null,
--������ƾ֤�ύ��( substr( LogNo, 7, 8 ) )
	OIFlag  char(1)   not null,
--�����˱�־ 0-���� 1-����
	BilSts  char(1)   not null,
--����״̬
--���ʣ�U-��ʼ, Z-�ѿ��ʳɹ� E-����ʧ�� S��ע�Ѹ��� T����ע������ Xȷ������
--���ʣ�0-��ʼ, A-�Ѳ�¼, B-������ C-��ת�� G-���ͳɹ�
	MsgId   char(4)   not null,
--�������ͱ�־
	TxnKnd  char(6)   not null,
--��������������ϸ������
	TxnAmt  char(15)  not null,
--���׽��
	TraTm   char(10)  not null,
--���׷������ں�ʱ��
	ClrDat  char(8)   default '',
--��������
	CcyCod  char(3)   not null,
--�������ױ���
	SvrCod  char(3)		default '',
--��������뷽ʽ��( 021-���������Ҵ�PIN		022-�������벻��PIN		011-�ֹ������Ҵ�PIN		012-�ֹ����벻��PIN )
	CenTm   char(14)  default '',
--���Ľ�������ʱ�������
	CenLog  char(16)  default '',
--���Ľ��������
	ThdTm   char(14)  default '',
--ҵ�����������ں�ʱ��( ����ʱ������д )
	ThdLog  char(16)  default '',
--ҵ������ˮ��( strcat( '00', LogNo ) )
	RtnCod  char(8)   default '',
--������
	CshFlg  char(1)   default '',
--�ֽ�/ת�ʱ�־( 0-�ֽ�		1-ת�� )
	SmrCod  char(4)   default '',
--ժҪ����( ��PDF�ļ�P91 )
	UsgCod  char(3)   default '',
--�ʽ���;( ��PDF�ļ�P89 )
	RSdFlg  char(1)   not null,
--�ط���ʶ( 0-��������	1-�ظ����� )
	AccFlg  char(1)   not null,
--�Թ�/��˽��ʶ( 0-�Թ�	1-��˽  )
	TBusTp  char(5)   default '',
--ҵ������( ��PDF�ļ�P90 )
	CardFg  char(2)   default '00',
--��/�۱�־( 00-����  01-����	02-�� )
	AccKnd  char(1)   default '0',
--�ʻ����� ( 0-�㻧		1-���� )
	FeeTyp  char(3)   default '',
--�����ѷ�ʽ
	PayFuc  char(3)   default '',
--֧������
	AuthCd  char(6)   default '',
--��Ȩ��
	PayLvl  char(1)   default '0',
--֧�����ȼ�
	SOpnBk	char(12)  default '',
--�����˿������к�( ��Ӳ�����֧���к� )
	SndNod  char(9)   default '',
--�����������
	SndAct  char(35)  default '',	
--�������ʺ�
	SndNm   char(60)  default '',
--����������
	SndAdr  char(60)  default '',
--�����˵�ַ
	RcvBNo  char(12)  default '',
--�������к�( ֱ�Ӳ������к� )
	ROpnBk	char(12)  default '',
--�����˿������к�( ��Ӳ������к� )
	RcvNod  char(9)   default '',
--�����������
	RcvAct  char(35)  default '',	
--�������ʺ�
	RcvNm   char(60)  default '',
--����������
	RcvAdr  char(60)  default '',
--�����˵�ַ
	AgrNo   char(60)  default '',
--�෽Э���
	Smr     varchar(300) default '',
--����ժҪ
	OrgId   char(32)  default '',
--��Ʊԭ����Ԫ��ʶ
	SvrKnd  char(1)   default '',
--������Ϣ����
	EtsFlg  char(1)   default '',
--����־
	TBilNo  char(30)  default '',
--˰Ʊ����
	TaxNo   char(20)  default '',
--��˰�˱���
	Taxer   char(60)  default '',
--��˰������
	TaxLvl  char(2)   default '',
--Ԥ�㼶��
	TSubCd  char(12)  default '',
--Ԥ���Ŀ
	TOrgCd  char(11)  default '',
--���ջ��ش���
	TActDt  char(8)   default '',
--˰Ʊ�޽�����
	SecKey  char(40)  default ' ',
--��Ѻ
	BrNo    char(6)   not null,
--���׷���
	NodNo   char(6)   not null,
--��������
	LogNo   char(14)  default '',
--ǰ����ˮ��
	ActFlg  char(1)   not null,
--�˻�����
	AVchTp  char(3)   default '',
--�˻�ƾ֤����
	VchCod  char(8)   default '',
--���ۺ���
	BokAct  char(21)  default '',
--�����ʺ�
	BActSq  char(5)   default '',
--һ��ͨ�˻����
	RvsNo   char(12)  default '',
--���ʺ�
	VchTyp  char(3)   default '',
--ƾ֤����
	VchNo   char(8)   default '',
--ƾ֤����
	FeeFlg  char(1)   default '',
--���ձ�־
	FeeAmt  char(15)  default '000000000000000',
--������
	PstAmt  char(15)  default '000000000000000',
--�ʵ��
	PstTyp  char(1)   default '',
--��ע����( 1-ȷ������ 2-��ע 3-ת����)
	PstNod  char(6)   default '',
--��ע���ʲ���
--��ˮҪ��
--��ˮҪ��
	DskNo   char(12)  default '',
--���̱��
	ActDat  char(8)   default '',
--�������
	TTxnCd  char(6)   default '',
--ǰ�ý�����
	HTxnCd  char(6)   default '',
--����������
	HTxnSt  char(1)   default 'U',
--��������״̬
	HRspCd  char(6)   default '',
--����������
	HLogNo  char(9)   default '',
--������ˮ��
	IsTxn   char(1)   default 'N',
--�Ƿ���������־������������Сͨ������  Y����N������
	TxnObj  char(8)   default '',
--��Сͨ��Ŀ�����
	TlrId   char(7)   default '',
--���й�Ա��
	ChkId   char(7)   default '',
--���˹�Ա
	Sup1Id  char(7)   default '',
--��Ȩ��Ա
	TckNo   char(11)  default '',
--�����ˮ��
	constraint PK_CBSBCHJNL PRIMARY KEY( TraKnd, SndBNo, SndDat, VchId, OIFlag )
);
create index ni1_CBSBCHJNL ON CBSBCHJNL( FilNam, OIFlag, BilSts  );


--13�����кű�
create table CbsBankCd
(
	BankNo   char(12)  not null,
--�к�
	SwftNo   char(12)  default '',
--Switch�к�
	SysId    char(4)   default '',
--ϵͳ��
	CityCd   char(4)   default '',
--��������
	BlArea   char(4)   not null,
--��������
	DirBNo   char(12)  not null,
--ֱ���������к�
	BnkTyp   char(3)   not null,
--�б����
	BankNm   char(60)  not null,
--��������
	SimBNm   char(20)  not null,
--���м��
	SecBNo   char(12)  default '',
--�����������к�
	Adr      char(60)  default '',
--���е�ַ
	PosCod   char(6)   default '',
--�ʱ�
	TelNo    char(20)  default '',
--��ϵ�绰
	FaxNo    char(20)  default '',
--����
	EMail    char(30)  default '',
--���ʵ�ַ
	Comman   char(16)  default '',
--��ϵ��
	DirFlg   char(1)   not null,
--ֱ�������б�־( 0-�������� 1-������ )
	CnpsFg   char(1)   not null,
--֧���кű�־( 0-��֧�� 1-֧�� )
	EffDat   char(8)   not null,
--��Ч����
	IvdDat   char(8)   default '',
--ͣ������
	ReMark   char(60)  default '',
--��ע
	constraint PK_CBSBANKCD PRIMARY KEY( BankNo )
);

--14����ҵ��ͨ��Ϣ
create table CbsBTxnCd
(
	BankNo   char(12)  not null,
--�к�
	TxnKnd   char(6)   not null,
--��ͨ�Ľ�������ϸ��
	CcyCod   char(3)   not null,
--����
	EffDat   char(8)   not null,
--��Ч����
	IvdDat   char(8)   default '',
--ͣ������
	constraint PK_CBSBTXNCD PRIMARY KEY( BankNo, TxnKnd, CcyCod )
);

--15ϵͳ������Ϣ
create table CbsCodeCd
(
	CodTyp   char(6)   not null,
--��������
	Code     char(18)  not null,
--����
	CodSmr   char(40)  not null,
--��������
	EffDat   char(8)   not null,
--��Ч����
	IvdDat   char(8)   default '',
--ͣ������
	constraint PK_CBSCODECD PRIMARY KEY( CodTyp, Code )
);

--16ϵͳ����Ϣ
create table CbsSyIdCd
(
	SysId    char(4)   not null,
--��������
	SysNam   char(60)  not null,
--��������
	BlArea   char(4)   not null,
--��������
	IdType   char(1)   not null,
--��Ա����( 1-���� 2-���� 3-���� )
	EffDat   char(8)   not null,
--��Ч����
	IvdDat   char(8)   default '',
--ͣ������
	constraint PK_CBSSYIDCD PRIMARY KEY( SYSID )
);

--17����������Ϣ
create table CbsAreaCd
(
	CityCd   char(4)   not null,
--��������
	CityNm   char(40)  not null,
--����
	UpgCod   char(4)   not null,
--��������
	CityFg   char(1)   not null,
--��Ա����( 1-���� 2-ʡ���ر������� 3-�� 4-�硢������ )
	constraint PK_CBSAREACD PRIMARY KEY( CityCd )
);

--18ҵ���ʺ�ʹ�ñ�
create table CbsBusAct
(
	BrNo     char(6)   not null,
--���к�
	NodNo    char(6)   not null,
--�����
	TxnKnd   char(6)   not null,
--ҵ������
	InAcNo   char(21)  not null,
--�ڲ��ʺ�
	constraint PK_CBSBUSACT PRIMARY KEY( BrNo, NodNo, TxnKnd )
);

--19���㱨����ʱ��
create table CbsClrRpt
(
  BchFlg  char(1)  not null,
--����������־( 0-����ҵ��  1-����ҵ�� )
	BrNo    char(6)  not null,
--���к�
	TxnKnd  char(6)  not null,
--ҵ������ϸ��
	InNum   char(10) default '0',
--�������
	InAmt   char(15) default '000000000000000',
--������
	OutNum   char(10) default '0',
--�������
	OutAmt   char(15) default '000000000000000',
--������
	constraint PK_CBSCLRRPT PRIMARY KEY( BrNo,TxnKnd )
);
--20�����Ŷ��ձ�
create table CbsExchNo
(
	BrNo    char(6)  not null,
--���к�
	ExchNo  char(10) not null,
--�����к�
	BankNo  char(12) not null,
--֧���к�
	constraint PK_CBSEXCHNO PRIMARY KEY( BrNo, ExchNo )
);
--21������ˮ��
create table CbsNetDtl
(
	DtlSts  char(1)  default 'U',
--��ϸ״̬( U-��ʼ S-���ʳɹ� G-ת���ɹ� F-ת��ʧ�� T-���ʳ�ʱ E-����ʧ��)
	LogNo   char(14) not null,
--ǰ����ˮ��
	ActDat  char(8)  not null,
--�������
	TlrId   char(7)  not null,
--���й�Ա��
	TckNo   char(11) default '',
--�����ˮ��
	TTxnCd  char(6)  default '',
--ǰ�ý�����	
	HTxnCd  char(6)  default '',
--����������	
	HTxnSt  char(1)  default 'U',
--��������״̬
	HLogNo  char(9)  default '',
--������ˮ��
	HRspCd  char(6)  default '',
--����������
	BrNo    char(6)  not null,
--���к�
	NodNo   char(6)  not null,
--�����
	WebChv  char(8)  not null,
--������ˮ��
	RecNo   char(14) not null,
--ϵͳ��ˮ��
	DrAct   char(21) not null,
--�跽�˺�
	DrNam   char(60) not null,
--�跽����
	CrAct   char(32) not null,
--�����˺�
	CrNam   char(60) not null,
--�跽����
	TxnAmt  char(15) not null,
--���׽��
	Rmk     char(60) default '',
--ժҪ
	RvsNo   char(12) not null,
--���˱��
	DonDat  char(8)  not null,
--�������ʻ������
	DonJnl  char(11) not null,
--����������ˮ
	Msg     char(60) default '',
--����
	OppExc  char(10) not null,
--�Է�������
	SndBNo  char(12) default '',
--�����к�
	RcvBNo  char(12) default '',
--�����к�
	FeeAmt  char(15) default '0',
--������
	PstAmt  char(15) default '0',
--�ʵ��
	FeeFlg  char(1)  default '0',
--���ÿ��ձ�־( 0-δ���� 1-�ѿ��� )
	constraint PK_CBSNETDTL PRIMARY KEY( LogNo )
);
create unique index ni1_CBSNETDTL ON CBSNETDTL( RecNo );
create index ni2_CBSNETDTL ON CBSNETDTL( BrNo,ActDat,DtlSts,FeeFlg );
--22���������ѱ�
create table CbsNetFee
(
	FeeSts  char(1)  default 'U',
--��ϸ״̬( U-��ʼ S-���ʳɹ� T-���ʳ�ʱ E-����ʧ��)
	LogNo   char(14) not null,
--ǰ����ˮ��
	DskNo   char(12) not null,
--���̱��
	ActDat  char(8)  not null,
--�������
	TlrId   char(7)  not null,
--���й�Ա��
	TckNo   char(11) default '',
--�����ˮ��
	TTxnCd  char(6)  default '',
--ǰ�ý�����	
	HTxnCd  char(6)  default '',
--����������	
	HTxnSt  char(1)  default 'U',
--��������״̬
	HLogNo  char(9)  default '',
--������ˮ��
	HRspCd  char(6)  default '',
--����������
	IsTxn   char(1)  default 'N',
--�Ƿ���������־������������Сͨ������  Y����N������
	TxnCnl  char(3)  default 'CBS' not null,
--��������
	CnlSub  char(10) default '',
--������
	TxnObj  char(8)  not null,
--��Сͨ��Ŀ�����
	UpdFlg  char(1)  default 'Y',
--���±�־
	UpdFld  char(20) default '',
--�����ֶ���
	BrNo    char(6)  not null,
--���к�
	NodNo   char(6)  not null,
--�����
	TxnMon  char(6)  not null,
--�����·�
	DrAct   char(21) not null,
--�跽�˺�
	DrNam   char(60) not null,
--�跽����
	TxnNum  char(6)  not null,
--���ױ���
	CcyCod  char(3)  default 'CNY',
--����
	FeeAmt  char(15) default '0',
--������
	PstAmt  char(15) default '0',
--�ʵ��
	PrtNum  char(2)  default '0',
	constraint PK_CBSNETDTL PRIMARY KEY( LogNo )
);
--23�����������ñ�
create table CbsFeeRpt
(
	Mon     char(6)   not null,
--�շ��·�
	SndBNo  char(12)  not null,
--�������к�
	TxnKnd  char(6)   not null,
--ҵ������ϸ��
  PkgNum  char(6)   default '',
--���װ���
	TxnNum  char(6)   default '0',
--���ױ���
	TxnCcy  char(3)   default '',
--���ױ���
	TxnAmt  char(15)  default '0',
--�����ܽ��
	FeeCcy  char(3)   default '',
--�շѱ���
	FeeAmt  char(15)  default '0'
--�շ��ܽ��
--	constraint PK_CBSFEERPT PRIMARY KEY( Mon,SndBNo,TxnKnd )
);
create index ni1_CBSFEERPT ON CBSFEERPT( Mon,SndBNo,TxnKnd );
