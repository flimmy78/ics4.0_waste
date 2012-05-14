--添加电子柜员
insert into pubdumtlr values('441999','EFE','','EPCLBI1');



--delete from pubaplbus where brno='441999' and  APLCLS='202' and bustyp='EFEA1';
insert into pubaplbus values('441999','202','','EFEA1','广东电力代收费');
--单位代码对照表(应用码、应用子码、业务类型、业务类型描述)

--delete from pubaplmng where brno='441999' and  APLCLS='202' and bustyp='EFEA1';
insert into pubaplmng values('441999','202','EFEA1','','9999999999');
insert into pubaplmng values('441999','202','CRP51','01','9999999999');
--应用管理表(应用码、业务类型、业务子码、单位代码)

--delete from pubjnldef where brno='441999' and bustyp='EFEA1';
insert into pubjnldef values('441999','EFEA1','9999999999','afetxnjnl','afetxnjnl','1','1');
--pubjnldef业务流水定义管理表(业务类型、、联机流水表名、批量流水表名、联机、批量对帐标记)

--增加清算参数
db2 "insert into efeaclrtbl values('441999', '4410000971','YYYYMMDD','1800','0','0')"
db2 "insert into efeaclrtbl values('441999', '4410000958','YYYYMMDD','1800','0','0')"
db2 "insert into efeaclrtbl values('441999', '4410000960','YYYYMMDD','1800','0','0')"
