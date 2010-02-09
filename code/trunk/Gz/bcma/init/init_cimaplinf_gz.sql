-- 本地应用码表: cimaplinf;
-- 字段顺序: 主机应用码,本地应用码,应用标识,应用名称
-- insert into cimaplinf values('XXX','XXX','XXX','XXX');
delete from cimaplinf where HstApCod='46' and ApCod ='49';
insert into cimaplinf values( '46', '49', '01', '母子帐户联动' );
