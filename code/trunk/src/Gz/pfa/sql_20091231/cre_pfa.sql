drop table PfaSubCfg;
drop table PfaOrgSts;
drop table PfaCusInf;
drop table PfaCodInf;
drop table PfaQuoBal;
drop table PfaVchBok;
drop table PfaTxnJnl;
drop table PfaClrRec;
drop table PfaClrJnl;
drop table PfaRptTbl;
drop table PfaCusAgr;
drop table PfaCrdInf;
drop table PfaCrdTxn;
drop table PfaCrdDtl;
drop table PfaCrdJnl;
--
--
--������������к�(���Ʊ�)
--
--
create table PfaSubCfg
(
  PfaSub      char(3)   not null,
--����Ӧ�ô���
  PfaNam      char(60)  not null,
--��������
  BrNo        char(6)   not null,
--���к�
  BrNm        char(60)  not null,
--��������
  OpnSts      char(1)   not null,
--����״̬ (0-�ѿ��� 1-�ѹ���)
  BokFlg      char(1)   not null,
--���ʱ�־( 0-���� 1-������ )
  PreDat      char(8)   not null,
--��һ�������
  CurDat      char(8)   not null,
--��ǰ��������
  NxtDat      char(8)   not null,
--��һ�������
  OprTm       char(14)  not null,
--����ʱ��
  AgtNod      char(6)   not null,
--��������
  ClrNod      char(6)   not null,
--���������
  PmsSeq      char(5)   not null,
--������ʷֻ����
  BepSeq      char(5)   not null,
--С�����ʷֻ����
  RActSq      char(5)   not null,
--26201���ջ���ţ����㸶�
  ClrAct      char(21)  not null,
--�ڲ������ʺ�
  ClrNam      char(60)  not null,
--�ڲ����㻧��
  ClrBTp      char(1)   not null,
--�����б�( 0-ϵͳ�� 1-ϵͳ�� )
  ClrMod      char(1)   not null,
--���㷽ʽ( 0-�������� 1-��֧���� )
  PfaKnd      char(1)   not null,
--֧������( 0-ֽ�� 1-���� )
  SOpnBk      char(12)  not null,
--�������к�
  SOpnNm      char(60)  not null,
--����������
  RcvAct      char(32)  not null,
--�����տ����˺�
  RcvNam      char(60)  not null,
--�����տ�������
  RbkNo       char(12)  not null,
--�տ����к�
  RbkNm       char(60)  not null,
--�տ�������
  FldNm1      char(10)  default '',
--����������
  FldNm2      char(10)  default '',
--����������
  FldNm3      char(10)  default '',
--����������
  FldNm4      char(10)  default '',
--����������
  FldNm5      char(10)  default '',
--����������
  FldNm6      char(10)  default '',
--����������
  FldNm7      char(10)  default '',
--����������
  FldNm8      char(10)  default '',
--����������
  FldNm9      char(10)  default '',
--����������
  RtnSeq      char(2)   default '00',
--�ļ����շ������
  RtnFlg      char(1)   default '0',
--���ر�־ (0-δ�� 1-�ѻ�)
  CONSTRAINT PK_PFASUBCFG PRIMARY KEY( PfaSub )
);
--
--
--����״̬��
--
--
create table PfaOrgSts
(
  BrNo        char(6)   not null,
--���к�
  PfaSub      char(3)   not null,  
--����Ӧ�ô���(001-������� 002-ʡ������ 003-�м����� 004-��������)
  OrgNod      char(6)   not null,
--������
  OrgNam      char(60)  not null,
--��������
  SgnFlg      char(1)   not null,
--ǩ��״̬ (0-��ǩ�� 1-ǩ��)
  BokFlg      char(1)   not null,
--���ʱ�־( 0-���� 1-������ )
  OrgTyp      char(1)   default '',
--��������
  ActDat      char(8)   not null,
--ǩ������
  CONSTRAINT PK_PFAORGSTS PRIMARY KEY( PfaSub,BrNo,OrgNod )
);
--
--
--Ԥ�㵥λ��Ϣ��
--
--
create table PfaCusInf
(
  CusSts      char(1)   not null,
--�˻�״̬( 0-��Ч 1-��Ч )
  PfaSub      char(3)   not null,
--����Ӧ�ô���
  BCusId      char(18)  not null,
--����Ԥ�㵥λ����
  BCusNm      char(60)  not null,
--Ԥ�㵥λ����
  TCusId      char(20)  default '',
--��λ������(��֯�ṹ����)
  ProId       char(18)  default '',
--�ϼ�Ԥ�㵥λ����
  ProNam      char(60)  default '',
--�ϼ�Ԥ�㵥λ����
  FCusId      char(18)  default '',
--һ��Ԥ�㵥λ����
  FCusNm      char(60)  default '',
--һ��Ԥ�㵥λ����
  ActNo       char(21)  default '',
--Ԥ�㵥λ�˺�
  ActNam      char(60)  default '',
--Ԥ�㵥λ�˺�����
  CusLvl      char(1)   default '',
--��λ����
  OpnNod      char(6)   default '',
--�������ź�
  BrNo        char(6)   not null,
--���к�
  OpnBNm      char(60)  default '',
--������������
  Addr        char(60)  default '',
--Ԥ�㵥λ��ַ
  Smr         char(60)  default '',
--��ע����ϵ�ˡ��绰�ȣ�
  RegDat      char(8)   default '',
--�Ǽ�����
  AmtTyp      char(20)  default '',
--�ʽ����� (0001-Ԥ���� 0002-Ԥ���� 0003-�Գ��ʽ� 0004-��Ϣ����)
  ActTyp      char(1)   default '',
--�˻�����
  TlrId       char(7)   not null,
--����Ա
  CONSTRAINT PK_PFACUSINF PRIMARY KEY( PfaSub,BCusId )
);
--create index ni1_PfaCusInf on PfaCusInf( PfaSub,ActNo );
--
--
--������Ϣ�����
--
--
create table PfaCodInf
(
  PfaSub      char(3)   not null,
--��������
  CodTyp      char(6)   not null,
--��������( SUBCOD-��Ŀ ECONTP-���÷��� PRJCOD-��Ŀ���� DPTCOD-ҵ���� TPAYTP-֧������ )
  Code        char(20)  not null,
--����
  CodNam      char(60)  not null,
--��������
  CONSTRAINT PK_PFACODINF PRIMARY KEY( PfaSub, CodTyp, Code )
);

