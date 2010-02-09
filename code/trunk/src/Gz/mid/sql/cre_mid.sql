drop table MidTxnJnl;
--
--
--ͳһ֧��ƽ̨��ˮ��
--
--
create table MidTxnJnl
(
	LogNo      char(14)  not null,
--ǰ����ˮ��
	TTxnCd     char(10)  not null,
--������������
	TxnCod     char(6)   not null,
--������
	TxnTyp     char(1)   not null,
--��������( N-�������� C-�������� R-�ط�����)
	BusTyp     char(6)   default '',
--ҵ������
	CrpCod     char(10)  default '',
--��λ����
	ActDat     char(8)   not null,
--�������
	CcyCod     char(3)   default '',
--���Ҵ���
	TxnAmt     char(15)  not null,
--���׽��
	Fee        char(15)  default '0',
--�����ѽ��
	ActNo      char(21)  default '',
--�ͻ��ʺ�
	ActNam     char(60)  default '',
--�ͻ�����
	OrgNo      char(6)   default '',
--������
	NodNo      char(6)   default '',
--���������                                                
	TlrId      char(7)   not null,
--���й�Ա��                                                
	CntrId     char(10)  default '',
--���й�̨��
	NodTrc     char(20)  default '',
--������ˮ��
	TxnCnl     char(3)   default '',
--��������
	ItgTyp     char(1)   not null,
--����������( 0-�ǳ��� 1-�ֶ����� 2-ϵͳ���� 6-�ط� )
	FTxnTm     char(14)  not null,
--ǰ�ý���ʱ��
	FRspCd     char(6)   default '',
--ǰ����Ӧ��
	HLogNo     char(9)   default '',
--������ˮ��
	TckNo      char(11)  default '',
--�����ˮ��
	HRspCd     char(6)   default '',
--������Ӧ��
	HTxnSt     char(1)   default 'U',
--��������״̬( S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ E-��� )
	HPrChk     char(1)   default '0',
--�������ռ���ʱ�־( 0-δ���� 1-�Ѷ��� 2-���ʲ��� )
	HLsChk     char(1)   default '0',
--���������ն��ʱ�־( 0-δ���� 1-�Ѷ��� 2-���ʲ��� )
	TCusId     char(30)  default '0',
--�������ͻ���ʶ
	TCusNm     char(60)  default '',
--�������ͻ�����
	TActDt     char(8)   default '',
--��������������(��Ȩƾ֤�Ǽ�����)
	TLogNo     char(20)  default '',
--��������ˮ��
	TRspCd     char(10)  default '',
--��������Ӧ��
	TTxnSt     char(1)   default 'U',
--����������״̬(  S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ T-��ʱ )
	ThdChk     char(1)   default '0',
--����������ʱ�־( 0-δ���� 1-�Ѷ��� )
	TxnSts     char(1)   default 'U',
--����״̬( S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ )
	TxnAtr     char(32)  default '',
--��������
	MstChk     char(1)   default '',
--Ҫ����ʱ�־( 0-������� 1-������� )
	LChkTm     char(10)  default '',
--�ϴζ���ʱ��
	BrNo       char(6)   not null,
--���к�
	BokFlg     char(1)   not null,
--���ʱ�־( 0�����ʡ�1�������� )
	BchFlg     char(1)   not null,
--��������( 0����1��С�2-���С�9������ƽ̨ )
	RpdFlg     char(1)   not null,
--�������ȼ�( 1-��ͨ��2-������3-�ؼ� )
	PMBTyp     char(2)   not null,
--ҵ������( 10���ֽ��� 11����ͨ��� 30��������� 40���ʽ���� 50�������� 51������ͬ�ǽ����������� 61�����п�����Ʊ�ݽ�������� 99������ )
	AccFlg     char(1)   not null,
--�����ʺ�����( 0���Թ� 2������ 4-�� )
	CclNo      char(12)  default '',
--���ʺ�
	SndAct     char(32)  default '',
--�������ʺ�
	SndNam     char(60)  default '',
--�����˻���
	SndAdr     char(60)  default '',
--�����˵�ַ
	SndBNo     char(12)  default '',
--�������к�
	RcvAct     char(32)  default '',
--�������ʺ�
	RcvNam     char(60)  default '',
--�����˻���
	RcvAdr     char(60)  default '',
--�����˵�ַ
	RcvBNo     char(12)  default '',
--�������к�
	Smr        char(60)  default '',
--ժҪ
	VchTyp     char(3)   default '',
--ƾ֤����
	VchNo      char(8)   default '',
--ƾ֤����
	BilDat     char(8)   default '',
--ǩ������
	PayPsw     char(16)  default '',
--֧������
	FeeTyp     char(1)   default '',
--�շѷ�ʽ( 1���ջ� 2-�ؼ� 3���Ż�  5���ֹ����� )
	PstAmt     char(15)  default '0',
--���ӻ㻮��
	FeeAmt     char(15)  default '0',
--������
	CONSTRAINT PK_MIDTXNJNL PRIMARY KEY( LogNo )
);
