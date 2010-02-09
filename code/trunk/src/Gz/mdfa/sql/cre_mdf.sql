drop table MDFFILLST;
drop table MDFYHYSHZ;
drop table MDFYHYSMX;
drop table MDFTXNJNL;
drop table MDFCUSINF;
--
--01���շ����ļ��嵥
--
create table MDFFILLST
(
  FilSts   char(1)    not null,
--������( F-ʧ��  S-�ɹ� )
  LstFNm   char(40)   not null,
--�б��ļ���
  DatFNm   char(40)   not null,
--�����ļ���
  OIFlag   char(1)    not null
--���շ��ͱ�־( 0-���� 1-���� )
);
--
--02Ӧ�ջ��ܱ�
--
create table MDFYHYSHZ
(
  DatFNm   char(40)   not null,
--�����ļ���
  YSHZZT   char(1)    not null,
--Ӧ������״̬
  YSPC     char(11)   not null,
--Ӧ������
  DSJBR    char(10)   default '',
--��˰������
  PCFSSJ   char(19)   not null,
--����ʱ��
  MXBS     char(9)    not null,
--��ϸ����
  MXZJE    char(15)   not null,
--��ϸ�ܽ��
  CJBS     char(9)    default '',
--�������
  CJZJE    char(15)   default '',
--������
  JFYH     char(2)    default '',
--�ɷ�����( 01-�������� 02-�������� 03-ũҵ���� 92-��������ҵ���� 52-������� 53-��ͨ���� )
  YHJBR    char(10)   default '',
--���о�����
  JSSJ     char(19)   default '',
--���н���ʱ��
  JSMXBS   char(9)    default '',
--���н�����ϸ����
  JSMXZJE  char(15)   default '',
--���н�����ϸ�ܽ��
  JSCJBS   char(9)    default '',
--���н��ճ������
  JSCJZJE  char(15)   default '',
--���н��ճ���ܽ��
  DZBZ     char(1)    default '2',
--���˱�־( 0-���˳ɹ� 1-����ʧ�� 2-δ���� )
  PCBZ     char(30)   default '',
--��ע
  DskNo    char(12)   default '',
--���̱��
  BokDat   char(8)    default '',
  constraint PK_MDFYHYSHZ PRIMARY KEY( YSPC )
);
CREATE INDEX ni1_MDFYHYSHZ ON MDFYHYSHZ( DskNo );
--
--03Ӧ����ϸ��
--
create table MDFYHYSMX
(
  YSMXZT   char(1)    not null,
--��ϸ״̬( U-��ʼ S-�ɹ� F-ʧ�� A-������ B-������ C-���ֺ˶�ͨ�� R-���� )
  YSPC     char(11)   not null,
--��˰���͸�����Ӧ������
  YSLSH    char(18)   not null,
--��˰���͸�����Ӧ����ˮ
  SBPC     char(9)    not null,
--�籣����ԭʼӦ������
  SBLSH    char(18)   not null,
--�籣����ԭʼӦ����ˮ��
  DYSBLSH  char(18)   not null,
--��Ӧ�籣��ˮ��( ���˶���ʽΪ"����"��"����"��"������"�ҽ��>0ʱ��д���������ˮ�ţ����˶���ʽΪ"������"�ҽ��<0ʱ��д���Ӧ��������ݵ���ˮ�� )
  TBSDM    char(1)    not null,
--Ͷ��������( A-��ɽ B-Խ�� C-���� D-���� E-���� F-���� G-���� H-���� K-���� N-��ɳ P-��خ Q-���� S-�ӻ� T-��� Z-����  )
  SBBM     char(20)   not null,
--�籣����
  SSQ      char(6)    not null,
--������( 440102-��ɽ�� 440103-������ 440104-Խ���� 440105-������ 440107-������ 440111-������ 440112-������ 440113-������ 440114-��˰�� 440116-����� 440117-��ɳ�� 440181-��خ�� 440182-������ 440183-������ 440184-�ӻ��� )
  HDFS     char(1)    not null,
--�˶���ʽ( 0-���� 1-���� 3-������ 4-���ֻ����ҽ��Ϊ�� 5-���ֻ������ҽ��Ϊ�� ע�����ݻ����¼�벿�ֻ�������¼�ɶԳ��� )
  TZNY     char(6)    not null,
--̨������
  SSRQ     char(6)    not null,
--�ѿ�������
  XZDM     char(2)    not null,
--���ִ���( 11-�������ϱ��� 12-ũת�����ϱ��� 13-������ũ�����ϱ��� 21-ʧҵ���� 31-����ҽ�Ʊ��� 32-����Աҽ�Ʋ��� 33-סԺ���� 34-����ҽ�Ʊ��� 35-�ش󼲲�ҽ�Ʋ��� 36-����ҽ�Ʊ��� 37-����ҽ�� 41-���˱��� 51-�������� 15-�������ϱ��� )
  ZMDM     char(2)    not null,
--����(��Ŀ����)( 1-���� 2-��λ 3-�籣��Ϣ 4-�籣����  )
  JE       char(15)   not null,
--���
  JFZT     char(1)    not null,
--�ɷ�����( 1-���� 2-��λ )
  JFLX     char(2)    not null,
--�ɷ�����( 0-���ڽ� 1-�����Խ� 2-Ԥ�� 3-���� 4-���� 5-�ɷ���ʷ�޶� 6-���ת�� 7-�ϲ��ɷ���ʷ 8-����72���Ĳ��������ʻ���� 9-���ڹ�����Աһ���Խɷ� 10-ת���ͳ�� )
  JFFS     char(1)    default '',
--�ɷѷ�ʽ
  JFYH     char(2)    not null,
--�ɷ�����( 01-�������� 02-�������� 03-ũҵ���� 92-��������ҵ���� 52-������� 53-��ͨ���� )
  YHHH     char(10)   default '',
--�ɷѿ��������к�
  KHYH     char(40)   default '',
--�ɷѿ�����������
  YHZH     char(40)   default '',
--�ɷ������ʺ�
  YHHM     char(40)   default '',
--�ɷ������л���
  LSH      char(14)   default '',
--��ˮ��
  TZTZ     char(6)    default '',
--����̨������
  FSSJ     char(19)   default '',
--����ʱ��
  SJZT     char(4)    default '',
--����״̬
  SJLY     char(1)    default '',
--������Դ
  BZ       char(30)   default '',
--��ע
  KDM       char(2)    not null,
--���и��ݿ������п������
-- 77-�оֹ��п���� 55-�оֽ��п���� 88-�о�ũ�п���� 91-�о����п���� 11-�оֹ������ 41-�оֽ��п����
-- 81-��خ���п���� 60-��خ���п���� 01-��خũ�п���� 27-��خ���п���� 12-��خ������� 42-��خ���п����
-- 79-�������п���� 56-�������п���� 02-����ũ�п���� 28-�������п���� 13-����������� 43-�������п����
-- 78-���ǹ��п���� 57-���ǽ��п���� 04-����ũ�п���� 29-�������п���� 14-���ǹ������ 44-���ǽ��п����
-- 80-�ӻ����п���� 59-�ӻ����п���� 03-�ӻ�ũ�п���� 30-�ӻ����п���� 15-�ӻ�������� 45-�ӻ����п����
  CdFLag   char(1)   not null,
--�����־( D-�� C-�� )
  DskNo    char(12)  default '',
--���̱��
  LogNo    char(14)  default '',
--ǰ����ˮ��
  RegDat   char(8)   not null,
--��������
  BokDat   char(8)   default '',
--�������
	BokAmt   char(15)  default '',
--ʵ�۽��
	TckNo    char(11)  default '',
--�����ˮ��
  DZPC     char(11)  default '',
--��������
  JYSJ     char(19)  default '',
--���н���ʱ��
  ZSFS     char(2)   default '',
--���շ�ʽ( 02-ǰ̨���� 03-��̨���� )
	RtnFlg   char(1)   default '0',
--����״̬( 0-δ��Ӧ 1-�ѻ�Ӧ )
	YHDZLSH  char(30)  default '',
--���ж�����ˮ��
	YHFSSJ   char(19)  default '',
--���ж��˷���ʱ��
  constraint PK_MDFYHYSMX PRIMARY KEY( YSLSH )
);
--CREATE INDEX ni1_MDFYHYSMX ON MDFYHYSMX( LogNo );
CREATE UNIQUE INDEX ni1_MDFYHYSMX ON MDFYHYSMX( SBLSH,KDM );
CREATE INDEX ni2_MDFYHYSMX ON MDFYHYSMX( YSPC,YSMXZT,CDFLAG );
CREATE INDEX ni3_MDFYHYSMX ON MDFYHYSMX( TBSDM, SBBM, XZDM, TZNY, CDFLAG );
--
--
--�ۿ���ˮ��
--
--
create table MdfTxnJnl
(
  LogNo    char(14)  not null,
--ǰ����ˮ��
  TTxnCd   char(6)   not null,
--�ӿڽ�����
  TxnCod   char(6)   not null,
--ǰ�ý�����
  HTxnCd   char(6)   not null,
--����������
  TxnTyp   char(1)   not null,
--��������( N-�������� C-�������� R-�ط�����)
  OIFlag   char(1)   not null,
--�����˱�־( 0-���� 1-���� )
  BusTyp   char(6)   default '',
--ҵ������
  CrpCod   char(12)  default '',
--��λ����
  ActDat   char(8)   not null,
--�������
  CcyCod   char(3)   default 'CNY',
--���Ҵ���
  TxnAmt   char(15)  not null,
--���׽��
  ActTyp   char(1)   default '',
--�˻�����( 0-�ֽ� 1-һ��ͨ 2-��ͨ���� 4-̫ƽ�� A-��ͨ�Թ� B-������� C-�㶫���� )
  AVchTp   char(3)   default '',
--�˻�ƾ֤����
  VchCod   char(8)   default '',
--���ۺ���
  ActNo    char(21)  default '',
--�����ʺ�
  BActSq   char(5)   default '',
--һ��ͨ�˻����
  RvsNo    char(12)  default '',
--���ʺ�
  VchTyp   char(3)   default '',
--ƾ֤����
  VchNo    char(8)   default '',
--ƾ֤����
  NodNo    char(6)   default '',
--���������
  BrNo     char(6)   not null,
--���׷���
  TlrId    char(7)   not null,
--���й�Ա��
  FTxnTm   char(14)  default '',
--ǰ�ý���ʱ��
  HLogNo   char(9)   default '',
--������ˮ��
  TckNo    char(11)  default '',
--�����ˮ��
  TTxnSt   char(1)   default 'U',
--����������״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ T-��ʱ V-�����ɹ� )
  TxnSts   char(1)   default 'U',
