drop table comtxnprt446;

create table comtxnprt446 	
--通讯费回执打印控制表
(
	ActDat char(8),		
--交易日期
	ActNo  char(21),
--交易账号
	TckNo	 char(11),  
--交易流水号
	prtcnt	int			  
--打印次数
);
create  unique index  ui1_comtxnprt446 on comtxnprt446(ActDat,TckNo);
