drop table PftBnkInf;
drop table PftChkTot;
drop table PftCusAgt;
drop table PftTxnJnl;
drop table PftTxnSum;
drop table PftVchReg;
drop table PftSec202Sum;
drop table PftSec202Dtl;
drop table PftBxt201;
drop table PftEft003;
--
--
--
--������Ϣ��
--
--
--
create table PftBnkInf
(
  BnkCls   char(1)   not null,
--�������� 0-ֱ�Ӳ�����  1-ҵ�����
  BrNo     char(6)   not null,
--���׷���
  BnkCod   char(12)  not null,
--����֧���к�
  CtlNod   char(6)   not null,
--ͨ����Ʋ��ź�
  ClrDat   char(8)   not null,
--��ǰ��������
  SysSts   char(1)   not null,
--ϵͳ����״̬ 0-ϵͳ�ر�  1-ϵͳ����
  Act01    char(21)  default '',
--22203�ۿ�ר��
  Act02    char(21)  default '',
--13801�˿�ר��
  UserPs   char(8)   default '',
  constraint PK_PFTBNKINF PRIMARY KEY(BnkCls,BrNo)
);
--
--
--
--�˶�ͳ�Ʊ�
--
--
--
create table PftChkTot
(
  BnkCod   char(12)   not null,
--���д���
  ClrDat   char(8)    not null,
--�ʽ��������
  ClrSce   char(1)    not null,
--�ʽ��������
  TTxnTp   char(2)    not null,
--��������
  ChkFlg   char(1)    default '0',
--���ʱ�ʶ 0δ���� 1���ʳɹ�
  TotNum   char(6)    not null,
--�ܱ���
  TotAmt   char(15)   not null,
--�ܽ��
  BnkNum   char(6)    default '',
--�����ܱ���
  BnkAmt   char(15)   default '',
--�����ܽ��
  CONSTRAINT PK_PFTCHKTOT PRIMARY KEY( BnkCOd,ClrDat,ClrSce,TTxnTp)
);
--
--
--
--��˰Э���
--
--
create table PftCusAgt
(
  Sts      char(1)   not null,
--״̬( 0-��Ч 1-��Ч )
  TCrpTp   char(1)   not null,
--���ջ������( 1-��˰ 2-��˰ 3-���� 4-����)
  AgtInf   char(35)  not null,
--Э��ȷ����
  ActTyp   char(1)   not null,
--�˻�����( 0-��ͨ�Թ� 1-һ��ͨ 2-��ͨ���� 4-̫ƽ�� A-��������Թ� B-�㶫ʡ�����Թ� )
  ActNo    char(21)  not null,
--��˰�˽ɿ��ʺ�
  ActNam   char(60)  default '',
--�ͻ�����
  VchTyp   char(3)   default '',
--ƾ֤����
  VchCod   char(8)   default '00000000',
--ƾ֤����
  ActSqn   char(5)   default '',
--һ��ͨ�˻����
  PfaSub   char(3)   default '',
--��������
  BCusId   char(18)  default '',
--����Ԥ�㵥λ����
  SubCod   char(30)  default '',
--Ԥ���Ŀ
  EConTp   char(20)  default '',
--���÷������
  PrjCod   char(20)  default '',
--Ԥ����Ŀ����
  DptCod   char(20)   default '',
--���Ҵ���
  CusTel   char(60)   default ' ',
--��˰����ϵ�绰
  OpnNod   char(6)   not null,
--��������
  OpnBr    char(6)   not null,
--��������
  CONSTRAINT PK_PFTCUSAGT PRIMARY KEY( TCrpTp,AgtInf,ActNo )
);
--
--
--��˰��ˮ��
--
--
create table PftTxnJnl
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
  BilSts   char(1)   default 'U',
--����״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ T-������ʱ W-��������ʱ V-�����ɹ� )
  OIFlag   char(1)   not null,
--�����˱�־( 0-���� 1-���� )
  BusTyp   char(6)   not null,
--ҵ������
  CrpCod   char(12)  default '',
--��λ����
  ActDat   char(8)   not null,
--�������
  CcyCod   char(3)   default 'CNY',
--���Ҵ���
  TxnAmt   char(15)  not null,
--���׽��
  ActNo    char(21)  default '',
--�ͻ��ʺ�
  ActNam   char(60)  default '',
--�ͻ�����
  ActTyp   char(2)   not null,
--�˻�����( 0-��ͨ�Թ� 1-һ��ͨ 2-��ͨ���� 4-̫ƽ�� A-��������Թ� B-�㶫ʡ�����Թ� )
  VchTyp   char(3)   default '',
--ƾ֤����
  VchCod   char(8)   default '00000000',
--ƾ֤����
  ActSqn   char(5)   default '',
--һ��ͨ�˻����
  PfaSub   char(3)   default '',
--��������
  BCusId   char(18)  default '',
--����Ԥ�㵥λ����
  SubCod   char(20)  default '',
--Ԥ���Ŀ
  EConTp   char(20)  default '',
--���÷������
  PrjCod   char(20)  default '',
--Ԥ����Ŀ����
  DptCod   char(20)  default '',
