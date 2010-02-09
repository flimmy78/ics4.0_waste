-- 交易码表: cimtxnpur;
-- 字段名称: 交易码,交易名称,主机应用码,本地应用码,交易授权级别,账务交易标志,管理交易标志
-- insert into cimtxnpur values('XXXXXX','XXX...','XXX','XX','XX','X','X');

delete from cimtxnpur where intcod like '4649%';
insert into cimtxnpur values('464901','母子帐户归属维护',     '46','49','01','0','1');
insert into cimtxnpur values('464902','母子帐户资金划拨记帐', '46','49','01','1','0');
insert into cimtxnpur values('464903','母子帐户资金划拨抹帐', '46','49','01','1','0');
insert into cimtxnpur values('464921','母子帐户归属浏览',     '46','49','01','1','1');
insert into cimtxnpur values('464941','交易清单凭证打印',     '46','49','01','1','1');
