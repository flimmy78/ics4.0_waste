db2 connect to db2front;
db2 "select distinct BrNo from puborginf" |grep 999 > BrLst
for i in `cat BrLst`
  do
    echo "����ά�����С�$i������.............................."
    for j in `ls *sql |grep -v pubdumtlr|grep -v pubftpcfg`
      do
       echo "����ά�����С�$i����$j������..................."
       sed -e "s/XXXXXX/$i/g" $j > $j.$i
       db2 -tvf $j.$i
       rm -f $j.$i
      done
    echo "���С�$i������ά����ϣ�����!!!!!!!!!!!!!!!!!!!!!!"
  done
rm -f BrLst
echo "�ύҵ������......................"
#db2 -tvf init_pubdumtlr_pft.sql
#db2 -tvf init_pubftpcfg_pft.sql
