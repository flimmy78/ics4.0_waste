-- 本地应用码表: pubftpcfg;
-- 字段顺序: 主机应用码,本地应用码,应用标识,应用名称
delete from pubftpcfg where BrNo='444999' and FtpId='PCL001';
delete from pubftpcfg where BrNo='446999' and FtpId='PCL001';
delete from pubftpcfg where BrNo='441999' and FtpId in ( 'PCL002','PCL003' );
insert into pubftpcfg values( '444999', 'PCL001', '182.59.1.96', 'steps', 'Zhuhaijh1', '$ObjPth', '$ObjFil', 'dat/term/recv', '$LclFil', 'bin', '', '珠海POS清算文件获取' );
insert into pubftpcfg values( '446999', 'PCL001', '182.84.2.183', 'report', 'report', '$ObjPth', '$ObjFil', 'dat/term/recv', '$LclFil', 'bin', '','佛山POS清算文件获取' );
insert into pubftpcfg values( '441999', 'PCL002', '$IPADR', '$USR', '$PWD', '$ObjPth', '$ObjFil', '$LclPth', '$LclFil', 'bin', '', '广州转帐POS清算文件获取' );
