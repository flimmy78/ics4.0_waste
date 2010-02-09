-- 本地应用码表: pubftpcfg;
-- 字段顺序: 主机应用码,本地应用码,应用标识,应用名称
delete from pubftpcfg where BrNo='441999' and FtpId in ('PFA001','PFA002','PFA003');
insert into pubftpcfg values( '441999', 'PFA001', '$PfaIp', '$PfaUsr', '$PfaPwd', '$PfaDir', '$PfaFil', '$IcsDir', '$IcsFil', 'bin', '', '财政支付列表' );
insert into pubftpcfg values( '441999', 'PFA002', '182.53.4.200', 'administrator', '134679', 'pay/icsup', '$IcsFil', 'dat/pfa/send', '$IcsFil', 'bin', '', '财政结果文件' );
insert into pubftpcfg values( '441999', 'PFA003', '182.53.1.10', 'adeexc', 'ade', '$AdeDir', '$AdeFil', 'dat/pfa/recv', '$AdeFil', 'bin', '', '公务卡文件列表' );
