--insert into pubseqrec values('441999','efecusagt:PAgtNo','441',0);
--insert into pubseqrec values('444999','efecusagt:PAgtNo','444',0);
--insert into pubseqrec values('446999','efecusagt:PAgtNo','446',0);
--insert into pubseqrec values('445999','efecusagt:PAgtNo','445',0);
--汕头需要分行号后添加应用码:insert into pubseqrec values('445999','efecusagt:PAgtNo','445102',0);
--insert into pubseqrec values('483999','efecusagt:PAgtNo','483',0);
--insert into pubseqrec values('484999','efecusagt:PAgtNo','484',0);
--insert into pubseqrec values('485999','efecusagt:PAgtNo','485',0);
--insert into pubseqrec values('491999','efecusagt:PAgtNo','491',0);
--insert into pubseqrec values('761999','efecusagt:PAgtNo','761',0);

--insert into pubcominf values('efe_441999','182.XXX.XXX.XXX','XXXX','广州电力电费');
--insert into pubcominf values('efe_444999','182.XXX.XXX.XXX','XXXX','珠海电力电费');
--insert into pubcominf values('efe_446999','182.XXX.XXX.XXX','XXXX','佛山电力电费');
--测试环境:insert into pubcominf values('efe_445999','182.55.200.52','5677','汕头电力电费');
--insert into pubcominf values('efe_483999','182.XXX.XXX.XXX','XXXX','东莞电力电费');
--insert into pubcominf values('efe_484999','182.XXX.XXX.XXX','XXXX','中山电力电费');
--insert into pubcominf values('efe_485999','182.XXX.XXX.XXX','XXXX','揭阳电力电费');
--insert into pubcominf values('efe_491999','182.XXX.XXX.XXX','XXXX','惠州电力电费');
--insert into pubcominf values('efe_761999','182.XXX.XXX.XXX','XXXX','江门电力电费');

--添加电子柜员
--insert into pubdumtlr values('441999','EFE','','EPCLBI1');
--insert into pubdumtlr values('485999','EFE','','EPA0IP1');
--insert into pubdumtlr values('445999','EFE','','EPA0FB1');

--电力基础信息表
--insert into efeinfctl values('441999','301','0500','20100919','','','','182.53.15.241','','1');
--insert into efeinfctl values('485999','301','5200','20100919','','','','182.53.15.241','','1');
--insert into efeinfctl values('445999','301','0500','20120101','','','','182.55.200.52','','1');

--delete from pubaplbus where brno='441999' and  APLCLS='202' and bustyp='EFEA1';
insert into pubaplbus values('441999','202','','EFEA1','广东电力代收费');
insert into pubaplbus values('485999','202','','EFEG1','揭阳电力代收费');
insert into pubaplbus values('445999','202','001','EFEC1','汕头电力代收费');
--单位代码对照表(应用码、应用子码、业务类型、业务类型描述)

--delete from pubaplmng where brno='441999' and  APLCLS='202' and bustyp='EFEA1';
insert into pubaplmng values('441999','202','EFEA1','','9999999999');
insert into pubaplmng values('441999','202','CRP51','01','9999999999');
insert into pubaplmng values('485999','202','EFEG1','','9999999999');
insert into pubaplmng values('485999','202','CRP51','01','9999999999');
insert into pubaplmng values('445999','202','EFEC1','','9999999999');
insert into pubaplmng values('445999','202','CRP51','01','9999999999');
--应用管理表(应用码、业务类型、业务子码、单位代码)

--delete from pubjnldef where brno='441999' and bustyp='EFEA1';
insert into pubjnldef values('441999','EFEA1','9999999999','afetxnjnl','afetxnjnl','1','1');
insert into pubjnldef values('485999','EFEG1','9999999999','afetxnjnl','afetxnjnl','1','1');
insert into pubjnldef values('445999','EFEC1','9999999999','afetxnjnl','afetxnjnl','1','1');
--pubjnldef业务流水定义管理表(业务类型、、联机流水表名、批量流水表名、联机、批量对帐标记)
