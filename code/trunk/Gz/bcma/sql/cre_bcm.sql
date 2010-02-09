drop table BcmActReg441;
drop table BcmTxnJnl441;
--
--
-- BCM���ſͻ��ʺŵǼǱ�
--
--
create table BcmActReg441
(
	Sts     char(1)      not null,
--״̬( 0-��Ч	1-��Ч )
	MActNo  char(21)     not null,
--�������ʺ�
	SActNo  char(21)     not null,
--�������ʺ�
	SActNm  char(60)     not null,
--�������ʺŻ���
	MaxAmt  char(15)     not null,
--�����
	Rmk     char(60)     default '',
--�����Ϣ
	ValDat  char(8)      not null,
--��Ч����
	BltTlr  char(7)      not null,
--������Ա
	BltNod  char(6)      not null,
--��������
	UpdTlr  char(7)      default '',
--�޸Ĺ�Ա
	UpdNod  char(6)      default '',
--�޸Ĳ���
	UpdDat  char(8)      default '',
--�޸�����
	constraint PK_BCMACTREG441 PRIMARY KEY( MActNo, SActNo )
);
--
--
-- BCM���Ž�����ˮ��
--
--
create table BcmTxnJnl441
(
	TxnSts  char(1)   not null,
--״̬
	LogNo   char(14)  not null,
--ǰ����ˮ��
	MActNo  char(21)  not null,
--�������ʺ�
	MActNm  char(60)  not null,
--�������ʺŻ���
	SActNo  char(21)  not null,
--�������ʺ�
	SActNm  char(60)  not null,
--�������ʺŻ���
	TxnAmt  char(15)  not null,
--������
	Smr     char(60)  default '',
--����ԭ��
	PrtCnt  char(2)   default '00',
--��ӡ����
	TlrId   char(7)   not null,
--���ʹ�Ա
	Sup1Id  char(7)   default '',
--����(��Ȩ��Ա)
	Sup2Id  char(7)   default '',
--����(��Ȩ��Ա)
	NodNo   char(6)   not null,
--��������
	BusTyp  char(5)   not null,
--ҵ������
	TTxnCd  char(6)   not null,
--ǰ�ý�����
	HTxnCd  char(6)   not null,
--����������
	ActDat  char(8)   default '',
--�������
	HLogNo  char(9)   default '',
--������ˮ��
	TckNo   char(11)  default '',
--�����ˮ��
	HTxnSt  char(1)   default '',
--��������״̬
	HRspCd  char(6)   default '',
--����������
	constraint PK_BCMTXNJNL441 PRIMARY KEY( LogNo )
);
