#######################################################################
###  ͨ��db2���ݵ��뵼������                                          #
###  ˵��:���뵼���ļ���":"Ϊ�ָ���                                   #
###  ����˵��
###  ����1: in 	--���ݵ���
###         out --���ݵ���
###  ����2: �ļ���
###  ����3: ����
###  ����:  db2bcp in �ļ��� ����
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
