DROP TABLE rtyactdtl;
DROP TABLE rtypayout;
DROP TABLE rtyactinf;
DROP TABLE rtyactiot;
DROP TABLE rtypaymnt;
DROP TABLE rtycdtmst;           
DROP TABLE rtyfmpmng;
DROP TABLE rtytvchf;
DROP TABLE rtyfmpinf;
-- ============================================================
--   ���ݹ���ϵͳ
--   Table: rtyactdtl   (����ʻ�����ת���տ���ϸ��)
-- ============================================================
CREATE TABLE rtyactdtl
(
	BkAct					CHAR(50)				DEFAULT '',
--����ʻ�
	PayNo					CHAR(20)				DEFAULT '',
--�ɿ�֪ͨ����
	InDat					CHAR(8)					DEFAULT '',
--�տ�����
	InAmt					CHAR(17)				DEFAULT '',
--ת����
	IfOsd					CHAR(1)					DEFAULT '',
--�Ƿ����
	VchNo					CHAR(12)				DEFAULT '',
--��Ʊ��
	BusLog				CHAR(14)				DEFAULT '',
--ҵ����ˮ��
	Status				CHAR(1)					DEFAULT ''
--״̬
) ;
create index rtyactdtl_idx  on rtyactdtl(InDat,BkAct);
create index rtyactdtl_idx1 on rtyactdtl(InDat,PayNO);
                               
