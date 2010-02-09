--在配置应用业务类型对照表-pubaplbus中添加纪录
insert into pubaplbus values('255',' ','CCP51','珠海市大中专收费');
--在配置应用业务管理表-pubaplmng中添加纪录
insert into pubaplmng values('255','CCP51',' ','9999999999');
--在配置业务流水定义管理表中添加纪录
insert into pubjnldef values('CCP51','9999999999','ccptxnjnl',' ','0','0');
insert into pubcrpagt values('CCP51','9999999999','','','90006','','','444000097012015006636','444000091018000440821','','','0','0','','29991231','0','0');

insert into cimaplinf values('46','55','01','珠海大中专收费');
insert into cimtxncls values('46','55','01','珠海大中专收费支行共用交易');
insert into cimtxncls values('46','55','02','珠海大中专收费主办行交易');

insert into cimclsdef values('46','55','01','465501');
insert into cimclsdef values('46','55','01','465502');
insert into cimclsdef values('46','55','01','465509');
insert into cimclsdef values('46','55','01','465519');
insert into cimclsdef values('46','55','01','465504');
insert into cimclsdef values('46','55','01','465505');
insert into cimclsdef values('46','55','01','465508');
insert into cimclsdef values('46','55','02','465506');
insert into cimclsdef values('46','55','02','465507');
insert into cimclsdef values('46','55','02','465510');
insert into cimtxnpur values('465501','现金缴费记账','46','55','01','1','1');
insert into cimtxnpur values('465502','转账缴费记账','46','55','01','1','1');
insert into cimtxnpur values('465509','现金缴款抹账','46','55','01','1','1');
insert into cimtxnpur values('465519','转账缴费抹账','46','55','01','1','1');
insert into cimtxnpur values('465504','轧账交易','46','55','01','1','1');
insert into cimtxnpur values('465505','交易流水查询','46','55','01','1','1');
insert into cimtxnpur values('465508','收费项目代码查询','46','55','01','1','1');
insert into cimtxnpur values('465506','收费项目代码增加','46','55','01','1','1');
insert into cimtxnpur values('465507','收费项目代码修改','46','55','01','1','1');
insert into cimtxnpur values('465510','收费项目代码删除','46','55','01','1','1');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465501','现金缴费记账','');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465502','转账缴费记账','');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465509','现金缴款抹账','');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465519','转账缴费抹账','');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465504','轧账交易','');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465505','交易流水查询','');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465508','收费项目代码查询','');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465506','收费项目代码增加','');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465507','收费项目代码修改','');
insert into mngaplinf values('ccp', '珠海大中专收费', 'TRM', '柜台终端','CTRMCCP1','大中专收费柜台通讯服务','465510','收费项目代码删除','');
