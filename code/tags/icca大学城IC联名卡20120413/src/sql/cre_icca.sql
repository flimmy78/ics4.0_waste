
-- ============================================================
--   ��ѧ��������
--   Table: iccatxnjnl   (��ѧ����������ֵ��ˮ��)
-- ============================================================
CREATE TABLE iccatxnjnl
(
  BrNo          CHAR(6)         DEFAULT ' ',
--���к�  
  LogNo         CHAR(14)        DEFAULT ' ',
--ǰ����ˮ��
  TLogNo        CHAR(30)        DEFAULT ' ',
--��������ˮ��
  HLogNo        CHAR(9)        DEFAULT ' ',
--������ˮ��
  TckNo         CHAR(12)        DEFAULT ' ',
--�����ˮ��
  ActDat        CHAR(8)         DEFAULT ' ',
--�������
  CrdNo         CHAR(30)        DEFAULT ' ',
--����
  ActNo         CHAR(30)        DEFAULT ' ',
--�ʺ�
  ICBak         CHAR(30)        DEFAULT ' ',
--���е���Ǯ���˺�
  ICSch         CHAR(30)        DEFAULT ' ',
--У԰������Ǯ���˺�
  TCusID        CHAR(30)        DEFAULT ' ',
--�ͻ���־
  TCusNm        CHAR(60)        DEFAULT ' ',
--�ͻ�����
  IDNo          CHAR(30)        DEFAULT ' ',
--֤������
  TxnAmt        CHAR(15)        DEFAULT ' ',
--���׽��
  Fee           CHAR(15)        DEFAULT ' ',
--������
  OrgNo         CHAR(6)        DEFAULT ' ',
--������
  TlrId         CHAR(7)        DEFAULT ' ',
--���׹�Ա
  MchID         CHAR(6)         DEFAULT ' ',
--�����̱��
  CAgtNo        CHAR(10)        DEFAULT ' ',
--��λ���
  PosNo         CHAR(5)         DEFAULT ' ',
--Ȧ������
  FTxnTm        CHAR(14)        DEFAULT ' ',
--ǰ�û�ʱ��
  TTxnTm        CHAR(14)        DEFAULT ' ',
--������ʱ��
  TxnCod        CHAR(6)         DEFAULT ' ',
--������
  TTxnCd        CHAR(6)         DEFAULT ' ',
--������������
  BusCls        CHAR(2)         DEFAULT ' ',
--ҵ������ 01:Ȧ��,02:����
  ChkFlg        CHAR(1)         DEFAULT '0',
--���˱�־
  HTxnSt        CHAR(1)         DEFAULT ' ',
--����״̬
  HRspCd        CHAR(6)         DEFAULT ' ',
--����������
  TTxnSt        CHAR(1)         DEFAULT ' ',
--������״̬
  TRspCd        CHAR(6)         DEFAULT ' ',
--������������
  TxnSts        CHAR(1)         DEFAULT 'U'
--����״̬ 0���׳ɹ���S���˳ɹ���U��ʼ��T���ɣ�C����
) ;


