--1   Table: caditmcod   ( �����շ��շ���Ŀ����� ) - ( �ļ�ͷ )
--ԭ�Թ�3.0ϵͳ����sf_content_tb
drop table caditmcod;
create table caditmcod
(
	CrgCod     	char(20)     not null,
--�շѱ���
  	CrgItm     	char(60)    not null,
--�շ���Ŀor����ԭ��
  	CrgDpt	 	char(60)	not null,
--�շѵ�λ
    	constraint PK_ZH_ITMCOD primary key( CrgCod )
);

--2   Table: cadtxnjnl   ( �����շѽ�����ˮ�� ) - ( �ļ��� )
drop table cadtxnjnl;
create table cadtxnjnl
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
   	TckNo           char(11)        default '0',
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
	VchSeq       	char(4)         default '0001',
--��Ʊ���
	CrgTyp      	char(1)		default '1',
--�շ�����(1-�����շѡ�����ר  2-��ɽ�ƾ��շ� )
	CadCcp      	char(1)		default '1',
--������ѧУ(1-�����շ� 2-����ר)
 	RcpNo		char(15)	default ' ',
--�վݱ��
	BilSqn		char(12)	default ' ',
--�ɿ�֪ͨ����
 	CrgWay  	char(1)		not null ,
--�շѷ�ʽ(0-�ֽ�,1-ת��,2-������ѯת��,3-����)
 	CusNam    	char(60)	default ' ',
--�ɿλ(��)
  	CrgDpt	 	char(60)	default ' ',
--�շѵ�λ
    primary key( LogNo )
);
create index ni1_cadtxnjnl on cadtxnjnl(ActDat);


--3   Table: cadjnldtl   ( �����շ��շ���ˮ��ϸ�� ) - ( �ļ�ͷ )
drop table cadjnldtl;
create table cadjnldtl
(
	CrgTyp     	char(1)		default '1',
--�շ�����(1-�����շѡ�����ר  2-��ɽ�ƾ��շ�)
	CadCcp     	char(1)		default '1',
--������ѧУ(1-�����շ� 2-����ר)
	RecSts   	char(2)    	default '0',
--��¼״̬    0-δ����  1-���˳ɹ���δ����  T-��ʱ  C-Ĩ��  3-�ѷ���  4-�ڶ��췢��
	ChkFlg		char(1)    	default '0',
--����״̬    0-δ����  1-������
	LogNo		char(14)	not null,
--ǰ����ˮ��
   	TckNo       char(11)    default '0',
--�����ˮ��
	VchSeq     	char(4)     default '0001',
--��Ʊ���
 	ItmSqn		char(6)		not null,
--�ڼ���(��һ���շѶ���һ��)
	ActDat     	char(8)    	default ' ',
--�������
	NodNo      	char(6)    	default ' ',
--���������
	TlrId      	char(7)    	default ' ',
--���й�Ա��
	CcyCod		char(3)		default 'CNY',
--���Ҵ���
	TxnAmt      char(15)    default ' ',
--�ܽ��
 	BilSqn		char(12)	default ' ',
--�ɿ�֪ͨ����
 	RcpNo		char(15)	default ' ',
--�վݱ��
 	RcpTyp		char(1)		default '1',
--�վ�����
 	CrgWay  	char(1)		not null,
--�շѷ�ʽ(0-�ֽ�,1-ת��)
	CrgCod     	char(7)		not null,
--�շѴ���
  	CrgItm     	char(60)   	default ' ',
--�շ���Ŀor����ԭ��
  	CrgDpt	 	char(60)	default ' ',
--�շѵ�λ
 	CusNam    	char(60)	default ' ',
--�ɿλ(��)
	ActNo      	char(21)   	default ' ',
--�ͻ��˺�
	CrgUni		char(6)		default 'Ԫ',
--�Ʒѵ�λ
	UniPri		char(12)	default ' ',
--����
 	UniNum		char(6)		default ' ',
--����
	ItmAmt		char(12)	default ' ',
--�������ܼ�
    constraint PK_ZH_TXNJNL primary key( LogNo,ItmSqn)
);

--4   Table: cadtmptbl   ( ��ʱ�� ) - ( �ļ�ͷ )
drop table cadtmptbl;
create table cadtmptbl
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
	CcyCod		char(3)		default 'CNY'
--���Ҵ���
);

--5   Table: cadfshact   ( ����������ר�շ��շѽ��˱� ) - ( �ļ�ͷ )
drop table cadfshact;
create table cadfshact
(
	CrgTyp      	char(1)		not null,
--�շ�����(1-�����շѡ�����ר  2-��ɽ�ƾ��շ�)
	ActDat      	char(8)    	not null,
--�������
	TxnSts	  	    char(1)	    default 'U',
--����״̬
	NodNo       	char(6)    	not null,
--���������
    constraint PK_ZH_TXNJNL primary key( CrgTyp,ActDat,NodNo)
);

--6   Table: cadnodinf
--ԭ�Թ�ϵͳ����Ϊsf_sfg_tb
drop table cadnodinf;
create table cadnodinf
(
    NodCod          char(4)     not null,
--�����շѱ���
    NodNam          char(20)    not null,
--�����շ�����
	NodNo      	    char(6)		not null,
--��������
    Status          char(1)     not null
--״̬ 0��Ч,1��Ч
);
--7   Table: cadtmptbl2   ( ��ʱ�� ) - ( �ļ�ͷ )
drop table cadtmptbl2;
create table cadtmptbl2
(
    TxnDat          char(8)     not null,
--�������
    NodNo           char(6)     not null
--���������
);

