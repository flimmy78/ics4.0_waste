drop table prtspenod446;

--�ʻ����϶��ձ�
create table prtspenod446
(
	ActNo		char(30) not null,
--�ʺ�
	ActNam	char(60)	default '',
--����
	OpenBr	char(30) default '',
--������
	OpBrNo	char(10) default ''
--�����к�
);

create index ni1_prtspenod446 on prtspenod446(ActNo);
