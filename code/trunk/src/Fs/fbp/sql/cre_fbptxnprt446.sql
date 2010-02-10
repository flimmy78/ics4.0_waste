drop table fbptxnprt446;

create table fbptxnprt446 	
--批量代扣费回执打印控制表
(
  BBusTyp char(3),
--批扣类型
	ActDat char(8),		
--交易日期
	ActNo  char(21),
--交易账号
	HLogNo	 char(9),  
--主机交易流水号
	prtcnt	int			  
--打印次数
);
create  unique index  ui1_fbptxnprt446 on fbptxnprt446(ActDat,HLogNo);
