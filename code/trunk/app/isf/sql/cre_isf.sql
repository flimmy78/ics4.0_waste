drop table yctreg;

create table yctreg
(
	sign_flag   char(1),  
--签约类型 1：手工签约 2：电话签约 3：网上签约
	inst_no     char(9),  
--签约机构 
	live_flag   char(1),  
--激活标志 0-激活 1-未激活
	tran_flag   char(1),  
--交易标志 0-允许交易 1-不允许交易
	acc_type    char(1),  
--扣款方式 1:预扣款用户 0:实时扣款用户
	yct_pwd     char(10),  
--羊城通密码 
	bank_acc    char(30),  
--账号 
	oper_tlr    char(3),  
--操作员 
	tran_date   char(14),  
--交易日期 
	sys_no      char(12),  
--系统参考号 
	ret_code    char(2),  
--响应代码 00-表示羊城通返回成功
	paper_no    char(21),  
--证件类型号码 
	contact_no  char(20),  
--合同编号 
	cust_name   char(30),  
--用户姓名 
	sex_code    char(1),  
--性别 
	phone_no    char(15),  
--电话号码 
	mobile_no   char(15),  
--手机号码 
	post_no     char(6),  
--邮编 
	address     char(50),  
--地址 
	email       char(50),  
--email邮箱 
	card1       char(10),  
--羊城通卡号1 
	card2       char(10),  
--羊城通卡号2 
	card3		    char(10),  
--羊城通卡号3 
	card4       char(10),  
--羊城通卡号4 
	limite      char(12),  
--额度 
	frequence   char(4),  
--频度 
	reg_date    char(4),  
--签约日期 
	cncl_date   char(4),  
--解约日期 
	cncl_flag   char(4),  
--签解约标志 0-签约 1-解约
	reserve1    char(30),  
--预留字段1 
	reserve2    char(30),  
--预留字段2 
	reserve3    char(30),  
--预留字段3 
	reserve4    char(60),  
--预留字段4 
	reserve5    char(60)
--预留字段5 
);

create unique index pk_yctreg on yctreg(bank_acc,card1,sys_no);
