#说明:需要导入以下两个表备份的最新数据
db2 connect to db2front
db2 "export to cadcode.out of DEL select * from icsadm.caditmcod"
db2 "export to cadnodinf.out of DEL select * from icsadm.cadnodinf"
