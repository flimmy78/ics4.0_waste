--��ʼ��Ӧ����Ϣ
--FTP��ʼ��˵������ʼ���������淽ʽ��ʼ�� dat/fbp,$FilNam,bin �������������޸ģ�ftpid��������Ϊҵ����+������ �� water_484999 
delete from pubftpcfg where BrNo='441999' AND ftpid like 'GZ_FBP%';
insert into pubftpcfg values('441999','GZ_FBP01','182.53.13.13','zsxn','bx','up','$RcvFil','dat/fbp','$LclFil','bin',' ','�����ļ��������ո�');
--��Ӧ IP��ַ �û��� ���� �Է����Ŀ¼ 
insert into pubftpcfg values('441999','GZ_FBP02','182.53.13.13','zsxn','bx','down','$SndFil','dat/fbp','$LclFil','bin',' ','�����ļ��������ո�');
--��Ӧ IP��ַ �û��� ���� �Է����Ŀ¼ 
