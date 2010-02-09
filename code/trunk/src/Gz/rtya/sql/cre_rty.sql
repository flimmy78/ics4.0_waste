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
--   房屋管理系统
--   Table: rtyactdtl   (监控帐户跨行转帐收款明细表)
-- ============================================================
CREATE TABLE rtyactdtl
(
	BkAct					CHAR(50)				DEFAULT '',
--监控帐户
	PayNo					CHAR(20)				DEFAULT '',
--缴款通知书编号
	InDat					CHAR(8)					DEFAULT '',
--收款日期
	InAmt					CHAR(17)				DEFAULT '',
--转入金额
	IfOsd					CHAR(1)					DEFAULT '',
--是否跨行
	VchNo					CHAR(12)				DEFAULT '',
--传票号
	BusLog				CHAR(14)				DEFAULT '',
--业务流水号
	Status				CHAR(1)					DEFAULT ''
--状态
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
--   房屋管理系统
--   Table: rtypayout   (监控帐号支出信息表)
-- ============================================================
CREATE TABLE rtypayout
(
	LogNo					CHAR(14)			NOT NULL,
--前置流水号
	TxnCod				CHAR(6)				NOT NULL,
--前置交易码
	ActDat				CHAR(8)				NOT NULL,
--会计日期
	CcyCod				CHAR(3)				DEFAULT '',
--货币
	OrgNo					CHAR(6)				DEFAULT '',
--机构号
	NodNo					CHAR(6)				DEFAULT '',
--银行网点号
	TlrId					CHAR(7)				NOT NULL,
--银行柜员号
	CntrId				CHAR(10)			DEFAULT '',
--银行柜台号
	NodTrc				CHAR(20)			DEFAULT '',
--网点流水号
	FTxnTm				CHAR(14)			NOT NULL,
--前置交易时间
	ThdChk				CHAR(1)				DEFAULT '0',
--与第三方对帐标志
	TxnSts				CHAR(1)				DEFAULT 'U',
--交易状态
	AuthNo				CHAR(20)			NOT NULL,
--支出批准书编号
	BkAct					CHAR(50)			NOT NULL,
--监控帐号
	BkCod					CHAR(10)			DEFAULT '',
--监控银行代码
	PotAmt				CHAR(17)			NOT NULL,
--支出金额
	GtrAct				CHAR(50)			NOT NULL,
--收款人帐号
	GtrNam				CHAR(100)			NOT NULL,
--收款人名称
	PotTim				CHAR(14)			NOT NULL,
--划款时间
	BkBal					CHAR(17)			NOT NULL,
--监控帐号余额
	BusLog				CHAR(14)			NOT NULL,
--业务流水号
	BkSts					CHAR(1)				NOT NULL,
--状态
	Inform				VARCHAR(300)	DEFAULT ''
--信息
) ; 
create index rtypayout_idx  on rtypayout(ActDat,BkAct);
create index rtypayout_idx1 on rtypayout(ActDat,AuthNo);
-- ============================================================
--   房屋管理系统
--   Table: rtyactinf   (监控帐号信息表)
-- ============================================================
CREATE TABLE rtyactinf
(
	NodNo					CHAR(6)				DEFAULT '',
--开户网点号
	CrpNam				VARCHAR(50)			DEFAULT '',
--公司名称
	BkAct					CHAR(50)				NOT NULL,
--监控帐户
	BkCod					CHAR(10)				NOT NULL,
--监控银行代码
	PSlCod				CHAR(20)				NOT NULL,
--预售证
	PrjNam				VARCHAR(100)		NOT NULL,
--项目名称
	Status				CHAR(1)					NOT NULL
--状态
) ; 
-- ============================================================
--   房屋管理系统
--   Table: rtyfmpmng   (房管局接入帐户管理表)
-- ============================================================
create table rtyfmpmng
(
FMPAcc			char(6)		not null,
--接入用户帐户
FMPPwd			char(10)	not null,
--接入密码
SeqnoId     char(4)   default '0000' 
--信息流水号
) ;
-- ============================================================
--   房屋管理系统                      
--   Table: rtytvhcf   (临时金融传票表)
-- ============================================================
CREATE TABLE rtytvchf
(
vchf_jrn_no          char(9)   default '',
--交易日志号
vchf_vch_seq         char(2)   default '',
--传票内套号
vchf_ap_code         char(2)   default '',
--应用码
vchf_ap_mmo          char(2)   default '',
--应用符
vchf_tr_code         char(4)   default '',
--交易码
vchf_tr_mmo          char(3)   default '',
--交易子码
vchf_tr_date         char(8)   default '',
--交易日期
vchf_tr_time         char(6)   default '',
--交易时间
vchf_bk              char(6)   default '',
--交易机构所属分行
vchf_br              char(6)   default '',
--交易机构号
vchf_dp              char(3)   default '',
--部门号
vchf_vch_no          char(12)  default '',
--传票号
vchf_tm_no           char(7)   default '',
--交易终端号
vchf_his_prt         char(1)   default '',
--历史项打印标志（Y/N）
vchf_reen_flag       char(1)   default '',
--重入标志(Y/N/F)
vchf_vch_ec_ind      char(1)   default '',
--更正交易传票标志（空/Y）
vchf_wff_flag        char(1)   default '',
--复核标志(Y/N/F/C)
vchf_sup1_id         char(7)   default '',
--交易授权主管1
vchf_sup2_id         char(7)   default '',
--交易授权主管2
vchf_conf_id         char(7)   default '',
--交易复核柜员
vchf_vch_type        char(1)   default '',
--历史记录类型（A/B/C/D/N/F）
vchf_vch_confirm     char(1)   default '',
--传票生效日标志            
vchf_vch_bk          char(6)   default '',
--帐户机构所属分行
vchf_vch_br          char(6)   default '',
--帐户机构号
vchf_vch_ccy         char(3)   default '',
--货币码
vchf_vch_jj          char(3)   default '',
--作业码
vchf_vch_tt          char(3)   default '',
--业务类别码
vchf_vch_ac          char(21)  default '',
--帐号
vchf_vch_sign        char(1)   default '',
--借贷方标志
vchf_vch_amt         char(17)  default '',
--金额
vchf_vch_val_date    char(8)   default '',
--起息日
vchf_vch_stno_type   char(3)   default '',
--凭证类型
vchf_vch_stno        char(8)   default '',
--单据号码
vchf_vch_opp_ind     char(1)   default '',
--系统内账号标志
vchf_vch_opp_ac      char(32)  default '',
--对方帐号
vchf_vch_part        char(24)  default '',
--技术摘要
vchf_vch_part_b      char(60)  default '',
--业务摘要
vchf_vch_m_ind       char(1)   default '',
--传票合并标志
vch_c_ind            char(1)   default ''	
--监督标志
) ;
-- ============================================================
--   房屋管理系统
--   Table: rtyactiot   (监控帐户收支表)
-- ============================================================
CREATE TABLE rtyactiot
(
	BkAct					CHAR(50)				NOT NULL,
--监控帐户
	BkDat					CHAR(8)					NOT NULL,
--监控日期
	BalOut				CHAR(17)				NOT NULL,
--当日支出金额
	BalIn					CHAR(17)				NOT NULL,
--当日收入金额
	BalAmt				CHAR(17)				NOT NULL,
--当日账户余额
	Status				CHAR(1)					NOT NULL
--状态
) ; 
create index rtyactiot_idx on rtyactiot(BkDat,BkAct);
-- ============================================================
--   房屋管理系统
--   Table: rtypaymnt   (商品房缴款信息表)
-- ============================================================
CREATE TABLE rtypaymnt
(
	LogNo					CHAR(14)		NOT NULL,
--前置流水号
	TxnCod				CHAR(6)			NOT NULL,
--前置交易码
	ActDat				CHAR(8)			NOT NULL,
--会计日期
	CcyCod				CHAR(3)			DEFAULT '',
--货币
	OrgNo					CHAR(6)			DEFAULT '',
--机构号
	NodNo					CHAR(6)			DEFAULT '',
--银行网点号
	TlrId					CHAR(7)			NOT NULL,
--银行柜员号
	CntrId				CHAR(10)		DEFAULT '',
--银行柜台号
	NodTrc				CHAR(20)		DEFAULT '',
--网点流水号
	FTxnTm				CHAR(14)		NOT NULL,
--前置交易时间
	ThdChk				CHAR(1)			DEFAULT '0',
--与第三方对帐标志
	TxnSts				CHAR(1)			DEFAULT 'U',
--交易状态
	PayNo					CHAR(20)		NOT NULL,
--缴款通知书编号
	BkAct					CHAR(50)		NOT NULL,
--监控帐号
	BkCod					CHAR(10)		NOT NULL,
--监控银行代码
	PblDat				CHAR(8)			NOT NULL,
--付款日期
	PblAmt				CHAR(17)		NOT NULL,
--付款金额
	PblBk					CHAR(10)		NOT NULL,
--缴款银行代码
	PblAct				CHAR(50)		NOT NULL,
--缴款帐号
	IfOsd					CHAR(1)			NOT NULL,
--是否跨行
	BusLog				CHAR(14)		NOT NULL,
--业务流水号
	CntCod				CHAR(20)		DEFAULT '',
--合同号
	TrmCod				CHAR(3)			DEFAULT '',
--期数
	BkSts					CHAR(1)			NOT NULL,
--状态
	Inform				VARCHAR(300)	DEFAULT ''
--信息
) ; 
create index rtypaymnt_idx  on rtypaymnt(ActDat,BkAct);
create index rtypaymnt_idx1 on rtypaymnt(ActDat,PayNo);
-- ============================================================
--   房屋管理系统
--   Table: rtyfmpinf  (存量房接入帐户管理表)
-- ============================================================
create table rtyfmpinf
(
FMPAcc      char(6)   not null,
--接入用户帐户
FMPPwd      char(10)  not null,
--接入密码
SeqnoId     char(4)   default '0000'
--信息流水号
) ;
