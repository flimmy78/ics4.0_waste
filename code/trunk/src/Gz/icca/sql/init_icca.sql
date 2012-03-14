--添加电子柜员
insert into pubdumtlr values('441999','ICC','','EPCLBI1');

--delete from pubaplbus where brno='441999' and  APLCLS='404' and bustyp='ICCA';
insert into pubaplbus values('441999','404','','ICCA','广州大学城联名卡');
--单位代码对照表(应用码、应用子码、业务类型、业务类型描述)

--delete from pubaplmng where brno='441999' and  APLCLS='404' and bustyp='ICCA';
insert into pubaplmng values('441999','404','ICCA','','9999999999');
--应用管理表(应用码、业务类型、业务子码、单位代码)

--delete from pubjnldef where brno='441999' and bustyp='ICCA';
insert into pubjnldef values('441999','ICCA','9999999999','afetxnjnl','afetxnjnl','1','1');
--pubjnldef业务流水定义管理表(业务类型、、联机流水表名、批量流水表名、联机、批量对帐标记)

