drop table comtxnprt446;

create table comtxnprt446 	
--ͨѶ�ѻ�ִ��ӡ���Ʊ�
(
	ActDat char(8),		
--��������
	ActNo  char(21),
--�����˺�
	TckNo	 char(11),  
--������ˮ��
	prtcnt	int			  
--��ӡ����
);
create  unique index  ui1_comtxnprt446 on comtxnprt446(ActDat,TckNo);
