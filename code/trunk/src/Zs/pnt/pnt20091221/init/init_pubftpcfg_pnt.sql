-- ����Ӧ�����: pubftpcfg;
-- �ֶ�˳��: ����Ӧ����,����Ӧ����,Ӧ�ñ�ʶ,Ӧ������
delete from pubftpcfg where BrNo='484999' and FtpId='PNT001';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT002';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT003';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT004';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT005';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT007';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT008';
delete from pubftpcfg where BrNo='484999' and FtpId='PNT009';
insert into pubftpcfg values( '484999', 'PNT001', '182.56.20.11', 'FTP442000010', '123456', '/JCSJ', '$ObjFil', 'dat/pnt/recv/jcsj', '$LclFil', 'bin', '', '��˰ϵͳ' );
insert into pubftpcfg values( '484999', 'PNT002', '182.56.20.11', 'FTP442000010', '123456', '/WTZW', '$ObjFil', 'dat/pnt/recv/wtzw', '$LclFil', 'bin', '', '��˰ϵͳ' );
insert into pubftpcfg values( '484999', 'PNT003', '182.56.20.11', 'FTP442000010', '123456', '/YHSC', '$ObjFil', 'dat/pnt/send/yhsc', '$LclFil', 'bin', '', '��˰ϵͳ' );
insert into pubftpcfg values( '484999', 'PNT004', '182.56.20.11', 'FTP442000010', '123456', '/FCXX', '$ObjFil', 'dat/pnt/recv/fcxx', '$LclFil', 'bin', '', '��˰ϵͳ' );
insert into pubftpcfg values( '484999', 'PNT005', '182.56.20.11', 'FTP442000010', '123456', '/PLKS', '$ObjFil', 'dat/pnt/recv/plks', '$LclFil', 'bin', '', '��˰ϵͳ' );
insert into pubftpcfg values( '484999', 'PNT007', '182.56.88.65', 'zslq', 'zslq', '.', '$ObjFil', 'dat/pnt/send/yhsc', '$LclFil', 'asc', '', '��˰ϵͳ' );
insert into pubftpcfg values( '484999', 'PNT008', '182.56.20.11', 'FTP442000010', '123456', '/442000/HZFCZH', '$ObjFil', 'dat/pnt/recv/hzdz','$LclFil', 'bin', '', '��˰ϵͳ' );
insert into pubftpcfg values( '484999', 'PNT009', '182.56.20.11', 'HZDZ442000010', '123456', '/', '$ObjFil', 'dat/pnt/send/hzdz','$L
clFil', 'bin', '', '��˰ϵͳ' );
