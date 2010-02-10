drop table arecoddat446;

--地区代码模糊查询数据表
create table    arecoddat446
(
   AreaNam        char(40)     not null,
--地区名称
   AreaCod      char(4)     not null
--地区代码
);
create index ni1_arecoddat446 on arecoddat446(AreaNam);
