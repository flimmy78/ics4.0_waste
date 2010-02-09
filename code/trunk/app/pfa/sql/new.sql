drop table PfaQuoBok001;
drop table PfaVchDtl001;
drop table PfaTotChk001;
drop table PfaDtlChk001;
--
--
--�㶫ʡ������ȵǼǱ�
--
--
create table PfaQuoBok001
(
  TActDt   char(8)   default '',
--��������
  TPkgNo   char(16)  default '',
--����ˮ��
	QuoKey   char(16)  not null,
--����(�뽻����ˮ�ŵ�ֵ)
	AQuoCd   char(60)  not null,
--ƾ֤���
	QuoId    char(16)  not null,
--���ID
  QuoSmr   char(100) default '',
--��ע
  SubCod   char(30)  default '',
--Ԥ���Ŀ���루֧�����ܱ��룩
  DptCod   char(30)  default '',
--ҵ����(ָ����Դ)
  BCusId   char(30)  not null,
--����Ԥ�㵥λ����
  EConTp   char(30)  default '',
--���÷���
	BilDat   char(8)   default '',
--�ƶ�����
  Mon      char(2)   not null,
--��
  PrjCod   char(20)  default '',
--��Ŀ����
  Year     char(4)   not null,
--��
  AmtKnd   char(20)  default '',
--�ʽ����� (0001-Ԥ���� 0002-Ԥ���� 0003-�Գ��ʽ� 0004-��Ϣ����)
  QuoAmt   char(15)  not null,
--��Ƚ��
---
---����Ҫ��
---
  QuoSts   char(1)   not null,
--��Ч״̬ (0-δ���� 1-�Ѹ��� 2-�Ѵ�ӡ��Ȩ����֪ͨ��)
  PfaSub   char(3)   not null,
--����Ӧ�ô���
  TxnFlg   char(1)   default '',
--�������� (0-���� 1-����)
  RegDat   char(8)   not null,
--�Ǽ�(�´�)����
  QuoTim   char(14)  not null,
--�´�ʱ��
  ABnkNo   char(10)  default '',
--��Ȩ���б��루�������б��룩
  ActNo    char(21)  default '',
--�����˺�
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
  CONSTRAINT PK_PFAQUOBOK001 PRIMARY KEY( PfaSub,Year,QuoKey )
);
--
--
--�㶫ʡ����֧��ƾ֤��ϸ��
--
--
create table PfaVchDtl001
(
  TActDt   char(8)   default '',
--��������
  TPkgNo   char(16)  default '',
--����ˮ��
	DtlKey   char(16)  not null,
--����(�뽻����ˮ�ŵ�ֵ)
  AVchCd   char(30)  not null,
--֧������
  MdAVCd   char(30)  default '',
--����ƾ֤����
  SubCod   char(30)  default '',
--Ԥ���Ŀ(���ܷ���)
  DtlAmt   char(15)  default '',
--֧�����
	TBusTp   char(30)  default '',
--ҵ������
  DptCod   char(30)  default '',
--ҵ����(ָ����Դ)
  BCusId   char(30)  default '',
--����Ԥ�㵥λ����
  EConTp   char(30)  default '',
--���÷������
  AmtKnd   char(30)  default '',
--�ʽ����� (0001-Ԥ���� 0002-Ԥ���� 0003-�Գ��ʽ� 0004-��Ϣ����)
  PyeAct   char(35)  default '',
--�տ����˺�
  PyeNam   char(60)  default '',
--�տ���ȫ��
  PyeBNm   char(60)  default '',
--�տ��˿�������
  VchDat   char(8)   not null,
--֧��������
  PayAct   char(35)  default '',
--�������ʺ�
  PayNam   char(60)  default '',
--������ȫ��
  PayBNm   char(60)  default '',
--�����˿�������
  PayBId   char(30)  default '',
--���λ����
  PrjCod   char(30)  default '',
--Ԥ����Ŀ����
  DtlSmr   char(100) default '',
--��;
  VchNo    char(8)   default '',
--����ƾ֤���
	QuoId    char(16)  not null,
--���ID
---
---����Ҫ��
---
  DtlSts   char(1)   default 'U',
--����״̬( R-������ U-��ʼ 0-�Ǽ� 1-ȷ�� 2-ʹ�� 3-���� 4-�˻� 5-����(��Ա����ȡ��) )
  PfaSub   char(3)   not null,
--��������
  Year     char(4)   not null,
--�������
  OIFlag   char(1)   not null,
--���׷��� (O-֧�� R-�˻� I-�����տ�) 
  UseAmt   char(15)  default '0',
--ʵ��ʹ�ý��
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
  CONSTRAINT PK_PFAVCHDTL001 PRIMARY KEY( PfaSub, Year, DtlKey )
);
create index ni1_PfaVchDtl001 on PfaVchDtl001( PfaSub, Year, AVchNo );
create index ni2_PfaVchDtl001 on PfaVchDtl001( PfaSub, PfaDat, ClrSts );
create unique index ni3_PfaVchDtl001 on PfaVchDtl001( PfaSub, Year, AVchCd );
--
--
--�㶫ʡ����֧�����ʶ��ʽ��
--
--
create table PfaTotChk001
(
  TActDt   char(8)   default '',
--��������
  TPkgNo   char(16)  default '',
--����ˮ��
  TotKey   char(16)  not null,
--����
	SubCod   char(30)  default '',
--��Ŀ
	ChkFlg	 char(1)   default '',
--���ʱ�ʶ��0-֧�������ۼ�֧�����޲��죻1-֧������в��죻2-�ۼ�֧������в��죻
--          3-��������ȱʧ������¼��4-֧������ȱʧ������¼��
  BnkCAmt  char(15)  defautl '',
--��Ѯ���£�����֧�����
  BnkTAmt  char(15)  default '',
--�����ۼ�֧�����
  PfaCAmt  char(15)  default '',
--��Ѯ���£�֧����֧�����
  PfaTAmt  char(15)  default '',
--֧�����ۼ�֧�����
  DptCod   char(30)  default '',
--���ұ���
	DffCAmt  char(15)  default '',
--��Ѯ���£�֧�������
	DffTAmt  char(15)  default '',
--�ۼ�֧�������
  BCusId   char(30)  default '',
--��λ����
  MonFlg   char(10)  default '',
--�£�Ѯ����ǰ��λ������(01-12)������λ����Ѯ(00���£�01����Ѯ��02����Ѯ��03����Ѯ)��
  PayMod   char(30)  default '',
--֧����ʽ
  PrjCod   char(30)  default '',
--��Ŀ����
  RtnKey   char(30)  default '',
--��������
  Year     char(4)   default '',
--���
  AmtKnd   char(30)  default '',
--�ʽ�����
  PfaSub   char(3)   not null,
--��������
  CONSTRAINT PK_PFATOTCHK001 PRIMARY KEY( PfaSub, Year, TotKey )
);
--
--
--�㶫ʡ����֧����ϸ���ʽ��
--
--
create table PfaDtlChk001
(
  TActDt   char(8)   default '',
--��������
  TPkgNo   char(16)  default '',
--����ˮ��
  DtlKey   char(16)  not null,
--����
	SubCod   char(30)  default '',
--��Ŀ
	ChkFlg	 char(1)   default '',
--���ʱ�ʶ��0-֧�������ۼ�֧�����޲��죻1-֧������в��죻2-�ۼ�֧������в��죻
--          3-��������ȱʧ������¼��4-֧������ȱʧ������¼��
  BnkAmt   char(15)  defautl '',
--����֧�����
  PfaAmt   char(15)  default '',
--֧����֧�����
  DptCod   char(30)  default '',
--���ұ���
	DffAmt   char(15)  default '',
--֧�������
  BCusId   char(30)  default '',
--��λ����
  PayMod   char(30)  default '',
--֧����ʽ
  PrjCod   char(30)  default '',
--��Ŀ����
  RtnKey   char(30)  default '',
--��������
  PfaDat   char(8)   default '',
--֧������
  AmtKnd   char(30)  default '',
--�ʽ�����
  PfaSub   char(3)   not null,
--��������
  CONSTRAINT PK_PFADTLCHK001 PRIMARY KEY( PfaSub, Year, DtlKey )
);
