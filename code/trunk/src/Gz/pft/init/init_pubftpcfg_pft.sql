-- 本地应用码表: pubftpcfg;
-- 字段顺序: 主机应用码,本地应用码,应用标识,应用名称
delete from pubftpcfg where BrNo='441999' and FtpId='PFT001';
insert into pubftpcfg values( '441999', 'PFT001', '182.53.4.194', 'rtsb', 'rtsb', '$PftDir', '$PftFil', '$IcsDir', '$IcsFil', 'bin', '', '广州市ETS系统' );