--����״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ T-��ʱ  )
  HTxnSt   char(1)   default 'U',
--��������״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ E-��� T-��ʱ)
  HRspCd   char(6)   default '',
--������Ӧ��
  DskNo    char(12)  default '',
--���̱��
  TxnObj   char(8)   default '',
--��Сͨ��Ŀ�����
  TxnCnl   char(3)   default 'MDF',
--��������
  IsTxn    char(1)   default '',
--�Ƿ���������
  UpdFlg   char(1)   default 'Y',
--���±�־
  UpdFld   char(20)  default '',
--�����ֶ���
------������ҵ������------
------������ҵ������------
------������ҵ������------
--YSLSH    char(18)  not null,
--��˰���͸�����Ӧ����ˮ
  CdFLag   char(1)   not null,
--�����־( D-�� C-�� )
  TBSDM    char(1)   not null,
--Ͷ��������( A-��ɽ B-Խ�� C-���� D-���� E-���� F-���� G-���� H-���� K-���� N-��ɳ P-��خ Q-���� S-�ӻ� T-��� Z-����  )
  SBBM     char(20)  not null,
--�籣����
  TZNY     char(6)   not null,
--̨������
  XZDM     char(2)   default '',
--���ִ���( 11-�������ϱ��� 12-ũת�����ϱ��� 13-������ũ�����ϱ��� 21-ʧҵ���� 31-����ҽ�Ʊ��� 32-����Աҽ�Ʋ��� 33-סԺ���� 34-����ҽ�Ʊ��� 35-�ش󼲲�ҽ�Ʋ��� 36-����ҽ�Ʊ��� 37-����ҽ�� 41-���˱��� 51-�������� 15-�������ϱ��� )
  CONSTRAINT PK_MDFTXNJNL PRIMARY KEY( LogNo )
);
--
--
--�ͻ����ϱ�
--
--
create table MdfCusInf
(
	RegDat   char(8)   not null,
--�������
  TBSDM    char(1)   not null,
--Ͷ��������( A-��ɽ B-Խ�� C-���� D-���� E-���� F-���� G-���� H-���� K-���� N-��ɳ P-��خ Q-���� S-�ӻ� T-��� Z-����  )
  SBBM     char(20)  not null,
--�籣����
  JFZT     char(1)   not null,
--�ɷ�����( 1-���� 2-��λ )
  SSQ      char(6)   not null,
--������( 440102-��ɽ�� 440103-������ 440104-Խ���� 440105-������ 440107-������ 440111-������ 440112-������ 440113-������ 440114-��˰�� 440116-����� 440117-��ɳ�� 440181-��خ�� 440182-������ 440183-������ 440184-�ӻ��� )
  DWMC     char(60)  default '',
--�ɷ�������(��λ�͸���)
  GRSF     char(3)   default '',
--������ݣ��ɷ������ 70-ѧ��ǰ��ͯ 71-��Сѧ�� 72-����רѧ�� 73-����δ������ 74-�Ǵ�ҵ��Ա 75-������ 76-����ѧ����
  CBDWBM   char(8)   default '',
--���ڲα���λ����
  CBDWMC   char(100) default '',
--���ڲα���λ����
  ZJLX     char(3)   default '',
--֤������( 1-���֤ 2-���� 3-����֤ 4-ѧ��֤ 5-���� )
  ZJHM     char(25)  default '',
--֤������
  XJHM     char(40)  default '',
--ѧ������
  JFYH     char(2)   default '',
--ǩԼ�ɷ�����( 01-�������� 02-�������� 03-ũҵ���� 92-��������ҵ���� 52-������� 53-��ͨ���� )
  YHHH     char(10)  default '',
--�ɷѿ��������к�
  KHYH     char(40)  default '',
--�ɷѿ�����������
  YHZH     char(40)  default '',
--�ɷ������ʺ�
  YHHM     char(40)  default '',
--�ɷ������л���
  YB       char(6)   default '',
--�ʱ�
  DWDZ     char(100) default '',
--��ϵ��ַ
  LXR      char(10)  default '',
--��ϵ��
  LXDH     char(15)  default '',
--��ϵ�绰
--LRSJ     char(19)  default '',
--¼��ʱ��
--XGSJ     char(19)  default ''
--�޸�ʱ��
  CONSTRAINT PK_MDFCUSINF PRIMARY KEY( TBSDM,SBBM )
);
CREATE INDEX ni1_MDFCUSINF ON MDFCUSINF( ZJHM );
