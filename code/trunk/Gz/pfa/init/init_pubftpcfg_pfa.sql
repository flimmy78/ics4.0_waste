-- ����Ӧ�����: pubftpcfg;
-- �ֶ�˳��: ����Ӧ����,����Ӧ����,Ӧ�ñ�ʶ,Ӧ������
delete from pubftpcfg where BrNo='441999' and FtpId in ('PFA001','PFA002','PFA003');
insert into pubftpcfg values( '441999', 'PFA001', '$PfaIp', '$PfaUsr', '$PfaPwd', '$PfaDir', '$PfaFil', '$IcsDir', '$IcsFil', 'bin', '', '����֧���б�' );
insert into pubftpcfg values( '441999', 'PFA002', '182.53.4.200', 'administrator', '134679', 'pay/icsup', '$IcsFil', 'dat/pfa/send', '$IcsFil', 'bin', '', '��������ļ�' );
insert into pubftpcfg values( '441999', 'PFA003', '182.53.1.10', 'adeexc', 'ade', '$AdeDir', '$AdeFil', 'dat/pfa/recv', '$AdeFil', 'bin', '', '�����ļ��б�' );
