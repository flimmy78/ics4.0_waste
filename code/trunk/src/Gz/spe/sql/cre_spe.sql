drop table SpeCusInf;
drop table SpeNodInf;
drop table SpeTxnInf;
drop table SpeTxnDtl;
--
--
-- �ͻ�������ݱ�
--
--
create table SpeCusInf
(
	cunb      char(13) not null,
-- �ͻ���
	acnm      char(30) not null,	
--����
--idtp      char(2)  not null,	
--֤������ 
	idno      char(20) not null, 
-- ֤���� 
	cutp	    char(16) not null,
--�ͻ���� 
	snum      int      default 0
--��ѯ����
);
CREATE INDEX ni1_SPECUSINF ON SpeCusInf( cunb );
--
--
-- �������Ա���ݱ�
--
--
create table SpeNodInf
(
	NodNo     char(6)  not null,
--�����
	NodNam    char(60) not null,	
--������
	MagNam    char(10) not null, 
--����Ա����
	MagLvl    char(1)  not null,
--����Ա����
	UniNo     char(4)  not null,
--�ֻ�����
	MobTel    char(15) not null,
--�ֻ�����
	Sts       char(1)  not null,
	constraint PK_SPENODINF PRIMARY KEY(NodNo,MobTel)
);
--
--
-- ����ҵ�������ݱ�
--
--
create table SpeTxnInf
(
	BrNo     char(6)   not null,
--���к�
	NodNo    char(6)   not null,
--�����
	ActDat   char(8)   not null,
--�������
	TlrId    char(7)   not null,
--��Ա��
	FTxnTm   char(14)  not null,
--ǰ�ý���ʱ��
	ActNo    char(21)  default '',
--��ѯ�ʺ�
	Cunb     char(13)  default ''
--�ͻ���
);
--
--
-- ������ϸ���ݱ�
--
--
create table SpeTxnDtl
(
	TckNo   char(11)   default '',
--�����ˮ��
	CardNo  char(19)   default '',
--����
	ActNo   char(21)   default '',
--�˺�
	BokDat  char(8)    default '',
--��������
	TxnSmr  char(60)   default '',
--ժҪ
	CdFlag  char( 1)   default '',
--�����־
	BokAmt  char(15)   not null,
--���˽��
	Bal     char(15)   not null,
--���
	BTxnCd  char(6)    default '',
--������
	BSubCd  char(3)    default '',
--��������
  Year    char(4)    default '',
--��
  PgNum   char(6)    default '',
--ҳ��
  PgSeq   char(2)    default '',
--ҳ�ڱ����
  OppAct  char(32)   default '',
--�Է��ʺ�
  OppNam  char(60)   default '',
--�Է�����
	TxnNod  char( 6)   default '',
--��������
	CcyCod  char( 3)   default '',
--����
	TxnLog  char(18)   default '',
--������־��
	TxnAdr  char(60)   default '',
--���׵ص�
	TxnDat  char( 8)   default '',
--��������
	TxnTim  char( 6)   default '',
--����ʱ��
	AuthCd  char( 6)   default ''
--��Ȩ��
);
