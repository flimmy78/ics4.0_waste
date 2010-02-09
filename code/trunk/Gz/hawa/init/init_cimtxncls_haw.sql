-- 本地交易分类表: cimtxncls;
-- 字段顺序: 主机应用码,本地应用码,应用分类码,分类名称
delete from cimtxncls where BrNo='441999' and HSTAPCOD='46' and APCOD='24';
insert into cimtxncls values( '441999', '46', '24', '01', '全行交易' );
insert into cimtxncls values( '441999', '46', '24', '02', '参数交易' );
insert into cimtxncls values( '441999', '46', '24', '03', '中心交易' );
insert into cimtxncls values( '441999', '46', '24', '04', '网点交易' );
