--/////////////////////
--/*  �㶫ʡ�̲����� */
--/*     տ������    */
--/////////////////////

--��ӵ��ӹ�Ա
insert into pubdumtlr values('441999','TBC','','EYYTBI1');


--delete from pubaplbus where brno='441999' and  APLCLS='438' and bustyp='TBCA1';
insert into pubaplbus values('441999','438','','TBCA1','�㶫�̲ݹ�˾');
--��λ������ձ�(Ӧ���롢Ӧ�����롢ҵ�����͡�ҵ����������)

--delete from pubaplmng where brno='441999' and  APLCLS='438' and bustyp='TCBA1';
insert into pubaplmng values('441999','438','TBCA1','','9999999999');
insert into pubaplmng values('441999','438','CRP51','01','9999999999');
--Ӧ�ù����(Ӧ���롢ҵ�����͡�ҵ�����롢��λ����)

--delete from pubjnldef where brno='441999' and bustyp='TCBA1';
insert into pubjnldef values('441999','TBCA1','9999999999','afetxnjnl','afetxnjnl','1','1');
--pubjnldefҵ����ˮ��������(ҵ�����͡���������ˮ������������ˮ�������������������ʱ��)

--����̲ݻ�����Ϣ��
insert into tbcbasinf values('441999','2090','տ���й�˾',' ',' ','20111114','2090','0');
