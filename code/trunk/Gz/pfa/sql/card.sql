drop table PfaCrdInf;
drop table PfaCrdTxn;
drop table PfaCrdDtl;
drop table PfaCrdJnl;
--
--
--����Ա������
--
--
create table PfaCrdInf
(
	PfaSub      char(3)   not null,
--��������
	CardNo      char(19)  not null,
--����
	CollDt      char(8)   default '',
--�ռ�����
	LmtAmt      char(15)  default '',
--���
	CrdSts      char(4)   default '',
--��Ƭ״̬
	IdType      char(4)   default '',
--֤������
	IdNo        char(60)  default '',
--֤������
	CardNm      char(30)  default '',
--����
	GendCd      char(2)   default '',
--�Ա�
	BthPlc      char(100) default '',
--����
	CrpNam      char(60)  default '',
--��λ����
	DptNam      char(30)  default '',
--��ְ����
	DutyCd      char(2)   default '',
--ְ��
	MobTel      char(20)  default '',
--�ֻ�����
	Email       char(30)  default '',
--�����ʼ�
	CrpTel      char(20)  default '',
--��λ�绰
	Addr        char(100) default '',
--�˵���ַ
	HisBr       char(12)  default '',
--ԭ����ϵͳ���к�
	EffDat      char(8)   default '',
--��������
	IvdDat      char(8)   default '',
--��Ч��
	SellId      char(12)  default '',
--Ӫ������
	BCusId      char(18)  default '',
--����Ԥ�㵥λ����
	BrNo        char(6)   not null,
--���к�
	ActDat      char(8)   not null,
--��������
	constraint PK_PFACRDINF PRIMARY KEY( PfaSub,CardNo )
);
--
--
--����Ա��������ϸ
--
--
create table PfaCrdTxn
(
	CardNo      char(19)  not null,
--����
	CollDt      char(8)   default '',
--�ռ�����
	HisBr       char(12)  default '',
--ԭ����ϵͳ���к�
	TxnDat      char(8)   not null,
--��������
	TxnTim      char(8)   default '',
--����ʱ��
	IbsDat      char(8)   default '',
--������������
	TxnSmr      char(60)  default '',
--����˵��
	MerId       char(15)  default '',
--�̻���
	TermId      char(9)   default '',
--�ն˺�
	MerNam      char(60)  default '',
--�̻�����
	TLogNo			char(6)   not null,
--������ˮ��
	DtlAmt      char(15)  default '',
--���׽��
	CcyCod      char(3)   default '',
--����
	ThdCod      char(4)   default '',
--������
	AuthCd      char(6)   default '',
--��Ȩ��
	SltOrg      char(12)  default '',
--���������
	PtgOrg      char(12)  default '',
--ת��������
	RefNum      char(30)  default '',
--�����ο���
	SltDat      char(8)   default '',
--��������
	CardNm      char(30)  default '',
--�ֿ�������
	HActDt      char(8)   default '',
--��ʷ���ѯ����(�ñ���ϸ��ȡ����)
	IdxNo  	    char(6)   default '',
--������
	PfaSub      char(3)   not null,
--����Ӧ�ô���
	Year        char(4)   default '',
--���
	BCusId      char(18)  default '',
--����Ԥ�㵥λ����
	SndFlg      char(1)   default '0',
--����״̬( 0-δ���� 1-�ѷ��� )
	constraint PK_PFACRDTXN PRIMARY KEY( PfaSub,CardNo,TxnDat,TLogNo )
);
create index ni1_PfaCrdTxn on PfaCrdTxn( PfaSub, HActDt, IdxNo );
--
--
--����Ա��������ϸ
--
--
create table PfaCrdDtl
(
	DtlSts      char(1)   not null,
--����״̬( U-��ʼ B-���� S-�ɹ� F-ʧ��)
	PfaSub      char(3)   not null,
--����Ӧ�ô���
	Year        char(4)   not null,
--���
	AVchCd      char(30)  not null,
--֧������
	PfaIdx      char(16)  not null,
--����������ϸ����
	CardNo      char(19)  not null,
--����
	CardNm      char(30)  not null,
--�ֿ�������
	TxnDat      char(8)   not null,
--��������
	TxnTim      char(8)   default '',
--����ʱ��
	MerId       char(15)  default '',
--�̻���
	TermId      char(8)   default '',
--�ն˺�
	MerNam      char(60)  default '',
--�̻�����
	TLogNo			char(6)   default '',
--������ˮ��
	DtlAmt      char(15)  default '',
--���׽��
	CcyCod      char(3)   default '',
--����
	ThdCod      char(4)   default '',
--������
	AuthCd      char(6)   default '',
--��Ȩ��
	HActDt      char(8)   default '',
--��ʷ���ѯ����(�ñ���ϸ��ȡ����)
	IdxNo  	    char(6)   default '',
--������
	BrNo        char(6)   default '',
--���к�
	BCusId      char(18)  default '',
--����Ԥ�㵥λ����
	BokAmt      char(15)  default '',
--�������
	TActDt      char(8)   default '',
--����ȷ������
	BokDat      char(8)   default '',
--��������
	LogNo       char(14)  default '',
--ǰ����ˮ��
  RtnFlg      char(1)   default '0',
--���ر�־ (0-δ�� 1-�ѻ�)
	constraint PK_PFACRDDTL PRIMARY KEY( PfaSub, Year, AVchCd, PfaIdx )
);
--
--
--����Ա��������ˮ��
--
--
create table PfaCrdJnl
(
	TxnSts      char(1)   default 'U',
--״̬( U-��ʼ S-�����ɹ� F-����ʧ�� T-������ʱ C-���� )
	TxnTyp      char(1)   default 'N',
--��������( N-�������� C-�������� R-�ط�����)
	LogNo       char(14)  not null,
--ǰ����ˮ��
	BrNo        char(6)   not null,
--���к�
	ActDat      char(8)   not null,
--�������
	HTxnSt      char(1)   default 'U',
--��������״̬
	HRspCd      char(6)   default '',
--����������
	HLogNo      char(9)   default '',
--������ˮ��
	TlrId       char(7)   default '',
--���й�Ա��
	TckNo       char(11)  default '',
--�����ˮ��
	CardNo      char(19)  default '',
--�ͻ��ʺ�
	CardNm      char(30)  not null,
--�ֿ�������
	CcyCod      char(3)   default '',
--���Ҵ���
	TotAmt      char(15)  not null,
--�����ܶ�
	TxnAmt      char(15)  not null,
--���׽��
	PfaSub      char(3)   not null,
--����Ӧ�ô���
	Year        char(4)   not null,
--���
	BCusId      char(18)  not null,
--����Ԥ�㵥λ����
	AVchCd      char(30)  not null,
--֧������
	constraint PK_PFACRDJNL PRIMARY KEY( LogNo )
);
create index ni1_PfaCrdJnl on PfaCrdJnl( PfaSub,Year,AVchCd );
