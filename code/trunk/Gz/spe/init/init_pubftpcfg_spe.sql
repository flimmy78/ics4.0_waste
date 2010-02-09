-- 本地应用码表: pubftpcfg;
-- 字段顺序: 主机应用码,本地应用码,应用标识,应用名称
delete from pubftpcfg where BrNo='441999' and FtpId='SPE441';
delete from pubftpcfg where BrNo='446999' and FtpId='SPE446';
insert into pubftpcfg values( '441999', 'SPE441', '182.53.13.66', 'balance', 'balance', '.', '$ObjFil', 'dat/spe/send', '$LclFil', 'bin', '', '支付系统数据发送' );
insert into pubftpcfg values( '446999', 'SPE446', '182.84.2.174', 'ftpuser', 'bocgb','plan', '$ObjFil', 'dat/spe/send', '$LclFil', 'bin', '', '支付系统数据发送' );
insert into pubftpcfg values( '484999', 'SPE484', '182.56.22.2', 'sybbcs', 'zsjhsa','ics/data', '$ObjFil', 'dat/spe/send', '$LclFil', 'bin', '', '支付系统数据发送' );
