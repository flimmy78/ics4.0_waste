DROP TABLE rtytvchf;
-- ============================================================
--   房屋管理系统                      
--   Table: rtytvhcf   (临时金融传票表)
-- ============================================================


CREATE TABLE rtytvchf
(
vchf_jrn_no          char(9)   default '',
--交易日志号
vchf_vch_seq         char(4)   default '',
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
