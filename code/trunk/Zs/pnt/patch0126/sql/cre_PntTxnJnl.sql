drop table PntTxnJnl;

create table PntTxnJnl
(
	LogNo    char(14)   not null,
--ǰ����ˮ��
	TTxnCd   char(6)    not null,
--�ӿڽ�����
	TxnCod   char(6)    not null,
--ǰ�ý�����
	HTxnCd   char(6)    not null,
--����������
	TxnTyp   char(1)    not null,
--��������( N-�������� C-�������� R-�ط�����)
	OIFlag   char(1)    not null,
--�����˱�־( 0-���� 1-���� )
	BusTyp   char(6)    not null,
--ҵ������
	CrpCod   char(12)   default '',
--��λ����
	ActDat   char(8)    not null,
--�������
	CcyCod   char(3)    default 'CNY',
--���Ҵ���
	TxnAmt   char(15)   not null,
--���׽��
	ActTyp   char(1)    not null,
--�˻�����( 0-�ֽ� 1-һ��ͨ 2-��ͨ���� 4-̫ƽ�� A-��ͨ�Թ� B-������� C-�㶫���� )
	AVchTp   char(3)    default '',
--�˻�ƾ֤����
	VchCod   char(8)    default '',
--���ۺ���
	ActNo    char(21)   default '',
--�����ʺ�
	BActSq   char(5)    default '',
--һ��ͨ�˻����
	RvsNo    char(12)   default '',
--���ʺ�
	VchTyp   char(3)    default '',
--ƾ֤����
	VchNo    char(8)    default '',
--ƾ֤����
	NodNo    char(6)     default '',
--���������
	BrNo     char(6)     not null,
--���׷���
	TlrId    char(7)     not null,
--���й�Ա��
	FTxnTm   char(14)    default '',
--ǰ�ý���ʱ��
	HLogNo   char(9)     default '',
--������ˮ��
	TckNo    char(11)    default '',
--�����ˮ��
	TTxnSt   char(1)    default 'U',
--����������״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ T-��ʱ V-�����ɹ� )
	TxnSts   char(1)    default 'U',
--����״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ T-��ʱ  )
	HTxnSt   char(1)     default 'U',
--��������״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ E-��� T-��ʱ)
	HRspCd   char(6)     default '',
--������Ӧ��
------������ҵ������------
------������ҵ������------
------������ҵ������------
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
	PayDat   char(8)    default '',
--�ɷ�����
  PActNo   char(50)   default '',
--����˻�
	Smr      char(60)   default '',
--��ע
	PrvDat   clob(2048) default '',   
--��������( PrjNum��PrjRec��RmkNum��RmkRec )
	BilSts   char(1)    default 'U',
--״̬( U-��ʼ B-���ʳɹ� S-ת���ɹ� X-ϵͳ����(δ����) F-����ʧ�� T-���ͳ�ʱ R-Ĩ��)
	ChkDat   char(8)    default '',
--��������
	ChkBch   char(2)    default '',
--��������
	CONSTRAINT PK_PNTTXNJNL PRIMARY KEY( LogNo )
);
