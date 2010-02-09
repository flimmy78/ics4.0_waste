-- 本地应用码表: pubftpcfg;
-- 字段顺序: 主机应用码,本地应用码,应用标识,应用名称
delete from pubftpcfg where BrNo='441999' and FtpId='MDF001';
insert into pubftpcfg values( '441999', 'MDF001', '182.53.4.200', 'administrator', '134679', 'mdf', '$FilNam', '$LclDir', '$FilNam', 'bin', '', '广州市医保系统' );
