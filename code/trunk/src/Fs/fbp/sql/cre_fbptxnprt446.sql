drop table fbptxnprt446;

create table fbptxnprt446 	
--�������۷ѻ�ִ��ӡ���Ʊ�
(
  BBusTyp char(3),
--��������
	ActDat char(8),		
--��������
	ActNo  char(21),
--�����˺�
	HLogNo	 char(9),  
--����������ˮ��
	prtcnt	int			  
--��ӡ����
);
create  unique index  ui1_fbptxnprt446 on fbptxnprt446(ActDat,HLogNo);
