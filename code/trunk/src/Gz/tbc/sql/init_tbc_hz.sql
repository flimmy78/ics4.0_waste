--/////////////////////
--/*  广东省烟草配置 */
--/*     惠州分行    */
--/////////////////////

--添加电子柜员
insert into pubdumtlr values('491999','TBC','','EYYTDT1');

--添加烟草基础信息表
insert into tbcbasinf values('491999','2002','惠州市公司',' ',' ','20111114','5950','0');

insert into pubaplbus values('491999','438','','TBCA1','广东烟草公司');

insert into pubaplmng values('491999','438','TBCA1','','9999999999');
insert into pubaplmng values('491999','438','CRP51','01','9999999999');

insert into pubjnldef values('491999','TBCA1','9999999999','afetxnjnl','afetxnjnl','1','1');
