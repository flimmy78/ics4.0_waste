drop table arecoddat446;

--��������ģ����ѯ���ݱ�
create table    arecoddat446
(
   AreaNam        char(40)     not null,
--��������
   AreaCod      char(4)     not null
--��������
);
create index ni1_arecoddat446 on arecoddat446(AreaNam);
