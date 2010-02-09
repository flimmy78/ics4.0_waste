drop table yctreg;

create table yctreg
(
	sign_flag   char(1),  
--ǩԼ���� 1���ֹ�ǩԼ 2���绰ǩԼ 3������ǩԼ
	inst_no     char(9),  
--ǩԼ���� 
	live_flag   char(1),  
--�����־ 0-���� 1-δ����
	tran_flag   char(1),  
--���ױ�־ 0-������ 1-��������
	acc_type    char(1),  
--�ۿʽ 1:Ԥ�ۿ��û� 0:ʵʱ�ۿ��û�
	yct_pwd     char(10),  
--���ͨ���� 
	bank_acc    char(30),  
--�˺� 
	oper_tlr    char(3),  
--����Ա 
	tran_date   char(14),  
--�������� 
	sys_no      char(12),  
--ϵͳ�ο��� 
	ret_code    char(2),  
--��Ӧ���� 00-��ʾ���ͨ���سɹ�
	paper_no    char(21),  
--֤�����ͺ��� 
	contact_no  char(20),  
--��ͬ��� 
	cust_name   char(30),  
--�û����� 
	sex_code    char(1),  
--�Ա� 
	phone_no    char(15),  
--�绰���� 
	mobile_no   char(15),  
--�ֻ����� 
	post_no     char(6),  
--�ʱ� 
	address     char(50),  
--��ַ 
	email       char(50),  
--email���� 
	card1       char(10),  
--���ͨ����1 
	card2       char(10),  
--���ͨ����2 
	card3		    char(10),  
--���ͨ����3 
	card4       char(10),  
--���ͨ����4 
	limite      char(12),  
--��� 
	frequence   char(4),  
--Ƶ�� 
	reg_date    char(4),  
--ǩԼ���� 
	cncl_date   char(4),  
--��Լ���� 
	cncl_flag   char(4),  
--ǩ��Լ��־ 0-ǩԼ 1-��Լ
	reserve1    char(30),  
--Ԥ���ֶ�1 
	reserve2    char(30),  
--Ԥ���ֶ�2 
	reserve3    char(30),  
--Ԥ���ֶ�3 
	reserve4    char(60),  
--Ԥ���ֶ�4 
	reserve5    char(60)
--Ԥ���ֶ�5 
);

create unique index pk_yctreg on yctreg(bank_acc,card1,sys_no);
