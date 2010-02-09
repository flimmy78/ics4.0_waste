drop table PclCusAgt;
drop table PclTxnDtl;
drop table PclAccJnl;
drop table PclTmpRpt;
drop table PclTrmAgt;
drop table PclDTxnDtl;
drop table PclITxnDtl;
drop table PclClrInf;
drop table PclDFeeJnl;
drop table PclFeeRat;
--
--
-- POS�ͻ�Э���
--
--
create table PclCusAgt
(
  Sts        char(1)      not null,
--״̬
  PosTyp     char(1)      not null,
--POS����( 0-����  1-���� )
  BusiNo     char(15)     not null,
--�̻���
  CusNam     char(60)     not null,
--�̻���
  SysFlg     char(1)      default '0',
--ϵͳ�����־
  DeptNo     char(6)      not null,
--��������
  OpnBr      char(6)      not null,
--��������
  AgrBr      char(6)      not null,
--�����������
  BankNo     char(12)     not null,
--����֧���к�
  BankNm     char(60)     not null,
--����֧������
  AccFlg     char(1)      not null,
--�Թ���˽��־��0-�Թ� 1-���� 2-����
  InAcNo     char(21)     not null,
--���ʣ����ʣ��ʺ�
  InAcNm     char(60)     not null,
--���ʣ����ʣ�����
  InMode     char(1)      not null,
--���ʷ�ʽ( 0-�������ܶ� 1-�������ܶ� 2-����������� )
  FeeRat     char(6)      not null,
--��������
  TopAmt     char(15)     not null,
--��߶��
  ValDt      char(8)      not null,
--��Ч����
  Smr        char(60)     default '',
--��ע
  CONSTRAINT PK_PCLCUSAGT PRIMARY KEY( PosTyp,BusiNo )
);
--
--
-- POS�ͻ�������ϸ��
--
--
create table PclTxnDtl
(
  Sts             char(1)    not null,
--״̬( 0-��ʼ 1-������ E-���� A-������ B-���ڼ��ʴ��� 9-?? )
  SeqNo           char(6)    not null,
--���
  IssCode         char(8)    not null,
--�����д���
  RecvIns         char(8)    default '',
--���շ���ʶ
  TranAcc         char(19)   not null,
--�����ʺ�
  AcqCode         char(8)    not null,
--�յ��д���
  ForWins         char(8)    not null,
--ת������
  AcqIns          char(8)    not null,
--������ʶ
  RefNo           char(12)   not null,
--ϵͳ�ο���
  CtrDt           char(8)    not null,
--���׷�����
  CtrTime         char(8)    not null,
--����ʱ��
  CtrTrn          char(6)    not null,
--POS������ˮ��
  TranAmt         char(12)   not null,
--���׽��
  MerStandComm    char(6)    not null,
--�ؿ���
  Mti             char(2)    not null,
--����������Ϣ��
  ProcCode        char(6)    not null,
--������
  MerType         char(4)    not null,
--�̻�����
  CtrPostDate     char(8)    not null,
--�����գ���������λ��չ��
  TermId          char(8)    not null,
--POS������
  MerId           char(15)   not null,
--�̻�����
  MerAccFromTbl   char(30)   not null,
--�̻��ʺ�
  TranCurr        char(3)    not null,
--���ױұ�
  ClearAmt        char(12)   not null,
--������
  ManuAuthFlag    char(1)    default '',
--�˹���Ȩ��־
  GnetAuthFlag    char(1)    default '',
--GNET����Ȩ��־
  AuthCode        char(6)    not null,
--������Ȩ��
  TxCode          char(3)    not null,
--�������ͱ�ʶ
  RepCode         char(2)    not null,
--������Ӧ��
  MerName         char(20)   not null,
--�̻���
  OrigCtrTrn      char(6)    default '',
--ԭ���ĸ��ٺ�
  OrigRefNo       char(12)   not null,
--����ϵͳ�ο���
  EndFlag         char(2)    not null,
--��ɱ��
  BankFee         char(12)   not null,
--����Ӧ�շ����
  MerFee          char(12)   not null,
--�̻�Ӧ�������
  PrvFlg          char(1)    default '',
--�����ʻ���ʶ
--PosTyp          char(1)    not null,
--POS����( 0-����  1-���� )
--TrmTyp          char(1)    not null,
--�ն�����( 0-���� 1-���� 2-ת�� 3-�������� 4-�������� )
--ChkFlg          char(1)    default '0',
--ת��POS���˱�־( 0-δ�� 1-�Ѷ� )
  InAcNo          char(21)   not null,
--���ʣ����ʣ��ʺ�
  CdFlag          char(1)    not null,
--�����־
  DeptNo          char(6)    not null,
--�������ź�
  OpnBr           char(6)    not null,
--�������к�
  AgrBr           char(6)    not null,
--�����������
  BankNo          char(12)   not null,
--֧���к�
  AccFlg          char(1)    not null,
--�Թ���˽��־��0-�Թ� 1-���� 2-����
  InMode          char(1)    not null,
--���ʷ�ʽ
  DskNo           char(12)   default '',
--���̱��
  LogNo           char(14)   default '',
--ǰ����ˮ��
  ActDat          char(8)    default '',
--�������
  HLogNo          char(9)    default '',
--������ˮ��
  TlrId           char(7)    default '',
--���й�Ա��
  TckNo           char(12)   default '',
--������Ʊ��
  HRspCd          char(6)    default '',
--������Ӧ��
  SPrtNum         char(2)    default '00',
--����֪ͨ���ӡ����
  RPrtNum         char(2)    default '00',
--�տ�֪ͨ���ӡ����
  ErrMsg          char(60)   default ''
--������Ϣ
);
CREATE INDEX ni1_PCLTXNDTL ON PclTxnDtl( CtrPostDate, AgrBr, CdFlag, Sts );
CREATE INDEX ni2_PCLTXNDTL ON PclTxnDtl( CtrPostDate, OpnBr, CdFlag, Sts );
--
--
-- POS�ͻ�������ϸ����Сͨ��ʹ�ã�
--
--
create table PclAccJnl
(
  LogNo        char(14)     not null,
--ǰ����ˮ��
  DskNo        char(12)     not null,
--���̱��
  BusTyp       char(5)      default 'PCL00',
--ҵ������
  CrpCod       char(12)     default 'PCL999999999',
--��λ����
  ActDat       char(8)      not null,
--�������
  TTxnCd       char(6)      not null,
--ǰ�ý�����
  HTxnCd       char(6)      not null,
--����������
  HLogNo       char(9)      default '',
--������ˮ��
  HTxnSt       char(1)      default 'U',
--��������״̬
  HRspCd       char(6)      default '',
--����������
  IsTxn        char(1)      default 'N',
--�Ƿ���������־������������Сͨ������  Y����N������
  TxnCnl       char(3)      default 'PCL',
--��������
  CnlSub       char(10)     default '',
--������
  TxnObj       char(8)      not null,
--��Сͨ��Ŀ�����
  UpdFlg       char(1)      default 'Y',
--���±�־
  UpdFld       char(20)     default 'HTxnCD|TCKNO|BUSTYP',
--�����ֶ���
  TlrId        char(7)      not null,
--���й�Ա��
  TckNo        char(11)     default '',
--�����ˮ��
  CtrPostDate  char(8)      not null,
--�����������ڣ���������λ��չ��
  PosTyp       char(1)      not null,
--POS����( 0-����  1-���� )
  MerId        char(15)     not null,
--�̻���
  SeqNo        char(6)      not null,
--���
  ClrAct       char(21)     not null,
--�����˺�
  BokAct       char(21)     not null,
--�����ʺ�
  SndFlg       char(1)      default '0',
--���ͱ�־( 0-�Թ� 1-���� 2-�� )
  InMode       char(1)      not null,
--���ʷ�ʽ
  TranAmt      char(15)     not null,
--���׽��
  ClearAmt     char(15)     not null,
--������
  MerFee       char(15)     not null,
--�����ѽ��
  DeptNo       char(6)      not null,
--��������
  OpnBr        char(6)      not null,
--���׷���
  CdFlag       char(1)      not null,
--�������
  CONSTRAINT PK_PCLACCJNL PRIMARY KEY( LogNo )
);
CREATE INDEX ni1_PCLACCJNL ON PclAccJnl( CtrPostDate, OpnBr, PosTyp, MerId, CdFlag );
--
--
-- POS�ͻ����ʱ���
--
--
create table PclTmpRpt
(
  MerId         char(15)     not null,
--�̻���
  CtrPostDate   char(8)      not null,
--���������գ���������λ��չ��
  TlrId         char(7)      default '',
--���й�Ա��
  TckNo         char(11)     default '',
--������Ʊ��
  InAcNo        char(21)     not null,
--�����ʺ�
  TranAmt       char(15)     default '0',
--���׽��
  ClearAmt      char(15)     default '0',
--������
  BankFee       char(15)     default '0',
--����Ӧ��������
  MerFee        char(15)     default '0',
--�̻�Ӧ��������
  InMode        char(1)      not null,
--���ʷ�ʽ
  OpnBr         char(6)      not null,
--��������
  MerAccFromTbl char(30)     not null,
--�̻��ʺ�
  MerName       char(20)     not null
--�̻�����
);
CREATE INDEX ni1_PCLTMPRPT ON PclTmpRpt( MerId );
--
--
-- POSת������ά��
--
--
create table PclTrmAgt
(
  PosTyp   char(1)   not null,
--POS����( 0-����  1-���� )
  MerId    char(15)  not null,
--�̻���
  TermId   char(8)   not null,
--POS������
  TrmTyp   char(1)   not null,
--�ն�����( 0-���� 1-���� 2-ת�� 3-�������� 4-�������� )
  CusNam   char(60)  not null,
--ת���̻���
  InAcNo   char(21)  not null,
--�����ʺ�
  InAcNm   char(60)  not null,
--�����˻�
  UniNo    char(4)   not null,
--�绰��������  0001���ƶ���0002����ͨ��0003��С��ͨ��0004���̶��绰
  MobTel   char(15)  not null,
--�ֻ�����
  Addr     char(60)  default '',
--��ַ
  FeeMod   char(1)   not null,
--�ͻ������շ�ģʽ
  FeeRat   char(6)   not null,
--�ͻ���������
  FeeAmt   char(15)  not null,
--�ͻ��������
  TFeeMod  char(1)   not null,
--�ͻ������շ�ģʽ
  TFeeRat  char(6)   not null,
--�ͻ���������
  TFeeAmt  char(15)  not null,
--�ͻ��������
  DeptNo   char(6)   not null,
--��������
  OpnBr    char(6)   not null,
--��������
  Sts      char(1)   not null,
--״̬( 0-��ͨ 1-���� )
  constraint PK_PCLTRMAGT PRIMARY KEY( PosTyp, MerId, TermId )
);
--
--
-- ת��POS�ɹ�������ϸ(����)��
--
--
create table PclDTxnDtl
(
  TxnSts        char(1)    default '0',
--״̬
  RefNo         char(12)   not null,
--ϵͳ�ο��ţ������������ļ��Ľ���ʱ�䣫POS����ˮ�Ź��ɣ�
  CtrPostDate   char(8)    not null,
--�����գ���������λ��չ��
  CtrDt         char(8)    not null,
--���׷�����
  CtrTime       char(6)    not null,
--����ʱ��
  TranAcc       char(19)   not null,
--ת�����ʺ�
  DMti          char(4)    not null,
--����������Ϣ��
  ProcCode      char(6)    not null,
--������
  CdFlag        char(1)    not null,
--�����־
  TranAmt       char(12)   not null,
--���׽��
  TxnAmt        char(15)   not null,
--������
  FeeAmt        char(15)   not null,
--�����ѽ��
  BnkFee        char(15)   not null,
--����������
  ThdFee        char(15)   not null,
--����������
  OrigRefNo     char(12)   not null,
--����ϵͳ�ο���
  MerId         char(15)   not null,
--�̻�����
  TermId        char(8)    not null,
--POS������
  CtrTrn        char(6)    not null,
--POS������ˮ��
  RepCode       char(6)    not null,
--������Ӧ��
  BankId        char(6)    not null,
--���д���
  TBusTp        char(4)    not null,
--ҵ�����
  LogNo         char(14)   default '',
--ǰ����ˮ��
  ActDat        char(8)    default '',
--�������
  HTxnSt        char(1)    default 'U',
--��������״̬
  HRspCd        char(6)    default '',
--����������
  TlrId         char(7)    default '',
--���й�Ա��
  ClrAct        char(21)   not null,
--���������˻�
  ActNo         char(21)   not null,
--ת�뿨�ʺ�
  ActNm         char(60)   not null,
--ת�뿨����
  TckNo         char(11)   default '',
--�����ˮ��
  DeptNo        char(6)    not null,
--���ź�
  OpnBr         char(6)    not null,
--��������
  ErrMsg        char(60)   default '',
--������Ϣ
  constraint PK_PCLDTXNDTL PRIMARY KEY( RefNo )
);
CREATE INDEX ni1_PCLDTXNDTL ON PclDTxnDtl( CtrPostDate, TxnSts );
--
--
-- ����POS�ɹ�������ϸ(����)��
--
--
create table PclITxnDtl
(
  TxnSts        char(1)    default '0',
--״̬
  CtrPostDate   char(8)    not null,
--�����գ���������λ��չ��
  TranAmt       char(12)   not null,
--���׽��
  TxnAmt        char(15)   not null,
--������
  FeeAmt        char(15)   not null,
--�����ѽ��
  PosTyp        char(1)    not null,
--�ն�����
  MerId         char(15)   not null,
--�̻�����
  TrmTyp        char(1)    not null,
--�ն�����( 0-���� 1-���� 2-ת�� 3-�������� 4-�������� )
  TermId        char(8)    not null,
--POS������
  LogNo         char(14)   not null,
--ǰ����ˮ��
  ActDat        char(8)    default '',
--�������
  HTxnSt        char(1)    default 'U',
--��������״̬
  HRspCd        char(6)    default '',
--����������
  ClrAct        char(21)   not null,
--���������˻�
  ActNo         char(21)   not null,
--ת�뿨�ʺ�
  ActNm         char(60)   not null,
--ת�뿨����
  TckNo         char(11)   default '',
--�����ˮ��
  DeptNo        char(6)    not null,
--���ź�
  OpnBr         char(6)    not null,
--��������
  ErrMsg        char(60)   default '',
--������Ϣ
  constraint PK_PCLITXNDTL PRIMARY KEY( LogNo )
);
CREATE INDEX ni1_PCLITXNDTL ON PclITxnDtl( CtrPostDate, TxnSts );
--
--
-- POS������Ϣ��
--
--
create table PclClrInf
(
  BrNo     char(6)   not null,
--�������
  ClrDat   char(8)   not null,
--��������
  PosTyp   char(1)   not null,
--POS����( 0-����  1-���� )
  TrmTyp   char(1)   not null,
--�ն�����( 0-���� 1-���� 2-ת�� 3-�������� 4-��������)
  SysSts   char(1)   not null,
--ϵͳ״̬( 0-�������ڶ��� 1-���ݶ���ɹ� 2-�ͻ��������ڽ��� 3-�ͻ�������� 4-�������������ڽ��� 5-������������� )
  DskNo    char(12)  default '',
--���̱��
  constraint PK_PCLCLRINF PRIMARY KEY( BrNo, ClrDat, PosTyp, TrmTyp )
);
--
--
-- ת��POS�����������
--
--
create table PclDFeeJnl
(
  LogNo    char(14)  not null,
--ǰ����ˮ��
  ClrBr    char(6)   not null,
--�������
  ClrDat   char(8)   not null,
--��������
  ClrTyp   char(1)   not null,
--��������( 0-���� 1-����)
  ActDat   char(8)   not null,
--�������
  HTxnSt   char(1)   default 'U',
--��������״̬
  HRspCd   char(6)   default '',
--����������
  TlrId    char(7)   not null,
--���й�Ա��
  TckNo    char(11)  default '',
--�����ˮ��
  ClrAct   char(21)  not null,
--�����˺�
  FeeAct   char(21)  not null,
--�����ʺŻ��������ʺ�
  TxnAmt   char(15)  not null,
--�����ѽ��
  constraint PK_PCLDFEEJNL PRIMARY KEY( LogNo )
);
--
--
-- ת��POS�����ѱ�
--
--
create table PclFeeRat
(
  Sts      char(1)   not null,
--״̬( 0-��Ч 1-��Ч )
  SysFlg   char(1)   not null,
--ϵͳ��־( 0-���� 1-ת�� )
  BrNo     char(6)   not null,
--���к�
  MinAmt   char(15)  not null,
--��ͽ��
  MaxAmt   char(15)  not null,
--��߽��
  FeeMod   char(1)   not null,
--�����շ�ģʽ
  FeeRat   char(5)   not null,
--����
  FeeAmt   char(15)  not null,
--���
  ValDt    char(8)   not null,
--��Ч����
  constraint PK_CBSFEERAT PRIMARY KEY( SysFlg, BrNo, MinAmt, MaxAmt )
);
