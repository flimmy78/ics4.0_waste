DROP TABLE rtytvchf;
-- ============================================================
--   ���ݹ���ϵͳ                      
--   Table: rtytvhcf   (��ʱ���ڴ�Ʊ��)
-- ============================================================


CREATE TABLE rtytvchf
(
vchf_jrn_no          char(9)   default '',
--������־��
vchf_vch_seq         char(4)   default '',
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
