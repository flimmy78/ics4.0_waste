--在配置应用业务类型对照表-pubaplbus中添加纪录
insert into pubaplbus values('238','001','CAD51','珠海市行政事业收费现金收费');
insert into pubaplbus values('238','002','CAD53','珠海市行政事业收费现金结转');
--在配置应用业务管理表-pubaplmng中添加纪录
insert into pubaplmng values('238','CAD51',' ','9999999999');
insert into pubaplmng values('238','CAD53',' ','9999999999');
--在配置业务流水定义管理表中添加纪录
insert into pubjnldef values('CAD51','9999999999','cadtxnjnl',' ','0','0');
insert into pubjnldef values('CAD53','9999999999','cadtxnjnl',' ','0','0');

--TActNo 	现金内部帐号的顺序号
--TActNo2 	珠海财政局人民币帐号
--TActNo3 	万山财局帐号
insert into pubcrpagt values('CAD51','9999999999','','','90006','','','','','','','0','0','','29991231','0','0');
insert into pubcrpagt values('CAD53','9999999999','','','90006','','','444000097012015006636','444000091018000440821','','','0','0','','29991231','0','0');


insert into cimaplinf values('46','38','01','珠海市行政事业收费');
insert into cimtxncls values('46','38','01','珠海行政事业收费支行共用交易');
insert into cimtxncls values('46','38','02','珠海行政事业收费主办行交易');

insert into cimclsdef values('46','38','01','463801');
insert into cimclsdef values('46','38','01','463802');
insert into cimclsdef values('46','38','01','463809');
insert into cimclsdef values('46','38','01','463819');
insert into cimclsdef values('46','38','01','463804');
insert into cimclsdef values('46','38','01','463805');
insert into cimclsdef values('46','38','01','463808');
insert into cimclsdef values('46','38','01','463829');
insert into cimclsdef values('46','38','02','463806');
insert into cimclsdef values('46','38','02','463807');
insert into cimclsdef values('46','38','02','463810');
insert into cimclsdef values('46','38','02','463812');
insert into cimclsdef values('46','38','02','463813');
insert into cimclsdef values('46','38','01','463814');
insert into cimclsdef values('46','38','02','463815');
insert into cimclsdef values('46','38','02','463816');
insert into cimtxnpur values('463801','现金缴费记账','46','38','01','1','1');
insert into cimtxnpur values('463802','转账缴款凭证打印','46','38','01','1','1');
insert into cimtxnpur values('463809','现金缴款抹账','46','38','01','1','1');
insert into cimtxnpur values('463819','转账缴费抹账','46','38','01','1','1');
insert into cimtxnpur values('463804','轧账交易','46','38','01','1','1');
insert into cimtxnpur values('463805','交易流水查询','46','38','01','1','1');
insert into cimtxnpur values('463808','收费项目代码查询','46','38','01','1','1');
insert into cimtxnpur values('463829','现金缴款结转抹账','46','38','01','1','1');
insert into cimtxnpur values('463806','收费项目代码增加','46','38','01','1','1');
insert into cimtxnpur values('463807','收费项目代码修改','46','38','01','1','1');
insert into cimtxnpur values('463810','收费项目代码删除','46','38','01','1','1');
insert into cimtxnpur values('463812','收取网点数据','46','38','01','1','1');
insert into cimtxnpur values('463813','打印全行汇总轧账单','46','38','01','1','1');
insert into cimtxnpur values('463814','现金缴款结转','46','38','01','1','1');
insert into cimtxnpur values('463815','数据统计打印拷盘','46','38','01','1','1');
insert into cimtxnpur values('463816','网点现金缴款结转情况查询','46','38','01','1','1');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463801','现金缴费记账','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463802','转账缴款凭证打印','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463809','现金缴款抹账','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463819','转账缴费抹账','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463804','轧账交易','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463805','交易流水查询','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463808','收费项目代码查询','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463829','现金缴款结转抹账','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463806','收费项目代码增加','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463807','收费项目代码修改','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463810','收费项目代码删除','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463812','收取网点数据','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463813','打印全行汇总轧账单','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463814','现金缴款结转','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463815','数据统计打印拷盘','');
insert into mngaplinf values('cad', '珠海市行政事业收费', 'TRM', '柜台终端','CTRMCAD1','行政事业收费柜台通讯服务','463816','网点现金缴款结转情况查询','');
