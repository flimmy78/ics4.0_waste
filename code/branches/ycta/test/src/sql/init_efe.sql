--��ӵ��ӹ�Ա
insert into pubdumtlr values('441999','EFE','','EPCLBI1');



--delete from pubaplbus where brno='441999' and  APLCLS='202' and bustyp='EFEA1';
insert into pubaplbus values('441999','202','','EFEA1','�㶫�������շ�');
--��λ������ձ�(Ӧ���롢Ӧ�����롢ҵ�����͡�ҵ����������)

--delete from pubaplmng where brno='441999' and  APLCLS='202' and bustyp='EFEA1';
insert into pubaplmng values('441999','202','EFEA1','','9999999999');
insert into pubaplmng values('441999','202','CRP51','01','9999999999');
--Ӧ�ù����(Ӧ���롢ҵ�����͡�ҵ�����롢��λ����)

--delete from pubjnldef where brno='441999' and bustyp='EFEA1';
insert into pubjnldef values('441999','EFEA1','9999999999','afetxnjnl','afetxnjnl','1','1');
--pubjnldefҵ����ˮ��������(ҵ�����͡���������ˮ������������ˮ�������������������ʱ��)

--�����������
db2 "insert into efeaclrtbl values('441999', '4410000971','YYYYMMDD','1800','0','0')"
db2 "insert into efeaclrtbl values('441999', '4410000958','YYYYMMDD','1800','0','0')"
db2 "insert into efeaclrtbl values('441999', '4410000960','YYYYMMDD','1800','0','0')"
