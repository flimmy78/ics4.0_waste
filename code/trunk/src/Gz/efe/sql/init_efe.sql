--insert into pubseqrec values('441999','efecusagt:PAgtNo','441',0);
--insert into pubseqrec values('444999','efecusagt:PAgtNo','444',0);
--insert into pubseqrec values('446999','efecusagt:PAgtNo','446',0);
--insert into pubseqrec values('445999','efecusagt:PAgtNo','445',0);
--��ͷ��Ҫ���кź����Ӧ����:insert into pubseqrec values('445999','efecusagt:PAgtNo','445102',0);
--insert into pubseqrec values('483999','efecusagt:PAgtNo','483',0);
--insert into pubseqrec values('484999','efecusagt:PAgtNo','484',0);
--insert into pubseqrec values('485999','efecusagt:PAgtNo','485',0);
--insert into pubseqrec values('491999','efecusagt:PAgtNo','491',0);
--insert into pubseqrec values('761999','efecusagt:PAgtNo','761',0);

--insert into pubcominf values('efe_441999','182.XXX.XXX.XXX','XXXX','���ݵ������');
--insert into pubcominf values('efe_444999','182.XXX.XXX.XXX','XXXX','�麣�������');
--insert into pubcominf values('efe_446999','182.XXX.XXX.XXX','XXXX','��ɽ�������');
--���Ի���:insert into pubcominf values('efe_445999','182.55.200.52','5677','��ͷ�������');
--insert into pubcominf values('efe_483999','182.XXX.XXX.XXX','XXXX','��ݸ�������');
--insert into pubcominf values('efe_484999','182.XXX.XXX.XXX','XXXX','��ɽ�������');
--insert into pubcominf values('efe_485999','182.XXX.XXX.XXX','XXXX','�����������');
--insert into pubcominf values('efe_491999','182.XXX.XXX.XXX','XXXX','���ݵ������');
--insert into pubcominf values('efe_761999','182.XXX.XXX.XXX','XXXX','���ŵ������');

--��ӵ��ӹ�Ա
--insert into pubdumtlr values('441999','EFE','','EPCLBI1');
--insert into pubdumtlr values('485999','EFE','','EPA0IP1');
--insert into pubdumtlr values('445999','EFE','','EPA0FB1');

--����������Ϣ��
--insert into efeinfctl values('441999','301','0500','20100919','','','','182.53.15.241','','1');
--insert into efeinfctl values('485999','301','5200','20100919','','','','182.53.15.241','','1');
--insert into efeinfctl values('445999','301','0500','20120101','','','','182.55.200.52','','1');

--delete from pubaplbus where brno='441999' and  APLCLS='202' and bustyp='EFEA1';
insert into pubaplbus values('441999','202','','EFEA1','�㶫�������շ�');
insert into pubaplbus values('485999','202','','EFEG1','�����������շ�');
insert into pubaplbus values('445999','202','001','EFEC1','��ͷ�������շ�');
--��λ������ձ�(Ӧ���롢Ӧ�����롢ҵ�����͡�ҵ����������)

--delete from pubaplmng where brno='441999' and  APLCLS='202' and bustyp='EFEA1';
insert into pubaplmng values('441999','202','EFEA1','','9999999999');
insert into pubaplmng values('441999','202','CRP51','01','9999999999');
insert into pubaplmng values('485999','202','EFEG1','','9999999999');
insert into pubaplmng values('485999','202','CRP51','01','9999999999');
insert into pubaplmng values('445999','202','EFEC1','','9999999999');
insert into pubaplmng values('445999','202','CRP51','01','9999999999');
--Ӧ�ù����(Ӧ���롢ҵ�����͡�ҵ�����롢��λ����)

--delete from pubjnldef where brno='441999' and bustyp='EFEA1';
insert into pubjnldef values('441999','EFEA1','9999999999','afetxnjnl','afetxnjnl','1','1');
insert into pubjnldef values('485999','EFEG1','9999999999','afetxnjnl','afetxnjnl','1','1');
insert into pubjnldef values('445999','EFEC1','9999999999','afetxnjnl','afetxnjnl','1','1');
--pubjnldefҵ����ˮ��������(ҵ�����͡���������ˮ������������ˮ�������������������ʱ��)
