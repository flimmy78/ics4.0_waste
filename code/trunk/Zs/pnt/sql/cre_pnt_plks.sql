drop table pntfilctl;
drop table pntbatrec;
drop table pntextbat;
drop table pntfilinf;
--�����ļ����Ʊ�
create table pntfilctl
(
   FileNo      char(10) not null,
-- �ļ���
   FileNam    char(50) not null,
-- �ļ���
   DskNo      char(12) not null,
-- ���κ�   
   BankCd     char(30) not null,
-- ���б���
   TCrpCd     char(30) not null,
-- ִ�յ�λ����
   TxnDat     char(8)  not null,
-- ����
   ActDat     char(8)  not null,
-- �������
   TotNum     char(10) not null,
-- �ܱ���
   TotAmt     char(16) not null,
-- �ܽ��
   RcvTim     char(14) not null default '',
-- �����ļ�ʱ��   
   SndTim     char(14) not null default '',
-- �����ļ�ʱ��
   TlrId      char(7)  not null default '',
-- ������Ա
   DskSts     char(1)  not null default '',
-- ����״̬(1Ϊδ�۷�,2Ϊ�ѿ۷�,3�Ѵ�ӡ)
   Primary key(DskNo)
);

--�����ļ���ϸ��
create table pntbatrec
(
   FSeqNo     char(15)    not null default ' ',
--ǰ�ü�¼���
   LogNo     char(14)    not null default ' ',
--��ˮ��
   FileNo    char(10)     not null,
--�ļ���
   DskNo     char(12)    not null,
--���κ�
   SeqNo     char(07)    not null,
--˳���
   BusTyp    char(6)     not null default ' ',
--ҵ������
   CrpCod   char(10)     not null default ' ', 
--��λ����
   ActDat   char(8)      not null,
--�������
   BSmr     char(04)     not null default ' ',
--ҵ��ժҪ��
   VchCod    char(03)    not null default ' ',
--ƾ֤����*
   ActTyp    char(01)    not null default ' ',
--�˺����� 2�˺� 4����
   ActSqn      char(5)   default ' ' not null,
--�˺�˳���
   ActNo     char(21)    not null default ' ',
--���˺�
   ActNam    char(60)    not null default ' ',
--����
   CAgtNo   char(10)    not null default ' ',
--��λ���
   TxnCod   char(06)    not null default ' ',
--������
   CcyCod   char(3)     not null default 'CNY',
--���Ҵ���
   TxnDat   char(08)    not null default ' ',
--��������
   TxnDir   char(01)    not null default ' ',
--�����־
   FulChk  char(01) not null default ' ',
--�����ۿ��־	��0�������ۿ� ��1������ʱ����ۿ�
   CrgFlg   char(01) not null default ' ',
--�շѱ�־
   CrgCod   char(04) not null default ' ',
--�շѴ���
   CActNo   char(21) not null default ' ',
--��λ�˺�
   RecSts   char(01) not null default ' ',
--״̬	SPACE-δ���� E-�������(Ӧ�г������) F-����ɹ� N-�����ཻ��ת��������  R-�����ཻ��ת�������� P-���ֿۿ�ɹ� X-Э�����
   Fee         char(15)    default ' ' not null,
--�����ѽ��
   HTxnCd       char(6)    default ' ',
--����������
   HLogNo       char(9)    default ' ' not null,
--������ˮ��
   HRspCd       char(6)    default ' ',
--������Ӧ��
   HTxnSt       char(1)    default 'U' not null,   
--U:Ԥ��״̬(ȱʡֵ) S���ɹ� F:ʧ�� C:������ U:Ԥ��״̬  X:����ʧ��  T:���ͳ�ʱ  D:���ױ�����  E:��������
   HPrChk      char(1)     default '0' not null,
--0:δ����(ȱʡֵ) 1:�Ѷ��� 2:���˲���
   HLsChk      char(1)     default '0' not null,
--0:δ����(ȱʡֵ) 1:�Ѷ��� 2:���˲���
   IsTxn     char(1)    default 'Y' not null,
--Y:Ҫ����  N:������
   TxnCnl       char(3) default ' ' not null,
--��������
   TxnObj       char(8) default ' ' not null,
--Ŀ�������
   TlrId        char(7) default ' ' not null,
--���˹�Ա��
   TTxnCd       char(6)     default ' ' not null,
--ǰ�ý�����
   BrNo         char(6)     default ' ' not null,
--���˷��к�
   NodNo       char(6)     default ' ' not null,
--���������
   TxnMod      char(1)     default ' ' not null,
--���׷�ʽ
   PayMod      char(1)     default ' ' not null,
--֧����ʽ
   FunCod   char(2 ) not null default ' ',
--ҵ������
	TVchId   char(50)   not null,
--�ɿ�֪ͨ�����
	TBilTp   char(8)    not null,
--Ʊ�����ͱ���
  TBilNo   char(20)   not null default ' ',
--Ʊ�ݺ���
	PayNam   char(60)   default '',
--�ɷ���(��λ)����
	TxnAmt   char(15)   not null,
--Ӧ���ܽ��
  PrjNum   char(1)    not null,
--�շ���Ŀ��
  TCusID    char(30) not null default ' ',
--�������ͻ���ʶ,ƾ����
  TCusNm    char(60) not null default ' ',
--�������ͻ�����
   RsFld1   char(30) not null default ' ',
--��ע
   CTBLNm      char(30)   not null  default ' ',
--��չ�ӱ���
   ExtKey      bigint ,
--��չ�ӱ��ֵ
    primary key(DskNo,SeqNo)
);

create table pntextbat
(
   ExtKey      bigint ,
--��չ�ӱ��ֵ
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

--�ļ���Ϣ��
create table pntfilInf
(
   FileNo      char(10) not null,
-- �ļ���
   FileNam    char(50) not null,
-- �ļ���  
   BankCd     char(30) not null,
-- ���б���
   TCrpCd     char(30) not null,
-- ִ�յ�λ����
   TxnDat     char(8)  not null,
-- ����
   ActDat     char(8)  not null,
-- �������
   TotNum     char(10) not null,
-- �ܱ���
   TotAmt     char(16) not null,
-- �ܽ��
   RcvTim     char(14) not null default '',
-- �����ļ�ʱ��   
   SndTim     char(14) not null default '',
-- �����ļ�ʱ��
   TlrId      char(7)  not null default '',
-- ������Ա
   DskSts     char(1)  not null default '',
-- ����״̬(1Ϊδ�۷�,2Ϊ�ѿ۷�,3�Ѵ�ӡ)
   Primary key(FileNo,FileNam)
);