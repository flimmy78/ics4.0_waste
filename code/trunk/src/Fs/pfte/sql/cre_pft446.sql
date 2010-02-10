drop table PftBnkInf446;
drop table PftChkTot446;
drop table PftCusAgt446;
drop table PftTxnJnl446;
drop table PftSec202Sum446;
drop table PftSec202Dtl446;
--
--
--
--������Ϣ��
--
--
--
create table PftBnkInf446
(
  BnkCls   char(1)   not null,
--�������� 0-ֱ�Ӳ�����  1-ҵ�����
  BrNo     char(6)   not null,
--���׷���
  BnkCod   char(12)  not null,
--����֧���к�
  CtlNod   char(6)   not null,
--ͨ����Ʋ��ź�
  ClrDat   char(8)   not null,
--��ǰ��������
  SysSts   char(1)   not null,
--ϵͳ����״̬ 0-ϵͳ�ر�  1-ϵͳ����
  Act01    char(21)  default '',
--22203�ۿ�ר��
  Act02    char(21)  default '',
--13801�˿�ר��
  UserPs   char(8)   default '',
  constraint PK_PFTBNKINF446 PRIMARY KEY(BnkCls,BrNo)
);
--
--
--
--�˶�ͳ�Ʊ�
--
--
--
create table PftChkTot446
(
  BnkCod   char(12)   not null,
--���д���
  ClrDat   char(8)    not null,
--�ʽ��������
  ClrSce   char(1)    not null,
--�ʽ��������
  TTxnTp   char(2)    not null,
--��������
  ChkFlg   char(1)    default '0',
--���ʱ�ʶ 0δ���� 1���ʳɹ�
  TotNum   char(6)    not null,
--�ܱ���
  TotAmt   char(15)   not null,
--�ܽ��
  BnkNum   char(6)    default '',
--�����ܱ���
  BnkAmt   char(15)   default '',
--�����ܽ��
  CONSTRAINT PK_PFTCHKTOT446 PRIMARY KEY( BnkCOd,ClrDat,ClrSce,TTxnTp)
);
--
--
--
--��˰Э���
--
--
create table PftCusAgt446
(
  Sts      char(1)   not null,
--״̬( 0-��Ч 1-��Ч )
  TCrpTp   char(1)   not null,
--���ջ������( 1-��˰ 2-��˰ 3-���� 5-����)
  AgtInf   char(35)  not null,
--Э��ȷ����
  ActTyp   char(1)   not null,
--�˻�����( 0-��ͨ�Թ� 1-һ��ͨ 2-��ͨ���� 4-̫ƽ�� A-��������Թ� B-�㶫ʡ�����Թ� )
  ActNo    char(21)  not null,
--��˰�˽ɿ��ʺ�
  ActNam   char(60)  default '',
--�ͻ�����
  VchTyp   char(3)   default '',
--ƾ֤����
  VchCod   char(8)   default '00000000',
--ƾ֤����
  ActSqn   char(5)   default '',
--һ��ͨ�˻����
  PfaSub   char(3)   default '',
--��������
  BCusId   char(18)  default '',
--����Ԥ�㵥λ����
  SubCod   char(20)  default '',
--Ԥ���Ŀ
  EConTp   char(20)  default '',
--���÷������
  PrjCod   char(20)  default '',
--Ԥ����Ŀ����
  DptCod   char(20)   default '',
--���Ҵ���
  CusTel   char(60)   default ' ',
--��˰����ϵ�绰
  OpnNod   char(6)   not null,
--��������
  OpnBr    char(6)   not null,
--��������
  CONSTRAINT PK_PFTCUSAGT446 PRIMARY KEY( TCrpTp,AgtInf,ActNo )
);
--
--
--��˰��ˮ��
--
--
create table PftTxnJnl446
(
  LogNo    char(14)  not null,
--ǰ����ˮ��
  TTxnCd   char(6)   not null,
--�ӿڽ�����
  TxnCod   char(6)   not null,
--ǰ�ý�����
  HTxnCd   char(6)   not null,
--����������
  TxnTyp   char(1)   not null,
--��������( N-�������� C-�������� R-�ط�����)
  BilSts   char(1)   default 'U',
--����״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ T-������ʱ W-��������ʱ V-�����ɹ� )
  OIFlag   char(1)   not null,
--�����˱�־( 0-���� 1-���� )
  BusTyp   char(6)   not null,
--ҵ������
  CrpCod   char(12)  default '',
--��λ����
  ActDat   char(8)   not null,
--�������
  CcyCod   char(3)   default 'CNY',
--���Ҵ���
  TxnAmt   char(15)  not null,
--���׽��
  ActNo    char(21)  default '',
--�ͻ��ʺ�
  ActNam   char(60)  default '',
--�ͻ�����
  ActTyp   char(2)   not null,
