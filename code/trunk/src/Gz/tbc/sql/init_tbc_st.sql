--/////////////////////
--/*  广东省烟草配置 */
--/*     汕头分行    */
--/////////////////////

--添加电子柜员
insert into pubdumtlr values('445999','TBC','','EPA0FB1');

--添加烟草基础信息表
insert into tbcbasinf values('445999','2032','汕头市公司',' ',' ','20111114','2032','0');

insert into pubaplbus values('445999','438','','TBCA1','广东烟草公司');

insert into pubaplmng values('445999','438','TBCA1','','9999999999');
insert into pubaplmng values('445999','438','CRP51','01','9999999999');

insert into pubjnldef values('445999','TBCA1','9999999999','afetxnjnl','afetxnjnl','1','1');
