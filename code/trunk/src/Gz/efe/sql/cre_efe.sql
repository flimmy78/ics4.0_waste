
-- ============================================================
--   �������ҵ��
--   Table: efeinfctl   (���翪�����Ʊ�)
-- ============================================================
CREATE TABLE efeinfctl
(
  BrNo          CHAR(6)         DEFAULT ' ',
--���к�  
  StrAddr       CHAR(12)        DEFAULT ' ',
--Դ��ַ
  DstAddr       CHAR(12)        DEFAULT ' ',
--Ŀ�ĵ�ַ
  WdoDat        CHAR(8)         DEFAULT ' ',
--��������
  ECD           CHAR(8)         DEFAULT ' ',
--�ո�����ҵ����
  CreOrg        CHAR(12)        DEFAULT ' ',
--ί�нڵ����
  OprCod        CHAR(8)         DEFAULT ' ',
--������Ա����
  DLIP          CHAR(15)        DEFAULT ' ',
--�����ǰ��IP
  DlTxt         CHAR(128)       DEFAULT ' ',
--������ע
  Status        CHAR(1)         DEFAULT '1'
--����ǩ��ǩ�˱�־ 0-ǩ�ˣ�1-ǩ��
) ;


-- ============================================================
--   �������ҵ��
--   Table: efechkinf   (���������Ϣ��)
-- ============================================================
CREATE TABLE efechkinf(  
  BrNo        CHAR(6)         DEFAULT ' ',
--���к�
  CAgtNo      CHAR(10)        DEFAULT ' ',
--��λ���
  LogNo       CHAR(14)        DEFAULT ' ',
--ǰ����ˮ��
  TLogNo      CHAR(30)        DEFAULT ' ',
--������ˮ��
  TckNo       CHAR(12)        DEFAULT ' ',
--�����ˮ��
  ECD         CHAR(12)         DEFAULT ' ',
--�ո�����ҵ����
  WDO         CHAR(8)         DEFAULT ' ',
--��������
  EDD         CHAR(3)         DEFAULT ' ',
--�������  
  JFH         CHAR(32)        DEFAULT ' ',
--�ɷѺ�
  KKB         CHAR(12)        DEFAULT ' ',
--�ۿ����к�
  ActNo       CHAR(32)        DEFAULT ' ',
--�ۿ��˻�/����
  KAT         CHAR(1)         DEFAULT ' ',
--�ۿ��˻����� 0���Թ��ʻ� 1����˽���� 2����˽���ÿ� 3����˽��ǿ� 4�����
  CUN         CHAR(3)         DEFAULT ' ',
--��������
  TxnAmt      CHAR(12)        DEFAULT ' ',
--�ۿ���
  KFG         CHAR(1)         DEFAULT '0', 
--�ۿʽ 0-���㲻�ۿ1-������ۿ�(ȱʡΪ0)
  ActNam      CHAR(64)        DEFAULT ' ', 
--�ͻ�����                              
  PCF         CHAR(1)         DEFAULT ' ', 
--���ֽɷѱ�־ 1 �����ֽɷ� 2 ����ȫ���ɷ�                                      
  MNT         CHAR(2)         DEFAULT ' ', 
--�ʽ��ֱ� ���ʽ Ĭ��01�ֽ�
  JBR         CHAR(8)         DEFAULT ' ', 
--�����˱��
  GDO         CHAR(16)        DEFAULT ' ', 
--�������Ա����                                   
  WYSB        CHAR(30)        DEFAULT ' ', 
--Ψһʶ����                                      
  SFF         CHAR(2)         DEFAULT ' ', 
--�շѷ�ʽ  
--01-�����ֽ� 02-�����ֽ� 03-�������� 04-ʵʱ���� 05-POS������
--06-֧Ʊ 07-��Ʊ 08-���� 09-ATM��                                   
  TxnCod      CHAR(6)         DEFAULT ' ', 
--������
  Status      CHAR(1)         DEFAULT 'U'
--״̬ S���˳ɹ���U��ʼ��T���ɣ�C������X����
);

-- ============================================================
--   �������ҵ��
--   Table: efechkdtl   (���������ϸ��)
-- ============================================================
CREATE TABLE efechkdtl(  
  BrNo        CHAR(6)         DEFAULT ' ',
--���к�
  LogNo       CHAR(14)        DEFAULT ' ',
--ǰ����ˮ��
  TLogNo      CHAR(30)        DEFAULT ' ',
--������ˮ��
  JFXH        CHAR(2)         DEFAULT ' ',
--�ɷ������
  JFJE        CHAR(12)        DEFAULT ' ',
--�ɷ�����
  MON         CHAR(6)         DEFAULT ' ',
--�·�  
  JLD         CHAR(5)         DEFAULT ' ',
--�������
  YSH         CHAR(16)        DEFAULT ' ',
--Ӧ��ƾ֤��
  CPS         CHAR(12)        DEFAULT ' ',
--����
  MNS         CHAR(2)         DEFAULT ' ',
--��Ѵ���
  PCC         CHAR(12)        DEFAULT ' '
--ΥԼ��
);