--���Ҵ���
  NodNo    char(6)   default '',
--���������
  BrNo     char(6)   not null,
--���׷���
  TlrId    char(7)   not null,
--���й�Ա��
  TxnCnl   char(3)   default '',
--��������
  FTxnTm   char(14)  default '',
--ǰ�ý���ʱ��
  HLogNo   char(9)   default '',
--������ˮ��
  TckNo    char(11)  default '',
--�����ˮ��
  PLogNo   char(14)  default '',
--���������ˮ��
  HTxnSt   char(1)   default 'U',
--��������״̬( S-�ɹ� F-ʧ�� R-��Ĩ�� C-������ U-Ԥ��״̬ E-��� T-��ʱ)
  HRspCd   char(6)   default '',
--������Ӧ��
  RspCod   char(6)   default '',
--ǰ�÷�����
  RtnCod   char(4)   default '',
--������
  ClrDat   char(8)   default '',
--�����������
  ClrSce   char(1)   default '',
--���������������
  BTxnID   char(16)  default '',
--���н���ʶ���
  ThdChk   char(1)   default '0',
--����������ʱ�־( 0-δ���� 1-�Ѷ��� )
  MsgFmt   char(6)   default '',
--��Ϣ��ʽ��
  TCrpCd   char(11)  not null,
--���ջ��ش���
  TActDt   char(8)   default '',
--���ջ����ύ����
  TLogNo   char(16)  not null,
--���ջ�������ˮ��
  RcvBNo   char(12)  not null,
--���մ������к�
  FskCod   char(11)  not null,
--�տ�������
  TTxnTp   char(2)   not null,
--��������������
  OTActDt  char(8)   default '',
--�������ջ����ύ����(����ʹ��)
  OTLogNo  char(16)  default '',
--�������ջ�����ˮ��(����ʹ��)
  AgtInf   char(35)  default '',
--ǩԼ������Ϣ
  SndAct   char(35)  default '',
--�������ʺ�
  SndNm    char(60)  default '',
--����������
  RcvAct   char(35)  default '',
--�������ʺ�
  RcvNm    char(60)  default '',
--����������
  TPayTp   char(1)   default '',
--�걨��ʽ����( OIFlag='0'ʱ e-�ֽ� f-ת�� g-POS )
  SavFld   char(2)   default '',
--������
  AppFlg   char(1)   default '0',
