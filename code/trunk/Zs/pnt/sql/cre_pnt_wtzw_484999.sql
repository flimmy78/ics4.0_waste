drop table PntWtzw;

--����������Ϣ�ļ�
create table PntWtzw
(
  RevDt       char(8)    not null,
--�տ�����
  TitNum       char(10)   not null,
--�ܱ���
  TBilTp        char(8)    not null,
--Ʊ������
  TBilNo        char(20)   not null,
--Ʊ�ݺ���
  TError        char(100)  not null,
--����ԭ��
CONSTRAINT PK_PNTWTZW PRIMARY KEY( RevDt,TBilTp,TBilNo )
);
