-- ����Ӧ�����: pubftpcfg;
-- �ֶ�˳��: ����Ӧ����,����Ӧ����,Ӧ�ñ�ʶ,Ӧ������
delete from pubftpcfg where BrNo='441999' and FtpId='SPE441';
delete from pubftpcfg where BrNo='446999' and FtpId='SPE446';
insert into pubftpcfg values( '441999', 'SPE441', '182.53.13.66', 'balance', 'balance', '.', '$ObjFil', 'dat/spe/send', '$LclFil', 'bin', '', '֧��ϵͳ���ݷ���' );
insert into pubftpcfg values( '446999', 'SPE446', '182.84.2.174', 'ftpuser', 'bocgb','plan', '$ObjFil', 'dat/spe/send', '$LclFil', 'bin', '', '֧��ϵͳ���ݷ���' );
insert into pubftpcfg values( '484999', 'SPE484', '182.56.22.2', 'sybbcs', 'zsjhsa','ics/data', '$ObjFil', 'dat/spe/send', '$LclFil', 'bin', '', '֧��ϵͳ���ݷ���' );