-- ============================================================
--   �������ҵ��
--   Table: efecusagt   (����ͻ�ǩԼ��)
-- ============================================================
CREATE TABLE efecusagt(  
  BrNo        CHAR(6)         DEFAULT ' ',
--���к�
  PAgtNo      CHAR(13)        DEFAULT ' ',
--�ͻ�Э����
  CAgtNo      CHAR(10)        DEFAULT ' ',
--��λ���
  SBN         CHAR(12)        DEFAULT ' ',
--�������к�/�ո�����ҵ����/�������ı��
  ECD         CHAR(12)        DEFAULT ' ',
--�ո�����ҵ����
  WDO         CHAR(8)         DEFAULT ' ',
--��������  
  EDD         CHAR(3)         DEFAULT ' ',
--�������
  JFH         CHAR(32)        DEFAULT ' ',
--�ɷѺ�
  UsrNam      CHAR(64)        DEFAULT ' ',
--�û�����
  KKB         CHAR(12)        DEFAULT ' ',
--�к�
  ActNo       CHAR(32)        DEFAULT ' ',
--�˻�/����
  KAT         CHAR(1)         DEFAULT ' ',
--�˻�����
  ActNam      CHAR(64)        DEFAULT ' ',
--�ͻ�����
  GPF         CHAR(1)         DEFAULT ' ',
--����/���ű�־ G:���ţ�P:����
  IdTyp       CHAR(2)         DEFAULT ' ',
--֤������
  IdNo        CHAR(32)        DEFAULT ' ',
--֤������
  ZPF         CHAR(1)         DEFAULT ' ',
--�˵��ʼ�����
  FPF         CHAR(1)         DEFAULT ' ',
--��Ʊ�ʼ�����
  JLD         CHAR(5)         DEFAULT ' ',
--�������
  FPM         CHAR(40)        DEFAULT ' ',
--��Ʊ�ʼ���
  FPC         CHAR(6)         DEFAULT ' ',
--��Ʊ�ʼ��ʱ�
  FPA         CHAR(60)        DEFAULT ' ',
--��Ʊ�ʼĵ�ַ
  ZPM         CHAR(40)        DEFAULT ' ',
--�ʵ��ʼ���
  ZPC         CHAR(6)         DEFAULT ' ',
--�ʵ��ʼ��ʱ�
  ZPA         CHAR(60)        DEFAULT ' ',
--�ʵ��ʼĵ�ַ
  YBZ         CHAR(1)         DEFAULT ' ',
--����֪ͨ��ʽ
  EML	        CHAR(64)        DEFAULT ' ',
--E-MAIL
  MOB         CHAR(30)        DEFAULT ' ',
--��ϵ�ֻ���
  TEL         CHAR(60)        DEFAULT ' ',
--��ϵ�绰
  TXT         CHAR(64)        DEFAULT ' ',
--��ע
  Status      CHAR(1)         DEFAULT ' '
--״̬  0:����;1:ע��
);


-- ============================================================
--   �������ҵ��
--   Table: efebatinf   (�������۱�)
-- ============================================================
CREATE TABLE efebatinf(  
  BrNo        CHAR(6)         DEFAULT ' ',
--���к�
  CAgtNo      CHAR(10)        DEFAULT ' ',
--��λ���
  LogNo       CHAR(14)        DEFAULT ' ',
--ǰ����ˮ��
  TLogNo      CHAR(30)        DEFAULT ' ',
--��������ˮ��
  DskNo       CHAR(12)        NOT NULL,
--���κ�
  TckNo       CHAR(12)        DEFAULT ' ',
--�����ˮ��
  ActDat      CHAR(8)         DEFAULT ' ',
--��������
  PID         CHAR(20)        DEFAULT ' ',
--����������Ϣ��ʶ
  EDD         CHAR(3)         DEFAULT ' ',
--�������
  PNO         CHAR(10)        DEFAULT ' ',
--���
  JFH         CHAR(32)        DEFAULT ' ',
--�ɷѺ�
  KKB         CHAR(12)        DEFAULT ' ',
--�ۿ����к�
  ActNo       CHAR(32)        DEFAULT ' ',
--�ۿ��˻�/����
  ActNam      CHAR(64)        DEFAULT ' ', 
--�˺ſͻ�����
  CUN         CHAR(3)         DEFAULT ' ',
--��������
  TxnAmt      CHAR(12)        DEFAULT ' ',
--�ۿ��� 
  KFG         CHAR(1)         DEFAULT ' ', 
--�ۿʽ 1-������ۿ2-���㲻�ۿ�
  DMO         CHAR(40)        DEFAULT ' ',
--˵��
  DEPT        CHAR(8)         DEFAULT ' ',
--������ҵ
  MON         CHAR(6)         DEFAULT ' ',
--�·�
  MNS         CHAR(2)         DEFAULT ' ',
--��Ѵ���
  CusNam      CHAR(40)        DEFAULT ' ',
--�ͻ�����
  GDZH        CHAR(32)        DEFAULT ' ',
--������ҵ�˺� 
  YKDF        CHAR(12)        DEFAULT ' ',
--Ӧ�۵��  
  PCC         CHAR(12)        DEFAULT ' ',
--ΥԼ��
  JLD         CHAR(5)         DEFAULT ' ',
--�������
  YSH         CHAR(16)        DEFAULT ' ',
--Ӧ��ƾ֤��                           
  WYSB        CHAR(30)        DEFAULT ' ', 
--Ψһʶ����                                                                    
  TxnCod      CHAR(6)         DEFAULT ' ', 
--������
  Status      CHAR(1)         DEFAULT 'U'
--״̬ S���˳ɹ���U��ʼ��T���ɣ�C������X����
);

-- ============================================================
--   �������ҵ��
--   Table: efechkrec   (������˼�¼��)
-- ============================================================
CREATE TABLE efechkrec(  
  BrNo        CHAR(6)         DEFAULT ' ',
--���к�
  ActDat      CHAR(8)         DEFAULT ' ',
--�������
  SndTim      CHAR(14)        DEFAULT ' ',
--����ʱ��
  LogNo       CHAR(14)        DEFAULT ' ',
--��ѯ��ˮ��
  ChkFil      CHAR(30)        DEFAULT ' ',
--�����ļ��� 
  TRspCd      CHAR(2)         DEFAULT ' ',
--����ַ��ش���
  RtnMsg      CHAR(60)        DEFAULT ' '
--����ַ�����Ϣ    
);