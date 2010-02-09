drop table PntTxnBok;




create table PntTxnBok
(
	CmdCod   char(3)    not null,
--������( ������������ )
	BankCd   char(30)   not null,
--���б���
	TCrpCd   char(30)   not null,
--ִ�յ�λ����
	TVchTp   char(2)    default '',
--�ɿ�֪ͨ�����
	TVchId   char(50)   not null,
--�ɿ�֪ͨ�����
	PayNam   char(60)   default '',
--�ɷ���(��λ)����
	TVchDt   char(8)    default '',
--�ɿ�֪ͨ������
	TBilTp   char(8)    not null,
--Ʊ�����ͱ���
	TBilNo   char(20)   not null,
--Ʊ�ݺ���
	BilAmt   char(15)   not null,
--Ӧ���ܽ��
	FulCrc   char(5)    default '',
--ȫ��У����
	PenAmt   char(15)   not null,
--Ӧ�������ɽ�
	PayDat   char(14)    default '',
--�ɷ�����
	Smr      char(60)   default '',
--��ע
	PrvDat   clob(2048) default '',   
--��������( PrjNum��PrjRec��RmkNum��RmkRec )
	BilSts   char(1)    default 'U',
--״̬( U-��ʼ B-���ʳɹ�(ȷ��) S-ת���ɹ� X-ϵͳ����(δ����) F-����ʧ�� T-���ͳ�ʱ R-Ĩ�� C-����δȷ�� D-�ѳ���)
	LogNo    char(14)   default '',
--ǰ����ˮ��
	ActDat   char(8)    not null,
--�������
	TckNo    char(11)   default '',
--�����ˮ
  RActNo   char(21)   default '',
--�տ��˺�
	ChkDat   char(8)    default '',
--��������
	ChkBch   char(2)    default '',
--��������
	CONSTRAINT PK_PNTTXNBOK PRIMARY KEY( TBilTp,TBilNo )
);