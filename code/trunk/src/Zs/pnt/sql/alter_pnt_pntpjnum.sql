drop table PntPjNum;
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
