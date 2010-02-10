--初始化虚拟柜员
--
delete from pubdumtlr where txncnl='PFT' and brno='446999';
insert into pubdumtlr values( '446999', 'PFT', '', 'EPFTDI1' );

delete from pubaplbus where BrNo='446999' AND APLCLS='259';
insert into pubaplbus values('446999', '259','','PFT01','佛山银税联网系统');

delete from pubjnldef where brno='446999' AND bustyp='PFT01';
insert into pubjnldef values('446999', 'PFT01','9999999999','pfttxnjnl446','pfttxnjnl446','1','1');

delete from pubaplmng where BrNo='446999' AND APLCLS='259';
insert into pubaplmng values('446999', '259','PFT01','','9999999999');

delete from pftBnkInf446 where BrNo='446999';

insert into PftBnkInf446 values('1','446999','61','446800','00000000','1','446800012220300001199','446800011380190005099','12345678');
insert into PftBnkInf446 values('0','446999','6101','446800','00000000','1','','','12345678');

delete from pftNodInf446 where BrNo='446999';
insert into PftNodInf446 values('446809','佛山分行营业部','446800', '6101','446999');
insert into PftNodInf446 values('446999','佛山分行','446800', '61','446999');
