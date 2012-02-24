
-- ============================================================
--   �������ҵ��
--   Table: efeaclrtbl   (���ݵ����������ڱ�)
-- ============================================================
CREATE TABLE efeaclrtbl
(
  BrNo          CHAR(6)         DEFAULT ' ',
--���к�  
  ClrDat        CHAR(8)         DEFAULT ' ',
--��������
  ClrTim        CHAR(6)         DEFAULT ' ',
--����ʱ��
  ClrSts        CHAR(1)         DEFAULT ' ',
--����״̬  0:����״̬��1:����״̬
  AutFlg        CHAR(1)         DEFAULT ' '
--ϵͳ��ʱ�Զ������־  0:�Զ�������Ч��1:��ֹ�Զ�����  
) ;


-- ============================================================
--   �������ҵ��
--   Table: efeaclrlog   (���ݵ����������ڱ��޸���־)
-- ============================================================
CREATE TABLE efeaclrlog
(
  BrNo          CHAR(6)         DEFAULT ' ',
--���к� 
  NodNo         CHAR(6)         DEFAULT ' ',
--�����  
  ClrDat        CHAR(8)         DEFAULT ' ',
--�޸���������
  ClrTim        CHAR(6)         DEFAULT ' ',
--�޸�����ʱ��
  ClrSts        CHAR(1)         DEFAULT ' ',
--�޸�����״̬  0:����״̬��1:����״̬
  AutFlg        CHAR(1)         DEFAULT ' ',
--�޸�ϵͳ��ʱ�Զ������־  0:�Զ�������Ч��1:��ֹ�Զ�����  
  TlrId         CHAR(8)         DEFAULT ' ',
--�޸Ĺ�Ա
  LogDat        CHAR(8)         DEFAULT ' ',
--�޸�����ʱ��
  LogTim        CHAR(6)         DEFAULT ' '
--�޸�����ʱ��
) ;


-- ============================================================
--   �������ҵ��
--   Table: efeaclrdtl   (���ݵ���������ϸ��)
-- ============================================================
CREATE TABLE efeaclrdtl
(
  BrNo          CHAR(6)         DEFAULT ' ',
--���к�
  NodNo         CHAR(6)         DEFAULT ' ',
--����� 
  TlrId         CHAR(8)         DEFAULT ' ',
--�����Ա
  CAgtNo        CHAR(10)        DEFAULT ' ',
--���㵥λЭ���
  ClrDat        CHAR(8)         DEFAULT ' ',
--��������
  ClrTim        CHAR(6)         DEFAULT ' ',
--����ʱ��
  ClrRst        CHAR(1)         DEFAULT ' ',
--�������  0:δ���㣻1:������
  ClrTyp        CHAR(1)         DEFAULT ' ',
--��������  0:�Զ����㣻1:�ֹ�����
  ClrTot        CHAR(8)         DEFAULT ' ',
--�������
  ClrAmt        CHAR(15)        DEFAULT ' '
--������
) ;