create table rtycdtmst
(           
ac_no                          char(21),
last_dt                        char(8),
last_tlr                       char(7),
tt_tmp                         char(3),
ac_sts                         char(1),
ac_name                        char(60),
open_br                        char(6),
ac_bk                          char(6),
ac_stswrd                      char(30),
ccy                            char(3),
ccy_type                       char(1),
bal                            char(17),
last_bal                       char(17),
accu_date                      char(8),
accu                           char(19),
adp_accu                       char(19),
ovr_accu                       char(19),
day_fbal                       char(17),
ibp_fbal                       char(17),
nday_fbal                      char(17),
adp_valdate                    char(8),
adp_bal                        char(17),
adp_int_code                   char(4),
adp_int_rate                   char(8),
ibac_flag                      char(1),
pay_type                       char(1),
int_method                     char(1),
fee_period                     char(1),
com_type                       char(2),
dep_type                       char(1),
frg_code                       char(8),   
frg_kind                       char(3),
cny_kind                       char(2),
page_flg                       char(1),
license_expdate                char(8),
ac_expdate                     char(8),
hold_cnt                       char(8),   
hold_amt                       char(17),
temp_hold_date                 char(8),
temp_hold_type                 char(1),
temp_code_amt                  char(17),
unint_amt                      char(17),
bud_int                        char(15),
int                            char(15),
ovr_int                        char(15),
last_int_date                  char(8),
last_ovrint_date               char(8),
int_date                       char(8),
sub_int_date                   char(8),
sub_adpint_date                char(8),
sub_ovrint_date                char(8),
int_code                       char(4),
int_rsel                       char(1),
int_rate                       char(8),
ovr_int_code                   char(4),
ovr_int_rate                   char(8),
ovr_limit                      char(17),
max_ovrbal                     char(17),
ovr_tt                         char(3),
ovr_valdate                    char(8),
ovr_expdate                    char(8),
first_ovrdate                  char(8),
ovr_enddate                    char(8),
ovr_flag                       char(1),
feerate_flg                    char(1),
open_date                      char(8),
dorm_type                      char(1),
dorm_date                      char(8),
ln_cnt                         char(8),   
td_cnt                         char(8),   
be_cnt                         char(8),   
rm_cnt                         char(8),   
dc_cnt                         char(8),   
edi_cnt                        char(8),   
gm_cnt                         char(8),   
close_br                       char(6),
close_tlr                      char(7),
close_date                     char(8),
cp_flg                         char(1)
) ;                                     
-- ============================================================
--   ���ݹ���ϵͳ
--   Table: rtypayout   (����ʺ�֧����Ϣ��)
-- ============================================================
CREATE TABLE rtypayout
(
	LogNo					CHAR(14)			NOT NULL,
--ǰ����ˮ��
	TxnCod				CHAR(6)				NOT NULL,
--ǰ�ý�����
	ActDat				CHAR(8)				NOT NULL,
--�������
	CcyCod				CHAR(3)				DEFAULT '',
--����
	OrgNo					CHAR(6)				DEFAULT '',
--������
	NodNo					CHAR(6)				DEFAULT '',
--���������
	TlrId					CHAR(7)				NOT NULL,
--���й�Ա��
	CntrId				CHAR(10)			DEFAULT '',
--���й�̨��
	NodTrc				CHAR(20)			DEFAULT '',
--������ˮ��
	FTxnTm				CHAR(14)			NOT NULL,
--ǰ�ý���ʱ��
	ThdChk				CHAR(1)				DEFAULT '0',
--����������ʱ�־
	TxnSts				CHAR(1)				DEFAULT 'U',
--����״̬
	AuthNo				CHAR(20)			NOT NULL,
--֧����׼����
	BkAct					CHAR(50)			NOT NULL,
--����ʺ�
	BkCod					CHAR(10)			DEFAULT '',
--������д���
	PotAmt				CHAR(17)			NOT NULL,
--֧�����
	GtrAct				CHAR(50)			NOT NULL,
--�տ����ʺ�
	GtrNam				CHAR(100)			NOT NULL,
--�տ�������
	PotTim				CHAR(14)			NOT NULL,
--����ʱ��
	BkBal					CHAR(17)			NOT NULL,
--����ʺ����
	BusLog				CHAR(14)			NOT NULL,
--ҵ����ˮ��
	BkSts					CHAR(1)				NOT NULL,
--״̬
	Inform				VARCHAR(300)	DEFAULT ''
--��Ϣ
) ; 
create index rtypayout_idx  on rtypayout(ActDat,BkAct);
create index rtypayout_idx1 on rtypayout(ActDat,AuthNo);
-- ============================================================
--   ���ݹ���ϵͳ
--   Table: rtyactinf   (����ʺ���Ϣ��)
-- ============================================================
CREATE TABLE rtyactinf
(
	NodNo					CHAR(6)				DEFAULT '',
--���������
	CrpNam				VARCHAR(50)			DEFAULT '',
--��˾����
	BkAct					CHAR(50)				NOT NULL,
--����ʻ�
	BkCod					CHAR(10)				NOT NULL,
--������д���
	PSlCod				CHAR(20)				NOT NULL,
--Ԥ��֤
	PrjNam				VARCHAR(100)		NOT NULL,
--��Ŀ����
	Status				CHAR(1)					NOT NULL
--״̬
) ; 
-- ============================================================
--   ���ݹ���ϵͳ
--   Table: rtyfmpmng   (���ֽܾ����ʻ������)
-- ============================================================
create table rtyfmpmng
(
FMPAcc			char(6)		not null,
--�����û��ʻ�
FMPPwd			char(10)	not null,
--��������
SeqnoId     char(4)   default '0000' 
--��Ϣ��ˮ��
) ;
-- ============================================================
--   ���ݹ���ϵͳ                      
--   Table: rtytvhcf   (��ʱ���ڴ�Ʊ��)
-- ============================================================
CREATE TABLE rtytvchf
(
vchf_jrn_no          char(9)   default '',
--������־��
vchf_vch_seq         char(2)   default '',
--��Ʊ���׺�
vchf_ap_code         char(2)   default '',
--Ӧ����
vchf_ap_mmo          char(2)   default '',
--Ӧ�÷�
vchf_tr_code         char(4)   default '',
--������
vchf_tr_mmo          char(3)   default '',
--��������
vchf_tr_date         char(8)   default '',
--��������
vchf_tr_time         char(6)   default '',
--����ʱ��
vchf_bk              char(6)   default '',
--���׻�����������
vchf_br              char(6)   default '',
--���׻�����
vchf_dp              char(3)   default '',
--���ź�
vchf_vch_no          char(12)  default '',
--��Ʊ��
vchf_tm_no           char(7)   default '',
--�����ն˺�
vchf_his_prt         char(1)   default '',
--��ʷ���ӡ��־��Y/N��
vchf_reen_flag       char(1)   default '',
--�����־(Y/N/F)
vchf_vch_ec_ind      char(1)   default '',
--�������״�Ʊ��־����/Y��
vchf_wff_flag        char(1)   default '',
--���˱�־(Y/N/F/C)
vchf_sup1_id         char(7)   default '',
--������Ȩ����1
vchf_sup2_id         char(7)   default '',
--������Ȩ����2
vchf_conf_id         char(7)   default '',
--���׸��˹�Ա
vchf_vch_type        char(1)   default '',
--��ʷ��¼���ͣ�A/B/C/D/N/F��
vchf_vch_confirm     char(1)   default '',
--��Ʊ��Ч�ձ�־            
vchf_vch_bk          char(6)   default '',
--�ʻ�������������
vchf_vch_br          char(6)   default '',
--�ʻ�������
vchf_vch_ccy         char(3)   default '',
--������
vchf_vch_jj          char(3)   default '',
--��ҵ��
vchf_vch_tt          char(3)   default '',
--ҵ�������
vchf_vch_ac          char(21)  default '',
--�ʺ�
vchf_vch_sign        char(1)   default '',
--�������־
vchf_vch_amt         char(17)  default '',
--���
vchf_vch_val_date    char(8)   default '',
--��Ϣ��
vchf_vch_stno_type   char(3)   default '',
--ƾ֤����
vchf_vch_stno        char(8)   default '',
--���ݺ���
vchf_vch_opp_ind     char(1)   default '',
--ϵͳ���˺ű�־
vchf_vch_opp_ac      char(32)  default '',
--�Է��ʺ�
vchf_vch_part        char(24)  default '',
--����ժҪ
vchf_vch_part_b      char(60)  default '',
--ҵ��ժҪ
vchf_vch_m_ind       char(1)   default '',
--��Ʊ�ϲ���־
vch_c_ind            char(1)   default ''	
--�ල��־
) ;
-- ============================================================
--   ���ݹ���ϵͳ
--   Table: rtyactiot   (����ʻ���֧��)
-- ============================================================
CREATE TABLE rtyactiot
(
	BkAct					CHAR(50)				NOT NULL,
--����ʻ�
	BkDat					CHAR(8)					NOT NULL,
--�������
	BalOut				CHAR(17)				NOT NULL,
--����֧�����
	BalIn					CHAR(17)				NOT NULL,
--����������
	BalAmt				CHAR(17)				NOT NULL,
--�����˻����
	Status				CHAR(1)					NOT NULL
--״̬
) ; 
create index rtyactiot_idx on rtyactiot(BkDat,BkAct);
-- ============================================================
--   ���ݹ���ϵͳ
--   Table: rtypaymnt   (��Ʒ���ɿ���Ϣ��)
-- ============================================================
CREATE TABLE rtypaymnt
(
	LogNo					CHAR(14)		NOT NULL,
--ǰ����ˮ��
	TxnCod				CHAR(6)			NOT NULL,
--ǰ�ý�����
	ActDat				CHAR(8)			NOT NULL,
--�������
	CcyCod				CHAR(3)			DEFAULT '',
--����
	OrgNo					CHAR(6)			DEFAULT '',
--������
	NodNo					CHAR(6)			DEFAULT '',
--���������
	TlrId					CHAR(7)			NOT NULL,
--���й�Ա��
	CntrId				CHAR(10)		DEFAULT '',
--���й�̨��
	NodTrc				CHAR(20)		DEFAULT '',
--������ˮ��
	FTxnTm				CHAR(14)		NOT NULL,
--ǰ�ý���ʱ��
	ThdChk				CHAR(1)			DEFAULT '0',
--����������ʱ�־
	TxnSts				CHAR(1)			DEFAULT 'U',
--����״̬
	PayNo					CHAR(20)		NOT NULL,
--�ɿ�֪ͨ����
	BkAct					CHAR(50)		NOT NULL,
--����ʺ�
	BkCod					CHAR(10)		NOT NULL,
--������д���
	PblDat				CHAR(8)			NOT NULL,
--��������
	PblAmt				CHAR(17)		NOT NULL,
--������
	PblBk					CHAR(10)		NOT NULL,
--�ɿ����д���
	PblAct				CHAR(50)		NOT NULL,
--�ɿ��ʺ�
	IfOsd					CHAR(1)			NOT NULL,
--�Ƿ����
	BusLog				CHAR(14)		NOT NULL,
--ҵ����ˮ��
	CntCod				CHAR(20)		DEFAULT '',
--��ͬ��
	TrmCod				CHAR(3)			DEFAULT '',
--����
	BkSts					CHAR(1)			NOT NULL,
--״̬
	Inform				VARCHAR(300)	DEFAULT ''
--��Ϣ
) ; 
create index rtypaymnt_idx  on rtypaymnt(ActDat,BkAct);
create index rtypaymnt_idx1 on rtypaymnt(ActDat,PayNo);
-- ============================================================
--   ���ݹ���ϵͳ
--   Table: rtyfmpinf  (�����������ʻ������)
-- ============================================================
create table rtyfmpinf
(
FMPAcc      char(6)   not null,
--�����û��ʻ�
FMPPwd      char(10)  not null,
--��������
SeqnoId     char(4)   default '0000'
--��Ϣ��ˮ��
) ;
