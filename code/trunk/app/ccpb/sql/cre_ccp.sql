--1   Table: ccpshlcod   ( ����ר�շѴ���� ) - ( �ļ�ͷ )
--ԭ�Թ�ϵͳ3.0��ı���sf_educodeofxz_tb
drop table ccpshlcod;
create table ccpshlcod
(
	ShlCod      char(10)    	not null,
--ѧУ�༶����
  	ShlNam      char(60)    not null,
--У��
  	ShlGr	 	char(2)		not null,
--�꼶
	SubNam		char(60)	not null,
--רҵ����
    	constraint PK_ZH_EDUCOD primary key( ShlCod )
);

--2   Table: ccptxnjnl   ( ����ר������ˮ�� ) - ( �ļ��� )
drop table ccptxnjnl;
create table ccptxnjnl
(
  BrNo          char(6)       not null,
--���к�
	LogNo		char(14)	not null,
--ǰ����ˮ��
	TTxnCd      	char(10)    	default ' ',
--������������
	TxnCod      	char(6)     	default ' ',
--������
	TxnTyp      	char(1)     	default ' ',
--��������
	BusTyp      	char(6)     	default ' ',
--ҵ������
	CrpCod      	char(10)    	default ' ',
--��λ����
    HTxnSb      	char(3)     	default ' ',
--��������
	ActDat      	char(8)     	default ' ',
--�������
	CcyCod		char(3)		default ' ',
--���Ҵ���
	TxnAmt      	char(15)    	default ' ',
--���׽��
	Fee         	char(15)    	default ' ',
--����������
	ActNo       	char(21)    	default ' ',
--�ͻ��˺�
	CrdNo       	char(30)    	default ' ',
--�ͻ�����
	OrgNo       	char(6)     	default ' ',
--������
	NodNo       	char(6)     	default ' ',
--���������
	TlrId       	char(7)     	default ' ',
--���й�Ա��
	ChkTlr       	char(7)     	default ' ',
--���˹�Ա��
	CntrId      	char(10)    	default ' ',
--���й�̨��
	NodTrc      	char(20)    	default ' ',
--������ˮ��
	TxnCnl      	char(3)     	default ' ',
--��������
	ItgTyp      	char(1)     	default ' ',
--����������
	FTxnTm      	char(14)    	default ' ',
--ǰ�ý���ʱ��
	FRspCd      	char(6)     	default ' ',
--ǰ����Ӧ��
	HLogNo      	char(9)     	default ' ',
--������ˮ��
	HRspCd      	char(6)     	default '999999',
--������Ӧ��
	HTxnSt      	char(1)     	default 'U',
--��������״̬
   	TckNo           char(11)        default ' ',
--�����ˮ��
	HPrChk      	char(1)     	default '0',
--�������ռ���˱�־
	HLsChk      	char(1)     	default '0',
--���������ն��˱�־
	TCusId      	char(30)    	default ' ',
--�������ͻ���ʶ
	TCusNm      	char(80)    	default ' ',
--�������ͻ�����
	TActDt      	char(8)     	default ' ',
--��������������
	TLogNo      	char(20)    	default ' ',
--��������ˮ��
	TRspCd      	char(10)    	default ' ',
--��������Ӧ��
	TTxnSt      	char(1)     	default 'U',
--����������״̬
	ThdChk      	char(1) 	default '0',
--����������˱�־ 0δ���� 1���˳ɹ� 2���� 3������������  4 ������������
	TxnSts		char(1)		default 'U',
--����״̬ S���׳ɹ� F����������ȷʧ�� T��ʱ Uδ֪״̬ X����ʧ�ܣ�δ����������
	TxnAtr		char(32)	default ' ',
--��������
	MstChk		char(1)		default '0',
--Ҫ����˱�־
	LChkTm		char(10)	default ' ',
--1970���������
	HTxnCd		char(6)	    default ' ',
--����������

--�����Ǳ�ҵ���õ����ֶ�
	VchSeq     	char(4)    default '0001',
--��Ʊ���
 	CrgWay  	char(1)		not null ,
--�շѷ�ʽ(0-�ֽ�,1-ת��,2-������ѯת��,3-����)
    RcpNo       char(15)    default ' ',
--�վݱ��
 	CusNam    	char(60)	default ' ',
--�ɿλ(��)
  	ShlNam      char(60)   	default ' ',
--У��
  	ShlGr	 	char(2)		default ' ',
--�꼶
	SubNam		char(60)	default ' ',
--רҵ����
    constraint PK_ZH_TXNJNL primary key( LogNo )
);
create index ni1_ccptxnjnl on ccptxnjnl(ActDat);

--3   Table: ccpjnldtl   ( �����շ��շ���ˮ��ϸ�� ) - ( �ļ�ͷ )
drop table ccpjnldtl;
create table ccpjnldtl
(
	RecSts   	char(2)    	default '0',
--��¼״̬    0-δ����  1-���˳ɹ���δ����  T-��ʱ  C-Ĩ��  3-�ѷ���  4-�ڶ��췢��
	LogNo		char(14)	not null,
--ǰ����ˮ��
   	TckNo       char(11)    default '0',
--�����ˮ��
	VchSeq     	char(4)     default '0001',
--��Ʊ���
	ActDat     	char(8)    	default ' ',
--�������
	NodNo      	char(6)    	default ' ',
--���������
	TlrId      	char(7)    	default ' ',
--���й�Ա��
	CcyCod		char(3)		default 'CNY',
--���Ҵ���
    RcpNo       char(15)    default ' ',
--�վݱ��
    RcpTyp      char(1)     default '5',
--�վ�����
    CrgWay      char(1)     not null,
--�շѷ�ʽ(0-�ֽ�,1-ת��)
	ShlCod     	char(7)    	not null,
--ѧУ�༶����
  	ShlNam      char(60)    default ' ',
--У��
  	ShlGr	 	char(2)		default ' ',
--�꼶
	SubNam		char(60)	default ' ',
--רҵ����
 	CusNam    	char(60)	default ' ',
--�ɿλ(��)
	ActNo       char(21)    default ' ',
--�ͻ��˺�
	TxnAt1     	char(12) 	default '0',
--ѧ�ӷ�
	TxnAt2     	char(12) 	default '0',
--ס�޷�
	TxnAt3      char(12) 	default '0',
--ʵϰ�����
	TxnAt4      char(12) 	default '0',
--������
	TxnAt5      char(12) 	default '0',
--���޷�
	TxnAt6      char(12) 	default '0',
--����
	TxnAmt      char(15)    default ' ',
--�ϼ�

    constraint PK_ZH_TXNJNL primary key( LogNo)
);

--4   Table: ccptmptbl   ( ��ʱ�� ) - ( �ļ�ͷ )
drop table ccptmptbl;
create table ccptmptbl
(
	VchSeq    	char(4)    	default ' ',
--��Ʊ���
	VchSts    	char(1)    	default ' ',
--��Ʊ״̬
	VchSig    	char(1)    	default ' ',
--�������־ D�裻C��
	ActNo     	char(21)   	default ' ',
--�˺�
	TxnAmt    	char(15)   	default ' ',
--���
    CcyCod      char(3)     default 'CNY'
--���Ҵ���
);
