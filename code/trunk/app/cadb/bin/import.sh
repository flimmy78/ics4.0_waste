#说明:需要导入以下两个表备份的最新数据
db2 connect to db2front
db2 "import from cadcode.out of DEL insert into icsadm.caditmcod"
db2 "import from cadnodinf.out of DEL insert into icsadm.cadnodinf"
