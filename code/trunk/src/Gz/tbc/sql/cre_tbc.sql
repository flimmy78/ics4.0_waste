
-- ============================================================
--   �㶫�̲�ҵ��
--   Table: tbccusagt   (�̲ݿͻ�ǩԼ��)
-- ============================================================
CREATE TABLE tbccusagt(  
  BrNo        CHAR(6)         DEFAULT ' ',
--���к�
  CAgtNo      CHAR(10)        DEFAULT ' ',
--��λ���
  CustId      CHAR(30)        ,
--�̲ݹ�˾�ͻ���
  DptId       CHAR(4)         DEFAULT ' ',
--���й�˾���
  ComId       CHAR(30)        DEFAULT ' ',
--��˾���
  TCusNm      CHAR(30)        DEFAULT ' ',
--�ͻ�����
  CusTyp      CHAR(2)         DEFAULT ' ',
--�ͻ����� 01:˽�˿ͻ�,02:�Թ��ͻ�
  PasTyp      CHAR(2)         DEFAULT ' ',
--֤������ 0�����֤,1:����,2:����֤,3:ʿ��֤,4:����֤,5:��ʱ���֤,6:���ڱ�,7:����
  PasId      CHAR(18)        DEFAULT ' ',
--֤������
  LiceId      CHAR(30)        DEFAULT ' ',
--Ӫҵִ�պ�
  AccTyp      CHAR(2)         DEFAULT ' ',
--��/�˻����� 01:���ÿ�02:��ͨ��,03:��λ��,04:�����˺�,05:�Թ��˻�,06:���뿨
  ActNo       CHAR(25)        DEFAULT ' ',
--��/�˻�����
  PasFlg      CHAR(1)         DEFAULT '0',
--����У���־
  PasWrd      CHAR(10)        DEFAULT ' ',
--����
  Addres      CHAR(100)       DEFAULT ' ',
--��ϵ��ַ
  TelNum      CHAR(20)        DEFAULT ' ',
--�绰����
  DevId       CHAR(20)        DEFAULT ' ',
--�豸��
  Teller      CHAR(10)        DEFAULT ' ',
--�̲ݹ�Ա��
  OpnDat      CHAR(8)         DEFAULT ' ',
--�������� 
  ClsDat      CHAR(8)         DEFAULT ' ',
--��������
  Status      CHAR(1)         DEFAULT ' '
--״̬  0:����;1:ע��
);



-- ============================================================
--   �㶫�̲�ҵ��
--   Table: tbcbasinf   (�̲ݻ�����Ϣ��)
-- ============================================================
CREATE TABLE tbcbasinf(
  BrNo        CHAR(6)         DEFAULT ' ',
--���к�
  DptId       CHAR(4)         DEFAULT ' ',
--���й�˾���
  DptNam      CHAR(40)        DEFAULT ' ',
--��˾��λȫ��  
  DevId       CHAR(15)        DEFAULT ' ',
--�豸��
  Teller      CHAR(10)        DEFAULT ' ',
--������
  TranDt      CHAR(8)         DEFAULT ' ',
--��������
  ComKey      CHAR(16)        DEFAULT ' ',
--ͨѶ��Կ
  SigSts      CHAR(1)         DEFAULT ' '
--ǩ��״̬   0:ǩ����1:ǩ��
);

