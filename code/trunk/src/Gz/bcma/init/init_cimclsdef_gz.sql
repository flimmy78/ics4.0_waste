--初始化特色业务权限分类
--
delete from cimclsdef where HSTAPCOD = '46' and APCOD='49';
insert into cimclsdef values('46','49','01','464901');
insert into cimclsdef values('46','49','03','464921');
insert into cimclsdef values('46','49','04','464902');
insert into cimclsdef values('46','49','04','464903');
insert into cimclsdef values('46','49','06','464941');