--�˻�����( 0-��ͨ�Թ� 1-һ��ͨ 2-��ͨ���� 4-̫ƽ�� A-��������Թ� B-�㶫ʡ�����Թ� )
  VchTyp   char(3)   default '',
--ƾ֤����
  VchCod   char(8)   default '00000000',
--ƾ֤����
  ActSqn   char(5)   default '',
--һ��ͨ�˻����
  PfaSub   char(3)   default '',
--��������
  BCusId   char(18)  default '',
--����Ԥ�㵥λ����
  SubCod   char(20)  default '',
--Ԥ���Ŀ
  EConTp   char(20)  default '',
--���÷������
  PrjCod   char(20)  default '',
--Ԥ����Ŀ����
  DptCod   char(20)  default '',
--���Ҵ���
  NodNo    char(6)   default '',
--���������
  BrNo     char(6)   not null,
--���׷���
  TlrId    char(7)   not null,
--���й�Ա��
  TxnCnl   char(3)   default '',
--��������
  FTxnTm   char(14)  default '',
--ǰ�ý���ʱ��
  HLogNo   char(9)   default '',
--������ˮ��
  TckNo    char(11)  default '',
--�����ˮ��
  PLogNo   char(14)  default '',
--���������ˮ��
  HTxnSt   char(1)   default 'U',
--��������״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ E-��� T-��ʱ)
  HRspCd   char(6)   default '',
--������Ӧ��
  RspCod   char(6)   default '',
--ǰ�÷�����
  RtnCod   char(4)   default '',
--������
  ClrDat   char(8)   default '',
--�����������
  ClrSce   char(1)   default '',
--���������������
  BTxnID   char(16)  default '',
--���н���ʶ���
  ThdChk   char(1)   default '0',
--����������ʱ�־( 0-δ���� 1-�Ѷ��� )
  MsgFmt   char(6)   default '',
--��Ϣ��ʽ��
  TCrpCd   char(11)  not null,
--���ջ��ش���
  TActDt   char(8)   default '',
--���ջ����ύ����
  TLogNo   char(16)  not null,
--���ջ�������ˮ��
  RcvBNo   char(12)  not null,
--���մ������к�
  FskCod   char(11)  not null,
--�տ�������
  TTxnTp   char(2)   not null,
--��������������
  OTActDt  char(8)   default '',
--�������ջ����ύ����(����ʹ��)
  OTLogNo  char(16)  default '',
--�������ջ�����ˮ��(����ʹ��)
  AgtInf   char(35)  default '',
--ǩԼ������Ϣ(��˰�˱���)
  SndAct   char(35)  default '',
--�������ʺ�
  SndNm    char(60)  default '',
--����������
  RcvAct   char(35)  default '',
--�������ʺ�
  RcvNm    char(60)  default '',
--����������
  TPayTp   char(1)   default '',
--�걨��ʽ����( OIFlag='0'ʱ e-�ֽ� f-ת�� g-POS )
  SavFld   char(2)   default '',
--������
  AppFlg   char(1)   default '0',
--��չҪ�ر�־
  TVchNo   char(24)  default '',
