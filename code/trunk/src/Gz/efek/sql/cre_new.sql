drop table EFEKRUNCTL;
drop table EFEKCUSAGT;
drop table EFEKBCHREC;
drop table EFEKTXNDTL;
drop table EFEKTXNJNL;
-- ============================================================
--   ϵͳ����״̬���Ʊ�
-- ============================================================
create table EFEKRUNCTL(
  DWBM   char(8)   not null,      --��λ����
  JYLSH  char(24)  not null,      --������ˮ��
  JYRQ   char(8)   not null,      --��������
  JYSJ   char(6)   default '',    --����ʱ��
--  GDDW   char(8)   default '',    --���絥λ
  YWBSH  char(6)   default '',    --ҵ���ʶ��
  CZRY   char(20)  default '',    --������Ա
  ZT     char(1)   default '',    --״̬( K����  Qǩ�� )
  BZ     char(128) default '',    --��ע
  BRNO   char(6)   default '',    --��������
  InAcNo char(40)  default '',    --�ռ�����˺�
  ClrAct char(40)  default '',     --���������˺�
  CONSTRAINT PK_EFEKRUNCTL PRIMARY KEY( DWBM )
);
-- ============================================================
--    ����ͻ�ǩԼ��
-- ============================================================
create table EFEKCUSAGT(
  ChkFlg   char(1)   default 'U',--�˶Ա�־( U-δ�˶ԣ�S-�˶Գɹ� F-�˶�ʧ�� )
  OIFLAG   char(1)   not null,   --���׷���
  DWBM     char(8)   not null,   --��λ����
	JFH	     char(20)	 not null,   --�ɷѺ�
  JSHMC	   char(64)  default '', --�����˻�����
  QYYHDM   char(4)	 default '', --ǩԼ���д���
  QYYHZH   char(40)  default '', --ǩԼ�����˻�
  QYYHZHMC char(128) default '', --ǩԼ�����˻�����
  ZHLX     char(2)   default '', --0�Թ��˻� 1��˽���� 2��˽���ÿ� 3��˽��ǿ� 4���
  ZJLX	   char(2)   default '', --֤������
  ZJHM     char(32)	 default '', --֤������
  LXDH     char(20)  default '', --��ϵ�绰
  SJHM     char(20)  default '', --�ֻ�����
  EMAIL    char(64)  default '', --����
  FQFJYLSH char(24)  default '', --���𷽽�����ˮ��
  FQFJYRQ  char(8)   default '', --���𷽽�������
  FQFJYSJ  char(6)   default '', --���𷽽���ʱ��
  JSFJYLSH char(24)  default '', --���շ�������ˮ��
  JSFJYRQ  char(8)   default '', --���շ���������
  JSFJYSJ  char(6)   default '', --���շ�����ʱ��
  QDBZ     char(1)   default '', --ǩԼ��־ 0���� 1�޸� 2ע��
  QYZT     char(1)   default '', --ǩԼ״̬ 1������ǩ 2�����ѱ����ȷ�� 3������ǩ
  NodNo    char(11)  default '', --�����
  BrNo     char(11)  default '', --���к�
  ActFlg   char(1)   not null,   --�����ڲ��˻�����(  0-�Թ� 1-���� 2-һ��ͨ 3-��ǿ� A-������� B-�ط����� )
  PfaSub   char(3)   default '', --��������
  BCusId   char(18)  default '', --Ԥ�㵥λ����
  PayCod   char(30)  default '', --�������֧������
  CONSTRAINT PK_EFEKCUSAGT PRIMARY KEY( DWBM,JFH )
);
-- ============================================================
--    ����ͻ�ǩԼ����ʷ��,��¼�ͻ�Э�����ĸ�������
-- ============================================================
create table EFEKCUSHIS(
  ChkFlg   char(1)   default 'U',--�˶Ա�־( U-δ�˶ԣ�S-�˶Գɹ� F-�˶�ʧ�� )
  OIFLAG   char(1)   not null,   --���׷���
  DWBM     char(8)   not null,   --��λ����
	JFH	     char(20)	 not null,   --�ɷѺ�
  JSHMC	   char(64)  default '', --�����˻�����
  QYYHDM   char(4)	 default '', --ǩԼ���д���
  QYYHZH   char(40)  default '', --ǩԼ�����˻�
  QYYHZHMC char(128) default '', --ǩԼ�����˻�����
  ZHLX     char(2)   default '', --0�Թ��˻� 1��˽���� 2��˽���ÿ� 3��˽��ǿ� 4���
  ZJLX	   char(2)   default '', --֤������
  ZJHM     char(32)	 default '', --֤������
  LXDH     char(20)  default '', --��ϵ�绰
  SJHM     char(20)  default '', --�ֻ�����
  EMAIL    char(64)  default '', --����
  FQFJYLSH char(24)  default '', --���𷽽�����ˮ��
  FQFJYRQ  char(8)   default '', --���𷽽�������
  FQFJYSJ  char(6)   default '', --���𷽽���ʱ��
  JSFJYLSH char(24)  default '', --���շ�������ˮ��
  JSFJYRQ  char(8)   default '', --���շ���������
  JSFJYSJ  char(6)   default '', --���շ�����ʱ��
  QDBZ     char(1)   default '', --ǩԼ��־ 0���� 1�޸� 2ע��
  QYZT     char(1)   default '', --ǩԼ״̬ 1������ǩ 2�����ѱ����ȷ�� 3������ǩ
  NodNo    char(11)  default '', --�����
  BrNo     char(11)  default '', --���к�
  ActFlg   char(1)   not null,   --�����ڲ��˻�����(  0-�Թ� 1-���� 2-һ��ͨ 3-��ǿ� A-������� B-�ط����� )
  PfaSub   char(3)   default '', --��������
  BCusId   char(18)  default '', --Ԥ�㵥λ����
  PayCod   char(30)  default '' --�������֧������
);
-- ============================================================
--    �������ۼ�¼��
-- ============================================================
create table EFEKBCHREC(
  RecSts  char(1)   default 'u',--������¼״̬( u-���պ� U-������� b-�������� B-��������� c������ C������� s��Ӧ���� S��Ӧ��� )
  OIFlag  char(1)   not null, --�����־( O-���з��� I-�������� )
--���ݰ�����
  FQFJYLSH	  char(24)  not null,   --������ˮ��
  FQFJYRQ	  char(8 )  default '', --��������
  FQFJYSJ	  char(6 )  default '', --����ʱ��
  DWBM	  char(8 )  default '', --��λ����
  SFFS	  char(3 )  default '', --�շѷ�ʽ
  FYLX	  char(3 )  default '', --��������
  KHBZ	  char(1 )  default '', --���б�־
  FQFWJMC	  char(36)  not null,   --�ļ�����
  FQFWJLX	  char(2 )  default '', --�ļ�����
  FQFWJMD5	  char(32)  default '', --�ļ�MD5
  ZBS	    char(11)  default '', --�ܱ���
  ZJE	    char(16)  default '', --�ܽ��
--�ļ�ͷ��һ������
  PLDSXXBS char(27) default '', --����������Ϣ��ʶ
  YHDM	  char(4 )  default '', --���д���
  SYHRQ	  char(8 )  default '', --����������
  HBFH	  char(5 )  default '', --���ҷ���
  DGBZ	  char(2 )  default '', --�Թ���־
  SM	    char(128) default '', --˵��
--��Ӧ�ļ���һ������
  JSFJYLSH char(24)  default '', --������ˮ��
  JSFYHJYRQ  char(8 )  default '', --��������
  JSFYHJYSJ	char(6 )  default '', --����ʱ��
  JSFWJMC	char(36)  default '', --�ļ�����
  JSFWJLX	char(2 )  default '', --�ļ�����
  JSFWJMD5	char(32)  default '', --�ļ�MD5
  CGBS    char(11)  default '', --�ɹ�����
  CGJE    char(16)  default '', --�ɹ����
  SBBS    char(11)  default '', --ʧ�ܱ���
  SBJE    char(16)  default '', --ʧ�ܽ��
  SFY     char(20)  default '', --�շ�Ա
  ActDat  char(8)   default '', --���л������
  DskNo   char(12)  default '', --�������̺�
  NodNo   char(6)   default '', --�����
  BrNo    char(6)   default '', --���к�
  CONSTRAINT PK_EFEKBCHREC PRIMARY KEY( OIFLAG, FQFJYLSH )
);
create unique index ni1_EFEKBCHREC ON EFEKBCHREC( OIFlag, FQFWJMC );
create index ni2_EFEKBCHREC ON EFEKBCHREC( DskNo );
-- ============================================================
--    ���罻����ϸ��
-- ============================================================
create table EFEKTXNDTL(
  DtlSts char(1)    default 'U', --��ϸ״̬( U-��ʼ B-������ S-�ɹ� F-ʧ�� C-����)
  BatFlg char(1)    not null, --������־( B-���� S-���� )
  TxnSrc char(3)    default '',  --������Դ( TRM-���� )
  WJMC	 char(36)   default '',  --�ļ�����
  OIFlag char(1)    not null, --�����־( O-���з��� I-�������� )
  FQFJYLSH char(24)   not null, --������ˮ��  
  XH       char(10)   not null default '0000000001',
  FQFJYRQ	 char(8 )   default '', --��������
  FQFJYSJ	 char(6 )   default '', --����ʱ��
  SFFS	 char(3 )   default '', --�շѷ�ʽ
  FYLX	 char(3 )   default '', --��������
  DWBM   char(20)   default '', --��λ����
  JFH    char(20)   default '', --�ɷѺ�
  JSHMC  char(64)   default '', --���㻧����
  KKYHDM char(4 )   default '', --�ۿ����д���
  KKZH   char(32)   default '', --�ۿ��˻�
  KKZHMC char(128)  default '', --�ۿ��˻�����
  BFJFBZ char(1 )   default '', --���ֽɷѱ�־
  ZWLSH  char(16)   default '', --������ˮ��
  DFNY   char(6 )   default '', --�������
  HBFH	 char(5 )   default 'RMB', --���ҷ���
  YKJE   char(16)   default '', --Ӧ�۽��
  BJ     char(16)   default '', --����
  WYJ    char(16)   default '', --ΥԼ��
  FKFS   char(1 )   default '', --���ʽ( 0-�ֽ� 1-���ֽ� )
  YFFBZ  char(1 )   default '', --Ԥ���ѱ�־
  YFFJE  char(16)   default '', --Ԥ���ѽ��
  SKJE   char(16)   default '', --ʵ�۽��
  XJYDGJXX char(128) default '', --Э��ŵ�(��У��Ĺؼ���Ϣ)
  TSBZ   char(1)    default '', --���ձ�־
  KKRQ   char(8 )   default '', --�ۿ�����
  KKSJ   char(6 )   default '', --�ۿ�ʱ��
  CXYY   char(128)  default '', --����ԭ��
  PJLY   char(1)    default '', --Ʊ����Դ(	0-�������� 1-�����ṩ )
  PJLX   char(2)    default '', --Ʊ������( 1-��ͨ��Ʊ 2-�վ� )
  FPDM   char(32)   default '', --��Ʊ����
  PJHM   char(16)   default '', --Ʊ�ݺ���
--�����ڲ�Ҫ��
  LogNo  char(14)   default '', --ǰ����ˮ��
  DskNo  char(12)   default '', --�������̺�
  ActDat char(8)    default '', --�������
  IsTxn  char(1)    default 'N',--�Ƿ���������־������������Сͨ������  Y����N������
  TxnObj char(8)    default '',--��Сͨ��Ŀ�����
  UpdFlg char(1)    default 'N',--���±�־
  UpdFld char(20)   default 'HTXNCD|BUSTYP|',--�����ֶ���
  TTxnCd char(6)    default '', --ǰ�ý�����
  TTxnSt char(1)    default '', --������״̬
  HTxnCd char(6)    default '', --����������
  HTxnSt char(1)    default 'U',--����״̬
  HLogNo char(9)    default '', --������ˮ��
  HRspCd char(6)    default '', --����������
  TRspCd char(6)    default '', --����������
  TlrId  char(7)    default '', --��Ա��
  TrmNo  char(7)    default '', --�ն˺�
  TckNo  char(11)   default '', --�����ˮ��
  RspCod char(6)    default '', --���д�������
  InAcNo char(40)   default '', --�ռ�����˺�
  NodNo  char(11)   default '', --�����
  BrNo   char(11)   default '', --���к�
  JSFJYLSH char(24)  default '', --������ˮ��
  JSFJYRQ char(8 )   default '', --��������
  JSFJYSJ char(6 )   default '', --����ʱ��
  YHSFLSH char(27)   default '', --������ˮ��
  DAZRQ  char(8 )   default '', --��������
  DAZSJ  char(6 )   default '', --����ʱ��
  DZPCLSH char(27)  default '', --����������ˮ��
  CONSTRAINT PK_EFEKTXNDTL PRIMARY KEY( OIFLAG, FQFJYLSH, XH )
); 
create index ni1_EFEKTXNDTL ON EFEKTXNDTL( LogNo );
create index ni2_EFEKTXNDTL ON EFEKTXNDTL( FQFWJMC );
-- ============================================================
--    ���罻����ˮ��
-- ============================================================
create table EFEKTXNJNL(
  LogNo      char(14)  not null,
--ǰ����ˮ��
  TTxnCd     char(10)  not null,
--������������
  TxnCod     char(6)   not null,
--������
  TxnTyp     char(1)   default 'N',
--��������( N-�������� C-�������� R-�ط����� )
  BusTyp     char(6)   default '',
--ҵ������
  CrpCod     char(12)  default '',
--��λ����
  ActDat     char(8)   not null,
--�������
  CcyCod     char(3)   default '',
--���Ҵ���
  TxnAmt     char(15)  not null,
--���׽��
  ActNo      char(21)  default '',
--�ͻ��ʺ�
  ActNam     char(60)  default '',
--�ͻ�����
  NodNo      char(6)   default '',
--���������
  TlrId      char(7)   not null,
--���й�Ա��
  NodTrc     char(20)  default '',
--������ˮ��
  TxnCnl     char(3)   default '',
--��������
  FTxnTm     char(14)  default '',
--ǰ�ý���ʱ��
  FRspCd     char(6)   default '',
--ǰ����Ӧ��
  HLogNo     char(9)   default '',
--������ˮ��
  TckNo      char(11)  default '',
--�����ˮ��
  HRspCd     char(6)   default '',
--������Ӧ��
  HTxnSt     char(1)   default 'U',
--��������״̬( S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ E-��� )
  TTxnSt     char(1)   default 'U',
--����������״̬(  S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ )
  TxnSts     char(1)   default 'U',
--����״̬( S-�ɹ� F-ʧ�� R-������ U-Ԥ��״̬ )
  BrNo       char(6)   not null,
--���к�
  VchTyp     char(3)   default '',
--����ƾ֤����
  VchNo      char(30)  default '',
--����ƾ֤���
  UdwDat     char(8)   default '',
--ǩ������
  VchCod     char(8)   default '',
--ƾ֤����
  Pin        char(16)  default '',
--֧������
  Smr        char(60)  default '',
--��;
  CclAct     char(21)  default '',
--�����ʺ�
  CclNo      char(12)  default '',
--���ʺ�
  CclSqn     char(4)   default '',
--�������
  PrvDat     clob(3072) default '',
  CONSTRAINT PK_EFEKTXNJNL PRIMARY KEY( LogNo )
);
