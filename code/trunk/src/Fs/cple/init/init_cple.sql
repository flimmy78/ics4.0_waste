delete from pubaplbus where BrNo='446999' AND APLCLS='236';
insert into pubaplbus values('446999', '236','001','CPL51','对私对公批量转账');
insert into pubaplbus values('446999', '236','002','CPL52','对私对公批量转账');

delete from pubaplmng where BrNo='446999' AND APLCLS='236';
insert into pubaplmng values('446999', '236','CPL51','01','9999999999');
insert into pubaplmng values('446999', '236','CPL52','01','9999999999');

delete from pubdumtlr WHERE brno='446999' AND TxnCnl='CPL'; 
insert into pubdumtlr values('446999', 'CPL','446999','EPA0DI0');

delete from pubjnldef where brno='446999' AND bustyp='CPL52';
delete from pubjnldef where brno='446999' AND bustyp='CPL51';
--对私转26201
insert into pubjnldef values('446999', 'CPL52','9999999999','afetxnjnl','afetxnjnl','0','1');
--26201转CD户
insert into pubjnldef values('446999', 'CPL51','9999999999','cpltxnjnl446','cpltxnjnl446','0','1');

delete from cplactreg446;
insert into cplactreg446 values ('4460000033','60142893710029918','446180012620110001399','0','000000000000000','446800','4460141','20080623');
