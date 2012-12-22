--添加电子柜员
insert into pubdumtlr values('441999','YCT','','EYCTBI1');

--delete from pubaplbus where brno='441999' and  APLCLS='445' and bustyp='YCTA1';
insert into pubaplbus values('441999','445','','YCTA1','广东羊城通自助充值');
--单位代码对照表(应用码、应用子码、业务类型、业务类型描述)

--delete from pubaplmng where brno='441999' and  APLCLS='445' and bustyp='YCTA1';
insert into pubaplmng values('441999','445','YCTA1','','9999999999');
--应用管理表(应用码、业务类型、业务子码、单位代码)

--delete from pubjnldef where brno='441999' and bustyp='EFEA1';
insert into pubjnldef values('441999','YCTA1','9999999999','afetxnjnl','afetxnjnl','1','1');
--pubjnldef业务流水定义管理表(业务类型、、联机流水表名、批量流水表名、联机、批量对帐标记)
