db2 connect to db2front;
for i in `cat BrLst`
  do
    echo "����ά�����С�$i������.............................."
    for j in `ls *sql |grep -v pubdumtlr`
      do
       echo "����ά�����С�$i����$j������..................."
       sed -e "s/XXXXXX/$i/g" $j > $j.$i
       db2 -tvf $j.$i
       rm -f $j.$i
      done
    echo "���С�$i������ά����ϣ�����!!!!!!!!!!!!!!!!!!!!!!"
  done
