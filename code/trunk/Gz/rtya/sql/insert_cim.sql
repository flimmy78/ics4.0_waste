insert into cimclsdef values('46','47','03','464701');
insert into cimclsdef values('46','47','05','464702');
insert into cimclsdef values('46','47','05','464703');
insert into cimclsdef values('46','47','05','464704');
insert into cimclsdef values('46','47','05','464705');
insert into cimclsdef values('46','47','05','464706');
insert into cimclsdef values('46','47','04','464707');
insert into cimclsdef values('46','47','04','464708');
insert into cimclsdef values('46','47','01','464709');
insert into cimclsdef values('46','47','05','464710');
insert into cimclsdef values('46','47','03','464711');
insert into cimclsdef values('46','47','02','464788');

insert into cimtxncls values( '46', '47', '01', '中心维护' );
insert into cimtxncls values( '46', '47', '02', '网点维护' );
insert into cimtxncls values( '46', '47', '03', '业务查询' );
insert into cimtxncls values( '46', '47', '04', '中心帐务' );
insert into cimtxncls values( '46', '47', '05', '网点帐务' );
insert into cimtxncls values( '46', '47', '06', '全行打印' );
insert into cimtxncls values( '46', '47', '07', '中心打印' );
insert into cimtxncls values( '46', '47', '08', '网点打印' );

insert into cimtxnpur values('464701','商品房缴款信息查询',  '46','47','03','1','0');
insert into cimtxnpur values('464702','商品房缴款信息提交',  '46','47','05','1','0');
insert into cimtxnpur values('464703','取消商品房缴款信息',  '46','47','05','1','0');
insert into cimtxnpur values('464704','获取支出批准书信息',  '46','47','05','1','0');
insert into cimtxnpur values('464705','监控帐户支出信息提交',  '46','47','05','1','0');
insert into cimtxnpur values('464706','取消监控帐户支出信息',  '46','47','05','1','0');
insert into cimtxnpur values('464707','监控帐户每日收支信息提交',  '46','47','04','1','1');
insert into cimtxnpur values('464708','监控帐户跨行转帐收款明细提交',  '46','47','04','1','1');
insert into cimtxnpur values('464709','密码修改',  '46','47','01','0','1');
insert into cimtxnpur values('464710','取消监控批准书信息查询',  '46','47','05','1','0');
insert into cimtxnpur values('464711','查询款项是否在监控范围',  '46','47','03','1','0');
insert into cimtxnpur values('464788','监控帐户信息维护',  '46','47','02','0','1');

db2 "insert into rtyfmpmng values ('0301','0301','0001')"
db2 "insert into cimaplinf values ('46','47','01','房屋管理系统')"
