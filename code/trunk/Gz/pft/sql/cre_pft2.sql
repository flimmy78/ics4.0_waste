drop table PftCrpInf;
drop table PftFilInf;
drop table PftSec203Sum;
drop table PftSec203Dtl;
--
--
--
--���ջ�����Ϣ��
--
--
--
create table PftCrpInf
(
  Sts      char(1)   not null,
--״̬( 0-��Ч 1-��Ч )
  TCrpTp   char(1)   not null,
--���ջ������( 1-��˰ 2-��˰ 3-���� 4-����)
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
  constraint PK_PFTCRPINF PRIMARY KEY( TCrpTp,TCrpCd )
);
--
--
--
--�����˿���Ϣ��
--
--
--
create table PftFilInf
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
  constraint PK_PFTFILINF primary key( PftFil )  
);
--
--
--�˿�ƾ֤���ܱ�
--
--
create table PftSec203Sum
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
  CONSTRAINT PK_PFTSEC203SUM PRIMARY KEY( PftFil,TCrpCd,TActDt,TLogNo )
);
create index ni1_PftSec03Sum on PftSec203Sum( ClrDat );
--
--
--�˿�ƾ֤��ϸ��
--
--
create table PftSec203Dtl
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
  CONSTRAINT PK_PFTSEC203DTL PRIMARY KEY( PftFil,TCrpCd,TActDt,TLogNo,DtlSeq )
);
