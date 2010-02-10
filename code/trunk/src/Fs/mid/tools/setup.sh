db2 connect to db2front
db2 -tvf cre_arecoddat446.sql
db2 -tvf init_arecoddat446.sql
db2 "delete from arecoddat446"
db2 "import from arecoddat446.txt of del insert into icsadm.arecoddat446"
