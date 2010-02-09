drop table PfaQuoBok001;
drop table PfaVchDtl001;
drop table PfaCmdSum102;
drop table PfaQuoBok102;
drop table PfaVchDtl102;
--
--
--ʡ�����·���ȵǼǱ�
--
--
create table PfaQuoBok001
(
  QuoSts   char(1)   not null,
--��Ч״̬ (0-δ���� 1-�Ѹ��� 2-�Ѵ�ӡ��Ȩ����֪ͨ��)
  PfaSub   char(3)   not null,
--����Ӧ�ô���
  Year     char(4)   not null,
--��
  TSeqNo   char(20)  not null,
--�ƻ�����
  BCusId   char(18)  not null,
--����Ԥ�㵥λ����
  SubCod   char(20)  default '',
--Ԥ���Ŀ���루֧�����ܱ��룩
  SubNam   char(60)  default '',
--Ԥ���Ŀ����
  EConTp   char(20)  default '',
--���÷���
  PrjCod   char(20)  default '',
--��Ŀ����
  DptCod   char(20)  default '',
--ҵ����(ָ����Դ)
  Mon      char(2)   not null,
--��
  TxnFlg   char(1)   default '',
--�������� (0-���� 1-����)
  QuoAmt   char(15)  not null,
--��Ƚ��
  QuoSmr   char(254) default '',
--��ע
  RegDat   char(8)   not null,
--�Ǽ�(�´�)����
  OTSeqNo  char(20)  default '',
--ԭ�ƻ�����
  QuoTim   char(14)  not null,
--�´�ʱ��
  ABnkNo   char(10)  default '',
--��Ȩ���б��루�������б��룩
  ActNo    char(21)  default '',
--�����˺�
  AmtTyp   char(20)  default '',
--�ʽ����� (0001-Ԥ���� 0002-Ԥ���� 0003-�Գ��ʽ� 0004-��Ϣ����)
  RtnFlg   char(1)   not null,
--���ر�־ (0-δ�� 1-�ѻ�)
  PrtCnt   char(2)   default '00',
--��ӡ����
  RegId    char(7)   default '',
--¼����
  ChkId    char(7)   default '',
--ȷ����
  NodNo    char(6)   default '',
--ȷ�ϲ���
  BrNo     char(6)   not null,
--ȷ�Ϸ��к�
  ActDat   char(8)   default '',
--ȷ�ϻ������
  UpdFlg   char(1)   default '0',
--���±�־( 0-δ�������� 1-�Ѹ������� )
  BokIdx   char(6)   default '',
--����
  QuoId    char(20)  default '',
--���ID
  CONSTRAINT PK_PFAQUOBOK001 PRIMARY KEY( PfaSub,Year,TSeqNo )
);
--
--
--ʡ����֧��ƾ֤��ϸ��
--
--
create table PfaVchDtl001
(
  DtlSts   char(1)   default 'U',
--����״̬( U-��ʼ 0-�Ǽ� 1-ȷ�� 2-ʹ�� 3-���� 4-�˻� 5-����(��Ա����ȡ��) )
  PfaSub   char(3)   not null,
--��������
  Year     char(4)   not null,
--�������
  VchDat   char(8)   not null,
--֧��������
  AVchCd   char(30)  not null,
--֧������
  QuoId    char(20)  default '',
--���ID
  PayNam   char(60)  default '',
--������ȫ��
  PayAct   char(35)  default '',
--�������ʺ�
  PayBNm   char(60)  default '',
--�����˿�������
  PyeNam   char(60)  default '',
--�տ���ȫ��
  PyeAct   char(35)  default '',
--�տ����˺�
  PyeBNm   char(60)  default '',
--�տ��˿�������
  OIFlag   char(1)   not null,
--���׷��� (O-֧�� R-�˻� I-�����տ�) 
  DtlAmt   char(15)  not null,
--֧�����
  UseAmt   char(15)  default '0',
--ʵ��ʹ�ý��
  BCusId   char(18)  not null,
--����Ԥ�㵥λ����
  FCusId   char(18)  not null,
--һ��Ԥ�㵥λ����
  DtlSmr   char(254) default '',
--��;
  SubCod   char(20)  default '',
--Ԥ���Ŀ(���ܷ���)
  EConTp   char(20)  default '',
--���÷������
  PrjCod   char(20)  default '',
--Ԥ����Ŀ����
  DptCod   char(20)  default '',
--ҵ����(ָ����Դ)
  ChkFlg   char(1)   default '',
--����ȷ�ϱ�־( 0-δȷ�� 1����ȷ�� )
  AmtTyp   char(20)  not null,
--�ʽ����� (0001-Ԥ���� 0002-Ԥ���� 0003-�Գ��ʽ� 0004-��Ϣ����)
  VchTyp   char(3)   default '',
--ƾ֤����
  VchNo    char(8)   default '',
--����ƾ֤���
--UdwDat   char(8)   default '',
--ǩ������
  TPayTp   char(20)  default '',
--֧������
  StlMod   char(2)   default '',
--���㷽ʽ ( 01-ת�� 02-�ֽ� 03-�Ż� 04-��� 05-��Ʊ 06-��Ʊ  99-����)
  TVchTp   char(1)   default '0',
--ƾ֤����( 0-��ͨ 1-�޶� 2-���� )
  OpAVCd   char(30)  default '',
--����֧��ƾ֤����(����)
--����Ҫ��
  RegDat   char(8)   not null,
--�Ǽ�����
  DtlTim   char(14)  not null,
--ƾ֤¼��ʱ��
  RefCod   char(2)   default '',
--�˻ش���
  PfaKnd   char(1)   not null,
--֧������ (0-ֽ�� 1-����)
  ActDat   char(8)   default '',
--�������
  PrtNum   char(2)   default '00',
--��ӡ����
  AVchNo   char(8)   default '',
--��Ȩƾ֤�ǼǺţ�������ϵͳ���ɣ�
  ClrSts   char(1)   default '0',
--�����־( 0-δ���� 1-������ 2-�ڲ�������� 3-��������ȷ�� 4-��������ʧ�� ) 
  ClrBNo   char(10)  default '',
--��������
  ClrDat   char(8)   default '',
--�ڲ���������
  PfaDat   char(8)   default '',
--������������
  RtnFlg   char(1)   default '0',
--��Ӧ��־ (0-δ�� 1-�ѻ�)
  DtlIdx   char(6)   default '',
--������
  CONSTRAINT PK_PFAVCHDTL001 PRIMARY KEY( PfaSub, Year, AVchCd )
);
create index ni1_PfaVchDtl001 on PfaVchDtl001( PfaSub, Year, AVchNo );
create index ni2_PfaVchDtl001 on PfaVchDtl001( PfaSub, PfaDat, ClrSts );
--
--
--Խ��������ָ�����α�
--
--
create table PfaCmdSum102
(
  CmdSts   char(1)   not null,
--״̬( U-δ���� S-����ͨ�� F-����ʧ�� )
  ACmdTp   char(1)   not null,
--ָ������(1-����� 2-֧���� )
  Year     char(4)   not null,
--�������
  ACmdNo   char(8)   not null,
--���κ�
  PfaLvl   char(2)   not null,
--��������( 00-�����в����� 01-�����в����� 02-������������ 03-������������ 04-�ӻ��в����� 05-����������� 06-������������ 07-Խ���������� 08-������������ )
  OrnAmt   char(15)  not null,
--�ϼƽ��
  RegTim   char(14)  not null,
--�´�����
  OrnCnt   char(6)   not null,
--����
  BilAth   char(10)  not null,
--�Ƶ���
  BankNo   char(12)  not null,
--���н����к�
  BankCd   char(21)  not null,
--�а����к�
  BankNm   char(40)  not null,
--�а�������
  MacKey   char(100) not null,
--У��λ
  constraint PK_PFACMDSUM102 PRIMARY KEY( Year,ACmdNo )
);
--
--
--Խ���������������ϸ��
--
--
create table PfaQuoBok102
(
  QuoSts   char(1)   not null,
--״̬( 0-δ���� 1-������� )
  Year     char(4)   not null,
--�������
  ACmdNo   char(8)   not null,
--���κ�
  TBusTp   char(4)   not null,
--ҵ������( 0101-ֱ��֧�����´� 0102-ֱ��֧��֧����� 0103-ֱ��֧������ֹ 0104-�ʽ��˿� )
--ҵ������( 0105-��Ȩ����´� 0106-��Ȩ��Ȼ��� )
--ҵ������( 0200-����֧�� 0201-��ֹ֧�� 0202-�ʽ���� 0203-������ )
  TVchNo   char(20)  not null,
--֧��ƾ֤���
  TQuoNo   char(20)  not null,
--��ȱ��
  QuoId    char(20)  not null,
--��ӦԤ��ָ����
  ClrBNm   char(80)  not null,
--������������
  ClrANm   char(80)  not null,
--�����л���
  ClrAct   char(40)  default '',
--�������˺�
  AgtBNm   char(80)  not null,
--��λ������
  ActNm    char(80)  not null,
--��λ�������ʻ�����
  ActNo    char(40)  not null,
--��λ�������˺�
  BCusId   char(8)   not null,
--Ԥ�㵥λ����
  BCusNm   char(100) not null,
--Ԥ�㵥λ����
  FCusId   char(8)   not null,
--һ��Ԥ�㵥λ����
  FCusNm   char(100) not null,
--һ��Ԥ�㵥λ����
  AmtTyp   char(8)   not null,
--�ʽ���Դ����
  AmtNam   char(50)  not null,
--�ʽ���Դ����
  TypCod   char(2)   not null,
--���ܿ�Ŀ���ͱ���
  TypNam   char(30)  not null,
--���ܿ�Ŀ��������
  SubCod   char(20)  not null,
--���ܷ����Ŀ����
  SubNam   char(60)  not null,
--���ܷ����Ŀ����
  PrjCod   char(8)   default '',
--��Ŀ����
  PrjNam   char(60)  default '',
--��Ŀ����
  QuoAmt   char(16)  not null,
--���
  TPayTp   char(3)   not null,
--֧�����ͱ���( 001-ͳ������ 002-��Ա����֧�� 003-ר��֧�� 004-�����ɹ� 005-����֧�� )
  TPayNm   char(30)  default '',
--֧����������
  DptCod   char(3)   not null,
--ָ����Դ����
  DptNam   char(30)  not null,
--ָ����Դ����
  EConTp   char(7)   default '',
--���÷����Ŀ����
  EConNm   char(60)  default '',
--���÷����Ŀ����
  QuoSmr   char(100) default '',
--��ע
  BasFlg   char(1)   not null,
--�Ƿ������ص�λ������( 0-����1-������ )
  BActNm   char(50)  default '',
--��λ����������
  BActNo   char(30)  default '',
--��λ�������ʺ�
  OpnBNm   char(30)  default '',
--��λ����������
  MacKey   char(100) not null,
--У��λ
  RsFld1   char(30)  default '',
--Ԥ���ֶ�1
  RsFld2   char(30)  default '',
--Ԥ���ֶ�1
  Mon      char(2)   default '',
--��
  TxnFlg   char(1)   default '',
--�������� (0-���� 1-����)
  ActDat   char(8)   default '',
--�������
  PfaSub   char(3)   not null,
--��������
  RegDat   char(8)   not null,
--��������
  UpdFlg   char(1)   default '0',
--���������־( 0-δ���� 1-�Ѹ��� )
  ChkDat   char(8)   default '',
--��������
  ChkId    char(7)   default '',
--������Ա
  RtnCod   char(3)   default '',
--������( 000-��ʾ�ɹ� 001-��ʾʧ�� 002-��ʾע�� )
  RtnMsg   char(60)  default '',
--�������
  PrtCnt   char(2)   default '00',
--��ӡ����
  BrNo     char(6)   default '',
--���к�
  constraint PK_PFAQUOBOK102 PRIMARY KEY( Year, ACmdNo, TVchNo, TQuoNo )
);
--create index ni1_PfaQuoBok102 on PfaQuoBok102( Year,ACmdNo );
--
--
--Խ��������֧������ϸ��
--
--
create table PfaVchDtl102
(
  DtlSts   char(1)   default 'U',
--����״̬( U-��ʼ 0-�Ǽ� 1-ȷ�� 2-ʹ�� 3-���� 4-�˻� 5-����(��Ա����ȡ��) )
  PfaSub   char(3)   not null,
--��������
  Year     char(4)   not null,
--�������
  ACmdNo   char(8)   default '',
--���κ�
  TLogNo   char(20)  default '',
--��ˮ��
  TBusTp   char(4)   default '',
--ҵ������
  DtlTim   char(14)  not null,
--֧������
  TQuoNo   char(20)  default '',
--��ȱ��
  QuoId    char(20)  default '',
--��ӦԤ��ָ����
  TypCod   char(2)   default '',
--���ܿ�Ŀ���ͱ���
  TypNam   char(40)  default '',
--���ܿ�Ŀ��������
  AVchCd   char(20)  not null,
--֧��ƾ֤��
  PayNam   char(60)  not null,
--������ȫ��
  PayAct   char(35)  not null,
--�������ʺ�
  PayBNm   char(60)  not null,
--�����˿�������
  PyeNam   char(60)  not null,
--������ȫ��
  PyeAct   char(35)  not null,
--�������ʺ�
  PyeBNm   char(60)  not null,
--�����˿�������
  DtlAmt   char(15)  not null,
--��Ʊ���
  UseAmt   char(15)  default '',
--ʵ�ý��
  StlMod   char(2)   default '',
--���㷽ʽ ( 01-ת�� 02-�ֽ� 03-�Ż� 04-��� 05-��Ʊ 06-��Ʊ 99-����)
  TVchTp   char(1)   default '0',
--ƾ֤����( 0-��ͨ 1-�޶� 2-���� )
  FCusId   char(8)   default '',
--һ��Ԥ�㵥λ����
  FCusNm   char(60)  default '',
--һ��Ԥ�㵥λ����
  BCusId   char(8)   default '',
--Ԥ�㵥λ����
  BCusNm   char(60)  default '',
--Ԥ�㵥λ����
  SubCod   char(20)  default '',
--���ܷ����Ŀ����
  SubNam   char(80)  default '',
--���ܷ����Ŀ����
  Usage    char(40)  default '',
--��;
  DtlSmr   char(60)  default '',
--��ע
  TPayTp   char(20)  default '',
--֧�����ͱ���
  TPayNm   char(30)  default '',
--֧����������
  DptCod   char(3)   default '',
--ָ����Դ����
  DptNam   char(30)  default '',
--ָ����Դ����
  EConTp   char(6)   default '',
--���÷����Ŀ����
  EConNm   char(30)  default '',
--���÷����Ŀ����
  AmtTyp   char(8)   default '',
--�ʽ���Դ����
  AmtNam   char(30)  default '',
--�ʽ���Դ����
  PrjCod   char(8)   default '',
--��Ŀ����
  PrjNam   char(50)  default '',
--��Ŀ����
  StlNam   char(20)  default '',
--���㷽ʽ����
  VchTyp   char(3)   default '',
--ƾ֤����
  VchNo    char(20)  default '',
--Ʊ�ݺ���
  VchDat   char(8)   default '',
--Ʊ������
  MacKey   char(64)  default '',
--У��λ
  RsFld1   char(100) default '',
--Ԥ���ֶ�1
  RsFld2   char(100) default '',
--Ԥ���ֶ�1
  OIFlag   char(1)   default '',
--���׷��� (O-֧�� R-�˻� I-�����տ�) 
  AVchNo   char(8)   default '',
--��Ȩƾ֤�ǼǺţ�������ϵͳ���ɣ�
  LogNo    char(14)  default '',
--���ʶ�Ӧǰ����ˮ
  ActDat   char(8)   not null,
--�������
  RegId    char(7)   not null,
--�Ǽǹ�Ա
  BokId    char(7)   default '',
--���ʹ�Ա
  BokTck   char(11)  default '',
--������ˮ��
  ChkId    char(7)   default '',
--���˹�Ա
  NodNo    char(6)   default '',
--���źţ�֧����ȷ�ϲ��ţ�
  RegDat   char(8)   not null,
--�Ǽ�����
  AVchTm   char(14)  not null,
--ƾ֤¼��ʱ��
  RefCod   char(2)   default '',
--�˻ش���
--PfaKnd   char(1)   not null,
--֧������ (0-ֽ�� 1-����)
  ClrSts   char(1)   default '0',
--�����־( 0-δ���� 1-������ 2-�ڲ�������� 3-��������ȷ�� 4-��������ʧ�� )
  ClrBNo   char(10)  default '',
--��������
  ClrDat   char(8)   default '',
--�ڲ���������
  PfaDat   char(8)   default '',
--������������
  DtlIdx   char(6)   default ''
--������
--  CONSTRAINT PK_PFAVCHDTL102 PRIMARY KEY( PfaSub, Year, TLogNo )
);
