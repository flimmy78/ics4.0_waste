--��ʼ��Ӧ����Ϣ
insert into cimaplinf values('441999','48','12','FBP','�����������ո�');
--cimaplinf,����Ӧ�����(�к�,����Ӧ����,����Ӧ����,Ӧ�ñ�ʶ,Ӧ����)

insert into pubaplbus values('441999', '409','', 'FBP01','�����������ո�');
--pubaplbusӦ����ҵ�����Ͷ��ձ�(�к�,Ӧ���롢Ӧ�����롢ҵ�����͡�ҵ������)

insert into pubaplmng values('441999', '409','FBP01','','9999999999');
--pubaplmngӦ�ù����(Ӧ������롢ҵ�����͡�ҵ�����롢��λ����)

insert into pubjnldef values('441999', 'FBP01','9999999999','afebatrec','afebatrec','1','1');
--pubjnldefҵ����ˮ��������(ҵ�����͡���������ˮ������������ˮ�������������������ʱ��)

insert into pubdumtlr values('441999', 'FBP','','EFBPBI1');
--pubdumtlr�����Ա��(���������������������������Ա��)

insert into mngaplmon values('441999', 'FBP',   'FBP01',   'afebatrec',  '0',  'TTxnCd',  'TxnSts');

--FTP��ʼ��˵������ʼ���������淽ʽ��ʼ�� dat/fbp,$FilNam,bin �������������޸ģ�ftpid��������Ϊҵ����+������ �� water_484999 
delete from pubftpcfg where BrNo='441999' AND ftpid like 'GZ_FBP%';
insert into pubftpcfg values('441999','GZ_FBP01','182.53.13.13','zsxn','bx','up','$RcvFil','dat/fbp','$LclFil','bin',' ','�����ļ��������ո�');
--��Ӧ IP��ַ �û��� ���� �Է����Ŀ¼ 
insert into pubftpcfg values('441999','GZ_FBP02','182.53.13.13','zsxn','bx','down','$SndFil','dat/fbp','$LclFil','bin',' ','�����ļ��������ո�');
--��Ӧ IP��ַ �û��� ���� �Է����Ŀ¼ 
