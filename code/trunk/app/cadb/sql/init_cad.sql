--������Ӧ��ҵ�����Ͷ��ձ�-pubaplbus����Ӽ�¼
insert into pubaplbus values('238','001','CAD51','�麣��������ҵ�շ��ֽ��շ�');
insert into pubaplbus values('238','002','CAD53','�麣��������ҵ�շ��ֽ��ת');
--������Ӧ��ҵ������-pubaplmng����Ӽ�¼
insert into pubaplmng values('238','CAD51',' ','9999999999');
insert into pubaplmng values('238','CAD53',' ','9999999999');
--������ҵ����ˮ������������Ӽ�¼
insert into pubjnldef values('CAD51','9999999999','cadtxnjnl',' ','0','0');
insert into pubjnldef values('CAD53','9999999999','cadtxnjnl',' ','0','0');

--TActNo 	�ֽ��ڲ��ʺŵ�˳���
--TActNo2 	�麣������������ʺ�
--TActNo3 	��ɽ�ƾ��ʺ�
insert into pubcrpagt values('CAD51','9999999999','','','90006','','','','','','','0','0','','29991231','0','0');
insert into pubcrpagt values('CAD53','9999999999','','','90006','','','444000097012015006636','444000091018000440821','','','0','0','','29991231','0','0');


insert into cimaplinf values('46','38','01','�麣��������ҵ�շ�');
insert into cimtxncls values('46','38','01','�麣������ҵ�շ�֧�й��ý���');
insert into cimtxncls values('46','38','02','�麣������ҵ�շ������н���');

insert into cimclsdef values('46','38','01','463801');
insert into cimclsdef values('46','38','01','463802');
insert into cimclsdef values('46','38','01','463809');
insert into cimclsdef values('46','38','01','463819');
insert into cimclsdef values('46','38','01','463804');
insert into cimclsdef values('46','38','01','463805');
insert into cimclsdef values('46','38','01','463808');
insert into cimclsdef values('46','38','01','463829');
insert into cimclsdef values('46','38','02','463806');
insert into cimclsdef values('46','38','02','463807');
insert into cimclsdef values('46','38','02','463810');
insert into cimclsdef values('46','38','02','463812');
insert into cimclsdef values('46','38','02','463813');
insert into cimclsdef values('46','38','01','463814');
insert into cimclsdef values('46','38','02','463815');
insert into cimclsdef values('46','38','02','463816');
insert into cimtxnpur values('463801','�ֽ�ɷѼ���','46','38','01','1','1');
insert into cimtxnpur values('463802','ת�˽ɿ�ƾ֤��ӡ','46','38','01','1','1');
insert into cimtxnpur values('463809','�ֽ�ɿ�Ĩ��','46','38','01','1','1');
insert into cimtxnpur values('463819','ת�˽ɷ�Ĩ��','46','38','01','1','1');
insert into cimtxnpur values('463804','���˽���','46','38','01','1','1');
insert into cimtxnpur values('463805','������ˮ��ѯ','46','38','01','1','1');
insert into cimtxnpur values('463808','�շ���Ŀ�����ѯ','46','38','01','1','1');
insert into cimtxnpur values('463829','�ֽ�ɿ��תĨ��','46','38','01','1','1');
insert into cimtxnpur values('463806','�շ���Ŀ��������','46','38','01','1','1');
insert into cimtxnpur values('463807','�շ���Ŀ�����޸�','46','38','01','1','1');
insert into cimtxnpur values('463810','�շ���Ŀ����ɾ��','46','38','01','1','1');
insert into cimtxnpur values('463812','��ȡ��������','46','38','01','1','1');
insert into cimtxnpur values('463813','��ӡȫ�л������˵�','46','38','01','1','1');
insert into cimtxnpur values('463814','�ֽ�ɿ��ת','46','38','01','1','1');
insert into cimtxnpur values('463815','����ͳ�ƴ�ӡ����','46','38','01','1','1');
insert into cimtxnpur values('463816','�����ֽ�ɿ��ת�����ѯ','46','38','01','1','1');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463801','�ֽ�ɷѼ���','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463802','ת�˽ɿ�ƾ֤��ӡ','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463809','�ֽ�ɿ�Ĩ��','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463819','ת�˽ɷ�Ĩ��','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463804','���˽���','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463805','������ˮ��ѯ','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463808','�շ���Ŀ�����ѯ','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463829','�ֽ�ɿ��תĨ��','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463806','�շ���Ŀ��������','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463807','�շ���Ŀ�����޸�','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463810','�շ���Ŀ����ɾ��','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463812','��ȡ��������','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463813','��ӡȫ�л������˵�','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463814','�ֽ�ɿ��ת','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463815','����ͳ�ƴ�ӡ����','');
insert into mngaplinf values('cad', '�麣��������ҵ�շ�', 'TRM', '��̨�ն�','CTRMCAD1','������ҵ�շѹ�̨ͨѶ����','463816','�����ֽ�ɿ��ת�����ѯ','');
