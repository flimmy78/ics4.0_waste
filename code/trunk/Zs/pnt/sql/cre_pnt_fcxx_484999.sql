drop table PntFccz;
drop table pntFcgk;
drop table PntHzfczh;

--����ר���ֳ���Ϣ�ļ�
create table PntFccz
(
  BankCd       char(30)   default '',
--���б���                           
  RcvAct       char(50)   default '',
--����˻�                           
  TxnDat       char(8)    not null,
--�ֳ�����                           
  CityCd       char(12)   default '',
--�ڶα�ʶ(�����������)             
  TotNum       char(10)   default '',
--�ܱ���                             
  TotAmt       char(16)   default '',
--�ܽ��                             
  ActNam       char(50)   default '',
--�˻�����                           
  ActBnk       char(100)  default '',
--�˻���������                       
  ActNo        char(50)   default '',
--�˺�                               
  TitNum       char(10)   default '',
--����                               
  TitAmt       char(16)   default '',
--�ֳ��ܽ��                         
  TCrpCd       char(30)   default '',
--ִ�յ�λ����
  TCrpNm       char(100)  default '',
--ִ�е�λ����                       
  PrjCod       char(14)   default '',
--�շ���Ŀ����                       
  PrjNam       char(100)  default '',
--�շ���Ŀ����                       
  DtlAmt       char(16)   default '',
--�ֳɽ��                           
  DtlSts       char(1)    default '',
--�ֳɱ�ʶ(1δ�ֳ�,2�ѷֳ�)
  DtlDat       char(8)    default '',
--��������
  DtAmt        char(16)   default ''
--���˽��  
);

--����ֳ���Ϣ�ļ�
create table PntFcgk
(
  BankCd       char(30)   default '',
--���б���
  RcvAct       char(50)   default '',
--����˻�
  TxnDat       char(8)     not null,
--�ֳ�����
  CityCd       char(12)   default '',
--�ڶα�ʶ(�����������)
  TotNum       char(10)   default '',
--�ܱ���
  TotAmt       char(16)   default '',
--�ܽ��
  ActNam       char(50)   default '',
--�˻�����
  ActBnk       char(100)  default '',
--�˻���������
  ActNo        char(50)   default '',
--�˺�
  TitNum       char(10)   default '',
--�ܱ���
  TitAmt       char(16)   default '',
--�ֳ��ܽ��
  SubCod       char(9)    default '',
--Ԥ���Ŀ����
  SubNam       char(100)  default '',
--Ԥ���Ŀ����
  PrjCod       char(14)   default '',
--�շ���Ŀ����
  PrjNam       char(100)  default '',
--�շ���Ŀ����
  DtlAmt       char(16)   default '',
--�ֳɽ��
  DtlSts       char(1)    default '',
--�ֳɱ�ʶ(1δ�ֳ�,2�ѷֳ�)
  DtlDat       char(8)    default '',
--��������
  DtAmt        char(16)   default ''
--���˽��  
);

--��˰ϵͳ�����Ļ��ֳܷɹ����ļ�
create table PntHzfczh
(
  ZHBankCd    char(30)   default '',
--ר�����б���
  ZHBankNm    char(100)  default '',
--ר����������
  TxnDat      char(8)     not null,
--�ֳ�����
  TotNum      char(12)   default '',
--�ڶ�����
  ZHActNo     char(100)  default '',
--ר���˻�����
  ZHActNm     char(50)   default '',
--ר���˺�
  TotAmt       char(16)   default '',
--�ֳ��ܽ��
  DSBankNo    char(30)    default '',
--�������б���
  DSBankNm    char(100)   default '',
--������������
  DSActNo     char(50)    default '',
--�����˺�
  ZCKM        char(20)    default '',
--֧����Ŀ
  JJCK        char(20)    default '',
--���ÿ�Ŀ
  TitNum       char(10)   default '',
--�ܱ���
  TitAmt       char(16)   default '',
--�ֳɽ��
  TCrpCd       char(20)   default '',
--ִ�յ�λ����
  TCrpNm       char(100)  default '',
--ִ�е�λ����                       
  PrjCod       char(14)   default '',
--�շ���Ŀ����                       
  PrjNam       char(100)  default '',
--�շ���Ŀ����                       
  DtlAmt       char(16)   default '',
--�ֳɽ�� 
  RevDat       char(10)   default '',
--�շ����� 
  DtlSts       char(1)    default ''
--�ֳɱ�ʶ(1δ�ֳ�,2�ѷֳ�)                        
);
		
