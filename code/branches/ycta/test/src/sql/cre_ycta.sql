-- ============================================================
--   ���ͨ������ֵ������ݱ�
--   Table: yctafiletj
-- ============================================================
CREATE TABLE yctafiletj
(
  ActDat       CHAR(8)         not null,
--�������
  SNO          CHAR(5)         DEFAULT ' ',
--���к�,1:JY�ļ�;2:CZ�ļ�
  FNAME        CHAR(24)        DEFAULT ' ',
--�ļ���
  FRS          CHAR(10)        DEFAULT ' ',
--�ļ���¼����
  RFS          CHAR(12)        DEFAULT ' ',
--��¼�������
);
create index ni1_yctafiletj on yctafiletj(ActDat, SNO);