--����˰Ʊ��(ƾ֤��)
  CONSTRAINT PK_PFTTXNJNL446 PRIMARY KEY( LogNo )
);
create unique index ni1_PftTxnJnl446 on PftTxnJnl446( TCrpCd, TActDt, TLogNo );
create index ni2_PftTxnJnl446 on PftTxnJnl446( TCrpCd, OTActDt, OTLogNo );
create index ni3_PftTxnJnl446 on PftTxnJnl446( MsgFmt, ClrDat, ClrSce, BTxnID );
--
--
--
--��˰ƾ֤���ܱ�
--
--
create table PftSec202Sum446
(
  MsgFmt   char(6)   not null,
--��Ϣ��ʽ��
  ClrDat   char(8)   not null,
--ETS�ʽ��������
  SndCod   char(12)  not null,
--�ļ����ͷ�����
  RcvCod   char(12)  not null,
--�ļ����շ�����
  ClrSce   char(4)   not null,
--ETS�ʽ��������
  FilSeq   char(10)  not null,
--�ļ����
  OIFlag   char(1)   default '',
--�����˱�־( 0-���� 1-���� )
  RcvBNo   char(12)  default '',
--���մ������к�
  RcvBNm   char(60)  default '',
--���մ���������
  ActDat   char(8)   default '',
--�����ύ����
  BTxnID   char(16)  default '',
--���н���ʶ���
  TTxnTp   char(2)   default '',
--��������������
  AgtInf   char(35)  default '',
--ǩԼ������Ϣ
  ActTyp   char(2)   default '',
--�˻�����( 0-��ͨ�Թ� 1-һ��ͨ 2-��ͨ���� 4-̫ƽ�� A-��������Թ� B-�㶫ʡ�����Թ� )
	SndAct   char(35)  default '',
--�������˺�
  RcvAct   char(35)  default '',
--�ɿ��ʺ�
	ActNo    char(21)  default '',
--�����˺�
  ActNam   char(60)  default '',
--����������
  TxnAmt   char(15)  not null,
--���
  PrtFlg   char(1)   default '',
--��ӡ��˰Ҫ�ر�־( 0-���� 2-����ҵ���д�ӡ���лص�ʱһ����ӡ��˰Ҫ�� )
  TaxNo    char(20)  default '',
--��˰��ʶ���
  TaxNam   char(100) default '',
--��˰������
  CrpKnd   char(40)  default '',
--��ҵע������
  TCrpNm   char(60)  default '',
--���ջ�������
  TLogNo   char(16)  not null,
--���ջ�������ˮ��
  FskNam   char(60)  default '',
--�տλ(����)����
  Smr      char(200) default '',
--��ע
  DtlNum   char(3)   not null,
--��ϸ��Ŀ
  DtlMac   char(64)  default '',
--��Ѻ
  PrtCnt   char(2)   default '00',
--��ӡ����
  OpnNod   char(6)   default '',
--�����
  OpnBr    char(6)   default '',
--���к�
  CONSTRAINT PK_PFTSEC202SUM446 PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq )
);
--
--
--��˰ƾ֤��ϸ��
--
--
create table PftSec202Dtl446
(
  MsgFmt   char(6)   not null,
--��Ϣ��ʽ��
  ClrDat   char(8)   not null,
--ETS�ʽ��������
  SndCod   char(12)  not null,
--�ļ����ͷ�����
  RcvCod   char(12)  not null,
--�ļ����շ�����
  ClrSce   char(4)   not null,
--ETS�ʽ��������
  FilSeq   char(10)  not null,
--�ļ����
  DtlSeq   char(3)   not null,
--��ϸ˳���
  TaxTyp   char(40)  default '',
--˰������
  PrjNam   char(60)  default '',
--ƷĿ����
  LvlNam   char(40)  default '',
--Ԥ�㼶������
  TaxDt    char(17)  default '',
--˰����������
  DtlAmt   char(15)  default '',
--��ϸ���
  TSubCd   char(12)  default '',
--Ԥ���Ŀ����
  TVchNo   char(20)  default '',
--����˰Ʊ��(ƾ֤��)
  CONSTRAINT PK_PFTSEC202DTL446 PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq,DtlSeq )
);
drop table PftCrpInf446;
drop table PftFskInf446;
drop table PftFilInf446;
drop table PftSec203Sum446;
drop table PftSec203Dtl446;
--
--
--
--���ջ�����Ϣ��
--
--
--
create table PftCrpInf446
(
  Sts      char(1)   not null,
--״̬( 0-��Ч 1-��Ч )
  TCrpTp   char(1)   not null,
--���ջ������( 1-��˰ 2-��˰ 3-���� 5-����)
  TCrpCd   char(11)  not null,
--���ջ��ش���
  TCrpNm   char(60)  not null,
--���ջ�������
  FskCod   char(11)  not null,
--��Ӧ�������
  FskNam   char(60)  not null,
--��Ӧ��������
  AgtBNo   char(8)   default '',
--�������к�
  AgtBNm   char(60)  default '',
--����������
  Rmk      char(60)  default '',
--��ע
  constraint PK_PFTCRPINF446 PRIMARY KEY( TCrpTp,TCrpCd )
);
--
--
--
--���������Ϣ��
--
--
create table PftFskInf446
(
  Sts      char(1)   not null,
--״̬( 0-��Ч 1-��Ч )
  FskCod   char(11)  not null,
--�������
  FskNam   char(60)  not null,
--��������
  constraint PK_PFTCRPINF446 PRIMARY KEY( FskCod,FskNam )
);
--
--�����˿���Ϣ��
--
--
--
create table PftFilInf446
(
  FilSts   char(1)   not null,
--�ļ�����״̬( 0-�������ڶ��� 1-���ݶ���ɹ� 2-�������ڽ��� 3-������� 4-�˿��˻����ڴ��� 5-�˿��˻���� )
  PftFil   char(60)  not null,
--�ļ���
  ClrDat   char(8)   not null,
--��������
  ActDat   char(8)   not null,
--�������
  MsgFmt   char(6)   default '',
--��Ϣ����
  RcvBNo   char(11)  default '',
--ֱ�Ӳ������к�
  BatNo    char(4)   default '',
--���κ�
  TotNum   char(6)   default '',
--�ܱ���
  TotAmt   char(15)  default '',
--�ܽ��
  RetCod   char(4)   default '',
--��������
  ErrNum   char(6)   default '',
--�������
  constraint PK_PFTFILINF446 primary key( PftFil )  
);
--
--
--�˿�ƾ֤���ܱ�
--
--
create table PftSec203Sum446
(
  PftFil   char(60)  not null,
--�ļ���
  MsgFmt   char(6)   not null,
--��Ϣ��ʽ��
  ClrDat   char(8)   not null,
--ETS�ʽ��������
  SndCod   char(12)  not null,
--�ļ����ͷ�����
  RcvCod   char(12)  not null,
--�ļ����շ�����
  ClrSce   char(4)   not null,
--ETS�ʽ��������
  OIFlag   char(1)   default '',
--�����˱�־( 0-���� 1-���� )
  TCrpCd   char(11)  not null,
--���ջ��ش���
  TActDt   char(8)   not null,
--���ջ����ύ����
  TLogNo   char(16)  not null,
--���ջ�������ˮ��
  RcvBNo   char(12)  not null,
--���մ������к�
  FskCod   char(11)  not null,
--�տ�������
  TTxnTp   char(2)   not null,
--��������������
  Smr      char(8)   default '',
--��ע
  TVchNo   char(20)  default '',
--����˰Ʊ��(ƾ֤��)
  RcvAct   char(35)  default '',
--�������ʺ�
  SndAct   char(35)  default '',
--�������ʺ�
  TxnAmt   char(15)  not null,
--���
  TPayTp   char(1)   default '',
--�걨��ʽ����( OIFlag='0'ʱ e-�ֽ� f-ת�� g-POS )
  PrtFlg   char(1)   not null,
--��ӡ��˰Ҫ�ر�־( 0-���� 2-����ҵ���д�ӡ���лص�ʱһ����ӡ��˰Ҫ�� )
  TaxNam   char(100) default '',
--��˰������
  TaxNo    char(20)  default '',
--��˰��ʶ���
  CrpKnd   char(4)   default '',
--��ҵע������
  DtlNum   char(3)   not null,
--��ϸ��Ŀ
  DtlMac   char(64)  default '',
--��Ѻ
  BilSts   char(1)   default 'U',
--������
  ActDat   char(8)   not null,
--�����ύ����
  LogNo    char(14)  default '',
--ǰ����ˮ��
  HRspCd   char(6)   default '',
--����������
  TckNo    char(11)  default '',
--�����ˮ��
  RtnCod   char(8)   default '',
--������
  ActTyp   char(2)   default '',
--�˻�����( 0-��ͨ�Թ� 1-һ��ͨ 2-��ͨ���� 4-̫ƽ�� A-��������Թ� B-�㶫ʡ�����Թ� )
  ActNo    char(21)  default '',
--�ɿ��ʺ�
  ActNam   char(60)  default '',
--����������
  PrtCnt   char(2)   default '00',
--��ӡ����
  OpnNod   char(6)   default '',
--�����
  OpnBr    char(6)   default '',
--���к�
  CONSTRAINT PK_PFTSEC203SUM446 PRIMARY KEY( PftFil,TCrpCd,TActDt,TLogNo )
);
create index ni1_PftSec03Sum446 on PftSec203Sum446( ClrDat );
--
--
--�˿�ƾ֤��ϸ��
--
--
create table PftSec203Dtl446
(
  PftFil   char(60)  not null,
--�ļ���
  TCrpCd   char(11)  not null,
--���ջ��ش���
  TActDt   char(8)   not null,
--���ջ����ύ����
  TLogNo   char(16)  not null,
--���ջ�������ˮ��
  DtlSeq   char(3)   not null,
--��ϸ˳���
  DtlAmt   char(15)  default '',
--��ϸ���
  LvlNam   char(40)  default '',
--Ԥ�㼶������
  TSubCd   char(12)  default '',
--Ԥ���Ŀ����
  TaxTyp   char(40)  default '',
--˰������
  TRtnCd   char(10)  default '',
--�˿�ԭ�����
  Rmk1     char(7)   default '',
--������һ
  Rmk2     char(16)  default '',
--�������
  CONSTRAINT PK_PFTSEC203DTL446 PRIMARY KEY( PftFil,TCrpCd,TActDt,TLogNo,DtlSeq )
);

drop table pftNodInf446;

--���մ����к�������ձ�
create table PftNodInf446
(
	NodNo	char(6) not null,		
--�����
	NodNam	char(60),	
--��������
	CtlNod char(6),
--��������
	RcvBNo char(4) not null,		
--���մ����к�
	BrNo	char(6) not null,		
--���к�
  constraint PK_PFTCRPINF446 PRIMARY KEY( NodNo, BrNo )
);

--
drop table PftRtnCod446;
--�˿�ԭ������ 
create table PftRtnCod446
(
	TRtnCd char(3) not null,	
--�˿�ԭ�����  
	TRtnNm char(30),				
--����
  constraint PK_PftRtnCod446 PRIMARY KEY( TRtnCd )
);