--��չҪ�ر�־
  CONSTRAINT PK_PFTTXNJNL PRIMARY KEY( LogNo )
);
create unique index ni1_PftTxnJnl on PftTxnJnl( TCrpCd, TActDt, TLogNo );
create index ni2_PftTxnJnl on PftTxnJnl( TCrpCd, OTActDt, OTLogNo );
create index ni3_PftTxnJnl on PftTxnJnl( MsgFmt, ClrDat, ClrSce, BTxnID );
--
--
--
--��˰ƾ֤���ܱ�
--
--
create table PftSec202Sum
(
  MsgFmt   char(6)   not null,
--��Ϣ��ʽ��
  ClrDat   char(8)   not null,
--ETS�ʽ��������
  SndCod   char(12)  not null,
--�ļ����ͷ�����
  RcvCod   char(12)  not null,
--�ļ����շ�����
  ClrSce   char(4)   not null,
--ETS�ʽ��������
  FilSeq   char(10)  not null,
--�ļ����
  OIFlag   char(1)   default '',
--�����˱�־( 0-���� 1-���� )
  RcvBNo   char(12)  default '',
--���մ������к�
  RcvBNm   char(60)  default '',
--���մ���������
  ActDat   char(8)   default '',
--�����ύ����
  BTxnID   char(16)  default '',
--���н���ʶ���
  TTxnTp   char(2)   default '',
--��������������
  AgtInf   char(35)  default '',
--ǩԼ������Ϣ
  ActTyp   char(2)   default '',
--�˻�����( 0-��ͨ�Թ� 1-һ��ͨ 2-��ͨ���� 4-̫ƽ�� A-��������Թ� B-�㶫ʡ�����Թ� )
	SndAct   char(35)  default '',
--�������˺�
  RcvAct   char(35)  default '',
--�ɿ��ʺ�
  ActNo    char(21)  default '',
--�����˺�
  ActNam   char(60)  default '',
--����������
  TxnAmt   char(15)  not null,
--���
  PrtFlg   char(1)   default '',
--��ӡ��˰Ҫ�ر�־( 0-���� 2-����ҵ���д�ӡ���лص�ʱһ����ӡ��˰Ҫ�� )
  TaxNo    char(20)  default '',
--��˰��ʶ���
  TaxNam   char(100) default '',
--��˰������
  CrpKnd   char(40)  default '',
--��ҵע������
  TCrpNm   char(60)  default '',
--���ջ�������
  TLogNo   char(16)  not null,
--���ջ�������ˮ��(����˰Ʊ��)
  FskNam   char(60)  default '',
--�տλ(����)����
  Smr      char(200) default '',
--��ע
  DtlNum   char(3)   not null,
--��ϸ��Ŀ
  DtlMac   char(64)  default '',
--��Ѻ
  PrtCnt   char(2)   default '00',
--��ӡ����
  OpnNod   char(6)   default '',
--�����
  OpnBr    char(6)   default '',
--���к�
  CONSTRAINT PK_PFTSEC202SUM PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq )
);
--
--
--��˰ƾ֤��ϸ��
--
--
create table PftSec202Dtl
(
  MsgFmt   char(6)   not null,
--��Ϣ��ʽ��
  ClrDat   char(8)   not null,
--ETS�ʽ��������
  SndCod   char(12)  not null,
--�ļ����ͷ�����
  RcvCod   char(12)  not null,
--�ļ����շ�����
  ClrSce   char(4)   not null,
--ETS�ʽ��������
  FilSeq   char(10)  not null,
--�ļ����
  DtlSeq   char(3)   not null,
--��ϸ˳���
  TaxTyp   char(40)  default '',
--˰������
  PrjNam   char(60)  default '',
--ƷĿ����
  LvlNam   char(40)  default '',
--Ԥ�㼶������
  TaxDt    char(17)  default '',
--˰����������
  DtlAmt   char(15)  default '',
--��ϸ���
  TSubCd   char(12)  default '',
--Ԥ���Ŀ����
  TVchNo   char(20)  default '',
--����˰Ʊ��(ƾ֤��)
  CONSTRAINT PK_PFTSEC202DTL PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq,DtlSeq )
);
--
--
--Ԥ����Ӧ������ϸ��
--
--
create table PftBxt201
(
  MsgFmt   char(6)   not null,
--��Ϣ��ʽ��
  ClrDat   char(8)   not null,
--ETS�ʽ��������
  SndCod   char(12)  not null,
--�ļ����ͷ�����
  RcvCod   char(12)  not null,
--�ļ����շ�����
  ClrSce   char(4)   not null,
--ETS�ʽ��������
  FilSeq   char(10)  not null,
--�ļ����
  TCrpCd   char(11)  not null,
--���ջ��ش���
  TActDt   char(8)   not null,
--���ջ����ύ����
  TLogNo   char(16)  not null,
--���ջ�������ˮ��
  RcvBNo   char(12)  not null,
--���մ������к�
  DirBNo   char(12)  not null,
--���մ����������к�
  TTxnTp   char(2)   not null,
--��������������
  TxnAct   char(35)  not null,
--�ɿ��ʺ�
  TaxNam   char(100) default '',
--��˰������
  TaxNo    char(20)  default '',
--��˰��ʶ���
  CrpKnd   char(40)  default '',
--��ҵע������
  DtlSeq   char(3)   not null,
--��ϸ˳���
  TSubCd   char(12)  default '',
--Ԥ���Ŀ
  TSubNm   char(60)  default '',
--Ԥ���Ŀ����
  AgtBNo   char(12)  not null,
--�������ר�������к�
  TActNo   char(35)  not null,
--�������ר���˻�
  DtlAmt   char(15)  not null,
--��ϸ���
  TaxTyp   char(40)  default '',
--˰������
  PrjNam   char(60)  default '',
--ƷĿ����
  TaxDt    char(17)  default '',
--˰����������
  DtlMac   char(64)  not null,
--��Ѻ
  CONSTRAINT PK_PFTBXT201 PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq )
);
--
--
--�ʽ�������Ϣ��
--
--
create table PftEft003
(
  MsgFmt   char(6)   not null,
--��Ϣ��ʽ��
  ClrDat   char(8)   not null,
--ETS�ʽ��������
  SndCod   char(12)  not null,
--�ļ����ͷ�����
  RcvCod   char(12)  not null,
--�ļ����շ�����
  ClrSce   char(4)   not null,
--ETS�ʽ��������
  FilSeq   char(10)  not null,
--�ļ����
  PyrCod   char(12)  default '',
--�������
  PyrNam   char(60)  default '',
--�������
  PyrBNo   char(12)  not null,
--�������֧���к�
  PyrBNm   char(60)  default '',
--�������֧������
  PyrAct   char(35)  default '',
--�տ����֧������
  PyeCod   char(12)  default '',
--�տ����
  PyeNam   char(60)  default '',
--�տ����
  PyeBNo   char(12)  not null,
--�տ����֧���к�
  PyeBNm   char(60)  default '',
--�տ����֧������
  PyeAct   char(35)  not null,
--�����˻�
  TTxnTp   char(2)   not null,
--��������������
  TRcvTp   char(1)   not null,
--��������
  TRTpNm   char(60)  default '',
--������������
  TaxKnd   char(12)  default '',
--˰������
  TaxNam   char(60)  default '',
--˰����������
  TxnAmt   char(15)  not null,
--���׽��
  TCrpCd   char(11)  default '',
--���ջ��ش���
  TCrpNm   char(60)  default '',
--���ջ�������
  DtlMac   char(64)  not null,
--��Ѻ
  CONSTRAINT PK_PFTEFT003 PRIMARY KEY( MsgFmt,ClrDat,SndCod,RcvCod,ClrSce,FilSeq )
);
