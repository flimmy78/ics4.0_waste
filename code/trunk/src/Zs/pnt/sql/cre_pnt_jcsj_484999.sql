drop table PntSfxm;
drop table Pntdwxx;
drop table PntDwxm;
drop table PntPjlx;
drop table PntPjff;
drop table PntXmpj;
drop table PntQyxx;
drop table PntPjNum;
drop table PntPrgx;


--�շ���Ŀ��Ϣ
create table PntSfxm
(
	BrNo          char(6)    not null,
--���к�
	PrjCod        char(14)   not null,
--�շ���Ŀ����
  PrjNam        char(200)  not null,
--�շ���Ŀ����
  SubCod        char(9)    default '',
--Ԥ���Ŀ����
  SubNam        char(100)  default '',
--Ԥ���Ŀ����
  SfxmSts       char(1)    not null
--״̬
  
);

--��λ��Ϣ
create table PntDwxx
(
	BrNo          char(6)    not null,
--���к�
  TCrpCd        char(30)   not null,
--��λ����
  TCrpNm        char(100)  not null,
--��λ����
  DwxxSts       char(1)    not null
--״̬
);

--��λ��Ŀ��Ϣ
create table PntDwxm
(
	BrNo          char(6)    not null,
--���к�
  TCrpCd        char(30)   not null,
--��λ����
	PrjCod        char(14)    not null
--�շ���Ŀ����
);

--Ʊ��������Ϣ
create table PntPjlx
(
	BrNo          char(6)    not null,
--���к�
	TBilTp        char(8)    not null,
--Ʊ�����ͱ���
	TBilNm        char(50)   not null,
--Ʊ����������
  PjlxSts       char(1)    not null
--״̬(0��ʾ����,1Ϊ����)

);

--Ʊ�ݷ�����Ϣ
create table PntPjff
(
	BrNo          char(6)    not null,
--���к�
	TBilTp        char(8)    not null,
--Ʊ�����ͱ���
  TBilStar      char(20)   not null,
--Ʊ����ʼ����
  TBilEnd       char(20)   not null,
--Ʊ����ֹ����
  TBilTot       char(10)   not null,
-- Ʊ�ݷ���
  TBilSts       char(1)    not null,
--Ʊ��״̬(1Ϊ����,3Ϊ�ѽ�ֹ)
  TBilReSts     char(1)    not null
--Ʊ�ݷֽ�״̬(1Ϊδ�ֽ�,2Ϊ�ѷֽ�)
 
);

--Ʊ�ݺ���
create table PntPjNum
(
  TBilTp        char(8)    not null,
--Ʊ�����ͱ���
  TBilNo        char(20)   not null,
--Ʊ�ݺ���
  TBilSts       char(1)    not null,
--Ʊ��״̬(1Ϊδʹ��,2Ϊ��ʹ��,3Ϊ��ֹʹ��,4Ϊ��ʱʹ��)
  TBilFFSts    char(1)     default '',
--Ʊ�ݷ���״̬(1Ϊδ����,2Ϊ�ѷ���)
  TBilNod      char(6)    default '',
--ʹ�õص�(��¼�����)
  TBilSeq      char(6)    default ''
--���
);

--��ĿƱ����Ϣ��
create table PntXmpj
(
	BrNo          char(6)    not null,
--���к�
	PrjCod        char(14)    not null,
--�շ���Ŀ����
	TBilTp        char(8)    not null
--Ʊ�����ͱ���

);

--������Ϣ
create table PntQyxx
(
	BrNo          char(6)    not null,
--���к�
  AreaNo        char(12)   not null,
--�������
  AreaNm        char(50)   not null
--��������

);

--֪ͨ��ǰ׺�����л���˻��Ĺ�ϵ
create table PntPrgx
(
	BrNo          char(6)    not null,
--���к�
  TCrpHD        char(2)    not null,
--֪ͨ��ǰ׺
  PActNm        char(100)  not null,
--�˻�����
  PActNo        char(50)   not null
--����˻�

);




