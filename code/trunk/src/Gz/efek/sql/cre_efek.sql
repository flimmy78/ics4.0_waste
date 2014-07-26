-- ============================================================
--   �������ҵ��
--    ����ͻ�ǩԼ��
-- ============================================================
CREATE TABLE efekcusagt(
  BrNo        CHAR(6)         DEFAULT ' ',    --���к�
  NodNo       CHAR(6)         DEFAULT ' ',    --������
  CAgtNo      CHAR(10)        DEFAULT ' ',    --��λ���
  WDMC        CHAR(64)        DEFAULT ' ',    --��������
  QDBZ        CHAR(1)         DEFAULT ' ',    --ǩ����־
  JFH         CHAR(20)        DEFAULT ' ',    --�ɷѺ�
  JSHMC       CHAR(64)        DEFAULT ' ',    --���㻧����
  XQYYHDM     CHAR(4)         DEFAULT ' ',    --ǩԼ���д���
  XQYZH       CHAR(32)        DEFAULT ' ',    --ǩԼ�˻�
  XQYZHMC     CHAR(128)       DEFAULT ' ',    --ǩԼ�˻�����
  ZHLX        CHAR(2)         DEFAULT ' ',    --�˻�����
  ZJLX        CHAR(2)         DEFAULT ' ',    --֤������
  ZJHM        CHAR(32)        DEFAULT ' ',    --֤������
  LXDH        CHAR(20)        DEFAULT ' ',    --��ϵ�绰
  SJHM        CHAR(20)        DEFAULT ' ',    --�ֻ�����
  EMAIL       CHAR(64)        DEFAULT ' ',    --E-MAIL
  BZ          CHAR(128)       DEFAULT ' ',    --��ע
);

-- ============================================================
--   �������ҵ��
--    ������
-- ============================================================
CREATE TABLE efekinfctl(
  BrNo        CHAR(6)         DEFAULT ' ',    --���к�
  NodNo       CHAR(6)         DEFAULT ' ',    --������
  CAgtNo      CHAR(10)        DEFAULT ' ',    --��λ���
  JYLSH       CHAR(24)        DEFAULT ' ',    --������ˮ��
  JYRQ        CHAR��8��       DEFAULT ' ',    --��������
  JYSJ        CHAR (6)        DEFAULT ' ',    --����ʱ��
  GDDW        CHAR(8)         DEFAULT ' ',    --���絥λ
  YWBSH       CHAR(6)         DEFAULT ' ',    --ҵ���ʶ��
  DWBM        CHAR(8)         DEFAULT ' ',    --��λ����
  CZRY        CHAR(20)        DEFAULT ' ',    --������Ա
  ZT          CHAR(1)         DEFAULT ' ',    --״̬
  BZ          CHAR(128)       DEFAULT ' ',    --��ע
);

-- ============================================================
--   �������ҵ��
--    ������ϸ��(������)
-- ============================================================
CREATE TABLE efekchkdtl(
  BrNo        CHAR(6)         DEFAULT ' ',    --���к�
  LogNo       CHAR(14)        DEFAULT ' ',    --������
  TLogNo      CHAR(30)        DEFAULT ' ',    --��λ���
  ActTyp      CHAR(1)         DEFAULT ' ',    --�ۿ��˻�����
  JYLSH       CHAR(24)        DEFAULT ' ',    --������ˮ��
  JYRQ        CHAR(8)         DEFAULT ' ',    --��������
  JYSJ        CHAR(6)         DEFAULT ' ',    --����ʱ��
  SFFS        CHAR(3)         DEFAULT ' ',    --�շѷ�ʽ
  FYLX        CHAR(3)         DEFAULT ' ',    --��������
  RZYHDM      CHAR(4)         DEFAULT ' ',    --�������д���
  DWBM        CHAR(8)         DEFAULT ' ',    --��λ����
  JFH         CHAR(20)        DEFAULT ' ',    --�ɷѺ�
  JSHMC       CHAR(64)        DEFAULT ' ',    --���㻧����
  YDDZ        CHAR(128)       DEFAULT ' ',    --�õ��ַ
  KKZH        CHAR(32)        DEFAULT ' ',    --�ۿ��˻�
  KKZHMC      CHAR(128)       DEFAULT ' ',    --�ۿ��˻�����
  BFJFBZ      CHAR(1)         DEFAULT ' ',    --���ֽɷѱ�־
  ZWLSH       CHAR(16)        DEFAULT ' ',    --������ˮ��
  DFNY        CHAR(6)         DEFAULT ' ',    --�������
  HBFH        CHAR(5)         DEFAULT ' ',    --���ҷ���
  SKJE        CHAR(16)        DEFAULT ' ',    --ʵ�۽��
); 