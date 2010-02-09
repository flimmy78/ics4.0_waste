-- 本地应用码表: pubftpcfg;
-- 字段顺序: 主机应用码,本地应用码,应用标识,应用名称
delete from pubftpcfg where BrNo='484999' and FtpId='PNT001';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT002';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT003';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT004';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT005';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT007';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT008';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT009';
insert into pubftpcfg values( '484999', 'PNT001', '182.56.20.11', 'FTP442000010', '123456', '/JCSJ', '$ObjFil', 'dat/pnt/recv/jcsj', '$LclFil', 'bin', '', '非税系统' );
insert into pubftpcfg values( '484999', 'PNT002', '182.56.20.11', 'FTP442000010', '123456', '/WTZW', '$ObjFil', 'dat/pnt/recv/wtzw', '$LclFil', 'bin', '', '非税系统' );
insert into pubftpcfg values( '484999', 'PNT003', '182.56.20.11', 'FTP442000010', '123456', '/YHSC', '$ObjFil', 'dat/pnt/send/yhsc', '$LclFil', 'bin', '', '非税系统' );
insert into pubftpcfg values( '484999', 'PNT004', '182.56.20.11', 'FTP442000010', '123456', '/FCXX', '$ObjFil', 'dat/pnt/recv/fcxx', '$LclFil', 'bin', '', '非税系统' );
insert into pubftpcfg values( '484999', 'PNT005', '182.56.20.11', 'FTP442000010', '123456', '/PLKS', '$ObjFil', 'dat/pnt/recv/plks', '$LclFil', 'bin', '', '非税系统' );
insert into pubftpcfg values( '484999', 'PNT007', '182.56.88.65', 'zslq', 'zslq', '.', '$ObjFil', 'dat/pnt/send/yhsc', '$LclFil', 'asc', '', '非税系统' );
insert into pubftpcfg values( '484999', 'PNT008', '182.56.20.11', 'FTP442000010', '123456', '/442000/HZFCZH', '$ObjFil', 'dat/pnt/recv/hzdz','$LclFil', 'bin', '', '非税系统' );
insert into pubftpcfg values( '484999', 'PNT009', '182.56.20.11', 'HZDZ442000010', '123456', '/', '$ObjFil', 'dat/pnt/send/hzdz','$L
clFil', 'bin', '', '非税系统' );
