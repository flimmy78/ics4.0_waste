drop table HawCrpInf;
drop table HawPrvInf;
drop table HawCrpTxn;
drop table HawPrvTxn;
--
--
--
--��λ��Ϣ��
--
--
--
create table HawCrpInf
(
	TCrpCd   char(50)   not null,
--��λ����
	TCrpNm   char(60)   default '',
--��λ����
	TCrpAd   char(200)  default '',
--��λ����
	MailCd   char(10)   default '',
--��������
  AreaCd   char(10)   default '',
--������
  TelNum   char(20)   default '',
--��ϵ�绰
  TelNam   char(20)   default '',
--��ϵ��
  TFulNm   char(60)   default '',
--���ܵ�λȫ��
  TCrpId   char(20)   default '',
--�����ʸ�
  EConTp   char(20)   default '',
--��������
  TCrpTp   char(20)   default '',
--��λ����
  TCrpBL   char(20)   default '',
--������ϵ
  TFncBn   char(50)   default '',
--��������
  TCrpBn   char(50)   default '',
--��λ����
  PrYear   char(10)   default '',
--��������
  PayDat   char(50)   default '',
--��н��
  DepNum   char(10)   default '',
--�㴢����
  DepAmt   char(50)   default '',
--�»㴢�ܶ�
  PerNum   char(10)   default '',
--һ���Է�������
  PreAmt   char(50)   default '',
--һ���Է����ܶ�
	CrpFrm   char(10)   default '',
  constraint PK_HAWCRPINF PRIMARY KEY( TCrpCd )
);
--
--
--
--�ͻ���Ϣ��
--
--
--
create table HawPrvInf
(
  IdNo     char(20)   not null,
--֤������
  PrvNam   char(60)   default '',
--�ͻ�����
	MonCnt   char(5)    default '',
--��������
  PMCntO   char(5)    default '',
--�Ʒ�������һ���ԡ�
  PMAmtO   char(15)   default '',
--�췢���
  PMCnt    char(5)    default '',
--�Ʒ����������¡�
  BegTim   char(8)    default '',
--��ʼʱ��
  EndTim   char(8)    default '',
--��������
  MonAmt   char(15)   default '',
--�»㴢��
  AmtStd   char(15)   default '',
--������׼
  PrvFrm   char(20)   default '',
--���˿������
  TRecNo   char(5)    default '',
--���
	Duty     char(20)   default '',
--ְ��
	TCrpCd   char(50)   default '',
--��λ����
	TCrpNm   char(60)   default '',
--��λ����
  constraint PK_HAWPRVINF PRIMARY KEY( IdNo )
);
--
--
--
--��λҵ����ˮ��
--
--
--
create table HawCrpTxn
(
	TLogNo   char(19)   not null,
--������ˮ��
	TCrpCd   char(50)   not null,
--��λ����
	CrpAct   char(30)   not null,
--��λ�˺�
	TTxnTp   char(1)    not null,
--��������( 1-���� 2-֧�� 3-��Ϣ )
	TxnAmt   char(15)   not null,
--���׽��
	TrAcDt   char(8)    not null,
--��������
	CrpBal   char(15)   not null,
--�Թ����
	SndFlg   char(1)    default '0',
--��¼����״̬( 0-δ���� 1-�ѷ��� )
	Sts      char(1)    default '0',
--��¼״̬( 0-��Ч 1-��Ч )
  constraint PK_HAWCRPTXN PRIMARY KEY( TLogNo )
);
--
--
--
--����ҵ����ˮ��
--
--
--
create table HawPrvTxn
(
	TLogNo   char(19)   not null,
--������ˮ��
  IdNo     char(20)   not null,
--֤������
	PrvAct   char(30)   not null,
--�����˺�
	TTxnTp   char(1)    not null,
--��������( 1-���� 2-֧�� 3-��Ϣ )
	TxnAmt   char(15)   not null,
--���׽��
	TrAcDt   char(8)    not null,
--��������
	PrvBal   char(15)   not null,
--�������
	CrpAct   char(30)   not null,
--��λ�˺�
	SndFlg   char(1)    default '0',
--��¼����״̬( 0-δ���� 1-�ѷ��� )
	Sts      char(1)    default '0',
--��¼״̬( 0-��Ч 1-��Ч )
  constraint PK_HAWPRVTXN PRIMARY KEY( TLogNo )
);
