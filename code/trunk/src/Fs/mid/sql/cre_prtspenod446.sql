drop table prtspenod446;

--帐户资料对照表
create table prtspenod446
(
	ActNo		char(30) not null,
--帐号
	ActNam	char(60)	default '',
--户名
	OpenBr	char(30) default '',
--开户行
	OpBrNo	char(10) default ''
--开户行号
);

create index ni1_prtspenod446 on prtspenod446(ActNo);
