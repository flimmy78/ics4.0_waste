--/////////////////////
--/*  广东省烟草配置 */
--/*     江门分行    */
--/////////////////////

--添加电子柜员
insert into pubdumtlr values('761999','TBC','','EYYTDU1');


--delete from pubaplbus where brno='441999' and  APLCLS='438' and bustyp='TBCA1';
insert into pubaplbus values('761999','438','','TBCA1','江门市烟草公司');
--单位代码对照表(应用码、应用子码、业务类型、业务类型描述)

--delete from pubaplmng where brno='441999' and  APLCLS='438' and bustyp='TCBA1';
insert into pubaplmng values('761999','438','TBCA1','','9999999999');
insert into pubaplmng values('761999','438','CRP51','01','9999999999');
--应用管理表(应用码、业务类型、业务子码、单位代码)

--delete from pubjnldef where brno='441999' and bustyp='TCBA1';
insert into pubjnldef values('761999','TBCA1','9999999999','afetxnjnl','afetxnjnl','1','1');
--pubjnldef业务流水定义管理表(业务类型、、联机流水表名、批量流水表名、联机、批量对帐标记)

--添加烟草基础信息表
insert into tbcbasinf values('761999','2022','江门市公司',' ',' ','20130520','2022','0');