--
--
--�������
--
--
create table PfaQuoBal
(
  BalSts      char(1)   not null,
--״̬(0-���� 1-ע��)
  BrNo        char(6)   not null,
--���к�
  PfaSub      char(3)   not null,
--����Ӧ�ô���
  Year        char(4)   not null,
--���
  BCusId      char(18)  not null,
--����Ԥ�㵥λ����
  TSeqNo      char(20)  default '',
--��ţ��ƻ����룩
  SubCod      char(20)  default '',
--Ԥ���Ŀ
  PrjCod      char(20)  default '',
--Ԥ����Ŀ
  EConTp      char(20)  default '',
--���÷���
  DptCod      char(20)  default '',
--ҵ����(ָ����Դ)
  AmtTyp      char(20)  default '',
--�ʽ����� (0001-Ԥ���� 0002-Ԥ���� 0003-�Գ��ʽ� 0004-��Ϣ����)
  QuoTot      char(15)  default '0',
--����ܶ�
  QuoBal      char(15)  default '0',
--������
  FrzAmt      char(15)  default '0',
--������
  ClrAct      char(40)  default ''
);
create unique index ni1_PfaQuoBal on PfaQuoBal( PfaSub,Year,BCusId,TSeqNo,SubCod,PrjCod,EConTp,DptCod );
--
--
--֧��ƾ֤�Ǽǲ�
--
--
create table PfaVchBok
(
  VchSts      char(1)    default '0',
--����״̬( U-��ʼ 0-�Ǽ� 1-ȷ�� 2-ʹ�� 3-���� 4-�˻� 5-����(��Ա����ȡ��) )
  BrNo        char(6)    not null,
--���к�
  PfaSub      char(3)    not null,
--����Ӧ�ô���
  Year        char(4)    not null,
--�������
  AVchNo      char(8)    not null,
--��Ȩƾ֤�ǼǺţ�������ϵͳ���ɣ�
  BusMod      char(1)    not null,
--ҵ������ (0-��Ȩ֧�� 1-ֱ��֧��)
  OIFlag      char(1)    not null,
--���׷��� (O-֧�� R-�˻� I-�����տ�)
  VchDat      char(8)    not null,
--֧��������
  CrpVch      char(8)    not null,
--��λƾ֤��(��)
  PayAct      char(35)   not null,
--�������ʺ�
  PayNam      char(60)   not null,
--������ȫ��
  PayBNm      char(60)   default '',
--�����˿�������
  PyeAct      char(35)   default '',
--�տ����˺�
  PyeNam      char(60)   default '',
--�տ���ȫ��
  PyeBNm      char(60)   default '',
--�տ��˿�������
  BCusId      char(18)   not null,
--����Ԥ�㵥λ����
  StlMod      char(2)    default '',
--���㷽ʽ ( 01-ת�� 02-�ֽ� 03-�Ż� 04-��� 05-��Ʊ 06-��Ʊ  99-����)
  VchTyp      char(3)    default '',
--ƾ֤����
  VchNo       char(8)    default '',
--����ƾ֤���
  UdwDat      char(8)    default '',
--ǩ������
  Pin         char(16)   default '',
--֧������
  TxnAmt      char(15)   not null,
--֧�����
  TPayTp      char(20)   default '',
--֧������
  RefCod      char(2)    default '',
--�˻ش���
  VchSmr      char(60)   default '',
--��;
  PayCnl      char(1)    default '',
--֧������
  DtlNum      char(2)    not null,
--��ϸ����
  TVchTp      char(1)    default '0',
--ƾ֤����( 0-��ͨ 1-�޶� 2-���� )
  ChkFlg      char(1)    default '',
--����ȷ�ϱ�־( 0-δȷ�� 1����ȷ�� )
  AmtTyp      char(20)    not null,
--�ʽ����� (0001-Ԥ���� 0002-Ԥ���� 0003-�Գ��ʽ� 0004-��Ϣ����)
  AmtSrc      char(10)   default '',
--�ʽ���Դ
  LogNo       char(14)   default '',
--���ʶ�Ӧǰ����ˮ
  ActDat      char(8)    not null,
--�������
  RegId       char(7)    not null,
--�Ǽǹ�Ա
  BokId       char(7)    default '',
--���ʹ�Ա
  BokTck      char(11)   default '',
--������ˮ��
  ChkId       char(7)    default '',
--���˹�Ա
  NodNo       char(6)    default '',
--���źţ�֧����ȷ�ϲ��ţ�
  AVchTm      char(14)   not null,
--ƾ֤¼��ʱ��
  PfaKnd      char(1)    not null,
--֧������ (0-ֽ�� 1-����)
  ClrSts      char(1)    default '0',
--�����־( 0-δ���� 1-������ 2-�ڲ�������� 3-��������ȷ�� 4-��������ʧ�� ) 
  ClrBNo      char(10)   default '',
--��������
  ClrDat      char(8)    default '',
--�ڲ���������
  PfaDat      char(8)    default '',
--������������
  RtnFlg      char(1)    not null,
--��Ӧ��־ (0-δ�� 1-�ѻ�)
  CONSTRAINT PK_PFAVCHBOK PRIMARY KEY( PfaSub, Year, AVchNo )
);
create unique index ni1_PfaVchBok on PfaVchBok( PfaSub,Year,BCusId,CrpVch );
create index ni2_PfaVchBok on PfaVchBok( PfaSub,Year,ClrBNo );
create index ni3_PfaVchBok on PfaVchBok( PfaSub, PfaDat, ClrSts );
--
--
--֧��������ˮ��
--
--
create table PfaTxnJnl
(
  LogNo      char(14)  not null,
--ǰ����ˮ��
  TTxnCd     char(10)  not null,
--������������
  TxnCod     char(6)   not null,
--������
  TxnTyp     char(1)   not null,
--��������( N-�������� C-�������� R-�ط����� )
  BusTyp     char(6)   not null,
--ҵ������
  CrpCod     char(10)  Default '',
--��λ����
  ActDat     char(8)   not null,
--�������
  CcyCod     char(3)   default '',
--���Ҵ���
  TxnAmt     char(15)  not null,
--���׽��
  Fee        char(15)  default '0',
--�����ѽ��
  ActNo      char(21)  default '',
--�ͻ��ʺ�
  CrdNo      char(30)  default '',
--�ͻ�����
  ActNam     char(60)  default '',
--�ͻ�����
  OrgNo      char(6)   default '',
--������
  NodNo      char(6)   default '',
--���������
  TlrId      char(7)   not null,
--���й�Ա��
  CntrId     char(10)  default '',
--���й�̨��
  NodTrc     char(20)  default '',
--������ˮ��
  TxnCnl     char(3)   default '',
--��������
  ItgTyp     char(1)   not null,
--����������( 0-�ǳ��� 1-�ֶ����� 2-ϵͳ���� 6-�ط� )
  FTxnTm     char(14)  not null,
--ǰ�ý���ʱ��
  FRspCd     char(6)   not null,
--ǰ����Ӧ��
  HLogNo     char(9)   default '',
--������ˮ��
  TckNo      char(11)  default '',
--�����ˮ��
  HRspCd     char(6)   default '',
--������Ӧ��
  HTxnSt     char(1)   default 'U',
--��������״̬( S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ E-��� )
  HPrChk     char(1)   default '0',
--�������ռ���ʱ�־( 0-δ���� 1-�Ѷ��� 2-���ʲ��� )
  HLsChk     char(1)   default '0',
--���������ն��ʱ�־( 0-δ���� 1-�Ѷ��� 2-���ʲ��� )
  TCusId     char(30)  default '0',
--�������ͻ���ʶ
  TCusNm     char(60)  default '',
--�������ͻ�����
  TActDt     char(8)   default '',
--��������������(��Ȩƾ֤�Ǽ�����)
  TLogNo     char(20)  default '',
--��������ˮ��
  TRspCd     char(10)  default '',
--��������Ӧ��
  TTxnSt     char(1)   default 'U',
--����������״̬(  S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ )
  ThdChk     char(1)   default '0',
--����������ʱ�־( 0-δ���� 1-�Ѷ��� )
  TxnSts     char(1)   default 'U',
--����״̬( S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ )
  TxnAtr     char(32)  default '',
--��������
  MstChk     char(1)   default '',
--Ҫ����ʱ�־( 0-������� 1-������� )
  LChkTm     char(10)  default '',
--�ϴζ���ʱ��
  BrNo       char(6)   not null,
--���к�
  PfaSub     char(3)   not null,
--����Ӧ����
  BCusId     char(18)  not null,
--����Ԥ�㵥λ����
  BusMod     char(1)   default '0',
--ҵ������ (0-��Ȩ֧�� 1-ֱ��֧��)
  OIFlag     char(1)   not null,
--���׷��� (O-֧�� R-�˻� I-�����տ�) 
  AVchCd     char(30)  default '',
--֧������
  TSeqNo     char(20)  default '',
--�ƻ�����
  SubCod     char(20)  default '',
--Ԥ���Ŀ
  PrjCod     char(20)  default '',
--Ԥ����Ŀ
  EConTp     char(20)  default '',
--���÷���
  DptCod     char(20)  default '',
--ҵ����(ָ����Դ)
  AVchNo     char(8)   not null,
--��Ȩƾ֤�ǼǺ���
  ActSts     char(1)   default '0',
--��ϸ״̬( 1-���� 2-���� 3-Ĩ�� )
  PayAct     char(35)  default '',
--�������ʺ�
  PayNam     char(60)  default '',
--���λȫ��
  PayAdr     char(60)  default '',
--���λ��ַ
  PayBNm     char(60)  default '',
--���λ��������
  PyeAct     char(35)  default '',
--�տλ�ʺ�
  PyeNam     char(60)  default '',
--�տλȫ��
  PyeAdr     char(60)  default '',
--�տλ��ַ
  PyeBNm     char(60)  default '',
--�տλ��������
  VchTyp     char(3)   default '',
--����ƾ֤����
  VchNo      char(8)   default '',
--����ƾ֤���
  UdwDat     char(8)   default '',
--ǩ������
  Pin        char(16)  default '',
--֧������
  Smr        char(60)  default '',
--��;
  EleBk      char(5)   default '',
--���к�
  CclAct     char(21)  default '',
--�����ʺ�
  CclNo      char(12)  default '',
--���ʺ�
  CclSqn     char(4)   default '',
--�������
  RBkNo      char(12)  default '',
--֧���к�
  ChkId      char(7)   default '',
--ƾ֤���˹�Ա��
  PChkId     char(7)   default '',
--֧�����˹�Ա��
  PayCnl     char(2)   default '',
--֧������( 0-����  1-֧��  2-����ƽ̨ )
  ClrSts     char(1)   default '0',
--�����־( 0-δ���� 1-������ 2-�ڲ�������� ) 
  ClrBNo     char(10)  default '',
--��������
  ClrDat     char(8)   default '',
--�ڲ���������
--PfaDat     char(8)   default '',
--������������
  PrvDat     clob(3072) default '',
  CONSTRAINT PK_PFATXNJNL PRIMARY KEY( LogNo )
);
create index ni1_PfaTxnJnl on PfaTxnJnl( PfaSub, AVchNo );
create index ni2_PfaTxnJnl on PfaTxnJnl( ActDat, TckNo );
create index ni3_PfaTxnJnl on PfaTxnJnl( PfaSub, ClrSts, HTxnSt, ActSts, TxnAmt );
--
--
--�����¼��
--
--
create table PfaClrRec
(
  ClrSts      char(1)   not null,
--����״̬(0-��ʼ״̬ 1-������ 2-������ )
  BrNo        char(6)   not null,
--���к�
  PfaSub      char(3)   not null,
--����Ӧ�ô���
  ClrTyp      char(1)   not null,
--��������( 0-ϵͳ������ 1-�˿����� 2-�������� )
  ClrBNo      char(10)  not null,
--��������
  OIFlag      char(1)   not null,
--���׷��� (O-֧�� R-�˻� I-�����տ�) 
  LogNo       char(14)  not null,
--��ˮ��
  RknVno      char(20)  default '',
--��������ƾ֤���
  BCusId      char(18)  default '',
--����Ԥ�㵥λ����
  BCusNm      char(60)  default '',
--����Ԥ�㵥λ����
  ActNo       char(21)  default '',
--�����ʺ�
  ActNm       char(60)  default '',
--����
  TxnAmt      char(15)  default '0',
--���
  ClrDat      char(8)   default '',
--��������(������ڣ�
  PfaDat      char(8)   default '',
--������������
  ClrTm       char(14)  default '0'
--����ʱ��
);
--create unique index ni1_PfaClrRec on PfaClrRec( PfaSub,ClrTyp,ClrBNo,OIFlag,BCusId,ActNo );
--
--
--������ˮ��
--
--
create table PfaClrJnl
(
  LogNo      char(14)  not null,
--ǰ����ˮ��
  TTxnCd     char(10)  not null,
--������������
  TxnCod     char(6)   not null,
--������
  TxnTyp     char(1)   not null,
--��������( N-�������� C-�������� R-�ط�����)
  BusTyp     char(6)   not null,
--ҵ������
  CrpCod     char(10)  Default '',
--��λ����
  ActDat     char(8)   not null,
--�������
  CcyCod     char(3)   default '',
--���Ҵ���
  TxnAmt     char(15)  not null,
--���׽��
  Fee        char(15)  default '0',
--�����ѽ��
  ActNo      char(21)  default '',
--�ͻ��ʺ�
  CrdNo      char(30)  default '',
--�ͻ�����
  ActNam     char(60)  default '',
--�ͻ�����
  OrgNo      char(6)   default '',
--������
  NodNo      char(6)   default '',
--���������
  TlrId      char(7)   not null,
--���й�Ա��
  CntrId     char(10)  default '',
--���й�̨��
  NodTrc     char(20)  default '',
--������ˮ��
  TxnCnl     char(3)   default '',
--��������
  ItgTyp     char(1)   not null,
--����������( 0-�ǳ��� 1-�ֶ����� 2-ϵͳ���� 6-�ط� )
  FTxnTm     char(14)  not null,
--ǰ�ý���ʱ��
  FRspCd     char(6)   not null,
--ǰ����Ӧ��
  HLogNo     char(9)   default '',
--������ˮ��
  TckNo      char(11)  default '',
--�����ˮ��
  HRspCd     char(6)   default '',
--������Ӧ��
  HTxnSt     char(1)   default 'U',
--��������״̬( S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ E-��� )
  HPrChk     char(1)   default '0',
--�������ռ���ʱ�־( 0-δ���� 1-�Ѷ��� 2-���ʲ��� )
  HLsChk     char(1)   default '0',
--���������ն��ʱ�־( 0-δ���� 1-�Ѷ��� 2-���ʲ��� )
  TCusId     char(30)  default '0',
--�������ͻ���ʶ
  TCusNm     char(60)  default '',
--�������ͻ�����
  TActDt     char(8)   default '',
--��������������(��Ȩƾ֤�Ǽ�����)
  TLogNo     char(20)  default '',
--��������ˮ��
  TRspCd     char(10)  default '',
--��������Ӧ��
  TTxnSt     char(1)   default 'U',
--����������״̬(  S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ )
  ThdChk     char(1)   default '0',
--����������ʱ�־( 0-δ���� 1-�Ѷ��� )
  TxnSts     char(1)   default 'U',
--����״̬( S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ )
  TxnAtr     char(32)  default '',
--��������
  MstChk     char(1)   default '',
--Ҫ����ʱ�־( 0-������� 1-������� )
  LChkTm     char(10)  default '',
--�ϴζ���ʱ��
  BrNo       char(6)   not null,
--���к�
  ClrSts     char(1)   default '0',
--����״̬(0-��ʼ״̬ 1-������ 2-������)
  ClrBNo     char(10)  default '',
--��������
  ClrDat     char(8)   default '',
--�ڲ���������
  PfaDat     char(8)   default '',
--������������
  OIFlag     char(1)   default '',
--���׷��� (O-֧�� R-�˻� I-�����տ�) 
  CONSTRAINT PK_PFACLRJNL PRIMARY KEY( LogNo )
);
--
--
--������Ӧ�ļ���ʱ��
--
--
create table PfaRptTbl
(
  PfaSub      char(3)    not null,
--����Ӧ�ô���
  BCusId      char(18)   not null,
--����Ԥ�㵥λ����
  BCusNm      char(60)   default '',
--Ԥ�㵥λ����
  SubCod      char(20)   default '',
--Ԥ���Ŀ(���ܷ���)
  SubNam      char(60)   default '',
--Ԥ���Ŀ����
  EConTp      char(20)   default '',
--���÷������
  EConNm      char(60)   default '',
--���÷�������
  PrjCod      char(20)   default '',
--Ԥ����Ŀ����
  PrjNam      char(60)   default '',
--Ԥ����Ŀ����
  DptCod      char(20)   default '',
--���Ҵ���
  DptNam      char(60)   default '',
--��������
  ActNo       char(35)   default '',
--�ʺ�
  OIFlag      char(1)    default '',
--���׷���
  TxnAmt      char(15)   default '0',
--֧�����
  PmsBNo      char(12)   default ''
);
--
--
--��������ҵ��Э���
--
--
create table PfaCusAgr
(
  AgrNo       char(60)   not null,
--���Э����
  PfaSub      char(3)    not null,
--��������
  BCusId      char(18)   not null,
--����Ԥ�㵥λ����
  SubCod      char(20)   default '',
--Ԥ���Ŀ
  EConTp      char(20)   default '',
--���÷������
  PrjCod      char(20)   default '',
--Ԥ����Ŀ����
  DptCod      char(20)   default '',
--���Ҵ���
  ActNo       char(21)   not null,
--������ʻ�
  BrNo        char(6)    not null,
  CONSTRAINT PK_PFACLRJNL PRIMARY KEY( AgrNo )
);
--
--
--����Ա������
--
--
create table PfaCrdInf
(
  PfaSub      char(3)   not null,
--��������
  CardNo      char(19)  not null,
--����
  CollDt      char(8)   default '',
--�ռ�����
  LmtAmt      char(15)  default '',
--���
  CrdSts      char(4)   default '',
--��Ƭ״̬
  IdType      char(4)   default '',
--֤������
  IdNo        char(60)  default '',
--֤������
  CardNm      char(30)  default '',
--����
  GendCd      char(2)   default '',
--�Ա�
  BthPlc      char(100) default '',
--����
  CrpNam      char(60)  default '',
--��λ����
  DptNam      char(30)  default '',
--��ְ����
  DutyCd      char(2)   default '',
--ְ��
  MobTel      char(20)  default '',
--�ֻ�����
  Email       char(30)  default '',
--�����ʼ�
  CrpTel      char(20)  default '',
--��λ�绰
  Addr        char(100) default '',
--�˵���ַ
  HisBr       char(12)  default '',
--ԭ����ϵͳ���к�
  EffDat      char(8)   default '',
--��������
  IvdDat      char(8)   default '',
--��Ч��
  SellId      char(12)  default '',
--Ӫ������
  BCusId      char(18)  default '',
--����Ԥ�㵥λ����
  BrNo        char(6)   not null,
--���к�
  ActDat      char(8)   not null,
--��������
  constraint PK_PFACRDINF PRIMARY KEY( PfaSub,CardNo )
);
--
--
--����Ա��������ϸ
--
--
create table PfaCrdTxn
(
  CardNo      char(19)  not null,
--����
  CollDt      char(8)   default '',
--�ռ�����
  HisBr       char(12)  default '',
--ԭ����ϵͳ���к�
  TxnDat      char(8)   not null,
--��������
  TxnTim      char(8)   default '',
--����ʱ��
  IbsDat      char(8)   default '',
--������������
  TxnSmr      char(60)  default '',
--����˵��
  MerId       char(15)  default '',
--�̻���
  TermId      char(9)   default '',
--�ն˺�
  MerNam      char(60)  default '',
--�̻�����
  TLogNo      char(6)   not null,
--������ˮ��
  DtlAmt      char(15)  default '',
--���׽��
  CcyCod      char(3)   default '',
--����
  ThdCod      char(4)   default '',
--������
  AuthCd      char(6)   default '',
--��Ȩ��
  SltOrg      char(12)  default '',
--���������
  PtgOrg      char(12)  default '',
--ת��������
  RefNum      char(30)  default '',
--�����ο���
  SltDat      char(8)   default '',
--��������
  CardNm      char(30)  default '',
--�ֿ�������
  HActDt      char(8)   default '',
--��ʷ���ѯ����(�ñ���ϸ��ȡ����)
  IdxNo        char(6)   default '',
--������
  PfaSub      char(3)   not null,
--����Ӧ�ô���
  Year        char(4)   default '',
--���
  BCusId      char(18)  default '',
--����Ԥ�㵥λ����
  SndFlg      char(1)   default '0',
--����״̬( 0-δ���� 1-�ѷ��� )
  constraint PK_PFACRDTXN PRIMARY KEY( PfaSub,CardNo,TxnDat,TLogNo )
);
create index ni1_PfaCrdTxn on PfaCrdTxn( PfaSub, HActDt, IdxNo );
--
--
--����Ա��������ϸ
--
--
create table PfaCrdDtl
(
  DtlSts      char(1)   not null,
--����״̬( U-��ʼ B-���� S-�ɹ� F-ʧ��)
  PfaSub      char(3)   not null,
--����Ӧ�ô���
  Year        char(4)   not null,
--���
  AVchCd      char(30)  not null,
--֧������
  PfaIdx      char(16)  not null,
--����������ϸ����
  CardNo      char(19)  not null,
--����
  CardNm      char(30)  not null,
--�ֿ�������
  TxnDat      char(8)   not null,
--��������
  TxnTim      char(8)   default '',
--����ʱ��
  MerId       char(15)  default '',
--�̻���
  TermId      char(8)   default '',
--�ն˺�
  MerNam      char(60)  default '',
--�̻�����
  TLogNo      char(6)   default '',
--������ˮ��
  DtlAmt      char(15)  default '',
--���׽��
  CcyCod      char(3)   default '',
--����
  ThdCod      char(4)   default '',
--������
  AuthCd      char(6)   default '',
--��Ȩ��
  HActDt      char(8)   default '',
--��ʷ���ѯ����(�ñ���ϸ��ȡ����)
  IdxNo        char(6)   default '',
--������
  BrNo        char(6)   default '',
--���к�
  BCusId      char(18)  default '',
--����Ԥ�㵥λ����
  BokAmt      char(15)  default '',
--�������
  TActDt      char(8)   default '',
--����ȷ������
  BokDat      char(8)   default '',
--��������
  LogNo       char(14)  default '',
--ǰ����ˮ��
  RtnFlg      char(1)    default '0',
--��Ӧ��־ (0-δ�� 1-�ѻ�)
  constraint PK_PFACRDDTL PRIMARY KEY( PfaSub, Year, AVchCd, PfaIdx )
);
--
--
--����Ա��������ˮ��
--
--
create table PfaCrdJnl
(
  TxnSts      char(1)   default 'U',
--״̬( U-��ʼ S-�����ɹ� F-����ʧ�� T-������ʱ C-���� )
  TxnTyp      char(1)   default 'N',
--��������( N-�������� C-�������� R-�ط�����)
  LogNo       char(14)  not null,
--ǰ����ˮ��
  BrNo        char(6)   not null,
--���к�
  ActDat      char(8)   not null,
--�������
  HTxnSt      char(1)   default 'U',
--��������״̬
  HRspCd      char(6)   default '',
--����������
  HLogNo      char(9)   default '',
--������ˮ��
  TlrId       char(7)   default '',
--���й�Ա��
  TckNo       char(11)  default '',
--�����ˮ��
  CardNo      char(19)  default '',
--�ͻ��ʺ�
  CardNm      char(30)  not null,
--�ֿ�������
  CcyCod      char(3)   default '',
--���Ҵ���
  TotAmt      char(15)  not null,
--�����ܶ�
  TxnAmt      char(15)  not null,
--���׽��
  PfaSub      char(3)   not null,
--����Ӧ�ô���
  Year        char(4)   not null,
--���
  BCusId      char(18)  not null,
--����Ԥ�㵥λ����
  AVchCd      char(30)  not null,
--֧������
  constraint PK_PFACRDJNL PRIMARY KEY( LogNo )
);
create index ni1_PfaCrdJnl on PfaCrdJnl( PfaSub,Year,AVchCd );
