-- 本地交易分类表: cimtxncls;
-- 字段顺序: 主机应用码,本地应用码,应用分类码,分类名称
delete from  cimtxncls where hstapcod='46' and APCOD='49';

insert into cimtxncls values( '46', '49', '01', '中心维护' );
insert into cimtxncls values( '46', '49', '02', '网点维护' );
insert into cimtxncls values( '46', '49', '03', '业务查询' );
insert into cimtxncls values( '46', '49', '04', '中心帐务' );
insert into cimtxncls values( '46', '49', '05', '网点帐务' );
insert into cimtxncls values( '46', '49', '06', '全行打印' );
insert into cimtxncls values( '46', '49', '07', '中心打印' );
insert into cimtxncls values( '46', '49', '08', '网点打印' );
