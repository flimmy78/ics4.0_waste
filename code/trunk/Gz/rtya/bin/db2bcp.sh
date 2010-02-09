#######################################################################
###  通用db2数据导入导出命令                                          #
###  说明:导入导出文件以":"为分隔符                                   #
###  参数说明
###  参数1: in 	--数据导入
###         out --数据导出
###  参数2: 文件名
###  参数3: 表名
###  例子:  db2bcp in 文件名 表名
###  author:xuan
#######################################################################

db2 connect to db2front

if [ $1 = "out" ]
then
			db2 "export to $2 of del modified by coldel: select * from $3"
fi

if [ $1 = "in" ]
then
			db2 "import from $2 of del modified by coldel: replace into $3"
fi

db2 disconnect db2front
